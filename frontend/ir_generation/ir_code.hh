#ifndef KIVI_IR_CODE_HH
#define KIVI_IR_CODE_HH

#include <optional>
#include <memory>
#include <vector>
#include <string>
#include <variant>
#include <string_view>

namespace intermediate_representation {
    class tac {
    public:
        /// The indexes of the fake registers
        typedef int fake_register_type;
        /**
         * @brief Enumeration class containing all the the three - address codes that KIVI uses
         */
        enum class type {
            Nop,            //< No operation
            Init,           //< Store a pointer to a value at address &identifier + offset where identifier is a function's base
            Add,            //< Perform addition
            Negate,         //< Negation
            Copy,           //< Assign a copy of another variable
            Read,           //< Read from address
            Write,          //< Write at address
            Equals,         //< Whether two values are equal
            IfNotZero,      //< Perform branch if not zero
            FunctionCall,   //< Function call
            Return          //< Return value
        };

    private:
        /// The type of the tac
        tac::type m_type{type::Nop};

        /// Reference to functions name (label)
        /// @note empty = none
        std::string m_identifier{};

        /// Offset
        off_t m_value{};

        /// Pointer to next statement in the chain. The end is marked with nullptr
        std::shared_ptr<tac> m_next{nullptr};

        /// Used for IfNotZero - if var[p0] <> 0, m_condition overrides next.
        std::optional<std::shared_ptr<tac>> m_condition{nullptr};

        /// Variable indexes
        std::vector<fake_register_type> m_operands{};

    public:
        tac() = default;
        tac(tac::type &tac_type, std::vector<fake_register_type> &operands);
        tac(tac::type &tac_type, std::string_view str = nullptr, int i = 0);
        tac(std::shared_ptr<tac> b, std::vector<fake_register_type> &operands, tac::type tac_type = type::IfNotZero);
        tac(std::vector<fake_register_type> &operands);
        ~tac() = default;

    public:
        [[nodiscard]] type tac_type() const;
        [[nodiscard]] std::string identifier() const;
        [[nodiscard]] off_t value() const;
        [[nodiscard]] const std::shared_ptr<tac> &next() const;
        [[nodiscard]] const std::optional<std::shared_ptr<tac>> &condition() const;
        [[nodiscard]] const std::vector<fake_register_type> &operands() const;
    };
}

#endif //KIVI_IR_CODE_HH
