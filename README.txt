libunittest is a portable C++ library for unit testing making use of C++11.

Features:

- unit and integration testing in C++
- follows the xUnit test patterns
- formatted XML output of the test results
- comes with rich assertions and is easily extendable
- option to only run specific tests without recompiling
- option to turn off exception handling for debugging purposes 
- supports test contexts which multiple tests can be run within
- supports to set timeouts for specific tests or all tests
- functionality to easily produce random values and containers 
- portable across various operating systems
- tests can be run in parallel
- macros only for registering test runs
- libunittest comes with tests and examples

libunittest has been successfully tested with:

* g++ -std=c++0x  (on Linux with GCC4.6)
* clang++ -std=c++0x -stdlib=libc++  (on MacOSX with Clang3.2)

In order to build and install libunittest simply unpack the archive, enter 
the resulting directory and execute: 

chmod u+x install.sh
./install.sh [install_directory]

If install_directory is not given then libunittest will be installed in a 
standard system location (/usr/local) requiring root privileges. 

libunittest is being developed by Christian Blume. Contact Christian at
chr.blume@gmail.com for any questions or comments.
