cmake_minimum_required(VERSION 3.0)
project(log4cplus_gelf LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_SHARED_LIBS "Build log4cplus_gelf as shared library" OFF)

# Initialize Conan #############################################################
if (NOT EXISTS conanbuildinfo.cmake)
    message(FATAL_ERROR "Run Conan first: conan install <path_to_your_conanfile.txt>")
endif ()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)

enable_testing()
add_subdirectory(test)