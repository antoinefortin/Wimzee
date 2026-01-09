# setup-deps.ps1
Write-Host "Installing Speedlog" -ForegroundColor Green

if (!(Test-Path "vendor")) {
    New-Item -ItemType Directory -Path "vendor"
}

if (!(Test-Path "vendor/spdlog")) {
    Write-Host "Downloading speedlog"
    git clone --depth 1 --branch v1.13.0 https://github.com/gabime/spdlog.git vendor/spdlog
} else {
    Write-Host "spdlog is already installed!"
}

# GLM
if (!(Test-Path "vendor/glm")) {
    Write-Host "Downloading  GLM..."
    git clone --depth 1 --branch 0.9.9.8 https://github.com/g-truc/glm.git vendor/glm
} else {
    Write-Host "GLM déjà installé!"
}



Write-Host "Terminé!" -ForegroundColor Green