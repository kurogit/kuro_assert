#pragma once

namespace kuro
{

/*!
 * \brief Enum containing the possible build modes for contract assertions.
 * \details Passed as part of contract_violation_info to the current contract violation handler.
 */
enum class contract_assertion_mode
{
    opt,
    test,
    safe
};

/*!
 * \brief Struct containing info for a contract violation.
 * \details Passed to the contract violation handler.
 */
struct contract_violation_info
{
    //! The assertion mode of the contract violation.
    contract_assertion_mode mode;
    //! The source text of the expression that caused the contract violation.
    const char* expression_test;
    //! The filename containing the source code that caused the contract violation.
    const char* filename;
    //! The number of the line the contract violation occurred on.
    unsigned long line_number;
};

//! Type of a contract violation handler.
using contract_violation_handler = void (*) (contract_violation_info const& info);

}  // namespace kuro
