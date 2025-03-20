# CMakeList.txt : CMake project for Project - Global Illumination, include source and define
# project specific logic here.
#

# CMake project for Project - Global Illumination

cmake_minimum_required(VERSION 3.11)

# Define your project and its executable
project(CMakeTarget VERSION 1.0 LANGUAGES CXX)

# Add the executable target with source files
file(GLOB SOURCES
    "Scene.cpp"
    "Scene.h"
    "Camera.h"
    "ColorDBL.h"
    "Rectangle.cpp"
    "Rectangle.h"
    "Triangle.cpp"
    "Triangle.h"
    "Ray.cpp"
    "Ray.h"
    "Material.h"
    "CollisionHandler.cpp"
    "CollisionHandler.h"
    "Shape.h"
    "Light.h"
    "Light.cpp"
    "Sphere.h"
    "Sphere.cpp"
    "CpuManagement.h"
)
add_executable(CMakeTarget ${SOURCES})

# Set C++ standard (CMake will handle the version check internally)
set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)

# FetchContent is used to download and include GLM
include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e # refs/tags/1.0.1
)

# Make GLM available to the project
FetchContent_MakeAvailable(glm)

# Link GLM to your main executable target
target_link_libraries(CMakeTarget PRIVATE glm::glm)

# TODO: Add tests and install targets if needed.
