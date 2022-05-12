/**
 * read or write a batch with 2 dicts
 */

#include <arrow/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <fstream>
#include <iostream>
#include <string.h>

// create an arrow table with tow dict fields std::unique_ptr < arrow::RecordBatchBuilder>
// builder;
arrow::Result<std::shared_ptr<arrow::RecordBatch>> BuildBatch() {
  std::vector<std::shared_ptr<::arrow::Field>> fields;
  fields.push_back(::arrow::field("as", ::arrow::dictionary(arrow::int8(), arrow::utf8())));
  fields.push_back(::arrow::field("bs", ::arrow::dictionary(arrow::int8(), arrow::utf8())));
  std::shared_ptr<::arrow::Schema> schema = ::arrow::schema(fields);
  std::unique_ptr<arrow::RecordBatchBuilder> builder;
  arrow::RecordBatchBuilder::Make(schema, arrow::default_memory_pool(), &builder);

  for (auto a : {"a1", "a2"})
    builder->GetFieldAs<::arrow::StringDictionaryBuilder>(0)->Append(a);
  for (auto a : {"b1", "b2"})
    builder->GetFieldAs<::arrow::StringDictionaryBuilder>(1)->Append(a);
  std::shared_ptr<arrow::RecordBatch> batch;
  ARROW_RETURN_NOT_OK(builder->Flush(&batch));
  return batch;
}

arrow::Result<std::shared_ptr<arrow::Buffer>> SerializeBatch(const arrow::RecordBatch &batch) {
  std::shared_ptr<arrow::ipc::RecordBatchWriter> writer;
  ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::ResizableBuffer> buffer,
                        arrow::AllocateResizableBuffer(1024));
  std::shared_ptr<arrow::io::OutputStream> sink =
      std::make_shared<arrow::io::BufferOutputStream>(buffer);
  ARROW_ASSIGN_OR_RAISE(writer, arrow::ipc::MakeStreamWriter(sink, batch.schema()));
  RETURN_NOT_OK(writer->WriteRecordBatch(batch));
  RETURN_NOT_OK(writer->Close());
  RETURN_NOT_OK(sink->Close());
  return buffer;
}

arrow::Result<std::shared_ptr<arrow::RecordBatch>> ReadBatch(
    const std::shared_ptr<arrow::Buffer> &buffer) {
  auto buf_reader = std::make_shared<arrow::io::BufferReader>(buffer);
  std::shared_ptr<arrow::RecordBatchReader> reader;
  ARROW_ASSIGN_OR_RAISE(reader, arrow::ipc::RecordBatchStreamReader::Open(buf_reader));
  return reader->Next();
}

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "usage: sometest <read|write> <file>" << std::endl;
    exit(0);
  }

  auto batch = *BuildBatch();

  if (strcmp(argv[1], "write") == 0) {
    std::cerr << "Serializing:" << std::endl;
    std::cerr << batch->schema()->ToString() << std::endl;
    std::cerr << batch->ToString() << std::endl;
    auto buffer = *SerializeBatch(*batch);
    std::ofstream ofs(argv[2], std::ios::binary);
    ofs.write(reinterpret_cast<const char *>(buffer->data()), buffer->size());
  }

  if (strcmp(argv[1], "read") == 0) {
    std::ifstream ifs(argv[2], std::ios::binary);
    size_t sz                             = ifs.seekg(0, std::ios_base::end).tellg();
    std::shared_ptr<arrow::Buffer> buffer = *arrow::AllocateBuffer(sz);
    ifs.seekg(0);
    ifs.read(reinterpret_cast<char *>(buffer->mutable_data()), sz);
    std::shared_ptr<arrow::RecordBatch> batch_in;
    batch_in = *ReadBatch(buffer);
    std::cerr << "Recovered:" << std::endl;
    std::cerr << batch_in->schema()->ToString() << std::endl;
    std::cerr << batch_in->ToString() << std::endl;
    if (!batch_in->Equals(*batch))
      throw std::runtime_error("Batches not identical");
  }

  return 0;
}
