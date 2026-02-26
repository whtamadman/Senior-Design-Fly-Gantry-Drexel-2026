cmake_minimum_required(VERSION 3.15)
project(BottomCameraDisplay)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Find Pylon SDK
set(PYLON_ROOT "$ENV{PYLON_ROOT}" CACHE PATH "Pylon SDK root directory")
if(NOT PYLON_ROOT)
    if(EXISTS "C:/Program Files/Basler/pylon 7")
        set(PYLON_ROOT "C:/Program Files/Basler/pylon 7")
    elseif(EXISTS "C:/Program Files/Basler/pylon 6")
        set(PYLON_ROOT "C:/Program Files/Basler/pylon 6")
    elseif(EXISTS "C:/Program Files (x86)/Basler/pylon 7")
        set(PYLON_ROOT "C:/Program Files (x86)/Basler/pylon 7")
    elseif(EXISTS "C:/Program Files (x86)/Basler/pylon 6")
        set(PYLON_ROOT "C:/Program Files (x86)/Basler/pylon 6")
    endif()
endif()

if(PYLON_ROOT)
    include_directories("${PYLON_ROOT}/include")
    link_directories("${PYLON_ROOT}/lib/x64")
    message(STATUS "Pylon SDK found at: ${PYLON_ROOT}")
else()
    message(FATAL_ERROR "Pylon SDK not found. Please set PYLON_ROOT environment variable.")
endif()

# Include parent directory for HardwareTriggerConfiguration.h
include_directories("${CMAKE_SOURCE_DIR}/..")

# Add executable
add_executable(bottom_camera_display bottom_camera_display.cpp)

# Link libraries
target_link_libraries(bottom_camera_display 
    ${OpenCV_LIBS}
    PylonBase_v7_4.lib
    PylonC_v7_3.lib
    PylonUtility_v7_4.lib
    GenApi_MD_VC141_v3_1_Basler_pylon.lib
    GCBase_MD_VC141_v3_1_Basler_pylon.lib
)

# Copy Pylon DLLs to output directory
if(EXISTS "${PYLON_ROOT}/Runtime/x64")
    add_custom_command(TARGET bottom_camera_display POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PYLON_ROOT}/Runtime/x64"
        $<TARGET_FILE_DIR:bottom_camera_display>
    )
endif()
