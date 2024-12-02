cmake_minimum_required(VERSION 3.20)

project(lr6)

set(LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASAN OFF)
set(TSAN OFF)

if(ASAN AND TSAN)
    message(FATAL_ERROR "Thread sanitizer and address sanitizer are mutually exclusive.")
endif()

if(ASAN)
add_compile_options("-fsanitize=address")
add_link_options("-fsanitize=address")
elseif(TSAN)
add_compile_options("-fsanitize=thread")
add_link_options("-fsanitize=thread")
endif()

include_directories("${CMAKE_SOURCE_DIR}/include")

enable_testing()
add_subdirectory(lib/googletest)
add_subdirectory(src)
add_subdirectory(src/lr6)
add_subdirectory(tests)
