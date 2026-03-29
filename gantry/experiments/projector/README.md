# DLP LightCrafter 4500
----
Dependencies that were part of the SDK (no separate install):
- GLFW 3.0.4 (in `3rd_party/`)
- HIDAPI (in `3rd_party/`)
- ASIO 1.10.4 (in `3rd_party/`)
----
## Necessary Installations
### Firmware
- DLPR350PROM — DLPC350 Configuration and Support Firmware v2.0
  - https://www.ti.com/tool/DLPR350
----
### Software
- **Visual Studio 2022 Build Tools**: provides MSVC compiler that easily integrates with CMake files on Windows; does not require full Visual Studio IDE installation
  - To install the 2022 Build Tools, first create a Microsoft account (if you do not already have one). Proceed to the Visual Studio Subscriptions portal and filter for 2022 Build Tools.
  - https://go.microsoft.com/fwlink/?linkid=836911
- **CMake** (use binary distribution): generates native build environment for automated testing, packaging, and configurations
  - https://cmake.org/download/
- **OpenCV** 4.12.0: open-source library that provides tools and algorithms for image processing, computer vision, and related work
  - https://opencv.org/releases/
----
### Integrating Installations
- DLPR350 Firmware
  - `dlpr350prom_v2.0.0.bin` — downloaded from ti.com under DLPR350 downloads, placed in `resources/lcr4500/` of SDK directory
    - Relative path already specified in `include/dlp_platforms/lightcrafter_4500/lcr4500.hpp` (line 538)
- OpenCV DLL
  - After **successful** SDK build: `opencv_world4120.dll` — copied from `\path\to\opencv\build\x64\vc16\bin\` to `build\bin\Release\` in SDK directory
- CMake
  - Ensure environment variables updated for CMake
- Build, compile, and run executables directly via **x64 Native Tools Command Prompt for VS 2022** terminal (`cd` into SDK directory)
----
### Test Grid Projection
In `CMakeLists.txt` in the SDK directory, update the path to `document.cpp` depending on where it is stored locally on your system (lines 335-337)
```
# Test grid executable
add_executable(test_grid "/path/to/Senior-Design-Fly-Gantry-Drexel-2026/gantry/experiments/projector/document.cpp")
target_link_libraries(test_grid DLP_SDK)
target_link_libraries(test_grid ${LIBS})
```
Build SDK using the following command. Update the OpenCV build directory path depending on where you have stored it locally. Additionally, `DDLP_BUILD_PG_FLYCAP2_C_CAMERA_MODULE` is currently set to OFF to avoid extraneous errors/warnings related to the camera.
```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 ^
-DOpenCV_DIR="\path\to\opencv\build" ^
-DDLP_BUILD_PG_FLYCAP2_C_CAMERA_MODULE=OFF
```
Build files have now been generated in `gantry/experiments/projector/DLP-ALC-LIGHTCRAFTER-SDK/build`. Make sure to provide the OpenCV DLL to the build folder (as mentioned above) before proceeding.

Compile test grid simulation:
```
cmake --build build --config Release --target test_grid
```

Run `test_grid.exe` to generate and project image:
```
build\bin\Release\test_grid.exe
```

Check for `grid_test.png` — it should appear in SDK directory.

Uncomment safe shutdown section of `main` to disconnect from the projector.
