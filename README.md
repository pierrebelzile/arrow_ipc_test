# arrow_ipc_test
interoperability testing between Rust and C++

Both files generate the same Arrow recordbatch. This batch has 2 columns, 
both dicts of string with int8 indices. Then both programs serialize this batch
using the Arrow IPC format.

The C++ program also supports reading the file. It is not able to recover the
file serialized by Rust.

# Building C++
1. Checkout recursively to instantiate the vcpkg submodule
2. Ensure that you have a c++ in context (which g++)
3. ./vcpkg/bootstrap-vcpkg.sh
4. cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
5. make -C build
6. ./build/rw read ./rust_out.bin

# C++ generation.
Ran with: a.out write out.bin.
Diplays:
<pre>
Serializing:
as: dictionary<values=string, indices=int8, ordered=0>
bs: dictionary<values=string, indices=int8, ordered=0>
as: 
  -- dictionary:
    [
      "a1",
      "a2"
    ]
  -- indices:
    [
      0,
      1
    ]
bs: 
  -- dictionary:
    [
      "b1",
      "b2"
    ]
  -- indices:
    [
      0,
      1
    ]
</pre>

The file out.bin has 856 bytes and the following content:
<pre>
$ hexdump -C out.bin
00000000  ff ff ff ff e0 00 00 00  14 00 00 00 00 00 00 00  |................|
00000010  00 00 0a 00 0c 00 06 00  05 00 08 00 0a 00 00 00  |................|
00000020  00 01 04 00 04 00 00 00  6c ff ff ff 04 00 00 00  |........l.......|
00000030  02 00 00 00 64 00 00 00  04 00 00 00 b4 ff ff ff  |....d...........|
00000040  00 00 01 05 14 00 00 00  3c 00 00 00 1c 00 00 00  |........<.......|
00000050  04 00 00 00 00 00 00 00  02 00 00 00 62 73 00 00  |............bs..|
00000060  08 00 10 00 08 00 04 00  08 00 00 00 0c 00 00 00  |................|
00000070  01 00 00 00 00 00 00 00  ac ff ff ff 00 00 00 01  |................|
00000080  08 00 00 00 a4 ff ff ff  10 00 18 00 08 00 06 00  |................|
00000090  07 00 0c 00 10 00 14 00  10 00 00 00 00 00 01 05  |................|
000000a0  14 00 00 00 40 00 00 00  1c 00 00 00 04 00 00 00  |....@...........|
000000b0  00 00 00 00 02 00 00 00  61 73 00 00 08 00 08 00  |........as......|
000000c0  00 00 04 00 08 00 00 00  0c 00 00 00 08 00 0c 00  |................|
000000d0  08 00 07 00 08 00 00 00  00 00 00 01 08 00 00 00  |................|
000000e0  04 00 04 00 04 00 00 00  ff ff ff ff a8 00 00 00  |................|
000000f0  14 00 00 00 00 00 00 00  0c 00 14 00 06 00 05 00  |................|
00000100  08 00 0c 00 0c 00 00 00  00 02 04 00 14 00 00 00  |................|
00000110  18 00 00 00 00 00 00 00  08 00 0a 00 00 00 04 00  |................|
00000120  08 00 00 00 10 00 00 00  00 00 0a 00 18 00 0c 00  |................|
00000130  04 00 08 00 0a 00 00 00  4c 00 00 00 10 00 00 00  |........L.......|
00000140  02 00 00 00 00 00 00 00  00 00 00 00 03 00 00 00  |................|
00000150  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000160  00 00 00 00 00 00 00 00  0c 00 00 00 00 00 00 00  |................|
00000170  10 00 00 00 00 00 00 00  04 00 00 00 00 00 00 00  |................|
00000180  00 00 00 00 01 00 00 00  02 00 00 00 00 00 00 00  |................|
00000190  00 00 00 00 00 00 00 00  00 00 00 00 02 00 00 00  |................|
000001a0  04 00 00 00 00 00 00 00  61 31 61 32 00 00 00 00  |........a1a2....|
000001b0  ff ff ff ff b0 00 00 00  14 00 00 00 00 00 00 00  |................|
000001c0  0c 00 14 00 06 00 05 00  08 00 0c 00 0c 00 00 00  |................|
000001d0  00 02 04 00 14 00 00 00  18 00 00 00 00 00 00 00  |................|
000001e0  08 00 12 00 08 00 04 00  08 00 00 00 18 00 00 00  |................|
000001f0  01 00 00 00 00 00 00 00  00 00 0a 00 18 00 0c 00  |................|
00000200  04 00 08 00 0a 00 00 00  4c 00 00 00 10 00 00 00  |........L.......|
00000210  02 00 00 00 00 00 00 00  00 00 00 00 03 00 00 00  |................|
00000220  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000230  00 00 00 00 00 00 00 00  0c 00 00 00 00 00 00 00  |................|
00000240  10 00 00 00 00 00 00 00  04 00 00 00 00 00 00 00  |................|
00000250  00 00 00 00 01 00 00 00  02 00 00 00 00 00 00 00  |................|
00000260  00 00 00 00 00 00 00 00  00 00 00 00 02 00 00 00  |................|
00000270  04 00 00 00 00 00 00 00  62 31 62 32 00 00 00 00  |........b1b2....|
00000280  ff ff ff ff b8 00 00 00  14 00 00 00 00 00 00 00  |................|
00000290  0c 00 16 00 06 00 05 00  08 00 0c 00 0c 00 00 00  |................|
000002a0  00 03 04 00 18 00 00 00  10 00 00 00 00 00 00 00  |................|
000002b0  00 00 0a 00 18 00 0c 00  04 00 08 00 0a 00 00 00  |................|
000002c0  5c 00 00 00 10 00 00 00  02 00 00 00 00 00 00 00  |\...............|
000002d0  00 00 00 00 04 00 00 00  00 00 00 00 00 00 00 00  |................|
000002e0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000002f0  02 00 00 00 00 00 00 00  08 00 00 00 00 00 00 00  |................|
00000300  00 00 00 00 00 00 00 00  08 00 00 00 00 00 00 00  |................|
00000310  02 00 00 00 00 00 00 00  00 00 00 00 02 00 00 00  |................|
00000320  02 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000340  00 01 00 00 00 00 00 00  00 01 00 00 00 00 00 00  |................|
00000350  ff ff ff ff 00 00 00 00                           |........|
00000358
</pre>

