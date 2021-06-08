#!/bin/bash

# ./tools/clean.sh

mkdir -p build
cd build
cmake .. && make
cd ..
