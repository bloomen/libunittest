#!/bin/bash
set -e
version=$1
if [ "x$version" = "x" ];then

sftp bloomen,libunittest@web.sourceforge.net << EOF
cd htdocs
put doc/web/*
EOF
exit $?

else

sftp bloomen,libunittest@web.sourceforge.net << EOF
cd htdocs
put doc/web/*
cd /home/frs/project/libunittest
put dist/libunittest-${version}.tar.gz
EOF
exit $?

fi
