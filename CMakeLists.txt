project(di-coin)

cmake_minimum_required(VERSION 3.8)

set(LIB lib)
set(SRC src)

add_executable(main ${SRC}/main.cpp)

# tests

set(TEST_DIR test)

add_subdirectory(${LIB}/googletest)
include_directories(${LIB}/googletest/googletest/include)

add_executable(test ${TEST_DIR}/g_test.cpp)

target_link_libraries(test gtest_main)
