@echo off
setlocal

set BUILD_DIR=build
set VCPKG_ROOT=%~dp0external\vcpkg

:: Clean CMake cache if old settings exist
if exist "%BUILD_DIR%\CMakeCache.txt" del "%BUILD_DIR%\CMakeCache.txt"

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

:: Configure using local vcpkg and MSVC
cmake .. ^
  -G "Visual Studio 17 2022" ^
  -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake ^
  -DVCPKG_TARGET_TRIPLET=x64-windows ^
  -DCMAKE_BUILD_TYPE=Release

:: Build the Release target
cmake --build . --config Release

:: Run the executable
.\Release\main.exe

endlocal
