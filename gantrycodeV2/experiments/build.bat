@echo off
:: Quick build script for Bottom Camera Display

echo ========================================
echo  Building Bottom Camera Display
echo ========================================
echo.

:: Check if build directory exists
if not exist "build" (
    echo Creating build directory...
    mkdir build
)

cd build

:: Check if CMake is installed
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo ERROR: CMake not found!
    echo Please install CMake: https://cmake.org/download/
    echo Or via Chocolatey: choco install cmake -y
    echo.
    pause
    exit /b 1
)

echo Configuring with CMake...
cmake .. -G "Visual Studio 17 2022" -A x64
if %errorlevel% neq 0 (
    echo.
    echo ERROR: CMake configuration failed!
    echo Check that all dependencies are installed.
    echo Run install_dependencies.ps1 first.
    echo.
    pause
    exit /b 1
)

echo.
echo Building project (Release mode)...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo.
    echo ERROR: Build failed!
    echo Check the error messages above.
    echo.
    pause
    exit /b 1
)

echo.
echo ========================================
echo  Build successful!
echo ========================================
echo.
echo Executable location: build\Release\bottom_camera_display.exe
echo.
echo To run the program:
echo   1. Make sure Basler camera is connected
echo   2. Run: .\Release\bottom_camera_display.exe
echo.
echo Or simply double-click run_camera.bat
echo.

cd ..

pause
