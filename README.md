# NeuroTrack: A Platform for Fly Brain Function (Drexel 2026 COE Senior Design)

## Project Overview
NeuroTrack is an updated robotic gantry model made in association with Bhandawat Laboratory at Drexel University to improve data quality in fruitfly research via enhanced hardware from Zaber Technologies integrated with open-source software.

This is a comprehensive automated system for real-time behavioral tracking and visual stimulus control in fly experiments. The system integrates dual-camera vision, motion control, projection mapping, and data collection into a unified C++ application designed for high-speed, coordinated control of experimental apparatus.

## Purpose

The fly gantry system enables researchers to:
- Track fly position and orientation in real-time using dual-camera setup
- Deliver precisely-timed visual stimuli via DLP projector
- Control motion platform (Zaber gantry) for targeted stimulus delivery
- Collect comprehensive experimental data in an organized, structured format
- Detect fly behavioral states using YOLO-based computer vision

## Directory Structure

### `/gantry/`
Main application code and experiments

#### `/gantry/fly_gantry_v3/`
**Primary application executable**
- **Core Application Files:**
  - `gantrycodeV3.cpp` - Main application with camera threads, UI, gantry control, and data collection
  - `pch.h/cpp` - Precompiled headers
  
- **Data Persistence:**
  - `MatlabSaveData.cpp/h` - MAT file writing via MATLAB C API
  - `BinarySaveData.cpp/h` - Binary data export
  
- **UI & Hardware:**
  - `WindowManager.cpp/h` - Camera feed display and mouse controls
  - `filter.cpp/h` - Image processing filters
  - `position.cpp/h` - Position tracking data structures
  - `HardwareTriggerConfiguration.h` - Trigger synchronization config
  
- **Build System:**
  - `build.bat` - Windows build script with dependency validation
  - `CMakeLists.txt` - CMake configuration for all SDK paths
  - `build/` - Build output directory with Visual Studio project files

- **Dependencies:**
  - `ZaberMotionLibrary/` - Zaber gantry motion control SDK
  - `DLP-ALC-LIGHTCRAFTER-SDK/` - TI DLP projector SDK (utilize include files specific to DLP 4500)

#### `/gantry/experiments/cameras/`
Camera calibration and dual-camera experiments
- `camera_alignment_*.py` - Python utilities for camera alignment
- `detect_basler_cameras.py` - Camera discovery and initialization
- `dual_basler_display.cpp` - Dual camera display application
- `run_dual_basler.bat` - Build script for camera experiments
- `projector_camera_mapping.m` - MATLAB mapping between camera and projector coordinates

#### `/gantry/experiments/gantry/`
Zaber gantry motion control testing
- `gantry.cpp/h` - Low-level gantry control and ASCII communication
- `test_gantry.cpp` - Motion control unit tests
- `zaber/` - Zaber library integration

#### `/gantry/experiments/projector/`
DLP projector calibration and control
- `calibration_test.cpp` - Projector calibration tests
- `camera_to_projector_matrix.csv` - Calibration data
- `DLP-ALC-LIGHTCRAFTER-SDK/` - Texas Instruments DLP SDK
- `document.cpp` - Projector documentation/utilities

## Technology Stack

### Hardware
- **Cameras:** Basler Pylon USB cameras (bottom + side)
- **Motion Control:** Zaber gantry system (ASCII protocol over COM4)
- **Projector:** TI DLP LightCrafter 4500 (DLP ALC SDK)
- **Computing:** Windows PC with Visual Studio 2022

### Software Stack
- **Language:** C++17
- **Build System:** CMake 3.15+
- **Video Processing:** OpenCV (4.x)
- **Parallel Computing:** OpenMP
- **Camera SDK:** Pylon (Basler)
- **Fly Detection:** YOLO v4 (Darknet-based)
- **Data Persistence:** 
  - MATLAB C API (R2026a) for MAT files
  - CSV for metadata
  - MJPEG AVI for video
- **Package Manager:** vcpkg

