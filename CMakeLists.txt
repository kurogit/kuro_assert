cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(kuro_assert
        VERSION 0.1.0
        LANGUAGES CXX)

# Options
option(KURO_ASSERT_BUILD_SHARED "Build kuro::assert as shared library" OFF)
set(BUILD_SHARED_LIBS ${KURO_ASSERT_BUILD_SHARED})

set(kuro_assert_HEADERS "include/kuro/ContractAssert.hpp")
set(kuro_assert_SOURCES "src/ContractAssert.cpp")

# Config for YouCompleteMe
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/.ycm_extra_conf.py.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/.ycm_extra_conf.py"
               @ONLY)

add_library(${PROJECT_NAME} ${kuro_assert_HEADERS} ${kuro_assert_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
