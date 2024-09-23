cmake_minimum_required(VERSION 3.5)
project(calculator VERSION 0.0.1 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
# qt_standard_project_setup()

add_subdirectory(rpn)

add_executable(${PROJECT_NAME} src/main.cpp src/appcontroller.cpp)
# qt_add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE rpn)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        rpn
        Qt6::Widgets
        Qt6::Gui
        Qt6::Core
)

