#!/usr/bin/bash
set -xe

export C_FLAGS="-g -Isrc/include -std=c2x -pedantic -Wall -W -Wno-missing-field-initializers"

mkdir -p src/include
python file-to-h.py pngegg.png logo > src/include/logo.h
gcc $C_FLAGS `pkg-config --cflags raylib` -o woo src/main.c `pkg-config -libs raylib`
