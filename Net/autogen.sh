#!/bin/bash

mkdir -p build-aux
libtoolize
aclocal -I m4
autoconf
autoheader
automake --add-missing
