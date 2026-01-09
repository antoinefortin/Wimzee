#!/bin/bash
echo "Installation de spdlog..."

mkdir -p vendor

if [ ! -d "vendor/spdlog" ]; then
    echo "Downloading SPpedlog..."
    git clone --depth 1 --branch v1.13.0 https://github.com/gabime/spdlog.git vendor/spdlog
else
    echo "spdlog already installed!"
fi

echo "Terminé!"