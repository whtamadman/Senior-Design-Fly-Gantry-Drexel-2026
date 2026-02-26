@echo off
:: Quick run script for Bottom Camera Display

echo ========================================
echo  Running Bottom Camera Display
echo ========================================
echo.

:: Check if executable exists
if not exist "build\Release\bottom_camera_display.exe" (
    echo ERROR: Executable not found!
    echo Please build the project first by running: build.bat
    echo.
    pause
    exit /b 1
)

echo Starting camera display...
echo Press ESC in the camera window to exit
echo.

:: Run the program
cd build\Release
bottom_camera_display.exe

cd ..\..

echo.
echo Camera display closed.
pause
