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
set(PYLON_ROOT "C:/Program Files/Basler/pylon/Development" CACHE PATH "Pylon SDK root directory")
set(PYLON_INCLUDE_DIR "${PYLON_ROOT}/include")
set(PYLON_LIB_DIR "${PYLON_ROOT}/lib/x64")

# MATLAB
set(MATLAB_ROOT "C:/Program Files/MATLAB/R2026a" CACHE PATH "MATLAB root directory")
set(MATLAB_INCLUDE_DIR "${MATLAB_ROOT}/extern/include")
set(MATLAB_LIB_DIR "${MATLAB_ROOT}/extern/lib/win64/microsoft")

# Zaber Motion Library
set(ZABER_ROOT "C:/Users/Public/Documents/Senior-Design-Fly-Gantry-Drexel-2026/gantry/fly_gantry_v3/ZaberMotionLibrary" CACHE PATH "Zaber Motion Library root directory")
set(ZABER_INCLUDE_DIR "${ZABER_ROOT}/include")

# DLP SDK (TI LightCrafter 4500)
set(DLP_SDK_ROOT "C:/Users/Public/Documents/Senior-Design-Fly-Gantry-Drexel-2026/gantry/experiments/projector/DLP-ALC-LIGHTCRAFTER-SDK" CACHE PATH "DLP SDK root directory" FORCE)
set(DLP_SDK_INCLUDE_DIR "${DLP_SDK_ROOT}/include")
set(DLP_SDK_LIB_DIR "${DLP_SDK_ROOT}/build/lib/Release")

# Darknet / YOLOv4
set(DARKNET_ROOT "C:/Users/SeniorDesign/Downloads/darknet-master/darknet-master" CACHE PATH "Darknet root directory")
set(DARKNET_INCLUDE_DIR "${DARKNET_ROOT}/include")
set(DARKNET_LIB_DIR     "${DARKNET_ROOT}/build/Release" CACHE PATH "Directory containing yolo_cpp_dll.lib")

# Migrate known legacy cache defaults to current defaults.
# CMake cache values persist across re-configures, so changed defaults above
# are not automatically applied if older values already exist in CMakeCache.txt.
if(PYLON_ROOT STREQUAL "C:/Program Files/Basler/pylon 7")
    set(PYLON_ROOT "C:/Program Files/Basler/pylon/Development" CACHE PATH "Pylon SDK root directory" FORCE)
    set(PYLON_INCLUDE_DIR "${PYLON_ROOT}/include")
    set(PYLON_LIB_DIR "${PYLON_ROOT}/lib/x64")
endif()

if(MATLAB_ROOT STREQUAL "C:/Program Files/MATLAB/R2022b")
    set(MATLAB_ROOT "C:/Program Files/MATLAB/R2026a" CACHE PATH "MATLAB root directory" FORCE)
    set(MATLAB_INCLUDE_DIR "${MATLAB_ROOT}/extern/include")
    set(MATLAB_LIB_DIR "${MATLAB_ROOT}/extern/lib/win64/microsoft")
endif()

