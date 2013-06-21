#!/bin/bash
set -e
export LD_LIBRARY_PATH=../build:$LD_LIBRARY_PATH
./unittest_test $*
