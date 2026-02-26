#!/usr/bin/env bash

rm -rf build
cmake -S . -B build
make -C build

gcc -g -Wall -Wextra main.c ./libtdmm/tdmm.c -o hw6 -I libtdmm