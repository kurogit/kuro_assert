
# Get doctest
file(DOWNLOAD 
    "https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h"
    ${CMAKE_CURRENT_BINARY_DIR}/include/doctest.h
    SHOW_PROGRESS)

add_executable(general_test "src/KuroAssertTest.cpp")
target_include_directories(general_test PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(general_test PRIVATE ${PROJECT_NAME})
add_test(NAME general_test COMMAND general_test)

# All of the follwoing tests differ in the value of KURO_ASSERT_ASSERTION_MODE

add_executable(test_mode_none src/KuroAssertTestModes.hpp src/KuroAssertTestModeNone.cpp)
target_include_directories(test_mode_none PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(test_mode_none PRIVATE ${PROJECT_NAME})
target_compile_definitions(test_mode_none PRIVATE KURO_ASSERT_ASSERTION_MODE=0)
add_test(NAME test_mode_none COMMAND test_mode_none)

add_executable(test_mode_opt src/KuroAssertTestModes.hpp src/KuroAssertTestModeOpt.cpp)
target_include_directories(test_mode_opt PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(test_mode_opt PRIVATE ${PROJECT_NAME})
target_compile_definitions(test_mode_opt PRIVATE KURO_ASSERT_ASSERTION_MODE=1)
add_test(NAME test_mode_opt COMMAND test_mode_opt)

add_executable(test_mode_test src/KuroAssertTestModes.hpp src/KuroAssertTestModeTest.cpp)
target_include_directories(test_mode_test PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(test_mode_test PRIVATE ${PROJECT_NAME})
target_compile_definitions(test_mode_test PRIVATE KURO_ASSERT_ASSERTION_MODE=2)
add_test(NAME test_mode_test COMMAND test_mode_test)

add_executable(test_mode_safe src/KuroAssertTestModes.hpp src/KuroAssertTestModeSafe.cpp)
target_include_directories(test_mode_safe PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(test_mode_safe PRIVATE ${PROJECT_NAME})
target_compile_definitions(test_mode_safe PRIVATE KURO_ASSERT_ASSERTION_MODE=3)
add_test(NAME test_mode_safe COMMAND test_mode_safe)
