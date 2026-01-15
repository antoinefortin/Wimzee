#!/bin/bash
set -e

echo "Building Wimzee on macOS..."

# Clean build
if [ -d "build" ]; then
    rm -rf build
fi

# Detect architecture
ARCH=$(uname -m)
if [ "$ARCH" = "arm64" ]; then
    TRIPLET="arm64-osx"
    echo "Detected Apple Silicon (M1/M2/M3)"
else
    TRIPLET="x64-osx"
    echo "Detected Intel Mac"
fi

# Configure
cmake -B build -S . \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=$TRIPLET

if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# Build
cmake --build build -- -j$(sysctl -n hw.ncpu)

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo ""
echo "Build successful!"
echo "Run: ./build/wimzee"