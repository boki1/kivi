#!/bin/bash

mkdir build
cd build

cmake .. && make test

cd ..
