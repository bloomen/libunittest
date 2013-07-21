#!/bin/bash
# This script runs the full test suite.
set -e
version=$(bash version.sh)

function separator {
    echo
    echo "######################"
    echo
}

function build {
    echo ">>> BUILDING $1 <<<"
    make clean
    make
}

function run {
    echo ">>> RUNNING $1 <<<"
}

echo "Running full test suite on libunittest-"$version

separator

cd build
build "library"
cd ..

separator

cd test
build "unit tests"
run "unit tests"
./run_test.sh
cd ..

cd examples
folders='minimal standard'
for folder in $folders;do
    separator
    cd $folder
    build "$folder example"
    run "$folder example"
    ./run_example.sh
    cd ..
done
cd ..

separator

cd doxygen
build "documentation"
file=html/index.html
if [ ! -f $file ];then
    echo "$file does not exist!"
    exit 1
fi
cd .. 

separator

echo "All tests passed!"
