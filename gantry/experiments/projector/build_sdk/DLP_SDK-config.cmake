
# Ensure C++11 compatibility
if(NOT MSVC)
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	elseif(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
		message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
	endif()
endif(NOT MSVC)

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif (WIN32)

FIND_LIBRARY(DLP_SDK_LIBRARY DLP_SDK
    PATHS /home/istiak/Senior-Design-Fly-Gantry-Drexel-2026/gantry/experiments/projector/build_sdk/lib
    NO_DEFAULT_PATH
)

option(DLP_LINK_HIDAPI_STATIC "Link the HIDAPI library statically into the DLP_SDK library..." ON)

if(NOT DLP_LINK_HIDAPI_STATIC)
	FIND_LIBRARY(HIDAPI_LIBRARY hidapi
		PATHS /home/istiak/Senior-Design-Fly-Gantry-Drexel-2026/gantry/experiments/projector/build_sdk/lib
		NO_DEFAULT_PATH
	)
	list(APPEND DLP_SDK_LIBRARIES ${DLP_SDK_LIBRARY} ${HIDAPI_LIBRARY})
endif(NOT DLP_LINK_HIDAPI_STATIC)

FIND_LIBRARY(GLFW_LIBRARY glfw3
    PATHS /home/istiak/Senior-Design-Fly-Gantry-Drexel-2026/gantry/experiments/projector/build_sdk/lib
    NO_DEFAULT_PATH
)


find_package( OpenCV REQUIRED core highgui features2d calib3d flann imgproc)

# Option to include the point grey camera module
option(DLP_BUILD_PG_FLYCAP2_C_CAMERA_MODULE "Include the TI developed Point Grey Research camera module..." OFF)
if(DLP_BUILD_PG_FLYCAP2_C_CAMERA_MODULE)
	
	if (WIN32)    
	
		find_library(	PG_FLYCAP_LIB 			FlyCapture2 				"${PG_FLYCAP_DIR}/lib")
		find_library(	PG_FLYCAP_LIB_C 		FlyCapture2_C 				"${PG_FLYCAP_DIR}/lib/C")
		get_filename_component(PG_FLYCAP_LIB_DIR "${PG_FLYCAP_LIB}" 	DIRECTORY)
		get_filename_component(PG_FLYCAP_DIR     "${PG_FLYCAP_LIB_DIR}" DIRECTORY)

		find_path(		PG_FLYCAP_BIN_DIR 	    FlyCapture2.dll 			"${PG_FLYCAP_DIR}/bin")
		find_path(		PG_FLYCAP_INCLUDE_DIR 	C/FlyCapture2_C.h 			"${PG_FLYCAP_DIR}/include")
		
	endif (WIN32)


	if (UNIX)
		if(NOT APPLE)
			find_path(		PG_FLYCAP_INCLUDE_DIR 	FlyCapture2.h 		"/usr/include/flycapture")		
			find_library(	PG_FLYCAP_LIB 			flycapture  		"/usr/lib/")
			find_library(	PG_FLYCAP_LIB_C			flycapture-c		"/usr/lib/")
						
	#		list(APPEND LIBS flycapture 	"${FLYCAPTURE2_LIB}")
	#		list(APPEND LIBS flycapture-c 	"${FLYCAPTURE2_C_LIB}")			
		endif(NOT APPLE)
	endif (UNIX)

	if (APPLE)
		message( FATAL_ERROR "The Point Grey camera module is NOT available for Mac. Exiting..." )
	endif (APPLE)
	
	# Add Point Grey FlyCapture2 as library to link with DLP SDK
	list(APPEND	INCLUDE_DIRS 	${PG_FLYCAP_INCLUDE_DIR})
	list(APPEND DLP_SDK_LIBRARIES 	${PG_FLYCAP_LIB})
	list(APPEND DLP_SDK_LIBRARIES	${PG_FLYCAP_LIB_C})	
endif(DLP_BUILD_PG_FLYCAP2_C_CAMERA_MODULE)

#list(APPEND DLP_SDK_LIBRARIES ${DLP_SDK_LIBRARY} ${HIDAPI_LIBRARY} ${GLFW_LIBRARY} opencv_core;opencv_highgui;opencv_features2d;opencv_calib3d;opencv_flann;opencv_imgproc;/usr/lib/x86_64-linux-gnu/libX11.so;/usr/lib/x86_64-linux-gnu/libXrandr.so;/usr/lib/x86_64-linux-gnu/libXi.so;/usr/lib/x86_64-linux-gnu/libXxf86vm.so;/usr/lib/x86_64-linux-gnu/librt.a;/usr/lib/x86_64-linux-gnu/libm.so;/usr/lib/x86_64-linux-gnu/libGL.so;usb-1.0;/usr/lib/x86_64-linux-gnu/libusb-1.0.so;udev;/usr/lib/x86_64-linux-gnu/libudev.so)
list(APPEND DLP_SDK_LIBRARIES ${DLP_SDK_LIBRARY} ${GLFW_LIBRARY} opencv_core;opencv_highgui;opencv_features2d;opencv_calib3d;opencv_flann;opencv_imgproc;/usr/lib/x86_64-linux-gnu/libX11.so;/usr/lib/x86_64-linux-gnu/libXrandr.so;/usr/lib/x86_64-linux-gnu/libXi.so;/usr/lib/x86_64-linux-gnu/libXxf86vm.so;/usr/lib/x86_64-linux-gnu/librt.a;/usr/lib/x86_64-linux-gnu/libm.so;/usr/lib/x86_64-linux-gnu/libGL.so;usb-1.0;/usr/lib/x86_64-linux-gnu/libusb-1.0.so;udev;/usr/lib/x86_64-linux-gnu/libudev.so)
list(APPEND DLP_SDK_INCLUDE_DIRS /usr/include/opencv4;/usr/include/opencv4;/usr/include/opencv4;/usr/include/opencv4;3rd_party/glfw-3.0.4/include;/home/istiak/Senior-Design-Fly-Gantry-Drexel-2026/gantry/experiments/projector/DLP-ALC-LIGHTCRAFTER-SDK/3rd_party/hidapi-master/hidapi;/home/istiak/Senior-Design-Fly-Gantry-Drexel-2026/gantry/experiments/projector/DLP-ALC-LIGHTCRAFTER-SDK/3rd_party/asio-1.10.4/include;/home/istiak/Senior-Design-Fly-Gantry-Drexel-2026/gantry/experiments/projector/DLP-ALC-LIGHTCRAFTER-SDK/include)
list(APPEND DLP_SDK_DEFINITIONS )


if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY) 
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY) 

