cmake_minimum_required(VERSION 3.5)
project(calculator VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

add_subdirectory(rpn)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/controller/appcontroller.cpp
    src/view/appview.cpp
    resources.qrc
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        rpn
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller
        ${CMAKE_CURRENT_SOURCE_DIR}/src/view
        # $<INSTALL_INTERFACE:include>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        rpn
        Qt6::Widgets
        Qt6::Gui
        Qt6::Core
)

