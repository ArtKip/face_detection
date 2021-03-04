cmake_minimum_required(VERSION 3.11)
project(FaceDetector)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_definitions(-DBOOST_ALL_NO_LIB)
find_package(Boost REQUIRED COMPONENTS filesystem regex) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIR})
endif()

set(header_files
	src/face_detector.h
	src/json/json.h
	src/json_results_saver.h
	src/image_processor.h
	src/path_manager.h
)

set(source_files
	src/face_detector_tool.cpp
	src/jsoncpp.cpp
	src/json_results_saver.cpp
	src/image_processor.cpp
	src/path_manager.cpp
    )
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(face_detect_lib SHARED src/face_detector.cpp src/face_detector.h)
target_link_libraries(face_detect_lib PUBLIC ${OpenCV_LIBS})

add_executable(face_detector_tool ${source_files} ${header_files})
target_link_libraries(face_detector_tool PRIVATE face_detect_lib ${Boost_LIBRARIES}) 

set(FACE_DETECTION_CONFIGURATION "${PROJECT_SOURCE_DIR}/assets/deploy.prototxt")
set(FACE_DETECTION_WEIGHTS "${PROJECT_SOURCE_DIR}/assets/res10_300x300_ssd_iter_140000_fp16.caffemodel")

target_compile_definitions(face_detector_tool PRIVATE FACE_DETECTION_CONFIGURATION="${FACE_DETECTION_CONFIGURATION}")
target_compile_definitions(face_detector_tool PRIVATE FACE_DETECTION_WEIGHTS="${FACE_DETECTION_WEIGHTS}")

target_compile_definitions(face_detect_lib PRIVATE FACE_DETECTION_CONFIGURATION="${FACE_DETECTION_CONFIGURATION}")
target_compile_definitions(face_detect_lib PRIVATE FACE_DETECTION_WEIGHTS="${FACE_DETECTION_WEIGHTS}")




include(GoogleTest)

# Download and compile gtest/gmock
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.1
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()

file(COPY test_data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test_data/)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(test_header_files
	src/face_detector.h
	src/image_processor.h
	src/path_manager.h
)

set(test_source_files
	src/image_processor.cpp
	src/path_manager.cpp
	src/test.cpp
    )

add_executable(face_detect_tests ${test_header_files} ${test_source_files})
target_link_libraries(face_detect_tests PRIVATE face_detect_lib gtest_main ${Boost_LIBRARIES})