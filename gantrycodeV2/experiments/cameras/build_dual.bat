@echo off
:: Build script for Dual Basler Camera Display

echo ========================================
echo  Building Dual Basler Camera Display
echo ========================================
echo.
echo This will build dual_basler_display.exe (Two Basler cameras)
echo.

:: Delete build directory if it exists
if exist "build_dual" (
    echo Deleting existing build directory...
    timeout /t 1 /nobreak >nul
    rmdir /s /q build_dual 2>nul
    if exist "build_dual" (
        echo Warning: Could not delete build_dual, trying to continue...
        timeout /t 2 /nobreak >nul
        rmdir /s /q build_dual 2>nul
    )
)

:: Create fresh build directory
if not exist "build_dual" (
    echo Creating build directory...
    mkdir build_dual
) else (
    echo Using existing build_dual directory...
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
if %errorlevel% equ 0 (
    echo [SUCCESS] Using Visual Studio 18 2026
    echo.
    goto :build
) else (
    echo [FAILED] Visual Studio 18 2026 configuration failed
    echo Cleaning build directory and trying other options...
    cd ..
    rmdir /s /q build_dual 2>nul
    mkdir build_dual
    cd build_dual
)

:: Try Visual Studio 17 2022
echo Attempting: Visual Studio 17 2022...
cmake .. -G "Visual Studio 17 2022" -A x64
if %errorlevel% equ 0 (
    echo [SUCCESS] Using Visual Studio 17 2022
    goto :build
)

echo.

:: Try Visual Studio 16 2019
echo Attempting: Visual Studio 16 2019...
cmake .. -G "Visual Studio 16 2019" -A x64 >nul 2>&1
if %errorlevel% equ 0 (
    echo [SUCCESS] Using Visual Studio 16 2019
    echo.
    goto :build
)

:: Try Visual Studio 15 2017  
echo Attempting: Visual Studio 15 2017...
cmake .. -G "Visual Studio 15 2017" -A x64 >nul 2>&1
if %errorlevel% equ 0 (
    echo [SUCCESS] Using Visual Studio 15 2017
    echo.
    goto :build
)

:: Try NMake Makefiles
echo Attempting: NMake Makefiles...
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release >nul 2>&1
if %errorlevel% equ 0 (
    echo [SUCCESS] Using NMake Makefiles
    echo.
    goto :build
)

:: Try MinGW Makefiles
echo Attempting: MinGW Makefiles...
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release >nul 2>&1
if %errorlevel% equ 0 (
    echo [SUCCESS] Using MinGW Makefiles
    echo.
    goto :build
)

:: Try Ninja
echo Attempting: Ninja...
cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release >nul 2>&1
if %errorlevel% equ 0 (
    echo [SUCCESS] Using Ninja
    echo.
    goto :build
)

:: All generators failed
echo.
echo ========================================
echo ERROR: No suitable build system found!
echo ========================================
echo.
echo CMake could not find any of the following:
echo   - Visual Studio 2026, 2022, 2019, or 2017
echo   - NMake (usually comes with VS)
echo   - MinGW-w64
echo   - Ninja build system
echo.
echo If you have Visual Studio installed:
echo   1. Make sure "Desktop development with C++" workload is installed
echo   2. Open Visual Studio Installer and verify C++ tools are installed
echo   3. Try running this from "Developer Command Prompt for VS"
echo.
echo To install build tools:
echo   - Visual Studio: https://visualstudio.microsoft.com/downloads/
echo   - Build Tools only: https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022
echo   - MinGW-w64: https://www.mingw-w64.org/
echo.
pause
exit /b 1

:build

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
echo Executable created:
if exist "Release\dual_basler_display.exe" (
    echo   [OK] build_dual\Release\dual_basler_display.exe
) else (
    echo   [MISSING] build_dual\Release\dual_basler_display.exe
)

if exist "dual_basler_display.exe" (
    echo   [OK] build_dual\dual_basler_display.exe
)

echo.
echo To run:
echo   .\Release\dual_basler_display.exe
echo   or .\dual_basler_display.exe
echo.

cd ..

pause
