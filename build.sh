#!/bin/bash

rm -rf build bin 

mkdir build && cd build

cmake ..

cmake --build .

cd ../bin 

./stltest



