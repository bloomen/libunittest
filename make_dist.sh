#!/bin/bash
version="3.0.0"

dir="libunittest-"$version
rm -rf $dir
mkdir $dir

shfiles='install.sh'
for f in $shfiles;do
	cp $f $dir
done

sed -i "s/VERSION_NUMBER/\"${version}\"/g" $dir/install.sh 

txtfiles='COPYING.txt README.txt CHANGES.txt'
for f in $txtfiles;do
	cp $f $dir
	todos $dir/$f
done

folders='build examples include src test'
for f in $folders;do
	cp -r $f $dir
done

cleans='build test examples/complete examples/minimal'
for f in $cleans;do
	cd $dir/$f
	make clean > /dev/null
	cd - > /dev/null
done

tar cfz $dir.tar.gz $dir
mkdir -p dist
mv $dir.tar.gz dist

rm -rf $dir
