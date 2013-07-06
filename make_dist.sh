#!/bin/bash
# This script creates a distribution archive in the dist folder.
# The dist folder is created in the current directory if not there yet.
set -e
version=$(bash version.sh)

dir="libunittest-"$version
rm -rf $dir
mkdir $dir

files='COPYING.txt README.txt CHANGES.txt install.sh version.sh'
for f in $files;do
	cp $f $dir
done

folders='build examples include src test doxygen'
for f in $folders;do
	cp -r $f $dir
done

cleans='build test examples/standard examples/minimal doxygen'
for f in $cleans;do
	cd $dir/$f
	make clean > /dev/null
	cd - > /dev/null
done

chmods=$(find $dir -name "*.sh")
for f in $chmods;do
    chmod -x $f
done

tar cfz $dir.tar.gz $dir
mkdir -p dist
mv $dir.tar.gz dist

rm -rf $dir

echo "Created dist/$dir.tar.gz"
