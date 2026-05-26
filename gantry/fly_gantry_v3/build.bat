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

REM Dependency paths (keep aligned with CMakeLists.txt defaults)
set OPENCV_DIR=C:\Users\SeniorDesign\Downloads\opencv\build
set PYLON_ROOT=C:\Program Files\Basler\pylon\Development
set MATLAB_ROOT=C:\Program Files\MATLAB\R2026a
set "ZABER_ROOT=C:\Users\Public\Documents\Senior-Design-Fly-Gantry-Drexel-2026\gantry\fly_gantry_v3\ZaberMotionLibrary"
set VCPKG_TOOLCHAIN=C:\Users\SeniorDesign\vcpkg\scripts\buildsystems\vcpkg.cmake
set VCPKG_TRIPLET=x64-windows

echo Build Type: %BUILD_TYPE%
echo.

echo Checking dependencies...
set MISSING_DEPS=0
set ERR_OPENCV=0
set ERR_PYLON=0
set ERR_MATLAB=0
set ERR_ZABER=0
set ERR_VCPKG=0

if not exist "%OPENCV_DIR%" (
    echo   [MISSING] OpenCV root: %OPENCV_DIR%
    echo            Expected folder containing OpenCVConfig.cmake
    set /a MISSING_DEPS+=1
    set ERR_OPENCV=1
) else (
    if not exist "%OPENCV_DIR%\OpenCVConfig.cmake" (
        echo   [MISSING] OpenCV config file: %OPENCV_DIR%\OpenCVConfig.cmake
        echo            OPENCV_DIR should point to the OpenCV build root.
        set /a MISSING_DEPS+=1
        set ERR_OPENCV=1
    ) else (
        echo   [OK] OpenCV_DIR: %OPENCV_DIR%
    )
)

if not exist "%PYLON_ROOT%\include" (
    echo   [MISSING] Pylon include folder: %PYLON_ROOT%\include
    set /a MISSING_DEPS+=1
    set ERR_PYLON=1
) else (
    if not exist "%PYLON_ROOT%\include\pylon\PylonIncludes.h" (
        echo   [MISSING] Pylon header: %PYLON_ROOT%\include\pylon\PylonIncludes.h
        set /a MISSING_DEPS+=1
        set ERR_PYLON=1
    )
)
if not exist "%PYLON_ROOT%\lib\x64" (
    echo   [MISSING] Pylon x64 lib folder: %PYLON_ROOT%\lib\x64
    set /a MISSING_DEPS+=1
    set ERR_PYLON=1
)
if %ERR_PYLON% EQU 0 (
    echo   [OK] Basler Pylon SDK: %PYLON_ROOT%
)

if not exist "%MATLAB_ROOT%\extern\include" (
    echo   [MISSING] MATLAB extern include folder: %MATLAB_ROOT%\extern\include
    set /a MISSING_DEPS+=1
    set ERR_MATLAB=1
) else (
    if not exist "%MATLAB_ROOT%\extern\include\mat.h" (
        echo   [MISSING] MATLAB header: %MATLAB_ROOT%\extern\include\mat.h
        set /a MISSING_DEPS+=1
        set ERR_MATLAB=1
    )
)
if not exist "%MATLAB_ROOT%\extern\lib\win64\microsoft\libmat.lib" (
    echo   [MISSING] MATLAB lib: %MATLAB_ROOT%\extern\lib\win64\microsoft\libmat.lib
    set /a MISSING_DEPS+=1
    set ERR_MATLAB=1
)
if not exist "%MATLAB_ROOT%\extern\lib\win64\microsoft\libmx.lib" (
    echo   [MISSING] MATLAB lib: %MATLAB_ROOT%\extern\lib\win64\microsoft\libmx.lib
    set /a MISSING_DEPS+=1
    set ERR_MATLAB=1
)
if %ERR_MATLAB% EQU 0 (
    echo   [OK] MATLAB SDK: %MATLAB_ROOT%
)

if not exist "%ZABER_ROOT%\lib\Release\zaber-motion.lib" (
    echo   [MISSING] Zaber release lib: %ZABER_ROOT%\lib\Release\zaber-motion.lib
    set /a MISSING_DEPS+=1
    set ERR_ZABER=1
)
if not exist "%ZABER_ROOT%\bin\Release\zaber-motion.dll" (
    echo   [MISSING] Zaber release DLL: %ZABER_ROOT%\bin\Release\zaber-motion.dll
    set /a MISSING_DEPS+=1
    set ERR_ZABER=1
)
if %ERR_ZABER% EQU 0 (
    echo   [OK] Zaber SDK: %ZABER_ROOT%
)

