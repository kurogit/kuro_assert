#include <kuro/ContractAssert.hpp>

#include <iostream>

namespace kuro
{

namespace
{

//! The currently set handler
contract_violation_handler globalHandler = nullptr;

//! Default handler. Prints violation and calls abort
[[noreturn]] void defaultHandler(const contract_violation_info& info)
{
    std::cerr << "Contract violation detected!\n"
              << "file: " << info.filename << "\n"
              << "line: " << info.line_number << "\n"
              << "failed check: " << info.expression_test << "\n\n";

    std::abort();
}

}  // namespace

contract_violation_handler get_contract_violation_handler() noexcept
{
    return globalHandler;
}

contract_violation_handler set_contract_violation_handler(contract_violation_handler handler) noexcept
{
    auto prevHandler = globalHandler;

    globalHandler = handler;

    return prevHandler;
}

void handle_contract_violation(const contract_violation_info& info)
{
    if(globalHandler == nullptr)
    {
        defaultHandler(info);
    }
    else
    {
        globalHandler(info);
    }
}

inline namespace ext
{
scoped_contract_violation_handler::scoped_contract_violation_handler(contract_violation_handler handler) noexcept
    : savedHandler_{get_contract_violation_handler()}
{
    set_contract_violation_handler(handler);
}
scoped_contract_violation_handler::~scoped_contract_violation_handler() noexcept
{
    set_contract_violation_handler(savedHandler_);
}

}  // namespace ext

namespace detail
{

static bool violationHappened = false;

void set_contract_assert_unit_test_status(bool status) noexcept
{
    violationHappened = status;
}
bool get_contract_assert_unit_test_status() noexcept
{
    return violationHappened;
}
void contract_assert_unit_test_handler(const contract_violation_info& /*unused*/)
{
    set_contract_assert_unit_test_status(true);
}

void contract_assert_unit_test_opt_handler(const kuro::contract_violation_info& info)
{
    violationHappened = info.mode == contract_assertion_mode::opt;
}
void contract_assert_unit_test_test_handler(const kuro::contract_violation_info& info)
{
    violationHappened = info.mode == contract_assertion_mode::test;
}
void contract_assert_unit_test_safe_handler(const kuro::contract_violation_info& info)
{
    violationHappened = info.mode == contract_assertion_mode::safe;
}

}  // namespace detail

}  // namespace kuro
