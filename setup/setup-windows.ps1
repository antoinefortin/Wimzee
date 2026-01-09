Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
# setup-windows.ps1
Write-Host "Installing MSYS2 for G++ dev env" -ForegroundColor Green

# Télécharge MSYS2
$msys2Installer = "$env:TEMP\msys2-installer.exe"
Write-Host "Downloading  MSYS2..."
Invoke-WebRequest -Uri "https://github.com/msys2/msys2-installer/releases/download/2024-01-13/msys2-x86_64-20240113.exe" -OutFile $msys2Installer

# Installe MSYS2 silencieusement
Write-Host "Installinig de MSYS2..."
Start-Process -FilePath $msys2Installer -ArgumentList "install --root C:\msys64 --confirm-command" -Wait -NoNewWindow

# Installe les packages nécessaires
Write-Host "Installing  g++, make, GLFW  and GLEW..."
$msys2Path = "C:\msys64\usr\bin\bash.exe"
& $msys2Path -lc "pacman -Syu --noconfirm"
& $msys2Path -lc "pacman -S --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-glfw mingw-w64-x86_64-glew"

# Ajoute au PATH
$mingwPath = "C:\msys64\mingw64\bin"
$currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($currentPath -notlike "*$mingwPath*") {
    Write-Host "Ajout au PATH..."
    [Environment]::SetEnvironmentVariable("Path", "$currentPath;$mingwPath", "User")
}

Write-Host "Installation done!" -ForegroundColor Green
Write-Host "Restart Visual Studio!"