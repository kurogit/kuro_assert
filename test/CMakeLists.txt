
# Get doctest
file(DOWNLOAD 
    "https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h"
    ${CMAKE_CURRENT_BINARY_DIR}/include/doctest.h
    SHOW_PROGRESS)

set(kuro_assert_test_SOURCES src/KuroAssertTest.cpp)

foreach(_test_src ${kuro_assert_test_SOURCES})
    get_filename_component(_test_name ${_test_src} NAME_WE)
    add_executable(${_test_name} ${_test_src})
    target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
    target_link_libraries(${_test_name} PRIVATE ${PROJECT_NAME})
    add_test(NAME ${_test_name} COMMAND ${_test_name})
endforeach()
