#!/bin/bash

mkdir -p build
mkdir -p src/autogen/kivi_parser
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
cd ..
./build/src/kivi/kivi $*
