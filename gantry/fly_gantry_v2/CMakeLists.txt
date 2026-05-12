cmake_minimum_required(VERSION 3.15)
project(FlyGantry VERSION 1.0 LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ============================================================================
# Find Required Packages
# ============================================================================

# Find OpenCV
find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc videoio imgcodecs)
if(OpenCV_FOUND)
    message(STATUS "OpenCV version: ${OpenCV_VERSION}")
    message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
endif()

# Find OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found")
endif()

# ============================================================================
# SDK Paths (Customizable - Edit these paths to match your system)
# ============================================================================

# NOTE: Spinnaker SDK removed - this version uses bottom camera only (Pylon/Basler)

# Pylon SDK (Basler camera)
set(PYLON_ROOT "C:/Program Files/Basler/pylon 7" CACHE PATH "Pylon SDK root directory")
set(PYLON_INCLUDE_DIR "${PYLON_ROOT}/include")
set(PYLON_LIB_DIR "${PYLON_ROOT}/lib/x64")

# NI-DAQmx
set(NIDAQMX_ROOT "C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C" CACHE PATH "NI-DAQmx root directory")
set(NIDAQMX_INCLUDE_DIR "${NIDAQMX_ROOT}/include")
set(NIDAQMX_LIB_DIR "${NIDAQMX_ROOT}/lib64/msvc")

# USB4 Decoder
set(USB4_ROOT "C:/Program Files/USB4/USB4DriverAndLibrarySetup" CACHE PATH "USB4 root directory")
set(USB4_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}") # USB4.h is in local directory
set(USB4_LIB_DIR "${USB4_ROOT}/X64")

# YOLO/Darknet
set(YOLO_ROOT "C:/darknet" CACHE PATH "YOLO/Darknet root directory")
set(YOLO_INCLUDE_DIR "${YOLO_ROOT}/include")
set(YOLO_LIB_DIR "${YOLO_ROOT}/build/darknet/x64")

# MATLAB
set(MATLAB_ROOT "C:/Program Files/MATLAB/R2022b" CACHE PATH "MATLAB root directory")
set(MATLAB_INCLUDE_DIR "${MATLAB_ROOT}/extern/include")
set(MATLAB_LIB_DIR "${MATLAB_ROOT}/extern/lib/win64/microsoft")

# ============================================================================
# Check if directories exist
# ============================================================================

if(NOT EXISTS ${PYLON_INCLUDE_DIR})
    message(WARNING "Pylon SDK not found at ${PYLON_ROOT}. Please set PYLON_ROOT correctly.")
endif()

if(NOT EXISTS ${NIDAQMX_INCLUDE_DIR})
    message(WARNING "NI-DAQmx not found at ${NIDAQMX_ROOT}. Please set NIDAQMX_ROOT correctly.")
endif()

if(NOT EXISTS ${USB4_LIB_DIR})
    message(WARNING "USB4 library not found at ${USB4_ROOT}. Please set USB4_ROOT correctly.")
endif()

if(NOT EXISTS ${YOLO_INCLUDE_DIR})
    message(WARNING "YOLO/Darknet not found at ${YOLO_ROOT}. Please set YOLO_ROOT correctly.")
endif()

if(NOT EXISTS ${MATLAB_INCLUDE_DIR})
    message(WARNING "MATLAB not found at ${MATLAB_ROOT}. Please set MATLAB_ROOT correctly.")
endif()

# ============================================================================
# Source Files
# ============================================================================

set(PROJECT_SOURCES
    gantrycodeV2.cpp
    pch.cpp
    gantry.cpp
    position.cpp
    filter.cpp
    topCamProc.cpp
    OptoStim.cpp
    WindowManager.cpp
    Calibration.cpp
    BinarySaveData.cpp
    MatlabSaveData.cpp
    Config.cpp
    matlab_i18n_init.c
)

set(PROJECT_HEADERS
    pch.h
    gantry.h
    position.h
    filter.h
    topCamProc.h
    OptoStim.h
    WindowManager.h
    Calibration.h
    flyViewStruc.h
    BinarySaveData.h
    MatlabSaveData.h
    Config.h
    USB4.h
    HardwareTriggerConfiguration.h
    matlab_i18n_init.h
)

# ============================================================================
# Create Executable
# ============================================================================

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# ============================================================================
# Include Directories
# ============================================================================

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${PYLON_INCLUDE_DIR}
    ${NIDAQMX_INCLUDE_DIR}
    ${USB4_INCLUDE_DIR}
    ${YOLO_INCLUDE_DIR}
    ${MATLAB_INCLUDE_DIR}
)

# ============================================================================
# Compiler Definitions
# ============================================================================