# Copy the required dll's if on windows
if (WIN32)
	# Copy OpenCV dll's
	file(COPY ${OpenCV_DIR}/bin/libopencv_calib3d${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dll 		DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	file(COPY ${OpenCV_DIR}/bin/libopencv_core${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dll 		DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	file(COPY ${OpenCV_DIR}/bin/libopencv_features2d${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dll 	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	file(COPY ${OpenCV_DIR}/bin/libopencv_flann${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dll 		DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	file(COPY ${OpenCV_DIR}/bin/libopencv_highgui${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dll 		DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	file(COPY ${OpenCV_DIR}/bin/libopencv_imgproc${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dll 		DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	
	# If Point Grey Module enabled copy the dll's
	if(DLP_BUILD_PG_FLYCAP2_C_CAMERA_MODULE)
        file(COPY ${PG_FLYCAP_BIN_DIR}/FlyCapture2.dll      DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        file(COPY ${PG_FLYCAP_BIN_DIR}/FlyCapture2_C.dll    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        file(COPY ${PG_FLYCAP_BIN_DIR}/libiomp5md.dll       DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	endif(DLP_BUILD_PG_FLYCAP2_C_CAMERA_MODULE)	
endif (WIN32)


file(COPY /home/istiak/Senior-Design-Fly-Gantry-Drexel-2026/gantry/experiments/projector/build_sdk/bin/resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include_directories(${DLP_SDK_INCLUDE_DIRS})
add_definitions(${DLP_SDK_DEFINITIONS})
