cmake_minimum_required(VERSION 3.2)
project(cppcore)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Lib/CMake")

set(CMAKE_CXX_STANDARD 11)

include(CTest)
include(Lib/CMake/GoogleTest.cmake)
include(Lib/CMake/BuildSetting.cmake)
include(Lib/CMake/CompileOptions.cmake)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

load_gtest()

enable_testing()
add_subdirectory(Src)
add_subdirectory(Test)

option(BUILD_COVERAGE "Build code coverage" On)
if (CMAKE_BUILD_TYPE MATCHES Debug AND CMAKE_COMPILER_IS_GNUCXX AND BUILD_COVERAGE)
    include(Lib/CMake/CodeCoverage.cmake)
    setup_target_for_coverage(coverage ctest coverage)
endif()