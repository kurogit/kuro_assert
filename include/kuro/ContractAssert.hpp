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
using contract_violation_handler = void (*)(contract_violation_info const& info);

//! Return the current contract violation handler or nullptr if none was set and the default handler is used.
contract_violation_handler get_contract_violation_handler() noexcept;

//! Set the contract violation handler and return the previous one or nullptr of the previous one is the default handler.
contract_violation_handler set_contract_violation_handler(contract_violation_handler handler) noexcept;

//! Handle the contract violation. Calls the current violation handler.
void handle_contract_violation(const contract_violation_info& info);

//! Some extensions not defined in N4253
inline namespace ext
{
class scoped_contract_violation_handler
{
public:
    explicit scoped_contract_violation_handler(contract_violation_handler handler) noexcept;
    ~scoped_contract_violation_handler() noexcept;

private:
    contract_violation_handler savedHandler_;
};
}  // namespace ext

//! Implementation details required in the header.
namespace detail
{

//! Set the status of the unit test macro. \c true means a contract violation occured.
void set_contract_assert_unit_test_status(bool status) noexcept;

//! Get the status of the unit test macro
bool get_contract_assert_unit_test_status() noexcept;

//! Contract violation handler for use in the unit test macros. Calls \c set_contract_assert_unit_test_status(true).
void contract_assert_unit_test_handler(const contract_violation_info&);

}  // namespace detail

}  // namespace kuro

// Here be macros

#define kuro_contract_assert_pass(exp)                                                                     \
    [&]() {                                                                                                \
        kuro::detail::set_contract_assert_unit_test_status(false);                                         \
        kuro::ext::scoped_contract_violation_handler h_{&kuro::detail::contract_assert_unit_test_handler}; \
        (exp);                                                                                             \
        return !kuro::detail::get_contract_assert_unit_test_status();                                      \
    }()
