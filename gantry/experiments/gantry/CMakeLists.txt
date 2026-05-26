cmake_minimum_required(VERSION 3.15)

project(ZaberGantryPortTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Zaber Motion Library location from the main gantry project.
set(ZABER_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../fly_gantry_v2/ZaberMotionLibrary")

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
    message(FATAL_ERROR "Could not find zaber-motion library under ${ZABER_ROOT}/lib")
endif()

if(NOT ZABER_MOTION_LIB_DEBUG)
    set(ZABER_MOTION_LIB_DEBUG "${ZABER_MOTION_LIB_RELEASE}")
endif()

add_executable(zaber_port_test
    test.cpp
)

target_include_directories(zaber_port_test PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(zaber_port_test PRIVATE
    $<$<CONFIG:Debug>:${ZABER_MOTION_LIB_DEBUG}>
    $<$<NOT:$<CONFIG:Debug>>:${ZABER_MOTION_LIB_RELEASE}>
)
