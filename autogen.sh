#!/bin/bash

aclocal -I m4
autoconf
autoheader
mkdir -p build-aux
automake --add-missing
libtoolize
