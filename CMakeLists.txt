project(di-coin)

cmake_minimum_required(VERSION 3.8)

set(APP main)
set(LIB lib)
set(SRC src)

# packages

find_package(OpenSSL REQUIRED)

add_subdirectory(${LIB}/googletest)
add_subdirectory(${LIB}/spdlog)

# binaries

## utils
include_directories(${SRC})
include_directories(${LIB}/spdlog/include)

add_library(utils STATIC 
    ${SRC}/crypto.cpp
)

target_link_libraries(utils OpenSSL::SSL)

# main app

add_executable(${APP} ${SRC}/main.cpp)
target_link_libraries(${APP} OpenSSL::SSL)

# tests

set(TEST_DIR test)

include_directories(
    ${LIB}/googletest/googletest/include
)

add_executable(test 
    ${TEST_DIR}/g_test.cpp
    ${TEST_DIR}/utils_test.cpp
)

target_link_libraries(test 
    gtest_main 
    utils
    spdlog
)
