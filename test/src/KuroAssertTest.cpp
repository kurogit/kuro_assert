/*!
 * \file
 * \details This file is part of https://github.com/kurogit/kuro_assert which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
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

TEST_CASE("test exitance of members in contract_violation_info")
{
    using kuro::contract_violation_info;

    contract_violation_info info;
    info.mode = kuro::contract_assertion_mode::safe;
    info.expression_test = "false";
    info.filename = "Test.cpp";
    info.line_number = 42;

    (void)info;
}

TEST_CASE("test that contract_violation_handler matches the specification")
{
    using kuro::contract_violation_handler;
    using kuro::contract_violation_info;

    CHECK((std::is_same<kuro::contract_violation_handler, void (*)(const contract_violation_info&)>::value));
}

void test_handler(kuro::contract_violation_info const& /*unused*/)
{
}
void test_handler_2(kuro::contract_violation_info const& /*unused*/)
{
}

TEST_CASE("test set_ and get_contract_violation_handler")
{
    using kuro::get_contract_violation_handler;
    using kuro::set_contract_violation_handler;

    // calling get_contract_violation_handler first, returns nullptr
    CHECK_FALSE(get_contract_violation_handler());

    // Setting the first handler returns nullptr
    CHECK_FALSE(set_contract_violation_handler(&test_handler));

    // After setting a handler it should be returned
    CHECK(get_contract_violation_handler() == &test_handler);

    // If another handler is set the previous one should be returned
    CHECK(set_contract_violation_handler(&test_handler_2) == &test_handler);

    // And returned again
    CHECK(get_contract_violation_handler() == &test_handler_2);

    // Reset handler
    set_contract_violation_handler(nullptr);
}

/*
// Not testable because of abort
TEST_CASE("test default")
{
    kuro_contract_assert(42 == 1);
}
*/

namespace testns_handler
{

int errCount = 0;

void testHandler(const kuro::contract_violation_info& /*unused*/)
{
    ++errCount;
}

TEST_CASE("test a previously set contract violation handler")
{
    kuro::scoped_contract_violation_handler h{&testHandler};

    REQUIRE(errCount == 0);

    kuro::contract_violation_info info = {kuro::contract_assertion_mode::test, "just a test", __FILE__, __LINE__};

    kuro::handle_contract_violation(info);

    REQUIRE(errCount == 1);
}

}  // namespace testns_handler

struct Test_contract_assert_pass_fixture
{
    void testPass()
    {
        // Nothing
    }
    void testFail()
    {
        kuro_contract_assert(42 == 1);
    }
};
TEST_CASE_FIXTURE(Test_contract_assert_pass_fixture, "test contract_assert_pass")
{
    // Check that the default handler is active.
    REQUIRE_FALSE(kuro::get_contract_violation_handler());

    CHECK(kuro_contract_assert_pass(testPass()));
    CHECK_FALSE(kuro_contract_assert_pass(testFail()));

    // Check that the default handler is active again.
    REQUIRE_FALSE(kuro::get_contract_violation_handler());
}
