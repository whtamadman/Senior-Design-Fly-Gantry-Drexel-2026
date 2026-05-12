# Building Fly Gantry with CMake (Bottom Camera Only Version)

This document describes how to build the Fly Gantry project using CMake.

**NOTE:** This version has been simplified to use only the bottom camera (Basler/Pylon) for fly tracking with YOLO. The top camera (Spinnaker SDK) has been removed.

## Prerequisites

Before building, ensure you have installed:

1. **CMake** (version 3.15 or higher)
   - Download from: https://cmake.org/download/

2. **Visual Studio 2019 or 2022** (with C++ development tools)
   - Community Edition is sufficient

3. **Required SDKs and Libraries:**

   - **OpenCV** (4.x recommended)
     - Download from: https://opencv.org/releases/
     - Or use vcpkg: `vcpkg install opencv:x64-windows`

   - **Pylon SDK** (for Basler bottom camera) **[REQUIRED]**
     - Download from: https://www.baslerweb.com/en/products/software/basler-pylon-camera-software-suite/

   - **NI-DAQmx** (for National Instruments DAQ hardware)
     - Download from: https://www.ni.com/en-us/support/downloads/drivers/download.ni-daqmx.html

   - **USB4 Library** (for encoder)
     - Provided by US Digital

   - **YOLO/Darknet** (for fly detection)
     - Build from: https://github.com/AlexeyAB/darknet

   - **MATLAB** (if using MATLAB data export features)
     - Install MATLAB R2022b or adjust paths in CMakeLists.txt

## Configuration

Before building, you may need to edit `CMakeLists.txt` to set the correct paths for your SDKs:

```cmake
# Edit these paths to match your system (Spinnaker removed - bottom camera only)
set(PYLON_ROOT "C:/Program Files/Basler/pylon 7" CACHE PATH "Pylon SDK root directory")
set(NIDAQMX_ROOT "C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C" CACHE PATH "NI-DAQmx root directory")
set(USB4_ROOT "C:/Program Files/USB4/USB4DriverAndLibrarySetup" CACHE PATH "USB4 root directory")
set(YOLO_ROOT "C:/darknet" CACHE PATH "YOLO/Darknet root directory")
set(MATLAB_ROOT "C:/Program Files/MATLAB/R2022b" CACHE PATH "MATLAB root directory")
```

Alternatively, you can set these paths via CMake GUI or command line without editing the file.

## Building with CMake (Command Line)

### Step 1: Create a build directory

```powershell
cd c:\Users\73856\Documents\PlatformIO\Projects\Senior-Design---Fly-Gantry\gantry\fly_gantry_v2
mkdir build
cd build
```

### Step 2: Configure the project

For Release build:
```powershell
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
```

For Debug build:
```powershell
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Debug
```

If using Visual Studio 2019:
```powershell
cmake .. -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Release
```

### Step 3: Build the project

```powershell
cmake --build . --config Release
```

Or for Debug:
```powershell
cmake --build . --config Debug
```

### Step 4: Run the executable

The executable will be in the `build/bin/Release` or `build/bin/Debug` directory:

```powershell
.\bin\Release\FlyGantry.exe
```

## Building with CMake GUI

1. Open CMake GUI
2. Set "Where is the source code" to: `c:\Users\73856\Documents\PlatformIO\Projects\Senior-Design---Fly-Gantry\gantry\fly_gantry_v2`
3. Set "Where to build the binaries" to: `c:\Users\73856\Documents\PlatformIO\Projects\Senior-Design---Fly-Gantry\gantry\fly_gantry_v2\build`
4. Click "Configure"
5. Select your Visual Studio version and "x64" platform
6. Adjust any SDK paths that are incorrect (red entries)
7. Click "Configure" again until no red entries remain
8. Click "Generate"
9. Click "Open Project" to open in Visual Studio
10. Build the solution in Visual Studio (F7 or Build > Build Solution)

## Building with Visual Studio directly

After running CMake, you can open the generated solution file:

```powershell
cd build
start FlyGantry.sln
```

Then build using Visual Studio's interface.

## Setting Custom SDK Paths

You can override SDK paths without editing CMakeLists.txt:

```powershell
cmake .. -G "Visual Studio 17 2022" -A x64 ^
  -DPYLON_ROOT="C:/My/Custom/Path/pylon" ^
  -DYOLO_ROOT="C:/My/Custom/Path/darknet"
```

## Troubleshooting

### OpenCV not found

If CMake cannot find OpenCV, set the OpenCV_DIR variable:

```powershell
cmake .. -DOpenCV_DIR="C:/SDK/opencv/build"
```

Or install via vcpkg and use the toolchain file:

```powershell
cmake .. -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

### Pylon library naming

The Pylon library names in CMakeLists.txt assume version 7.4. If you have a different version, check the actual library names in your Pylon installation at:
- `C:/Program Files/Basler/pylon X/lib/x64`

And adjust the library names in CMakeLists.txt accordingly (search for `PylonBase_v7_4_MD`).

### Missing DLLs

The CMakeLists.txt includes post-build commands to copy DLLs to the output directory. If the executable fails to run due to missing DLLs, check that:
1. The SDK paths are correct
2. The DLL names match your SDK versions
3. The DLLs exist in the expected locations

You can manually copy required DLLs to the same directory as the executable.

## Notes

- The project requires 64-bit (x64) architecture for all SDKs
- Make sure all SDK paths use forward slashes (/) or escaped backslashes (\\\\) in CMakeLists.txt
- The executable requires all DLLs to be in the same directory or in the system PATH
- Configuration files (OptoCenter.txt, etc.) should be in the same directory as the executable

## Clean Build

To perform a clean build, delete the build directory and start over:

```powershell
cd c:\Users\73856\Documents\PlatformIO\Projects\Senior-Design---Fly-Gantry\gantry\fly_gantry_v2
Remove-Item -Recurse -Force build
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```
