cmake_minimum_required(VERSION 3.6)
project(computerVisionEx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(computerVisionEx ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(computerVisionEx ${OpenCV_LIBS})