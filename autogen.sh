#!/bin/bash

aclocal -I m4
autoheader
autoconf
mkdir -p build-aux
automake --add-missing
