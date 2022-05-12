use arrow::array::*;
use arrow::datatypes::*;
use arrow::record_batch::RecordBatch;
use std::boxed::Box;
use std::io::Write;
use std::sync::Arc;

fn build_batch() -> arrow::error::Result<RecordBatch> {
    let mut fields = Vec::with_capacity(2);
    let mut arrays: Vec<ArrayRef> = Vec::with_capacity(2);

    {
        let key_builder = PrimitiveBuilder::<Int8Type>::new(2);
        let value_builder = StringBuilder::new(2);
        let mut builder = StringDictionaryBuilder::new(key_builder, value_builder);
        for v in &["a1", "a2"] {
            builder.append(v)?;
        }
        let array = builder.finish();
        fields.push(Field::new("as", array.data_type().clone(), true));
        arrays.push(Arc::new(array));
    }

    {
        let key_builder = PrimitiveBuilder::<Int8Type>::new(2);
        let value_builder = StringBuilder::new(2);
        let mut builder = StringDictionaryBuilder::new(key_builder, value_builder);
        for v in &["b1", "b2"] {
            builder.append(v)?;
        }
        let array = builder.finish();
        fields.push(Field::new("bs", array.data_type().clone(), true));
        arrays.push(Arc::new(array));
    }

    let schema = std::sync::Arc::new(Schema::new(fields));
    let batch = RecordBatch::try_new(schema, arrays)?;
    Ok(batch)
}

fn main() -> std::result::Result<(), Box<dyn std::error::Error>> {
    let batch = build_batch()?;
    println!("{:?}", batch);
    let mut writer =
        arrow::ipc::writer::StreamWriter::try_new(Vec::with_capacity(1024), &batch.schema())?;
    writer.write(&batch)?;
    writer.finish()?;
    let bytes = writer.into_inner()?;

    // write those bytes to a file
    let mut file = std::fs::File::create("out.bin")?;
    file.write_all(&bytes)?;
    Ok(())
}
