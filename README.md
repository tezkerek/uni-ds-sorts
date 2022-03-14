### Build

    $ mkdir debug/
    $ cmake -B debug/
    $ cmake --build debug/

### Run

Generate tests:

    $ mkdir tests/
    $ ./debug/generate tests/

Benchmark sorting algorithms:

    $ ./debug/sorts tests/