if not exist "%VCPKG_TOOLCHAIN%" (
    echo   [MISSING] vcpkg toolchain file: %VCPKG_TOOLCHAIN%
    set /a MISSING_DEPS+=1
    set ERR_VCPKG=1
) else (
    echo   [OK] vcpkg toolchain file: %VCPKG_TOOLCHAIN%
)

if %MISSING_DEPS% GTR 0 (
    echo.
    echo ERROR: %MISSING_DEPS% required dependency paths are missing.
    echo Fix the missing items above, or update the SDK path variables in this script.
    echo.
    echo SDK-specific guidance:
    if %ERR_OPENCV% EQU 1 echo   - OpenCV: set OPENCV_DIR to your OpenCV build root that contains OpenCVConfig.cmake.
    if %ERR_PYLON% EQU 1 echo   - Pylon: set PYLON_ROOT to the Basler pylon Development folder.
    if %ERR_MATLAB% EQU 1 echo   - MATLAB: set MATLAB_ROOT to your MATLAB install root with extern\include and extern\lib\win64\microsoft.
    if %ERR_ZABER% EQU 1 echo   - Zaber: set ZABER_ROOT to folder containing lib\Release\zaber-motion.lib and bin\Release\zaber-motion.dll.
    if %ERR_VCPKG% EQU 1 echo   - vcpkg: set VCPKG_TOOLCHAIN to vcpkg\scripts\buildsystems\vcpkg.cmake.
    echo.
    pause
    exit /b 1
)

echo All required dependency paths were found.
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
REM CMAKE_TOOLCHAIN_FILE is only honored on initial configure for a build folder.
REM If an old cache exists without toolchain, clean cache and run initial configure again.
set NEED_TOOLCHAIN_REINIT=0
if exist "CMakeCache.txt" (
    findstr /B /C:"CMAKE_TOOLCHAIN_FILE:FILEPATH=" CMakeCache.txt >nul
    if !ERRORLEVEL! NEQ 0 (
        set NEED_TOOLCHAIN_REINIT=1
    ) else (
        findstr /B /C:"CMAKE_TOOLCHAIN_FILE:FILEPATH=%VCPKG_TOOLCHAIN%" CMakeCache.txt >nul
        if !ERRORLEVEL! NEQ 0 (
            set NEED_TOOLCHAIN_REINIT=1
        )
    )
)

if !NEED_TOOLCHAIN_REINIT! EQU 1 (
    echo Detected existing CMake cache without the expected vcpkg toolchain.
    echo Cleaning cache to allow first-configure toolchain injection...
    if exist "CMakeCache.txt" del /f /q "CMakeCache.txt"
    if exist "CMakeFiles" rmdir /s /q "CMakeFiles"
)

if exist "CMakeCache.txt" cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DOpenCV_DIR="%OPENCV_DIR%" -DVCPKG_TARGET_TRIPLET=%VCPKG_TRIPLET%
if not exist "CMakeCache.txt" cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DOpenCV_DIR="%OPENCV_DIR%" -DCMAKE_TOOLCHAIN_FILE="%VCPKG_TOOLCHAIN%" -DVCPKG_TARGET_TRIPLET=%VCPKG_TRIPLET%

if errorlevel 1 goto configure_failed

echo.
echo ========================================
echo Building project...
echo ========================================
echo.

REM Build the project
cmake --build . --config %BUILD_TYPE% -- /m

if errorlevel 1 goto build_failed

goto build_success

:configure_failed
    echo.
    echo ERROR: CMake configuration failed!
    echo.
    echo Common issues:
    echo   - Visual Studio 2022 not installed (try changing to "Visual Studio 16 2019")
    echo   - SDK paths in CMakeLists.txt are incorrect
    echo   - Required libraries are missing from the configured SDK folders
    echo.
    echo Checked dependency paths:
    echo   - OpenCV_DIR: %OPENCV_DIR%
    echo   - PYLON_ROOT: %PYLON_ROOT%
    echo   - MATLAB_ROOT: %MATLAB_ROOT%
    echo   - ZABER_ROOT: %ZABER_ROOT%
    echo   - VCPKG_TOOLCHAIN: %VCPKG_TOOLCHAIN%
    echo   - VCPKG_TARGET_TRIPLET: %VCPKG_TRIPLET%
    echo.
    echo Check the error messages above for details.
    pause
    cd ..
    exit /b 1

:build_failed
    echo.
    echo ERROR: Build failed!
    echo Check the error messages above for details.
    pause
    cd ..
    exit /b 1

:build_success

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