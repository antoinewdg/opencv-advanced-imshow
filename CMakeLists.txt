cmake_minimum_required(VERSION 2.8)
project(project_name)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES src/main.cpp
        src/utils.h
        )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(project_name ${SOURCE_FILES})


# EXTERNAL LIBRAIRIES =====================

# OpenCV
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(project_name ${OpenCV_LIBS})