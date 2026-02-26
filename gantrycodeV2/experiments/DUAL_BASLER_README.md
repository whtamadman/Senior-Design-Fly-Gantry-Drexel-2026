# Dual Basler Camera Display - Quick Guide

This program displays two Basler cameras simultaneously with index selection.

## What You Need

- **2 Basler cameras** connected via USB
- **Pylon SDK** installed
- **OpenCV** installed
- **Visual Studio** (C++ compiler)

## Quick Start

1. **Build the program**:
   ```batch
   build_dual.bat
   ```

2. **Run the program**:
   ```batch
   run_dual_basler.bat
   ```

3. **Select your cameras**:
   ```
   === Basler Cameras Found ===
   Total Basler cameras: 2
     [0] Basler acA1920-40um (Serial: 12345678)
     [1] Basler acA2040-25um (Serial: 87654321)
   
   Enter Camera 1 index (default 0): 0
   Enter Camera 2 index (default 1): 1
   ```

4. **Two windows will appear** showing both camera feeds

5. **Press ESC** in either window to exit

## Key Features

### Automatic Camera Enumeration
The program automatically finds all Basler cameras and shows you:
- Index number [0], [1], [2], etc.
- Camera model name
- Serial number

### Index Selection
You select which camera to use by entering its index number. This is useful when:
- You have more than 2 cameras connected
- You want to use specific cameras
- Cameras are connected in different orders

### Dual Display
Both cameras run in parallel threads, capturing frames simultaneously and displaying them in separate windows.

### Same Settings for Both
Currently, both cameras use the same configuration:
- **Resolution**: 592 × 600 pixels
- **Exposure**: 1000 μs (1 ms)
- **Offset**: X=112, Y=16
- **Features**: Horizontal flip, chunk mode with timestamps

## How It Works

### Thread Architecture
```
Main Thread
├── Display Loop (shows both windows)
├── Camera 1 Thread
│   └── Captures frames → camera1FrameQueue
└── Camera 2 Thread
    └── Captures frames → camera2FrameQueue
```

### Code Structure

**Camera Enumeration** (Lines 137-169):
```cpp
DeviceInfoList_t devices;
CTlFactory::GetInstance().EnumerateDevices(devices);
for (size_t i = 0; i < devices.size(); i++) {
    cout << "[" << i << "] " << devices[i].GetFriendlyName() ...
}
```

**Camera Selection** (Lines 172-230):
```cpp
// User selects index
int cameraIndex = 0;  // from user input

// Create camera with that index
CBaslerUsbInstantCamera camera(
    CTlFactory::GetInstance().CreateDevice(devices[cameraIndex])
);
```

**Separate Event Handlers**:
- `CCamera1ImageHandler` - Processes Camera 1 frames
- `CCamera2ImageHandler` - Processes Camera 2 frames

Each handler pushes frames to its own queue for display.

## Customizing Camera Settings

### Change Resolution for One Camera

Edit the camera thread functions (lines 172-230 for Camera 1, 233-295 for Camera 2):

```cpp
// Camera 1 - keep at 592x600
camera.Width.SetValue(592);
camera.Height.SetValue(600);
```

```cpp
// Camera 2 - change to different resolution
camera.Width.SetValue(1920);
camera.Height.SetValue(1080);
camera.OffsetX.SetValue(0);
camera.OffsetY.SetValue(0);
```

### Change Exposure

```cpp
// Camera 1 - shorter exposure
camera.ExposureTime.SetValue(500.0);  // 0.5ms

// Camera 2 - longer exposure
camera.ExposureTime.SetValue(2000.0);  // 2ms
```

### Disable Horizontal Flip

```cpp
camera.ReverseX.SetValue(false);  // Change from true to false
```

## Troubleshooting

### "Need at least 2 Basler cameras connected!"
**Problem**: Only 1 or 0 cameras detected.

**Solutions**:
- Check both cameras are connected via USB
- Use `pylon Viewer` to verify cameras are detected
- Try different USB ports
- Restart computer

### "Camera index X out of range!"
**Problem**: Selected index doesn't exist.

**Solutions**:
- Check the camera list - only indices shown are valid
- Use lower index (0, 1, etc.)
- Make sure all cameras are connected before starting

### "Both cameras set to same index"
**Problem**: You selected the same camera for both displays.

**Solutions**:
- This creates a conflict - one camera can't be opened twice
- Use different indices (e.g., Camera 1 = 0, Camera 2 = 1)
- The program will warn you and ask to confirm

### One window not updating
**Problem**: Only one camera shows frames.

**Solutions**:
- Check console for error messages
- Verify both camera threads started successfully
- USB bandwidth might be limited - try different USB controllers
- Check that both cameras are powered

### Low frame rate
**Problem**: Cameras running slowly.

**Solutions**:
- Use USB 3.0 ports (blue connectors)
- Reduce resolution if needed
- Check USB bandwidth (two high-res cameras need lots of bandwidth)
- Connect cameras to different USB controllers

## Comparison with Original Code

| Feature | Original Code | This Program |
|---------|--------------|--------------|
| Camera count | 1 Basler + 1 Spinnaker | 2 Basler |
| Selection | Always first device | Index selection |
| Enumeration | No list shown | Shows all cameras |
| Purpose | Full gantry control | Camera testing |

## Advanced Usage

### Select by Serial Number

Instead of index, you can modify the code to select by serial number:

```cpp
// In Camera1Thread or Camera2Thread:
string targetSerial = "12345678";  // Your camera's serial
CDeviceInfo info;
info.SetSerialNumber(targetSerial.c_str());
CBaslerUsbInstantCamera camera(
    CTlFactory::GetInstance().CreateDevice(info)
);
```

### Save Frames to Disk

Add to the event handlers:

```cpp
virtual void OnImageGrabbed(...) {
    // ... existing code ...
    
    // Save every 100th frame
    if (camera1Data.frameCount % 100 == 0) {
        string filename = "camera1_frame_" + 
                         to_string(camera1Data.frameCount) + ".png";
        imwrite(filename, opencvImage);
    }
}
```

### Record Video

```cpp
// In main(), before display loop:
VideoWriter video1("camera1.avi", 
                  VideoWriter::fourcc('M','J','P','G'), 
                  30, Size(592, 600), false);

// In display loop:
if (camera1FrameQueue.try_pop(camera1Frame)) {
    video1.write(camera1Frame);
    imshow("Camera 1", camera1Frame);
}
```

## What's Different from Single Camera?

### Two Event Handlers
- Each camera needs its own event handler class
- Separate frame counters and data structures
- Prevents conflicts between cameras

### Two Threads
- Each camera runs in its own thread
- Allows parallel capture without blocking
- Better performance than sequential capture

### Two Queues
- `camera1FrameQueue` and `camera2FrameQueue`
- Decouples capture from display
- Display speed doesn't affect capture rate

## Next Steps

1. **Test with your cameras** - Verify both work
2. **Adjust settings** - Experiment with resolution, exposure
3. **Integrate** - Use this pattern in your main application
4. **Extend** - Add features like recording, processing, etc.

For more examples, see:
- [bottom_camera_display.cpp](bottom_camera_display.cpp) - Simpler single camera
- [dual_camera_display.cpp](dual_camera_display.cpp) - Basler + Spinnaker version
- [OVERVIEW.md](OVERVIEW.md) - Comparison of all programs
