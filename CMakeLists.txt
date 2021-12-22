cmake_minimum_required(VERSION 3.1.0)

project(lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(lab4 "Main.cpp" "Window.cpp"  "Window.h")
target_link_libraries(lab4 Qt6::Widgets)

if (WIN32)
    set_property(TARGET lab4 PROPERTY WIN32_EXECUTABLE true)

    add_custom_command(
        TARGET lab4 POST_BUILD
        COMMAND ${Qt6_DIR}/../../../bin/windeployqt $<TARGET_FILE:lab4>
    )
endif (WIN32)
