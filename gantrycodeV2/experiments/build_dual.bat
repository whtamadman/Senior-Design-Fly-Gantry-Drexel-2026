@echo off
:: Build script for Dual Camera Display

echo ========================================
echo  Building Camera Display Programs
echo ========================================
echo.
echo This will build THREE programs:
echo   1. bottom_camera_display.exe (Single Basler)
echo   2. dual_basler_display.exe (Two Basler cameras)
echo   3. dual_camera_display.exe (Basler + Spinnaker)
echo.

:: Check if CMakeLists_dual.txt should be used
if exist "CMakeLists_dual.txt" (
    echo Using CMakeLists_dual.txt for building...
    copy /Y CMakeLists_dual.txt CMakeLists.txt >nul
)

:: Check if build directory exists
if not exist "build_dual" (
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
cmake .. -G "Visual Studio 17 2022" -A x64
if %errorlevel% neq 0 (
    echo.
    echo ERROR: CMake configuration failed!
    echo.
    echo Common issues:
    echo   - Spinnaker SDK not found
    echo   - Set SPINNAKER_ROOT environment variable
    echo   - Download from: https://www.flir.com/products/spinnaker-sdk/
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
echo Executables created:
if exist "Release\bottom_camera_display.exe" (
    echo   [OK] build_dual\Release\bottom_camera_display.exe
) else (
    echo   [MISSING] build_dual\Release\bottom_camera_display.exe
)

if exist "Release\dual_basler_display.exe" (
    echo   [OK] build_dual\Release\dual_basler_display.exe
) else (
    echo   [MISSING] build_dual\Release\dual_basler_display.exe
)

if exist "Release\dual_camera_display.exe" (
    echo   [OK] build_dual\Release\dual_camera_display.exe
) else (
    echo   [WARNING] build_dual\Release\dual_camera_display.exe
    echo   Note: This requires Spinnaker SDK installed
)

echo.
echo To run:
echo   1. Single Basler: .\Release\bottom_camera_display.exe
echo   2. Two Basler: .\Release\dual_basler_display.exe
echo   3. Basler + Spinnaker: .\Release\dual_camera_display.exe
echo.

cd ..

pause
