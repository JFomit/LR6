cmake_minimum_required(VERSION 3.20)

set(LIBRARY_SOURCES
    "string.cpp"
    "input.cpp"
    "utf8.cpp"
    "task.cpp"
    "print.cpp"
    "task_1.cpp"
    "task_2.cpp"
    "task_3.cpp")

add_library(app STATIC ${LIBRARY_SOURCES})
