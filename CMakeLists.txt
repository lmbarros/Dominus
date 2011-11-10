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

# Treat Qt include dirs as system directories, so that we don't get warnings
# from them.
include_directories(SYSTEM ${QT_INCLUDE_DIR})


# Warnings to use
set(DOMINUS_GXX_WARNINGS "-Wall -pedantic")

# Process sub-directories
add_subdirectory(src)
