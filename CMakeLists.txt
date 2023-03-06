# begin basic metadata
# minimum CMake version required for C++20 support and precompiled headers
cmake_minimum_required(VERSION 3.16)

project(necalc VERSION 0.0.0 LANGUAGES CXX)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# set the C++ standard to use to C++20 always
set(CMAKE_CXX_STANDARD "20")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    NECALC_VERSION_STRING
    "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
)
set(NECALC_ESCAPED_VERSION_STRING "\"${NECALC_VERSION_STRING}\"")

# add custom dependencies directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# a better way to load dependencies
include(CPM)

CPMFindPackage(
    NAME Arby
    GIT_REPOSITORY https://github.com/saxbophone/arby.git
    GIT_TAG josh/124-power-2-log-optimise
)

add_executable(necalc necalc.cpp)
# pass in version of project as preprocessor definitions
target_compile_definitions(necalc PRIVATE NECALC_VERSION_STRING=${NECALC_ESCAPED_VERSION_STRING})
target_link_libraries(necalc PRIVATE Arby::arby)
target_precompile_headers(
    necalc
        PRIVATE
            <arby/Nat.hpp>
)
set_property(TARGET necalc PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
