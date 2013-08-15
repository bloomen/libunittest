libunittest is a portable C++ library for unit testing making use of C++11.

Features:

- unit and integration testing in C++
- follows the xUnit test patterns
- formatted XML output of the test results
- comes with rich assertions and is easily extendable
- option to only run specific tests without recompiling
- option to turn off exception handling for debugging purposes 
- supports setting timeouts for specific tests or even all tests
- supports test contexts which multiple tests can be run within
- functionality to easily produce random values and containers 
- portable across various operating systems
- tests can be run in parallel
- macros only for registering test runs
- libunittest comes with tests and examples

libunittest has been successfully tested with:

CXX=g++ (on Linux with GCC4.7)
CXX=g++ (on Cygwin/Windows with GCC4.7)
CXX='clang++ -stdlib=libc++ -U__STRICT_ANSI__' (on MacOSX with Clang3.2)

In order to build and install libunittest simply unpack the distribution 
archive, enter the resulting directory and do: 

make [CXX=compiler]
make install [INSTALLDIR=/path/to/install]

The default compiler is g++ which is used if no compiler is given. 
If INSTALLDIR is not given then libunittest will be installed in a  
standard system location (/usr/local) requiring root privileges. 

To build and run the tests, do:

make -C test
make -C test run

To build the documentation, do:

make -C doc

To invoke a complete library check, do:

make check

Please also check out the examples shipped with this library.

libunittest is being developed by Christian Blume. Contact Christian at
chr.blume@gmail.com for any questions or comments.
