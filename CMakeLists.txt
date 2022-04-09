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
add_subdirectory(${LIB}/json)
add_subdirectory(${LIB}/libfort)

include_directories(${LIB}/spdlog/include)
include_directories(${LIB}/json/include)
include_directories(${LIB}/json/include/nlohmann)
include_directories(${LIB}/libfort/lib/)

# binaries

## utils
include_directories(${SRC})

add_library(utils STATIC 
    ${UTILS}/crypto.cpp
    ${UTILS}/time_utils.cpp
)

target_compile_features(utils PUBLIC cxx_std_20)

target_link_libraries(utils OpenSSL::SSL)

## core

add_library(core STATIC
    ${CORE}/miner.cpp
    ${CORE}/block.cpp
    ${CORE}/blockchain.cpp
    ${CORE}/transaction.cpp
)

target_compile_features(core PUBLIC cxx_std_20)

# main app

add_executable(${APP} 
    ${SRC}/main.cpp
    ${SRC}/cli/cli.cpp
    ${SRC}/cli/handler/echo_cmd.cpp
    ${SRC}/context/application.cpp
    ${SRC}/core/block.cpp
    ${SRC}/core/blockchain.cpp
    ${SRC}/core/miner.cpp
    ${SRC}/core/transaction.cpp
    ${SRC}/utils/crypto.cpp
    ${SRC}/utils/time_utils.cpp
)

target_compile_features(${APP} PUBLIC cxx_std_20)

target_link_libraries(${APP} 
    OpenSSL::SSL
    utils
    libfort::fort
)

# tests

set(TEST_DIR test)

include_directories(
    ${LIB}/googletest/googletest/include
)

add_executable(test 
    ${TEST_DIR}/g_test.cpp
    ${TEST_DIR}/block_test.cpp
    ${TEST_DIR}/utils_test.cpp
    ${TEST_DIR}/miner_test.cpp
    ${TEST_DIR}/libfort_test.cpp
    ${TEST_DIR}/jsonlib_test.cpp
    ${TEST_DIR}/blockchain_test.cpp
    ${TEST_DIR}/transaction_test.cpp
)

target_link_libraries(test 
    nlohmann_json
    gtest_main 
    spdlog
    utils
    core
    libfort::fort
)
