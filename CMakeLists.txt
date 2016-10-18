cmake_minimum_required(VERSION 2.8)
project(opencv_advanced_imshow)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES src/main.cpp
        src/oai/image_view.h
        src/oai/zoom_manager.h
        src/oai/drag_manager.h
        src/oai/ui_manager.h
        src/oai/rect_select_manager.h
        src/oai/rgba_transformer.h
        )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(opencv_advanced_imshow ${SOURCE_FILES})


# EXTERNAL LIBRAIRIES =====================

# OpenCV
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(opencv_advanced_imshow ${OpenCV_LIBS})

# SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(opencv_advanced_imshow ${SFML_LIBRARIES})
endif ()