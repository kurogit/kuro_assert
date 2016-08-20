#include <kuro/ContractAssert.hpp>

namespace kuro
{

namespace
{
contract_violation_handler globalHandler = nullptr;
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

}  // namespace kuro
