#!/bin/bash
# This script safely extracts the current version from src/version.cpp
# and prints it to screen
set -e
ident='make_tuple'
string=$(cat src/version.cpp | grep $ident)
string=${string//[[:space:]]}
pos=$(awk -v a="$string" -v b="$ident" 'BEGIN{print index(a,b)}')
let pos=$pos+10
major=${string:$pos:1}
let pos=$pos+2
minor=${string:$pos:1}
let pos=$pos+2
patch=${string:$pos:1}
version="${major}.${minor}.${patch}"
echo $version
