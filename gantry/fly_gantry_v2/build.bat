@echo off
REM Build script for Fly Gantry project
REM This script configures and builds the project using CMake

setlocal enabledelayedexpansion

echo ========================================
echo Fly Gantry CMake Build Script
echo ========================================
echo.

REM Check if CMake is installed
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake is not installed or not in PATH
    echo Please install CMake from https://cmake.org/download/
    pause
    exit /b 1
)

REM Set build type (default to Release)
set BUILD_TYPE=Release
if not "%1"=="" (
    set BUILD_TYPE=%1
)

echo Build Type: %BUILD_TYPE%
echo.

REM Create build directory
if not exist "build" (
    echo Creating build directory...
    mkdir build
) else (
    echo Build directory already exists.
)

cd build

echo.
echo ========================================
echo Configuring with CMake...
echo ========================================
echo.

REM Configure the project
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=%BUILD_TYPE%

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: CMake configuration failed!
    echo.
    echo Common issues:
    echo   - Visual Studio 2022 not installed (try changing to "Visual Studio 16 2019")
    echo   - SDK paths in CMakeLists.txt are incorrect
    echo   - Missing dependencies
    echo.
    echo Check the error messages above for details.
    pause
    cd ..
    exit /b 1
)

echo.
echo ========================================
echo Building project...
echo ========================================
echo.

REM Build the project
cmake --build . --config %BUILD_TYPE% -- /m

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed!
    echo Check the error messages above for details.
    pause
    cd ..
    exit /b 1
)

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Executable location: build\bin\%BUILD_TYPE%\FlyGantry.exe
echo.
echo To run the program:
echo   cd build\bin\%BUILD_TYPE%
echo   FlyGantry.exe
echo.

cd ..
pause
