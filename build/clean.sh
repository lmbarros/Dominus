#!/bin/sh

#
# Calling rm -rf manually is too dangerous ;-)
#

rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile src Dominus* \
    dominus* *.sln *.vcproj *.sln.cache ZERO_CHECK* ALL_BUILD* Release PACKAGE*
