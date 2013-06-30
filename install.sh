#!/bin/bash
# This scripts installs libunittest in a given location.
# Usage: sh install.sh [install_directory]
# If install_directory is not given than libunittest will be installed in a 
# standard system location (/usr) requiring root privileges.
# The version in VERSION.txt is used to distinguish between installed libraries.
# libunittest is only installed if all tests pass. 
set -e
version=$(head -n 1 VERSION.txt)

dir=$1

if [ "x$dir" = "x" ]; then
	dir=/usr
fi

echo "Compiling ... "

cd build
make clean >/dev/null
rm -f libunittest.so*
make
mv libunittest.so libunittest.so.$version
ln -s libunittest.so.$version libunittest.so
cd ..

echo
echo "Testing ..."

cd test
make clean >/dev/null
make
sh run_test.sh
cd ..

echo
echo "Installing ..."

inc_dir=$dir/include
lib_dir=$dir/lib

mkdir -p $dir
mkdir -p $inc_dir
mkdir -p $lib_dir

cp -r -v include/* $inc_dir
cp -v build/libunittest.so.$version $lib_dir
rm -f $lib_dir/libunittest.so
ln -sv $lib_dir/libunittest.so.$version $lib_dir/libunittest.so

echo
echo "libunittest successfully installed!"
