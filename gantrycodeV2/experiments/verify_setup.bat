@echo off
:: Verification script to check if all files are in place

echo ========================================
echo  Setup Verification
echo ========================================
echo.

:: Check for required files in current directory
echo Checking files in experiments folder...
if exist "bottom_camera_display.cpp" (
    echo [OK] bottom_camera_display.cpp
) else (
    echo [MISSING] bottom_camera_display.cpp
)

if exist "CMakeLists.txt" (
    echo [OK] CMakeLists.txt
) else (
    echo [MISSING] CMakeLists.txt
)

if exist "build.bat" (
    echo [OK] build.bat
) else (
    echo [MISSING] build.bat
)

if exist "install_dependencies.bat" (
    echo [OK] install_dependencies.bat
) else (
    echo [MISSING] install_dependencies.bat
)

echo.
echo Checking files in parent directory...
if exist "..\HardwareTriggerConfiguration.h" (
    echo [OK] HardwareTriggerConfiguration.h ^(in parent folder^)
) else (
    echo [MISSING] HardwareTriggerConfiguration.h ^(in parent folder^)
    echo WARNING: This file is required for compilation!
)

echo.
echo ========================================
echo Verification complete!
echo ========================================
echo.
echo If all files show [OK], you can proceed with:
echo   1. install_dependencies.bat (install dependencies)
echo   2. build.bat (build the project)
echo   3. run_camera.bat (run the application)
echo.
pause
