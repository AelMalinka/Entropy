#!/bin/bash

aclocal -I m4
libtoolize
autoconf
autoheader
mkdir -p build-aux
automake --add-missing
