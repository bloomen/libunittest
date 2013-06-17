#!/bin/bash
version=VERSION_NUMBER

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
make clean >/dev/null || exit 1
rm -f libunittest.so*
make || exit 1
mv libunittest.so libunittest.so.$version
ln -s libunittest.so.$version libunittest.so
cd ..

echo
echo "Installing ..."

inc_dir=$dir/include
lib_dir=$dir/lib

mkdir -p $inc_dir || exit 1
mkdir -p $lib_dir || exit 1

cp -r -v include/* $inc_dir || exit 1
cp -v build/libunittest.so.$version $lib_dir || exit 1
rm -f $lib_dir/libunittest.so
ln -sv $lib_dir/libunittest.so.$version $lib_dir/libunittest.so || exit 1

echo
echo "libunittest successfully installed!"
