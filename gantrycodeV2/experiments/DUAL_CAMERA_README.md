# Dual Camera Display - Usage Guide

This program displays both the Basler (bottom) and Spinnaker (top) cameras simultaneously, with the ability to select cameras by index.

## Features

- **Camera Enumeration**: Lists all available cameras from both manufacturers
- **Index Selection**: Choose which camera to use when multiple cameras of the same type are connected
- **Dual Display**: Shows both camera feeds in separate windows
- **Multi-threaded**: Runs cameras in parallel threads for optimal performance

## How Camera Selection Works

### Single Camera Type (Original simple code)
```cpp
// Gets the FIRST camera found
CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
```

### Multiple Cameras (This program)
```cpp
// List all cameras
DeviceInfoList_t devices;
CTlFactory::GetInstance().EnumerateDevices(devices);

// Select camera by index
CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateDevice(devices[index]));
```

## Camera Configuration

### Basler Camera (Bottom View)
- **Resolution**: 592 × 600 pixels
- **Exposure**: 1000 μs (1 ms)
- **Offset**: X=112, Y=16
- **Features**: Horizontal flip, chunk mode with timestamps

### Spinnaker Camera (Top View)  
- **Resolution**: 864 × 864 pixels
- **Offset**: X=560, Y=260
- **Mode**: Continuous acquisition

## Building the Project

### Prerequisites
- Visual Studio 2022 (or Build Tools)
- OpenCV
- Pylon SDK (Basler)
- **Spinnaker SDK (FLIR/Point Grey)** - Required for dual camera!

### Install Spinnaker SDK
1. Download from: https://www.flir.com/products/spinnaker-sdk/
2. Run installer
3. Set environment variable: `SPINNAKER_ROOT=C:\Program Files\FLIR Systems\Spinnaker`

### Build Commands
```powershell
# Option 1: Build both programs using the dual CMakeLists
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Option 2: Use the provided batch file (after updating it for dual build)
.\build.bat

# Executables will be in:
# build/Release/bottom_camera_display.exe  (Basler only)
# build/Release/dual_camera_display.exe    (Both cameras)
```

## Running the Program

### Step 1: Connect Cameras
- Connect Basler USB camera
- Connect Point Grey/FLIR camera

### Step 2: Verify Cameras
You can test each camera individually:
- **Basler**: Use "pylon Viewer" (comes with Pylon SDK)
- **Spinnaker**: Use "SpinView" (comes with Spinnaker SDK)

### Step 3: Run the Program
```powershell
cd build\Release
.\dual_camera_display.exe
```

### Step 4: Select Cameras
The program will show:
```
=== Basler Cameras Found ===
Total Basler cameras: 1
  [0] Basler acA1920-40um (Serial: 12345678)

=== Spinnaker Cameras Found ===
Total Spinnaker cameras: 1
  [0] Blackfly S BFS-U3-20S4M (Serial: 87654321)

Enter Basler camera index (default 0): 0
Enter Spinnaker camera index (default 0): 0
```

Just press Enter to use defaults (index 0), or enter a different number if you have multiple cameras.

## Program Architecture

### Thread Structure
```
Main Thread
├── Display Loop (handles both windows)
├── Basler Camera Thread
│   └── Frame capture → baslerFrameQueue
└── Spinnaker Camera Thread
    └── Frame capture → spinnakerFrameQueue
```

### Data Flow
```
Basler Camera                    Spinnaker Camera
     ↓                                ↓
OnImageGrabbed callback          GetNextImage()
     ↓                                ↓
Convert to Mat                   Convert to Mat
     ↓                                ↓
baslerFrameQueue                 spinnakerFrameQueue
     ↓                                ↓
     └────────────┬───────────────────┘
                  ↓
           Main Display Loop
           ├── imshow("Basler...")
           └── imshow("Spinnaker...")
```

## If You Only Have One Camera Type

### Only Basler Camera
Use the simpler program:
```powershell
.\bottom_camera_display.exe
```

### Only Spinnaker Camera
Modify `dual_camera_display.cpp`:
- Comment out `baslerThread` related code
- Only run `spinnakerThread`

## Selecting Specific Cameras

### By Index (What this program does)
```cpp
// Basler
DeviceInfoList_t devices;
CTlFactory::GetInstance().EnumerateDevices(devices);
CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateDevice(devices[1])); // Second camera

// Spinnaker
CameraList camList = system->GetCameras();
CameraPtr pCam = camList.GetByIndex(1); // Second camera
```

### By Serial Number
```cpp
// Basler
CDeviceInfo info;
info.SetSerialNumber("12345678");
CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateDevice(info));

// Spinnaker (more complex - need to iterate through list)
for (unsigned int i = 0; i < camList.GetSize(); i++)
{
    CameraPtr cam = camList.GetByIndex(i);
    INodeMap& nodeMap = cam->GetTLDeviceNodeMap();
    CStringPtr serial = nodeMap.GetNode("DeviceSerialNumber");
    if (serial->ToString() == "87654321")
    {
        pCam = cam;
        break;
    }
}
```

## Troubleshooting

### "Spinnaker camera index X out of range"
- Only X cameras detected. Check camera connection
- Try SpinView to verify camera is detected

### "Basler camera index X out of range"
- Only X cameras detected. Check USB connection
- Try pylon Viewer to verify camera is detected

### Cameras from both SDKs not showing
- Each SDK only sees its manufacturer's cameras
- Spinnaker only sees FLIR/Point Grey cameras
- Pylon only sees Basler cameras
- This is normal and expected!

### One window not updating
- Check that both camera threads are running
- Look for error messages in console
- Verify camera permissions and USB bandwidth

## Key Code Sections

### Camera Enumeration (Lines 93-148)
- `ListBaslerCameras()` - Shows all Basler cameras
- `ListSpinnakerCameras()` - Shows all Spinnaker cameras

### Camera Threads (Lines 150-310)
- `BaslerCameraThread()` - Captures Basler frames
- `SpinnakerCameraThread()` - Captures Spinnaker frames

### Main Loop (Lines 350-390)
- Displays frames from both queues
- Handles ESC key to exit

## Comparison with Original Code

| Feature | Original (gantrycodeV2.cpp) | This Program |
|---------|----------------------------|--------------|
| Camera selection | Always first device | User selects by index |
| Camera enumeration | No list shown | Lists all cameras |
| Threading | OpenMP sections | std::thread |
| Display | Part of complex workflow | Dedicated display program |
| Purpose | Full gantry control system | Camera testing/viewing |

## Next Steps

After verifying cameras work:
1. Use this as a template for your own multi-camera code
2. Integrate index selection into your main gantry code
3. Add serial number selection for production environments
4. Implement camera-specific error handling

