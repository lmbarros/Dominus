# General settings
project(Dominus)
cmake_minimum_required(VERSION 2.6)
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

# Add path of custom CMake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Packages
find_package(Qt4)
include(${QT_USE_FILE})

# Process sub-directories
add_subdirectory(src)
