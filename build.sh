#!/usr/bin/env bash

rm -rf build
cmake -S . -B build
make -C build

gcc main.c ./libtdmm/tdmm.c -o main -I./libtdmm/ -lm