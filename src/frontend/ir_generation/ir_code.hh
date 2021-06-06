#ifndef KIVI_IR_CODE_HH
#define KIVI_IR_CODE_HH

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace intermediate_representation
{
/**
 * @brief Three-Address Code
 * @details Used to represent each individual "fake" instruction
 */
	class tac
	{
	 public:
		typedef tac* tac_ptr;             //< The type used for TAC chaining
		typedef unsigned vregister_type; //< The indexes of the "fake" (virtual) registers
		typedef std::vector<vregister_type> operands_type; //< Used to represent all virtual register expected_actual_operands for the current TAC

		/**
		 * @brief Enumeration class containing all the three-address codes
		 */
		enum class type
		{
			Nop,    ///< No operation
			Init,    ///< Store a pointer to a value at address &identifier + offset where identifier is a function's base
			Add,    ///< Perform addition
			Negate, ///< Negation
			Multiplication, ///< Multiplication
			Division,        ///< Division
			Modulo, ///< Modulo operator
			Copy,            ///< Assign a copy of another variable
			Equals,            ///< Whether two values are equal
			IfNotZero,        ///< Perform branch if not zero
			FunctionCall,    ///< Function call
			Return, ///< Return value
			Goto ///< Unconditional branch to label
		};

	 private:
		/// The type of the tac. Default value is type::Nop
		tac::type m_type{ type::Nop };

		/// Reference to function's name (label)
		std::string m_identifier{};

		/// Value
		int m_value{};

		/// Label and mark whether it is a function
		std::optional<std::pair<std::string_view, bool>> m_label;

		/// Pointer to next statement in the chain
		/// The end is marked with nullptr
		tac_ptr m_next{ nullptr };

		/// Used _only_ for the IfNotZero TAC
		/// TODO: Change to std::optional
		/// Problem: Cannot get pointer to the value stored inside the std::optional<>
		/// Current workaround: Store an additional boolean to denote whether m_conditional is used
		tac_ptr m_condition{ nullptr };
		bool m_has_condition{ false };
		std::optional<std::string_view> m_branching_label;

		/// Contains all virtual registers used
		tac::operands_type m_operands{};

	 public: // Ctors
		/// Default construction
		tac() = default;

		/// Copy construction
		tac(const tac&) = default;

		/// Manual construction - all fields
		explicit tac(type tac_type, const operands_type& operands = {}, int value = {}, const std::string& i = {},
			tac_ptr condition = nullptr, const tac_ptr& next = { nullptr });

		/// Init construction
		tac(const std::string& str, int value, const tac::operands_type& operands);

		tac(const std::string& i, const tac::operands_type& operands);

		/// IfNotZero _only_ construction
		tac(const tac_ptr& branch, const tac::operands_type& operands);

		/// Goto _only_ construction
		explicit tac(tac_ptr branch);

		/// Nop construction
		explicit tac(const tac::operands_type& operands);

	 public: // Getters
		[[nodiscard]] tac::type get_type() const
		{
			return m_type;
		}

		[[nodiscard]] const std::string& identifier() const
		{
			return m_identifier;
		}

		[[nodiscard]] const int value() const
		{
			return m_value;
		}

		[[nodiscard]] const tac_ptr& next()
		{
			return m_next;
		}

		[[nodiscard]] /* mut */ tac_ptr& next_mut()
		{
			return m_next;
		}

		[[nodiscard]] std::optional<tac_ptr> condition()
		{
			if (m_has_condition)
				return { m_condition };
			return {};
		}

		[[nodiscard]] /* mut */ tac_ptr& condition_mut()
		{
			return m_condition;
		}

		[[nodiscard]] tac_ptr* condition_double_ptr() noexcept
		{
			return &m_condition;
		}

		[[nodiscard]] tac_ptr* next_double_ptr() noexcept
		{
			return &m_next;
		}

		/**
		 * @brief Put a label before this TAC statement
		 * @param label_name The name of the label
		 * @param is_function Mark whether this label is the beginning of a function or not
		 * @return true if value have been successfully placed, and false if not
		 */
		bool labelize(const std::string_view& label_name, bool is_function = false)
		{
			if (m_label.has_value())
				return false;

			m_label.emplace(label_name, is_function);
			return true;
		}


		void set_has_condition(bool has = true)
		{
			m_has_condition = has;
		}

		/**
		 * @warning Unsafe
		 * @brief Returns the contained pointed _without_ checking whether there is an actual value
		 * @note Use with caution! Be absolutely sure that there is an actual value store in the std::optional<>
		 * @note If no actual value is present a nullptr is returned!
		 * @return Pointer to the code structure
		 */
		[[nodiscard]] /* unsafe */ tac_ptr condition_ptr() const /* unsafe */
		{
			return m_condition;
		}

		void set_condition_ptr(tac_ptr ptr)
		{
			m_condition = ptr;
		}

		[[nodiscard]] const std::vector<vregister_type>& operands() const
		{
			return m_operands;
		}

		void place_branching_label(const std::string_view& t_label)
		{
			if (get_type() != type::IfNotZero || m_branching_label.has_value())
				return;

			m_branching_label.emplace(t_label);
		}

		[[nodiscard]] std::string_view branching_label() const
		{
			return m_branching_label.value_or("[NO_LABEL]");
		}

		[[nodiscard]] std::string_view label() const
		{
			return m_label.value_or(std::make_pair("[NO LABEL]", false)).first;
		}

		[[nodiscard]] bool is_function_label() const
		{
			return m_label.value_or(std::make_pair("[NO LABEL]", false)).second;
		}

		[[nodiscard]] bool has_label() const
		{
			return m_label.has_value();
		}
		[[nodiscard]] bool has_branching_label() const
		{
			return m_branching_label.has_value();
		}
	};
} // namespace intermediate_representation

#endif // KIVI_IR_CODE_HH
