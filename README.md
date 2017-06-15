# miko's project
[![Build Status](https://travis-ci.org/sinomiko/project.svg?branch=master)](https://travis-ci.org/sinomiko/project)
[![Coverage Status](https://coveralls.io/repos/github/sinomiko/project/badge.svg?branch=master)](https://coveralls.io/github/sinomiko/project?branch=master)
[![License](https://img.shields.io/badge/license-%20BSD--3-blue.svg)](../master/LICENSE)


# Demo

C/C++ unit test demo using [Google Test](https://code.google.com/p/googletest) deployed to
[Travis-CI](https://travis-ci.org/sinomiko/project/builds) with test coverage
deployed to [Coveralls](https://coveralls.io/github/sinomiko/project).

- [Build and test history](https://travis-ci.org/sinomiko/project/builds)
- [Code coverage](https://coveralls.io/github/sinomiko/project)
- Licensed under [BSD-3](../master/LICENSE)

## c plus plus code

### How to use scons build hello

```sh
git clone --recursive https://github.com/sinomiko/project.git

cd cpp_project/hello 

scons

./hello

```

### How to use google test running the test 

Either using `make test`:
```
$ make test

Running tests...
Test project /home/user/project/build
    Start 1: unit
1/1 Test #1: unit .............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```

Or directly using `unit_tests`:
```
$ ./unit_tests

[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from example
[ RUN      ] example.add
[       OK ] example.add (0 ms)
[ RUN      ] example.subtract
[       OK ] example.subtract (0 ms)
[----------] 2 tests from example (1 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (1 ms total)
[  PASSED  ] 2 tests.


```


## django project

## javascript code

## python code

## shell script




## Acknowledgments

Container Travis setup thanks to [Joan Massich](https://github.com/massich).

