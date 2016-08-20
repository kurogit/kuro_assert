#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <type_traits>

#include <kuro/ContractAssert.hpp>

TEST_CASE("test_contract_assertion_mode")
{
    using kuro::contract_assertion_mode;

    contract_assertion_mode m = contract_assertion_mode::opt;
    (void)m;
    m = contract_assertion_mode::test;
    (void)m;
    m = contract_assertion_mode::safe;
    (void)m;
}

TEST_CASE("test_contract_violation_info")
{
    using kuro::contract_violation_info;

    contract_violation_info info;
    info.mode = kuro::contract_assertion_mode::safe;
    info.expression_test = "false";
    info.filename = "Test.cpp";
    info.line_number = 42;

    (void)info;
}

TEST_CASE("test_contract_violation_handler_matches_specification")
{
    using kuro::contract_violation_handler;
    using kuro::contract_violation_info;

    CHECK((std::is_same<kuro::contract_violation_handler, void (*)(const contract_violation_info&)>::value));
}

void test_handler(kuro::contract_violation_info const&)
{
}
void test_handler_2(kuro::contract_violation_info const&)
{
}

TEST_CASE("test_set_and_get_contract_violation_handler")
{
    using kuro::get_contract_violation_handler;
    using kuro::set_contract_violation_handler;

    // calling get_contract_violation_handler first, returns nullptr
    CHECK_FALSE(get_contract_violation_handler());

    // Setting the first handler return nullptr
    CHECK_FALSE(set_contract_violation_handler(&test_handler));

    // After setting a handler it should be returned
    CHECK(get_contract_violation_handler() == &test_handler);

    // If another handler is set the previous one should be retuerned
    CHECK(set_contract_violation_handler(&test_handler_2) == &test_handler);

    // And returned again
    CHECK(get_contract_violation_handler() == &test_handler_2);
}
