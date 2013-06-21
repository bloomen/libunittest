#!/bin/bash
version=VERSION_NUMBER
set -e

dir=$1

if [ "x$dir" = "x" ]; then
	dir=/usr
fi

if [ ! -d "$dir" ]; then
	echo "$dir does not exist!"
	exit 1
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

mkdir -p $inc_dir
mkdir -p $lib_dir

cp -r -v include/* $inc_dir
cp -v build/libunittest.so.$version $lib_dir
rm -f $lib_dir/libunittest.so
ln -sv $lib_dir/libunittest.so.$version $lib_dir/libunittest.so

echo
echo "libunittest successfully installed!"
