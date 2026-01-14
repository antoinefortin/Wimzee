@echo on
echo Setting up Wimzee...

REM Clone vcpkg si pas là
if not exist vcpkg (
    git clone https://github.com/Microsoft/vcpkg.git
)

REM Bootstrap vcpkg
cd vcpkg
if not exist vcpkg.exe (
    call bootstrap-vcpkg.bat -disableMetrics
)

REM Install dependencies
vcpkg install --triplet=x64-windows-static
cd ..

echo Setup complete! Now run build.bat
pause