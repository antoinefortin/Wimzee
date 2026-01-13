# setup-deps.ps1
Write-Host "Installing dependencies..." -ForegroundColor Green

if (!(Test-Path "vendor")) {
    New-Item -ItemType Directory -Path "vendor"
}

# spdlog
if (!(Test-Path "vendor/spdlog")) {
    Write-Host "Downloading spdlog..."
    git clone --depth 1 --branch v1.13.0 https://github.com/gabime/spdlog.git vendor/spdlog
} else {
    Write-Host "spdlog already installed!"
}

# GLM
if (!(Test-Path "vendor/glm")) {
    Write-Host "Downloading GLM..."
    git clone --depth 1 --branch 0.9.9.8 https://github.com/g-truc/glm.git vendor/glm
} else {
    Write-Host "GLM already installed!"
}

# stb (stb_image)
if (!(Test-Path "vendor/stb")) {
    Write-Host "Downloading stb..."
    git clone --depth 1 https://github.com/nothings/stb.git vendor/stb
} else {
    Write-Host "stb already installed!"
}

Write-Host "Terminé!" -ForegroundColor Green