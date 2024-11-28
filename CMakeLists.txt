cmake_minimum_required(VERSION 3.20)

project(lr6)

set(LANGUAGS CXX)
set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

include_directories("${CMAKE_SOURCE_DIR}/include")

enable_testing()

add_subdirectory(src)
add_subdirectory(src/lr6)
