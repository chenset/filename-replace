cmake_minimum_required(VERSION 3.3)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5UiTools REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
#SET(QT_USE_QTUITOOLS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON) # Both source and binary


add_executable(
        main
        textfinder.cpp
        textfinder.h
#        forms/textfinder.xml
        textfinder.qrc
        main.cpp
        forms/input.txt
)

target_link_libraries(main Qt5::Widgets Qt5::UiTools)

