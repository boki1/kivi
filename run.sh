#!/bin/bash

mkdir -p build
mkdir -p src/autogen/kivi_parser
cd build
cmake ..
make
cd ..
./build/src/kivi/kivi $*
