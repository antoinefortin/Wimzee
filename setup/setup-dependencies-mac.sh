#!/bin/bash

brew install glfw glew  

echo "Installing dependencies..."
mkdir -p vendor

# spdlog
if [ ! -d "vendor/spdlog" ]; then
    echo "Downloading spdlog..."
    git clone --depth 1 --branch v1.13.0 https://github.com/gabime/spdlog.git vendor/spdlog
else
    echo "spdlog already installed!"
fi

# GLM
if [ ! -d "vendor/glm" ]; then
    echo "Downloading GLM..."
    git clone --depth 1 --branch 0.9.9.8 https://github.com/g-truc/glm.git vendor/glm
else
    echo "GLM already installed!"
fi


# stb (stb_image)
if [ ! -d "vendor/stb" ]; then
    echo "Downloading stb..."
    git clone --depth 1 https://github.com/nothings/stb.git vendor/stb
else
    echo "stb already installed!"
fi



echo "Terminé!"