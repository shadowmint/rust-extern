# rust-extern

Example of an external static rust library called from C.

## Build

    cargo build -v
    cc -c test.c
    cc -o test test.o target/libextern.a -l[FLAGS]

The BUILD is dependent on your local build.

The FLAGS will be listed when you run cargo build -v. For example, on OSX these are:

     Running `rustc src/test.rs --crate-name extern --crate-type dylib --crate-type staticlib -C metadata=bf68444529321665 -C extra-filename=-bf68444529321665 --out-dir /Users/doug/dev/rust-extern/target -L /Users/doug/dev/rust-extern/target -L /Users/doug/dev/rust-extern/target/deps`
        Compiling externtest v0.1.0 (file:/Users/doug/dev/rust-extern)
        warning: link against the following native artifacts when linking against this static library
        note: the order and any duplication can be significant on some platforms, and so may need to be preserved
        note: library: System
        note: library: pthread
        note: library: c
        note: library: m

So you would run:

    cc -o test test.o target/debug/libextern.a -lSystem -lpthread -lc -lm

On an linux machine it might be:

    cc -o test test.o target/debug/libextern.a -ldl -lpthread -lgcc_s -lc -m

You can also dynamically link:

    cc -o test test.o target/debug/extern.dylib

However, notice that otool -L will list all the dependencies that dylib invokes.

### Manually parse cargo output on each platform?

Isn't that really irritating to do?

Yes.

There are various solutions to parsing the output of cargo and pumping that
into your build tool; included is a sample cmake (www.cmake.org) file to
perform this task automatically.

Notice that this step automatically invokes cargo to build the rust library.

Usage:

    mkdir build
    cd build
    cmake ..
    make

Output:

    doug@wrang:rust-extern doug$ cmake ..
    RUST LIBS: /home/doug/dev/rust-extern/target/libextern.a
    RUST DEPS: dl;pthread;gcc_s;pthread;c;m
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /home/doug/dev/rust-extern/build

    doug@wrang:rust-extern doug$ make
    Linking C executable test
    [100%] Built target test

Note that the cmake script to parse this is literally parsing the raw string output
from cargo. In theory cargo will (eventually) provide some kind of low level support
for this.

#### Building on windows?

Um. Well, it does actually work, but you must use MSYS and GCC not
visual studio. Here's a very quick getting started guide:

- Install Rust: http://www.rust-lang.org/install.html

- Install MSYS: http://www.mingw.org/wiki/msys

- Use the cmake "MSYS Makefiles" generator to build:

Notice that you must use both the same version of rust and MSYS; ie. either
32-bit or 64-bit for both. Notice that the default download for MSYS is 32-bit
and the default for rust is 64-bit; ie. the default downloads for both are not
compatible.

From the MSYS shell:

    cd build
    cmake .. -G "MSYS Makefiles" (or use cmake-gui)
    make
    ./test.exe

### Output of test

    doug@wrang:rust-extern doug$ ./test
    Trigger called
    Nope
    Trigger called
    Invoking callback
    No callback bound
    Register called
    Trigger called
    Nope
    Trigger called
    Invoking callback
    C-callback invoked with value: 100

## C Fixture

To ensure the C library compile step is working, a basic C implementation of
libextern is provided in the `c` folder.

To build:

    mkdir build_c
    cd build_c
    cmake ..
    make
    make install

For windows use 'cmake .. -G "MSYS Makefiles"'.

Make sure to run make install to generate the correct version of the dynamic
library.

You can now modify the CMakeList.txt file to use the c version of the code.
