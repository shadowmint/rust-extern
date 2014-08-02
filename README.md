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

On an linux machine it might be:

    cc -o test test.o libexterntest-47c19edaec6ef908.a -ldl -lpthread -lgcc_s -lc -m

You can also dynamically link:

    cc -o test test.o target/libexterntest-bf68444529321665.dylib

However, notice that otool -L will list all the dependencies that dylib invokes.

### Manually parse cargo output on each platform? 

Isn't that really irritating to do?

Yes.

There are various solutions to parsing the output of cargo and pumping that
into your build tool; included is a sample cmake (www.cmake.org) file to 
perform this task automatically.

Usage:

    mkdir build
    cd build
    cmake ..
    make

Output:

    doug@wrang:rust-extern doug$ cmake ..
    RUST LIBS: /home/doug/dev/rust-extern/target/libexterntest-47c19edaec6ef908.a
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

- Install Rust nightly snapshot: http://www.rust-lang.org/install.html

- Install MSYS: http://www.gaia-gis.it/spatialite-3.0.0-BETA/mingw64_how_to.html

- Download the cargo nightly: https://github.com/rust-lang/cargo#installing-cargo-from-nightlies

- Install cargo from the terminal using install.sh

- Use the cmake "MSYS Makefiles" generator:


    cmake .. -G "MSYS Makefiles" 
    (or use cmake-gui)


- Now you can proceed as normal:


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

woo... :P
