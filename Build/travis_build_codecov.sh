#!/usr/bin/env bash

set -e

cmake . -DCMAKE_BUILD_TYPE=Debug -DBUILD_COVERAGE=ON
cmake --build . -j $(nproc)
ctest -j $(nproc) --output-on-failure