target_compile_definitions(${PROJECT_NAME} PRIVATE
    UNICODE
    _UNICODE
    $<$<CONFIG:Release>:NDEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
)

# Add Pylon specific definitions if on Windows
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PYLON_WIN_BUILD)
endif()

# ============================================================================
# Link Directories
# ============================================================================

target_link_directories(${PROJECT_NAME} PRIVATE
    ${PYLON_LIB_DIR}
    ${NIDAQMX_LIB_DIR}
    ${USB4_LIB_DIR}
    ${YOLO_LIB_DIR}
    ${MATLAB_LIB_DIR}
)

# ============================================================================
# Link Libraries
# ============================================================================

# OpenCV libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# OpenMP
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

# SDK Libraries (Debug configuration uses debug versions where applicable)
target_link_libraries(${PROJECT_NAME} PRIVATE
    # Pylon SDK (adjust library names based on your Pylon version)
    # Common Pylon libraries for USB cameras - used for bottom camera only
    $<$<CONFIG:Debug>:PylonBase_v7_4_MDd>
    $<$<CONFIG:Debug>:PylonC_v7_4_MDd>
    $<$<CONFIG:Debug>:PylonUtility_v7_4_MDd>
    $<$<CONFIG:Release>:PylonBase_v7_4_MD>
    $<$<CONFIG:Release>:PylonC_v7_4_MD>
    $<$<CONFIG:Release>:PylonUtility_v7_4_MD>
    
    # NI-DAQmx
    nidaqmx
    
    # USB4
    USB4
    
    # YOLO
    yolo_cpp_dll
    
    # MATLAB
    libmat
    libmx
    
    # Windows system libraries
    kernel32
    user32
    gdi32
    winspool
    comdlg32
    advapi32
    shell32
    ole32
    oleaut32
    uuid
    odbc32
    odbccp32
)

# ============================================================================
# Compiler Options
# ============================================================================

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W3                 # Warning level 3
        /MP                 # Multi-processor compilation
        /bigobj             # Increase number of sections in .obj file
        $<$<CONFIG:Release>:/O2>     # Optimize for speed
        $<$<CONFIG:Release>:/GL>     # Whole program optimization
    )
    
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/LTCG>   # Link-time code generation
    )
endif()

# ============================================================================
# Post-Build Commands (Copy DLLs to output directory)
# ============================================================================

# Function to copy DLLs if they exist
function(copy_dll_if_exists dll_path)
    if(EXISTS ${dll_path})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${dll_path}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "Copying ${dll_path}"
        )
    endif()
endfunction()

# Copy required DLLs to output directory
if(WIN32)
    # Pylon DLLs (adjust version numbers as needed) - for bottom camera
    file(GLOB PYLON_DLLS "${PYLON_ROOT}/Runtime/x64/*.dll")
    foreach(dll ${PYLON_DLLS})
        copy_dll_if_exists(${dll})
    endforeach()
    
    # NI-DAQmx DLL
    copy_dll_if_exists("${NIDAQMX_ROOT}/../../../Shared/nicaiu.dll")
    
    # USB4 DLL
    copy_dll_if_exists("${USB4_ROOT}/X64/USB4.dll")
    
    # YOLO DLL
    copy_dll_if_exists("${YOLO_ROOT}/build/darknet/x64/yolo_cpp_dll.dll")
    
    # MATLAB DLLs
    copy_dll_if_exists("${MATLAB_ROOT}/bin/win64/libmat.dll")
    copy_dll_if_exists("${MATLAB_ROOT}/bin/win64/libmx.dll")
    copy_dll_if_exists("${MATLAB_ROOT}/bin/win64/libmex.dll")
endif()

# ============================================================================
# Installation
# ============================================================================

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# ============================================================================
# Print Configuration Summary
# ============================================================================

message(STATUS "")
message(STATUS "========================================")
message(STATUS "Fly Gantry Configuration Summary")
message(STATUS "========================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")
message(STATUS "Dependencies:")
message(STATUS "  OpenCV: ${OpenCV_VERSION}")
message(STATUS "  OpenMP: ${OpenMP_CXX_VERSION}")
message(STATUS "  Pylon (Bottom Camera): ${PYLON_ROOT}")
message(STATUS "  NI-DAQmx: ${NIDAQMX_ROOT}")
message(STATUS "  USB4: ${USB4_ROOT}")
message(STATUS "  YOLO: ${YOLO_ROOT}")
message(STATUS "  MATLAB: ${MATLAB_ROOT}")
message(STATUS "")
message(STATUS "NOTE: This version uses bottom camera only (no top camera/Spinnaker)")
message(STATUS "========================================")
message(STATUS "")
