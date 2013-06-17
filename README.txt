libunittest is a portable C++ library for unit testing making use of C++11.

Features:

- unit and integration testing in C++
- follows the xUnit test patterns
- formatted XML output of the test results
- option to only run specific tests without recompiling 
- comes with rich assertions and is easily extendable
- supports test contexts which multiple tests can be run within
- tests can be run in parallel due to full thread-safety
- portable across various operating systems such as Linux and MacOSX
- macros only for registering test runs

libunittest has been successfully tested with:

* g++ -std=c++0x  (on Linux with GCC4.6)
* clang++ -std=c++0x -stdlib=libc++  (on MacOSX with Clang3.2)

In order to build and install libunittest simply unpack the archive, enter 
the resulting directory and execute: 

sh install.sh [install_directory]

If install_directory is not given than libunittest will be installed in a 
standard system location (/usr) requiring root privileges.

libunittest is being developed by Christian Blume. Contact Christian at
chr.blume@gmail.com for any questions or comments.
