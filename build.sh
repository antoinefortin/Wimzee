#!/bin/bash
set -e

echo "Building Wimzee on Linux..."

# Clean build
if [ -d "build" ]; then
    rm -rf build
fi

# Configure
cmake -B build -S . \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=x64-linux

if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# Build
cmake --build build -j$(nproc)

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo ""
echo "Build successful!"
echo "Run: ./build/wimzee"