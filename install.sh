#!/bin/sh

# $1: Build type [Debug, Release, RelWithDebInfo]

conan install . --output-folder=build --build=missing -s build_type=$1 && cd build && cmake ..  -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$1 && cd ..
