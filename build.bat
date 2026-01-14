@echo off
echo Building Wimzee with VS2022...

REM Clean build
if exist build rd /s /q build

REM Configure
cmake -B build -S . ^
  -G "Visual Studio 17 2022" ^
  -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake ^
  -DVCPKG_TARGET_TRIPLET=x64-windows-static

if %errorlevel% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b %errorlevel%
)

REM Build
cmake --build build --config Release

if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b %errorlevel%
)

echo Build successful!
pause