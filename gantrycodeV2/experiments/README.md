# Bottom Camera Display - Setup Guide

This guide will help you install all dependencies and build the bottom camera display application.

**Note:** This project is located in the `experiments` folder. Make sure you're in this directory when running the scripts.

## Quick Start

### Step 0: Verify Setup
Run `verify_setup.bat` to ensure all required files are present.

### Step 1: Install Dependencies

**Option A - Automated (Recommended):**
1. Right-click `install_dependencies.ps1`
2. Select "Run with PowerShell" or "Run as Administrator"
3. Follow the prompts

**Option B - If PowerShell is blocked:**
1. Open PowerShell as Administrator
2. Run: `Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser`
3. Run: `.\install_dependencies.ps1`

### Step 2: Build the Project

After dependencies are installed, choose one method:

#### Method 1: CMake (Easiest)
```powershell
# Note: Make sure you're in the experiments folder
cd experiments

# Install CMake if you don't have it
choco install cmake -y

# Build the project
mkdir build
cd build
cmake ..
cmake --build . --config Release

# Run
.\Release\bottom_camera_display.exe
```

#### Method 2: Visual Studio
1. Open Visual Studio 2022
2. File → Open → CMake → Select CMakeLists.txt
3. Build → Build All (Ctrl+Shift+B)
4. Run (F5)

## Required Dependencies

✓ **Visual Studio 2022** (or Build Tools) - For C++ compiler and `concurrent_queue`
✓ **OpenCV** - For image display (`imshow`, `Mat`, etc.)
✓ **Pylon SDK** - For Basler camera control
✓ **Basler USB Camera** - Hardware must be connected

## Manual Installation

If the automated script fails, install manually:

### 1. Visual Studio
Download from: https://visualstudio.microsoft.com/downloads/
- Choose "Visual Studio 2022 Community" (free)
- During installation, select "Desktop development with C++"

### 2. OpenCV
Download from: https://opencv.org/releases/
- Extract to `C:\opencv`
- Set environment variable: `OpenCV_DIR = C:\opencv\build`
- Add to PATH: `C:\opencv\build\x64\vc16\bin`

### 3. Pylon SDK
Download from: https://www.baslerweb.com/en/downloads/software-downloads/
- Select "pylon Camera Software Suite" for Windows
- Run installer (it will set environment variables automatically)

### 4. CMake (Optional but recommended)
Download from: https://cmake.org/download/
Or via Chocolatey: `choco install cmake -y`

## Troubleshooting

### "Pylon SDK not found"
- Set environment variable: `PYLON_ROOT = C:\Program Files\Basler\pylon 7`
- Restart your computer

### "OpenCV not found"
- Set environment variable: `OpenCV_DIR = C:\opencv\build`
- Make sure OpenCV bin folder is in PATH

### "Camera not detected"
- Ensure Basler camera is connected via USB
- Check in Pylon Viewer (comes with Pylon SDK)
- Try a different USB port (USB 3.0 recommended)

### "concurrent_queue not found"
- Make sure you're using Visual Studio compiler (MSVC)
- Check that you have Desktop development with C++ workload installed

## Testing Camera Connection

Before running the program, test your camera with Pylon Viewer:
1. Open "pylon Viewer" from Start Menu
2. Your camera should appear in the device list
3. Click "Connect" and "Continuous Shot" to verify

## Building Without CMake

If you prefer to use Visual Studio directly without CMake:
1. Create a new C++ Console Application project
2. Add `bottom_camera_display.cpp` to the project
3. Configure include directories:
   - Right-click project → Properties → C/C++ → General → Additional Include Directories
   - Add: `$(PYLON_ROOT)\include`, `$(OpenCV_DIR)\include`, `.`
4. Configure library directories:
   - Properties → Linker → General → Additional Library Directories
   - Add: `$(PYLON_ROOT)\lib\x64`, `$(OpenCV_DIR)\x64\vc16\lib`
5. Add library dependencies:
   - Properties → Linker → Input → Additional Dependencies
   - Add: `PylonBase_v7_4.lib`, `PylonC_v7_3.lib`, `PylonUtility_v7_4.lib`, 
          `GenApi_MD_VC141_v3_1_Basler_pylon.lib`, `GCBase_MD_VC141_v3_1_Basler_pylon.lib`,
          `opencv_world4XX.lib` (replace XX with your version)

## Support

For more help:
- Pylon Documentation: https://docs.baslerweb.com/
- OpenCV Documentation: https://docs.opencv.org/
- CMake Documentation: https://cmake.org/documentation/

## Files Created by Installation Script

- `CMakeLists.txt` - CMake build configuration
- `BUILD_INSTRUCTIONS.txt` - Detailed build instructions
- `install_dependencies.ps1` - Installation script (you're reading the guide for this)
