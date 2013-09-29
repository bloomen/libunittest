#!/bin/bash
version=$1
if [ "x$version" = "x" ];then
    echo "Error: No version given"
    exit 1
fi

sftp bloomen,libunittest@web.sourceforge.net << EOF
cd htdocs
put doc/web/*.html
cd css
put doc/web/css/*.css
cd ../debian
put distribution/libunittest-dev_${version}_i386.deb
cd /home/frs/project/libunittest
put distribution/libunittest-${version}.tar.gz
EOF
exit $?
