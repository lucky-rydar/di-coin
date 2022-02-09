project(di-coin)

cmake_minimum_required(VERSION 3.8)

set(APP main)
set(LIB lib)
set(SRC src)

set(UTILS src/utils)
set(CORE src/core)

# packages

find_package(OpenSSL REQUIRED)

add_subdirectory(${LIB}/googletest)
add_subdirectory(${LIB}/spdlog)

# binaries

## utils
include_directories(${SRC})
include_directories(${LIB}/spdlog/include)

add_library(utils STATIC 
    ${UTILS}/crypto.cpp
    ${UTILS}/time_utils.cpp
)

target_link_libraries(utils OpenSSL::SSL)

## core

add_library(core STATIC
    ${CORE}/miner.cpp
    ${CORE}/block.cpp
    ${CORE}/blockchain.cpp
)

# main app

add_executable(${APP} 
    ${SRC}/main.cpp
)
target_link_libraries(${APP} 
    OpenSSL::SSL
    utils
)

# tests

set(TEST_DIR test)

include_directories(
    ${LIB}/googletest/googletest/include
)

add_executable(test 
    ${TEST_DIR}/g_test.cpp
    ${TEST_DIR}/utils_test.cpp
    ${TEST_DIR}/miner_test.cpp
    ${TEST_DIR}/blockchain_test.cpp
)

target_link_libraries(test 
    gtest_main 
    spdlog
    utils
    core
)
