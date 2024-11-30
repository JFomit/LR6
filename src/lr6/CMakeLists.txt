cmake_minimum_required(VERSION 3.20)

set(LIBRARY_SOURCES
    "string.cpp")

add_library(app STATIC ${LIBRARY_SOURCES})
