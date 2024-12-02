cmake_minimum_required(VERSION 3.20)

add_executable(tests "task_1.cpp" "task_2.cpp")
target_link_libraries(tests gtest gtest_main app)

add_test(app_gtests tests)