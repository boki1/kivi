#ifndef KIVI_IR_CODE_HH
#define KIVI_IR_CODE_HH

#include <optional>
#include <memory>
#include <vector>
#include <string>
#include <variant>

namespace intermediate_representation {
    class tac {
    public:
        /// The type of the atom when one is required
        typedef std::variant<std::monostate, int, std::string> atom_type;
        /// The indexes of the fake registers
        typedef int fake_register_type;
        /**
         * @brief Enumeration class containing all the the three - address codes that KIVI uses
         */
        enum class type {
            Nop,            //< No operation
            Init,           //< Assign value
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

        /// The atom
        tac::atom_type m_atom;

        /// Pointer to next statement in the chain. The end is marked with nullptr
        std::shared_ptr<tac> m_next{nullptr};

        /// Used for IfNotZero - if var[p0] <> 0, m_condition overrides next.
        std::optional<std::shared_ptr<tac>> m_condition{nullptr};

        /// Variable indexes
        std::vector<fake_register_type> m_operands{};

    public:
        tac() = default;
        ~tac() = default;

    public:
        [[nodiscard]] type tac_type() const;

        [[nodiscard]] const atom_type &atom() const;

        [[nodiscard]] const std::shared_ptr <tac> &next() const;

        [[nodiscard]] const std::optional<std::shared_ptr<tac>> &condition() const;

        [[nodiscard]] const std::vector<fake_register_type> &operands() const;

    };
}

#endif //KIVI_IR_CODE_HH
