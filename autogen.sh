#!/bin/sh
set -x
#libtoolize --automake --copy --debug --force
aclocal
autoheader
automake --foreign --add-missing --copy
autoconf
