/*!
 * \file
 * \details This file is part of https://github.com/kurogit/kuro_assert which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <kuro/ContractAssert.hpp>

#include "KuroAssertTestModes.hpp"

TEST_CASE_FIXTURE(Test_assertion_modes_fixture, "test none mode")
{
    SUBCASE("pass checks")
    {
        CHECK(kuro_contract_assert_pass(failOpt()));
        CHECK(kuro_contract_assert_pass(failTest()));
        CHECK(kuro_contract_assert_pass(failSafe()));
    }
    SUBCASE("fail checks")
    {
        CHECK(kuro_contract_assert_fail_opt(failOpt()));
        CHECK(kuro_contract_assert_fail_test(failOpt()));
        CHECK(kuro_contract_assert_fail_safe(failOpt()));

        CHECK(kuro_contract_assert_fail_opt(failTest()));
        CHECK(kuro_contract_assert_fail_test(failTest()));
        CHECK(kuro_contract_assert_fail_safe(failTest()));

        CHECK(kuro_contract_assert_fail_opt(failSafe()));
        CHECK(kuro_contract_assert_fail_test(failSafe()));
        CHECK(kuro_contract_assert_fail_safe(failSafe()));
    }
}
