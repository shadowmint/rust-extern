# rust-extern

Example of an external static rust library called from C.

## Build

    cargo build -v
    cc -c test.c
    cc -o test test.o lib/libexterntest-[BUILD].a -l[FLAGS]

The BUILD is dependent on your local build.

The FLAGS will be listed when you run cargo build -v. For example, on OSX these are:

     Running `rustc src/test.rs --crate-name externtest --crate-type dylib --crate-type staticlib -C metadata=bf68444529321665 -C extra-filename=-bf68444529321665 --out-dir /Users/doug/dev/rust-extern/target -L /Users/doug/dev/rust-extern/target -L /Users/doug/dev/rust-extern/target/deps`
        Compiling externtest v0.1.0 (file:/Users/doug/dev/rust-extern)
        warning: link against the following native artifacts when linking against this static library
        note: the order and any duplication can be significant on some platforms, and so may need to be preserved
        note: library: System
        note: library: pthread
        note: library: c
        note: library: m

So you would run:

    cc -o test test.o target/libexterntest-bf68444529321665.a -lSystem -lpthread -lc -lm

You can also dynamically link:

    cc -o test test.o target/libexterntest-bf68444529321665.dylib

However, notice that otool -L will list all the dependencies that dylib invokes.

### Output

    doug-2:rust-extern doug$ ./test
    110

woo... :P
