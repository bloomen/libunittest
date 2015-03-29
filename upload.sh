#!/bin/bash
set -e
tarball=$1
if [ "x$tarball" = "x" ];then
    echo "No tarball provided"
    exit 1
fi

sftp bloomen,libunittest@web.sourceforge.net << EOF
cd htdocs
put doc/web/*
cd /home/frs/project/libunittest
put $tarball
EOF
