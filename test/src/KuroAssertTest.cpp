#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

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

    CHECK((std::is_same<kuro::contract_violation_handler, void (*) (const contract_violation_info&)>::value));
}