# Rust Generation
Running the equivalent Rust version generates:
<pre>
$ ../target/debug/test
RecordBatch { schema: Schema { fields: [Field { name: "as", data_type: Dictionary(Int8, Utf8), nullable: true, dict_id: 0, dict_is_ordered: false, metadata: None }, Field { name: "bs", data_type: Dictionary(Int8, Utf8), nullable: true, dict_id: 0, dict_is_ordered: false, metadata: None }], metadata: {} }, columns: [DictionaryArray {keys: PrimitiveArray<Int8>
[
  0,
  1,
] values: StringArray
[
  "a1",
  "a2",
]}
, DictionaryArray {keys: PrimitiveArray<Int8>
[
  0,
  1,
] values: StringArray
[
  "b1",
  "b2",
]}
], row_count: 2 }
</pre>

The output file out.bin also has 856 bytes but they are different:
<pre>
$ hexdump -C out.bin
00000000  ff ff ff ff e0 00 00 00  10 00 00 00 00 00 0a 00  |................|
00000010  0e 00 0c 00 0b 00 04 00  0a 00 00 00 14 00 00 00  |................|
00000020  00 00 00 01 04 00 0a 00  0c 00 00 00 08 00 04 00  |................|
00000030  0a 00 00 00 08 00 00 00  08 00 00 00 00 00 00 00  |................|
00000040  02 00 00 00 54 00 00 00  04 00 00 00 c4 ff ff ff  |....T...........|
00000050  2c 00 00 00 24 00 00 00  00 00 01 05 08 00 00 00  |,...$...........|
00000060  20 00 00 00 b4 ff ff ff  04 00 00 00 ac ff ff ff  | ...............|
00000070  08 00 00 00 00 00 00 01  00 00 00 00 a4 ff ff ff  |................|
00000080  02 00 00 00 62 73 00 00  10 00 18 00 14 00 0e 00  |....bs..........|
00000090  0f 00 04 00 10 00 08 00  10 00 00 00 40 00 00 00  |............@...|
000000a0  34 00 00 00 00 00 01 05  10 00 00 00 34 00 00 00  |4...........4...|
000000b0  08 00 08 00 00 00 04 00  08 00 00 00 0c 00 00 00  |................|
000000c0  08 00 0c 00 04 00 0b 00  08 00 00 00 08 00 00 00  |................|
000000d0  00 00 00 01 00 00 00 00  04 00 04 00 04 00 00 00  |................|
000000e0  02 00 00 00 61 73 00 00  ff ff ff ff a0 00 00 00  |....as..........|
000000f0  10 00 00 00 0c 00 18 00  16 00 15 00 04 00 08 00  |................|
00000100  0c 00 00 00 1c 00 00 00  20 00 00 00 00 00 00 00  |........ .......|
00000110  00 00 00 00 00 02 04 00  08 00 0a 00 00 00 04 00  |................|
00000120  08 00 00 00 10 00 00 00  00 00 0a 00 14 00 0c 00  |................|
00000130  08 00 04 00 0a 00 00 00  24 00 00 00 0c 00 00 00  |........$.......|
00000140  02 00 00 00 00 00 00 00  01 00 00 00 02 00 00 00  |................|
00000150  00 00 00 00 00 00 00 00  00 00 00 00 03 00 00 00  |................|
00000160  00 00 00 00 00 00 00 00  08 00 00 00 00 00 00 00  |................|
00000170  08 00 00 00 00 00 00 00  10 00 00 00 00 00 00 00  |................|
00000180  18 00 00 00 00 00 00 00  08 00 00 00 00 00 00 00  |................|
00000190  03 00 00 00 00 00 00 00  00 00 00 00 02 00 00 00  |................|
000001a0  04 00 00 00 00 00 00 00  61 31 61 32 00 00 00 00  |........a1a2....|
000001b0  ff ff ff ff a0 00 00 00  10 00 00 00 0c 00 18 00  |................|
000001c0  16 00 15 00 04 00 08 00  0c 00 00 00 1c 00 00 00  |................|
000001d0  20 00 00 00 00 00 00 00  00 00 00 00 00 02 04 00  | ...............|
000001e0  08 00 0a 00 00 00 04 00  08 00 00 00 10 00 00 00  |................|
000001f0  00 00 0a 00 14 00 0c 00  08 00 04 00 0a 00 00 00  |................|
00000200  24 00 00 00 0c 00 00 00  02 00 00 00 00 00 00 00  |$...............|
00000210  01 00 00 00 02 00 00 00  00 00 00 00 00 00 00 00  |................|
00000220  00 00 00 00 03 00 00 00  00 00 00 00 00 00 00 00  |................|
00000230  08 00 00 00 00 00 00 00  08 00 00 00 00 00 00 00  |................|
00000240  10 00 00 00 00 00 00 00  18 00 00 00 00 00 00 00  |................|
00000250  08 00 00 00 00 00 00 00  03 00 00 00 00 00 00 00  |................|
00000260  00 00 00 00 02 00 00 00  04 00 00 00 00 00 00 00  |................|
00000270  62 31 62 32 00 00 00 00  ff ff ff ff b0 00 00 00  |b1b2............|
00000280  10 00 00 00 0c 00 1a 00  18 00 17 00 04 00 08 00  |................|
00000290  0c 00 00 00 20 00 00 00  20 00 00 00 00 00 00 00  |.... ... .......|
000002a0  00 00 00 00 00 00 00 03  04 00 0a 00 14 00 0c 00  |................|
000002b0  08 00 04 00 0a 00 00 00  34 00 00 00 0c 00 00 00  |........4.......|
000002c0  02 00 00 00 00 00 00 00  02 00 00 00 02 00 00 00  |................|
000002d0  00 00 00 00 00 00 00 00  00 00 00 00 02 00 00 00  |................|
000002e0  00 00 00 00 00 00 00 00  00 00 00 00 04 00 00 00  |................|
000002f0  00 00 00 00 00 00 00 00  08 00 00 00 00 00 00 00  |................|
00000300  08 00 00 00 00 00 00 00  08 00 00 00 00 00 00 00  |................|
00000310  10 00 00 00 00 00 00 00  08 00 00 00 00 00 00 00  |................|
00000320  18 00 00 00 00 00 00 00  08 00 00 00 00 00 00 00  |................|
00000330  ff 00 00 00 00 00 00 00  00 01 00 00 00 00 00 00  |................|
*
00000350  ff ff ff ff 00 00 00 00                           |........|
00000358
</pre>

# Reading Rust output in C++
Atempting to read in C++ confuses the two dictionaries:
<pre>
$ a.out read /apps/home/belzilep/dse/services/service-record2/collector/out.bin
Recovered:
as: dictionary<values=string, indices=int8, ordered=0>
bs: dictionary<values=string, indices=int8, ordered=0>
as: 
  -- dictionary:
    [
      "b1",
      "b2"
    ]
  -- indices:
    [
      0,
      1
    ]
bs: 
  -- dictionary:
    [
      "b1",
      "b2"
    ]
  -- indices:
    [
      0,
      1
    ]

terminate called after throwing an instance of 'std::runtime_error'
  what():  Batches not identical
</pre>
