#!/bin/bash
cd ..
version=$(bash version.sh)
cd - >/dev/null
echo $version
