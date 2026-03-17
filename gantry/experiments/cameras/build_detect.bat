@echo off
:: Build script for Basler Camera Detection

echo ========================================
echo  Building Basler Camera Detection
echo ========================================
echo.
echo This will build detect_basler_cameras.exe
echo.

:: Delete build directory if it exists
if exist "build_dual" (
    echo Using existing build directory...
) else (
    echo Creating build directory...
    mkdir build_dual
)

cd build_dual

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
echo Detecting Visual Studio installation...
echo.

:: Try Visual Studio 18 2026
echo Attempting: Visual Studio 18 2026...
cmake .. -G "Visual Studio 18 2026" -A x64

if %errorlevel% neq 0 (
    :: Try Visual Studio 17 2022
    echo.
    echo Attempting: Visual Studio 17 2022...
    cmake .. -G "Visual Studio 17 2022" -A x64
    
    if %errorlevel% neq 0 (
        :: Try Visual Studio 16 2019
        echo.
        echo Attempting: Visual Studio 16 2019...
        cmake .. -G "Visual Studio 16 2019" -A x64
        
        if %errorlevel% neq 0 (
            echo.
            echo ERROR: CMake configuration failed!
            echo Could not find a suitable Visual Studio installation.
            echo.
            echo Please ensure you have Visual Studio 2019, 2022, or 2026 installed with C++ support.
            echo.
            pause
            exit /b 1
        )
    )
)

echo.
echo CMake configuration successful!
echo.
echo Building detect_basler_cameras in Release mode...
cmake --build . --config Release --target detect_basler_cameras

if %errorlevel% neq 0 (
    echo.
    echo ERROR: Build failed!
    echo Please check the output above for error messages.
    echo.
    pause
    exit /b 1
)

echo.
echo ========================================
echo  Build Complete!
echo ========================================
echo.
echo Executable location: build_dual\Release\detect_basler_cameras.exe
echo.
echo To run the program, use: run_detect.bat
echo.

cd ..
pause
