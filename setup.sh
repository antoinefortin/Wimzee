#!/bin/bash
set -e

echo "Setting up Wimzee on Linux..."

# Clone vcpkg if not there
if [ ! -d "vcpkg" ]; then
    echo "Cloning vcpkg..."
    git clone https://github.com/Microsoft/vcpkg.git
fi

# Bootstrap vcpkg
cd vcpkg
if [ ! -f "vcpkg" ]; then
    echo "Bootstrapping vcpkg..."
    ./bootstrap-vcpkg.sh -disableMetrics
fi

cd ..

echo ""
echo "Setup complete!"
echo "Now run: ./build.sh"