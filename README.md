### Build

Build in release mode for optimizations:

    $ mkdir release/
    $ cmake -B release/ -DCMAKE_BUILD_TYPE="Release"
    $ cmake --build release/

### Run

Generate tests:

    $ mkdir tests/
    $ ./release/generate tests/

Benchmark sorting algorithms:

    $ ./release/sorts tests/
