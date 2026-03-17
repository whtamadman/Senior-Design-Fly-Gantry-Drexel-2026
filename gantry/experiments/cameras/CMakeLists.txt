cmake_minimum_required(VERSION 3.15)
project(DualBaslerDisplay)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV - Set the path to help CMake find it
set(OpenCV_DIR "$ENV{OpenCV_DIR}" CACHE PATH "OpenCV directory")
if(OpenCV_DIR)
    # If user provided OpenCV_DIR but it doesn't directly contain OpenCVConfig.cmake,
    # try common subfolders (e.g. append /lib or /x64/vc15/lib)
    if(NOT EXISTS "${OpenCV_DIR}/OpenCVConfig.cmake")
        if(EXISTS "${OpenCV_DIR}/lib/OpenCVConfig.cmake")
            set(OpenCV_DIR "${OpenCV_DIR}/lib")
        elseif(EXISTS "${OpenCV_DIR}/x64/vc15/lib/OpenCVConfig.cmake")
            set(OpenCV_DIR "${OpenCV_DIR}/x64/vc15/lib")
        elseif(EXISTS "${OpenCV_DIR}/build/x64/vc15/lib/OpenCVConfig.cmake")
            set(OpenCV_DIR "${OpenCV_DIR}/build/x64/vc15/lib")
        endif()
    endif()
else()
    # Prefer local build location that contains OpenCVConfig.cmake
    if(EXISTS "C:/Users/labadmin/opencv/build/x64/vc15/lib/OpenCVConfig.cmake")
        set(OpenCV_DIR "C:/Users/labadmin/opencv/build/x64/vc15/lib")
    elseif(EXISTS "C:/Users/labadmin/opencv/build/x64/vc15/OpenCVConfig.cmake")
        set(OpenCV_DIR "C:/Users/labadmin/opencv/build/x64/vc15")
    elseif(EXISTS "C:/opencv/build/OpenCVConfig.cmake")
        set(OpenCV_DIR "C:/opencv/build")
    elseif(EXISTS "C:/Program Files (x86)/opencv/build/OpenCVConfig.cmake")
        set(OpenCV_DIR "C:/Program Files (x86)/opencv/build")
    endif()
endif()

# Add OpenCV to CMAKE_PREFIX_PATH
if(OpenCV_DIR)
    message(STATUS "OpenCV directory hint: ${OpenCV_DIR}")
    list(APPEND CMAKE_PREFIX_PATH "${OpenCV_DIR}")
endif()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

# Find Pylon SDK
set(PYLON_ROOT "$ENV{PYLON_ROOT}" CACHE PATH "Pylon SDK root directory")
if(NOT PYLON_ROOT)
    #Change if Needed
    if(EXISTS "C:/Program Files/Basler/pylon")
        set(PYLON_ROOT "C:/Program Files/Basler/pylon")
    endif()
endif()

if(PYLON_ROOT)
#Change if Needed
    include_directories("${PYLON_ROOT}/Development/include")
    
    # Add Pylon library directories  
    if(EXISTS "${PYLON_ROOT}/Development/lib/x64")
        link_directories("${PYLON_ROOT}/Development/lib/x64")
    endif()
    if(EXISTS "${PYLON_ROOT}/lib/x64")
        link_directories("${PYLON_ROOT}/lib/x64")
    endif()
    
    message(STATUS "Pylon SDK found at: ${PYLON_ROOT}")
else()
    message(FATAL_ERROR "Pylon SDK not found. Please set PYLON_ROOT environment variable.")
endif()

# Include parent directory for HardwareTriggerConfiguration.h
include_directories("${CMAKE_SOURCE_DIR}/..")
# Also include the fly_gantry_v2 folder where HardwareTriggerConfiguration.h resides
if(EXISTS "${CMAKE_SOURCE_DIR}/../../fly_gantry_v2")
    include_directories("${CMAKE_SOURCE_DIR}/../../fly_gantry_v2")
endif()

# Pylon libraries (updated for newer Pylon SDK)
set(PYLON_LIBS
    PylonBase_v11.lib
    PylonC_v10.lib
    PylonUtility_v11.lib
    GenApi_MD_VC142_v3_5_Basler_pylon_v1.lib
    GCBase_MD_VC142_v3_5_Basler_pylon_v1.lib
)

# === Detect Basler Cameras ===
add_executable(detect_basler_cameras detect_basler_cameras.cpp)
target_link_libraries(detect_basler_cameras ${PYLON_LIBS})

# Copy Pylon DLLs for detect_basler_cameras
if(EXISTS "${PYLON_ROOT}/Runtime/x64")
    add_custom_command(TARGET detect_basler_cameras POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PYLON_ROOT}/Runtime/x64"
        $<TARGET_FILE_DIR:detect_basler_cameras>
    )
endif()

# === Dual Basler Display (Two Basler cameras) ===
add_executable(dual_basler_display dual_basler_display.cpp)
target_link_libraries(dual_basler_display ${OpenCV_LIBS} ${PYLON_LIBS})

# Copy Pylon DLLs for dual_basler_display
if(EXISTS "${PYLON_ROOT}/Runtime/x64")
    add_custom_command(TARGET dual_basler_display POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PYLON_ROOT}/Runtime/x64"
        $<TARGET_FILE_DIR:dual_basler_display>
    )
endif()