# Migrate legacy local DLP cache path to experiments/projector SDK location.
if(DLP_SDK_ROOT STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/DLP-ALC-LIGHTCRAFTER-SDK")
    set(DLP_SDK_ROOT "C:/Users/Public/Documents/Senior-Design-Fly-Gantry-Drexel-2026/gantry/experiments/projector/DLP-ALC-LIGHTCRAFTER-SDK" CACHE PATH "DLP SDK root directory" FORCE)
    set(DLP_SDK_INCLUDE_DIR "${DLP_SDK_ROOT}/include")
    set(DLP_SDK_LIB_DIR "${DLP_SDK_ROOT}/build/lib/Release")
endif()

# Migrate legacy absolute Zaber cache path to local workspace copy.
if(ZABER_ROOT STREQUAL "C:/Users/SeniorDesign/Downloads/ZaberMotionLibrary")
    set(ZABER_ROOT "C:/Users/Public/Documents/Senior-Design-Fly-Gantry-Drexel-2026/gantry/fly_gantry_v3/ZaberMotionLibrary" CACHE PATH "Zaber Motion Library root directory" FORCE)
    set(ZABER_INCLUDE_DIR "${ZABER_ROOT}/include")
endif()

# ============================================================================
# Check if directories exist
# ============================================================================

if(NOT EXISTS "${PYLON_INCLUDE_DIR}")
    message(WARNING "Pylon SDK not found at ${PYLON_ROOT}. Please set PYLON_ROOT correctly.")
endif()

if(NOT EXISTS "${MATLAB_INCLUDE_DIR}")
    message(WARNING "MATLAB not found at ${MATLAB_ROOT}. Please set MATLAB_ROOT correctly.")
endif()

if(NOT EXISTS "${ZABER_ROOT}")
    message(WARNING "Zaber Motion Library not found at ${ZABER_ROOT}. Please set ZABER_ROOT correctly.")
endif()
if(NOT EXISTS "${ZABER_INCLUDE_DIR}")
    message(WARNING "Zaber include folder not found at ${ZABER_INCLUDE_DIR}. Please set ZABER_ROOT correctly.")
endif()

if(NOT EXISTS "${DLP_SDK_INCLUDE_DIR}")
    message(WARNING "DLP SDK not found at ${DLP_SDK_ROOT}. Please set DLP_SDK_ROOT correctly.")
endif()

# ============================================================================
# Source Files
# ============================================================================

set(PROJECT_SOURCES
    gantrycodeV3.cpp
    pch.cpp
    gantry.cpp
    position.cpp
    filter.cpp
    WindowManager.cpp
    BinarySaveData.cpp
    MatlabSaveData.cpp
    matlab_i18n_init.c
)

set(PROJECT_HEADERS
    pch.h
    gantry.h
    position.h
    filter.h
    WindowManager.h
    flyViewStruc.h
    BinarySaveData.h
    MatlabSaveData.h
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
    ${MATLAB_INCLUDE_DIR}
    ${ZABER_INCLUDE_DIR}
    ${DLP_SDK_INCLUDE_DIR}
    ${DARKNET_INCLUDE_DIR}
)

# ============================================================================
# Compiler Definitions
# ============================================================================

target_compile_definitions(${PROJECT_NAME} PRIVATE
    UNICODE
    _UNICODE
    OPENCV
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
    ${MATLAB_LIB_DIR}
    ${DLP_SDK_LIB_DIR}
    ${DARKNET_LIB_DIR}
    "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.26100.0/um/x64"
)

# Resolve Pylon libs by prefix so any installed version can be used.
function(select_latest_pylon_lib prefix outvar)
    file(GLOB _candidates "${PYLON_LIB_DIR}/${prefix}*.lib")
    if(_candidates)
        list(SORT _candidates COMPARE NATURAL ORDER DESCENDING)
        list(GET _candidates 0 _selected)
        set(${outvar} "${_selected}" PARENT_SCOPE)
        get_filename_component(_selected_name "${_selected}" NAME)
        message(STATUS "Selected ${prefix} library: ${_selected_name}")
    else()
        set(${outvar} "" PARENT_SCOPE)
        message(FATAL_ERROR "Could not find ${prefix}*.lib in ${PYLON_LIB_DIR}")
    endif()
endfunction()

select_latest_pylon_lib("PylonBase" PYLON_BASE_LIB)
select_latest_pylon_lib("PylonC" PYLON_C_LIB)
select_latest_pylon_lib("PylonUtility" PYLON_UTILITY_LIB)

# Resolve Zaber motion libs for Debug/Release.
find_library(ZABER_MOTION_LIB_RELEASE
    NAMES zaber-motion
    PATHS
        "${ZABER_ROOT}/lib/Release"
        "${ZABER_ROOT}/lib"
)

find_library(ZABER_MOTION_LIB_DEBUG
    NAMES zaber-motion
    PATHS
        "${ZABER_ROOT}/lib/Debug"
        "${ZABER_ROOT}/lib"
)

if(NOT ZABER_MOTION_LIB_RELEASE)
    message(FATAL_ERROR "Could not find zaber-motion release library under ${ZABER_ROOT}/lib")
endif()
if(NOT ZABER_MOTION_LIB_DEBUG)
    # Fallback to release lib if debug lib is not available.
    set(ZABER_MOTION_LIB_DEBUG "${ZABER_MOTION_LIB_RELEASE}")
endif()

# ============================================================================
# Link Libraries
# ============================================================================

# OpenCV libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# OpenMP
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

# SDK Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    # Pylon SDK (bottom camera only) - resolved dynamically by prefix/version.
    ${PYLON_BASE_LIB}
    ${PYLON_C_LIB}
    ${PYLON_UTILITY_LIB}
    
    # MATLAB
    libmat
    libmx

    # Zaber motion library
    $<$<CONFIG:Debug>:${ZABER_MOTION_LIB_DEBUG}>
    $<$<NOT:$<CONFIG:Debug>>:${ZABER_MOTION_LIB_RELEASE}>
    
    # DLP SDK (TI LightCrafter 4500)
    DLP_SDK
    glfw3
    opengl32

    # Darknet / YOLO wrapper library
    darknet
    
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
    setupapi
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
    
    # MATLAB DLLs
    copy_dll_if_exists("${MATLAB_ROOT}/bin/win64/libmat.dll")

    # Darknet DLL
    copy_dll_if_exists("${DARKNET_LIB_DIR}/darknet.dll")
    copy_dll_if_exists("${MATLAB_ROOT}/bin/win64/libmx.dll")
    copy_dll_if_exists("${MATLAB_ROOT}/bin/win64/libmex.dll")
    copy_dll_if_exists("${MATLAB_ROOT}/bin/win64/libmwi18n.dll")
    copy_dll_if_exists("${MATLAB_ROOT}/bin/win64/libmwfl.dll")
    copy_dll_if_exists("${MATLAB_ROOT}/bin/win64/libmwfoundation_usm.dll")
    copy_dll_if_exists("${MATLAB_ROOT}/bin/win64/libmwfoundation_filesystem.dll")

    # Zaber DLLs: copy only the runtime matching the active build config.
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<$<CONFIG:Debug>:${ZABER_ROOT}/bin/Debug/zaber-motion.dll>$<$<NOT:$<CONFIG:Debug>>:${ZABER_ROOT}/bin/Release/zaber-motion.dll>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying config-matched zaber-motion.dll"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<$<CONFIG:Debug>:${ZABER_ROOT}/bin/Debug/zaber-motion-core.dll>$<$<NOT:$<CONFIG:Debug>>:${ZABER_ROOT}/bin/Release/zaber-motion-core.dll>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying config-matched zaber-motion-core.dll"
    )
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
message(STATUS "  MATLAB: ${MATLAB_ROOT}")
message(STATUS "  Zaber: ${ZABER_ROOT}")
message(STATUS "")
message(STATUS "NOTE: This version uses bottom camera only (no top camera/Spinnaker)")
message(STATUS "========================================")
message(STATUS "")