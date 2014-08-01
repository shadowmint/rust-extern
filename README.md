# rust-extern

Example of an external static rust library called from C.

## Build

    cargo build -v
    cc -c test.c
    cc -o test test.o lib/libexterntest-[BUILD].a -l[FLAGS]

The BUILD is dependent on your local build.

The FLAGS will be listed when you run cargo build -v. For example, on OSX these are:

    cc -o test test.o target/libexterntest-bf68444529321665.a -lSystem -lpthread -lc -lm

You can also dynamically link:

    cc -o test test.o target/libexterntest-bf68444529321665.dylib

However, notice that otool -L will list all the dependencies that dylib invokes.
