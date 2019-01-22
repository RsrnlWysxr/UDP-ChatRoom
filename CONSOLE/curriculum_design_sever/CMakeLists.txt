cmake_minimum_required(VERSION 3.12)
project(curriculum_design)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.0/lib/cmake")

set(SOURCE_FILES main.cpp Server.h)

find_package(Qt5Widgets REQUIRED)

add_executable(curriculum_design ${SOURCE_FILES})

target_link_libraries(curriculum_design Qt5::Widgets)
