#
# This file is part of https://github.com/kurogit/kuro_assert which is licensed under the MIT License.
# Copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
#

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

set(BUILD_SHARED_LIBS ${KURO_ASSERT_BUILD_SHARED})

add_library(${PROJECT_NAME} ${kuro_assert_HEADERS} ${kuro_assert_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>" "$<INSTALL_INTERFACE:include>")
# Let CMake handle the correct std flag
target_compile_features(${PROJECT_NAME} PUBLIC
                                          cxx_strong_enums
                                          cxx_noexcept
                                          cxx_nullptr
                                          cxx_auto_type
                                          cxx_inline_namespaces
                                          cxx_uniform_initialization)
# Warnings
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(enabled_warnings -Weverything -Werror -pedantic-errors)
    set(disabled_warnings -Wno-c++98-compat
                          -Wno-padded)
endif()
target_compile_options(${PROJECT_NAME} PRIVATE ${enabled_warnings} ${disabled_warnings})

if(${KURO_ASSERT_BUILD_TESTING})
    enable_testing()
    # Add unit tests using doctest
    add_subdirectory(test)
endif()


set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include/kuro")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "kuro::")

include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)
install(
    FILES "${kuro_assert_HEADERS}"
    DESTINATION "${include_install_dir}"
)
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)
install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)
