#!/bin/bash
set -e
if [ "$(uname)" = "Darwin" ];then
    export DYLD_LIBRARY_PATH=../build:$DYLD_LIBRARY_PATH
else
    export LD_LIBRARY_PATH=../build:$LD_LIBRARY_PATH
fi
./unittest $*
