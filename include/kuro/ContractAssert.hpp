#pragma once

namespace kuro
{

/*!
 * \brief Enum containing the possible build modes for contract assertions
 * \details Passed as part of contract_violation_info to the current contract violation handler
 */
enum class contract_assertion_mode
{
    opt,
    test,
    safe
};

}  // namespace kuro
