cmake_minimum_required(VERSION 3.11)
project(FaceDetector)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

#set(Boost_USE_STATIC_LIBS OFF) 
#set(Boost_USE_MULTITHREADED ON)  
#set(Boost_USE_STATIC_RUNTIME OFF) 
#set (Boost_DEBUG ON)  #<---------- Real life saver

add_definitions(-DBOOST_ALL_NO_LIB)

find_package(Boost REQUIRED COMPONENTS filesystem regex) 

if(Boost_FOUND)
    message(STATUS "Success!")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIR})
endif()

set(header_files
	face_detector.h
)

set(source_files
	face_detector.cpp
    )
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(face_detect_lib SHARED ${source_files} ${header_files})
target_link_libraries(face_detect_lib PUBLIC ${OpenCV_LIBS})

add_executable(face_detector_tool face_detector_tool.cpp )
target_link_libraries(face_detector_tool PUBLIC face_detect_lib ${Boost_LIBRARIES}) 

set(FACE_DETECTION_CONFIGURATION "${PROJECT_SOURCE_DIR}/assets/deploy.prototxt")
set(FACE_DETECTION_WEIGHTS "${PROJECT_SOURCE_DIR}/assets/res10_300x300_ssd_iter_140000_fp16.caffemodel")

target_compile_definitions(face_detector_tool PRIVATE FACE_DETECTION_CONFIGURATION="${FACE_DETECTION_CONFIGURATION}")
target_compile_definitions(face_detector_tool PRIVATE FACE_DETECTION_WEIGHTS="${FACE_DETECTION_WEIGHTS}")

target_compile_definitions(face_detect_lib PRIVATE FACE_DETECTION_CONFIGURATION="${FACE_DETECTION_CONFIGURATION}")
target_compile_definitions(face_detect_lib PRIVATE FACE_DETECTION_WEIGHTS="${FACE_DETECTION_WEIGHTS}")
