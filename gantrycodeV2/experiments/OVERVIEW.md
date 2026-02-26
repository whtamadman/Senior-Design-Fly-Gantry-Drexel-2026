# Camera Display Programs - Quick Reference

This folder contains three camera display programs with different capabilities.

## Programs Available

### 1. Bottom Camera Display (Simple)
**File**: `bottom_camera_display.cpp`

**What it does**:
- Displays ONLY the Basler bottom camera
- Always selects the first Basler camera found
- Simpler code, easier to understand

**Use when**:
- You only have one Basler camera
- Testing Basler camera setup
- Learning how the camera system works

**Build**: `build.bat`
**Run**: `run_camera.bat`

---

### 2. Dual Basler Camera Display (Two Basler)
**File**: `dual_basler_display.cpp`

**What it does**:
- Displays TWO Basler cameras simultaneously
- Lists all available Basler cameras
- Lets you select cameras by index number
- Shows both feeds in separate windows

**Use when**:
- You have two Basler cameras connected
- Need to view both cameras at once
- Testing dual Basler camera setup
- Understanding how to handle multiple cameras of same type

**Build**: `build_dual.bat`
**Run**: `run_dual_basler.bat`

---

### 3. Dual Camera Display (Basler + Spinnaker)
**File**: `dual_camera_display.cpp`

**What it does**:
- Displays BOTH Basler (bottom) AND Spinnaker (top) cameras
- Lists all available cameras from both manufacturers
- Lets you select cameras by index number
- Shows both feeds simultaneously in separate windows

**Use when**:
- You have both camera types connected
- Need to select specific cameras when multiple are present
- Testing the full dual-camera setup
- Understanding how different SDKs handle cameras

**Build**: `build_dual.bat`
**Run**: `run_dual_camera.bat`

---

## Quick Start

### For Single Basler Camera
```batch
1. install_dependencies.bat   (first time only)
2. build.bat
3. run_camera.bat
```

### For Two Basler Cameras
```batch
1. install_dependencies.bat   (first time only)
2. build_dual.bat
3. run_dual_basler.bat
```

### For Basler + Spinnaker Cameras
```batch
1. install_dependencies.bat      (first time only)
2. Install Spinnaker SDK manually (see DUAL_CAMERA_README.md)
3. build_dual.bat
4. run_dual_camera.bat
```

---

## File Reference

| File | Purpose |
|------|---------|
| `bottom_camera_display.cpp` | Single Basler camera viewer |
| `dual_basler_display.cpp` | Two Basler cameras with index selection |
| `dual_camera_display.cpp` | Basler + Spinnaker with index selection |
| `HardwareTriggerConfiguration.h` | Camera trigger config (in parent folder) |
| `CMakeLists.txt` | Build config for single camera |
| `CMakeLists_dual.txt` | Build config for all programs |
| `install_dependencies.bat` | Install Pylon, OpenCV, VS |
| `install_dependencies.ps1` | PowerShell installation script |
| `build.bat` | Build single camera program |
| `build_dual.bat` | Build all camera programs |
| `run_camera.bat` | Run single camera program |
| `run_dual_basler.bat` | Run dual Basler program |
| `run_dual_camera.bat` | Run Basler+Spinnaker program |
| `verify_setup.bat` | Check if files are in place |
| `README.md` | Setup guide for single camera |
| `DUAL_CAMERA_README.md` | Detailed guide for Basler+Spinnaker |
| `OVERVIEW.md` | This file - program comparison |

---

## Key Differences

### Camera Detection

**Simple (bottom_camera_display.cpp)**:
```cpp
CBaslerUsbInstantCamera camera(
    CTlFactory::GetInstance().CreateFirstDevice()  // Always gets first camera
);
```

**Advanced (dual_camera_display.cpp)**:
```cpp
// List all cameras
DeviceInfoList_t devices;
CTlFactory::GetInstance().EnumerateDevices(devices);

// Let user choose
int index = 0;  // or get from user input

// Create camera with selected index
CBaslerUsbInstantCamera camera(
    CTlFactory::GetInstance().CreateDevice(devices[index])
);
```

### Dependencies

| Dependency | Bottom Camera | Dual Basler | Basler+Spinnaker |
|------------|---------------|-------------|------------------|
| Visual Studio | ✓ Required | ✓ Required | ✓ Required |
| OpenCV | ✓ Required | ✓ Required | ✓ Required |
| Pylon SDK | ✓ Required | ✓ Required | ✓ Required |
| **Spinnaker SDK** | ✗ Not needed | ✗ Not needed | ✓ **Required** |

---

## Troubleshooting

### "Camera not found"
1. Check USB connection
2. Try camera manufacturer's viewer:
   - Basler: pylon Viewer
   - Spinnaker: SpinView
3. Try different USB port (USB 3.0 preferred)

### "Spinnaker SDK not found" (dual camera only)
1. Download: https://www.flir.com/products/spinnaker-sdk/
2. Install
3. Set environment variable: `SPINNAKER_ROOT=C:\Program Files\FLIR Systems\Spinnaker`
4. Restart computer

### "Build failed"
1. Run `verify_setup.bat` to check files
2. Make sure all dependencies installed
3. Check error messages for missing libraries
4. See README.md for manual build instructions

---

## Understanding the Code

### How Original Code Finds Cameras (from gantrycodeV2.cpp)

**Top Camera (Spinnaker)**:
```cpp
SystemPtr system = System::GetInstance();
CameraList camList = system->GetCameras();
CameraPtr pCam = camList.GetByIndex(0);  // First Spinnaker camera
```

**Bottom Camera (Pylon)**:
```cpp
CBaslerUsbInstantCamera camera(
    CTlFactory::GetInstance().CreateFirstDevice()  // First Basler camera
);
```

**Why no conflict?**
- Spinnaker SDK only sees FLIR/Point Grey cameras
- Pylon SDK only sees Basler cameras
- Each SDK maintains its own device list

### How Dual Camera Program Improves This

1. **Lists all cameras** before selecting
2. **Lets you choose** which camera by index
3. **Shows camera info** (model name, serial number)
4. **Handles errors** if index is out of range

This is essential when:
- Multiple Basler cameras connected
- Multiple Spinnaker cameras connected
- Need specific camera for specific purpose
- Cameras might be connected in different order

---

## Next Steps

1. **Start simple**: Test with `bottom_camera_display` first
2. **Verify each camera**: Use manufacturer's viewer software
3. **Move to dual**: Once both cameras work individually
4. **Integrate**: Use techniques from dual_camera_display in your main code

For detailed instructions, see:
- [README.md](README.md) - Single camera setup
- [DUAL_CAMERA_README.md](DUAL_CAMERA_README.md) - Dual camera setup
