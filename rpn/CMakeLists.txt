cmake_minimum_required(VERSION 3.5)
project(rpn VERSION 0.0.1 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)

## library find functions
# find_package(Vulkan REQUIRED)

## add external libraries
# add_subdirectory(external/glm)
# add_subdirectory(external/glfw)
# add_subdirectory(external/SDL)
# add_subdirectory(external/assimp)

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
    PRIVATE
        src/rpn.cpp
        src/rpncalc.cpp
        src/stack.cpp
        src/undoredo.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    SYSTEM
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    PRIVATE
)

