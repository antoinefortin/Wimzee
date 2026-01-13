@echo off
rd /s /q build
if not exist build mkdir build
cmake -S . -B build -Wno-dev -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build build --config Release