/*!
 * \file
 * \details This file is part of https://github.com/kurogit/kuro_assert which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#pragma once

#include <kuro/ContractAssert.hpp>

struct Test_assertion_modes_fixture
{
    void failOpt()
    {
        kuro_contract_assert_opt(false);
    }
    void failTest()
    {
        kuro_contract_assert_test(false);
    }
    void failSafe()
    {
        kuro_contract_assert_safe(false);
    }
};
