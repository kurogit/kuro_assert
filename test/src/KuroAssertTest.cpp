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
