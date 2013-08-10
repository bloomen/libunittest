#!/bin/bash
# This script safely extracts the current version from src/version.cpp
# and prints it to screen
set -e
ident='return'
string=$(grep $ident src/version.cpp)
string=${string//[[:space:]]}
pos=$(awk -v a="$string" -v b="$ident" 'BEGIN{print index(a,b)}')
let pos=$pos+6
version=${string:$pos:-2}
echo $version
