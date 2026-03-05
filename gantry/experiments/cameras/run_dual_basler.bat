@echo off
:: Run script for Dual Basler Camera Display

echo ========================================
echo  Dual Basler Camera Display Launcher
echo ========================================
echo.

:: Check if executable exists
if not exist "build_dual\Release\dual_basler_display.exe" (
    echo ERROR: Executable not found!
    echo Please build the project first by running: build_dual.bat
    echo.
    echo Other options:
    echo   - Single Basler camera: run_camera.bat
    echo   - Basler + Spinnaker: run_dual_camera.bat
    echo.
    pause
    exit /b 1
)

echo Starting dual Basler camera display...
echo.
echo Requirements:
echo   - Two Basler cameras must be connected
echo.
echo The program will:
echo   1. List all available Basler cameras
echo   2. Ask you to select camera indices
echo   3. Display both camera feeds
echo.
echo Press ESC in either window to exit
echo.
pause

:: Run the program
cd build_dual\Release
dual_basler_display.exe

cd ..\..

echo.
echo Camera display closed.
pause