### SDK Dependencies
- **Pylon SDK:** `C:/Program Files/Basler/pylon/Development`
- **MATLAB R2026a:** `C:/Program Files/MATLAB/R2026a`
- **Zaber Motion Library:** `gantry/fly_gantry_v3/ZaberMotionLibrary/`
- **DLP SDK:** `gantry/experiments/projector/DLP-ALC-LIGHTCRAFTER-SDK/`
- **Darknet/YOLO:** `C:/Users/SeniorDesign/Downloads/darknet-master/`

## Data Output Structure

Experimental data is organized by date and run timestamp:
```
Documents/Data/
  YYYYMMDD/              # Date folder
    YYYYMMDDHHMM/       # Run timestamp folder
      run_manifest.txt   # File listing and metadata
      video_bottom.avi   # Raw bottom camera video
      video_bottom_yolo.avi  # Annotated fly detection
      video_side.avi     # Side camera video
      frames.txt         # Per-frame data (timing, position, YOLO state)
      frames.mat         # MATLAB data structure (auto-saved every 500 frames)
      metadata.csv       # Experimental metadata
```

### Data Files Generated
- **`.txt`** - Frame-by-frame data with headers (frame number, timestamp, center-of-mass, encoder position, YOLO detection state, stimulus voltage)
- **`.avi`** - MJPEG-compressed video streams (bottom raw, side raw, YOLO-annotated)
- **`.mat`** - MATLAB binary format with complete frame vectors (18 channels including fly detection, stimulus state, motor position)
- **`_meta.csv`** - Arena dimensions, stimulus parameters, experimental notes

## Building the Project

### Prerequisites
1. **Visual Studio 2022** with C++ workload
2. **CMake 3.15+**
3. **vcpkg** for dependency management
4. **SDKs installed** at paths defined in `CMakeLists.txt`

### Build Steps
```bash
cd gantry/fly_gantry_v3
.\build.bat              # Configure and build (Release by default)
# Or specify Debug:
.\build.bat Debug
```

Build outputs:
- Executable: `build/bin/FlyGantry.exe`
- Libraries: `build/lib/`

## Running the Application

```bash
cd gantry/fly_gantry_v3/build/bin
.\FlyGantry.exe
```

### Runtime Controls
- **S** - Toggle data collection (start/stop recording)
- **STOP Button** - Halt gantry motion and data collection (keeps app running)
- **EXIT Button** - Close application and save final data
- **Mouse Clicks** - Select stimuli and trigger projector patterns
- Run timer displayed in UI shows elapsed time while collecting data

## Key Features

**Real-time dual-camera Vision**
- Dual Basler cameras (bottom + side) at high frame rates
- Synchronized capture with projector stimulus timing

**Fly Detection & Tracking**
- YOLO v4-based body/head segmentation
- Center-of-mass calculation per frame
- Behavioral state classification

**Motion Control**
- Zaber gantry with X/Y/Z axes
- Real-time position feedback via quadrature encoders
- ASCII protocol over COM4

**Visual Stimulus Delivery**
- DLP projector arena mapping
- Synchronized projector patterns with camera frames
- Stimulus timing and voltage logging

**Comprehensive Data Logging**
- Per-frame data collection (25+ parameters)
- Automatic MATLAB export
- Video with flying detection overlays
- Timestamped metadata

**Organized Data Management**
- Automatic date/run-based folder hierarchy
- File manifest with complete output listing
- Immediate file creation for real-time monitoring

## Project Status

- **V3 (Current):** Full-featured implementation with dual-camera, projector, gantry, YOLO detection, and comprehensive data export
- **V2 (Legacy):** Previous iteration; superseded by V3
- **Experiments:** Modular camera calibration, gantry testing, and projector alignment utilities

## Contact & References

**Senior Design:** Drexel University 2026

**Primary Application:** `gantry/fly_gantry_v3/gantrycodeV3.cpp`

**Build Script:** `gantry/fly_gantry_v3/build.bat`
