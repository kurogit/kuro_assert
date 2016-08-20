cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(kuro_assert
        VERSION 0.1.0
        LANGUAGES CXX)

# Options
option(KURO_ASSERT_BUILD_SHARED "Build kuro::assert as shared library" OFF)
option(KURO_ASSERT_BUILD_TESTING "Build unit tests" OFF)

set(kuro_assert_HEADERS "include/kuro/ContractAssert.hpp")
set(kuro_assert_SOURCES "src/ContractAssert.cpp")

# Config for YouCompleteMe
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/.ycm_extra_conf.py.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/.ycm_extra_conf.py"
               @ONLY)

set(BUILD_SHARED_LIBS ${KURO_ASSERT_BUILD_SHARED})
add_library(${PROJECT_NAME} ${kuro_assert_HEADERS} ${kuro_assert_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(${KURO_ASSERT_BUILD_TESTING})
    enable_testing()
    # Add unit tests using doctest
    add_subdirectory(test)
endif()
