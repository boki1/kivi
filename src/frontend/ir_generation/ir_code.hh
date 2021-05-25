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
	typedef tac *tac_ptr;			 //< The type used for TAC chaining
	typedef unsigned vregister_type; //< The indexes of the "fake" (virtual) registers
	typedef std::vector<vregister_type>
		operands_type; //< Used to represent all virtual register operands for the current TAC

	/**
	 * @brief Enumeration class containing all the three-address codes
	 */
	enum class type
	{
		Nop,	///< No operation
		Init,	///< Store a pointer to a value at address &identifier + offset where identifier is a function's base
		Add,	///< Perform addition
		Negate, ///< Negation
		Multiplication, ///< Multiplication
		Division,		///< Division
		ModuloOperator, ///< ModuloOperator operator
		Copy,			///< Assign a copy of another variable
		Read,			///< Read from address
		Write,			///< Write at address
		Equals,			///< Whether two values are equal
		IfNotZero,		///< Perform branch if not zero
		FunctionCall,	///< Function call
		Return			///< Return value
	};

  private:
	/// The type of the tac. Default value is type::Nop
	tac::type m_type{type::Nop};

	/// Reference to function's name (label)
	/// @note empty = none
	std::string m_identifier{};

	/// Offset
	int m_value{};

	/// Pointer to next statement in the chain
	/// The end is marked with nullptr
	tac_ptr m_next{nullptr};

	/// Used _only_ for the IfNotZero TAC
	/// TODO: Change to std::optional
	/// Problem: Cannot get pointer to the value stored inside the std::optional<>
	/// Current workaround: Store an additional boolean to denote whether m_conditional is used
	tac_ptr m_condition{nullptr};
	bool m_has_condition{false};

	/// Contains all virtual registers used
	tac::operands_type m_operands{};

  public: // Ctors
	/// Default construction
	tac() = default;

	/// Copy construction
	tac(const tac &) = default;

	/// Manual construction - all fields
	explicit tac(type tac_type, const operands_type &operands = {}, int value = {}, const std::string &i = {},
				 tac_ptr condition = nullptr, const tac_ptr &next = {nullptr});

	/// Init construction
	tac(const std::string &str, int value, const tac::operands_type &operands);

	tac(const std::string &i, const tac::operands_type &operands);

	/// IfNotZero _only_ construction
	tac(const tac_ptr &branch, const tac::operands_type &operands);

	/// Nop construction
	explicit tac(const tac::operands_type &operands);

  public: // Getters
	[[nodiscard]] tac::type get_type() const
	{
		return m_type;
	}

	[[nodiscard]] const std::string &identifier() const
	{
		return m_identifier;
	}

	[[nodiscard]] const int value() const
	{
		return m_value;
	}

	[[nodiscard]] const tac_ptr &next()
	{
		return m_next;
	}

	[[nodiscard]] /* mut */ tac_ptr &next_mut()
	{
		return m_next;
	}

	[[nodiscard]] std::optional<tac_ptr> condition()
	{
		if (m_has_condition)
			return {m_condition};
		return {};
	}

	[[nodiscard]] /* mut */ tac_ptr &condition_mut()
	{
		return m_condition;
	}

	[[nodiscard]] tac_ptr *condition_double_ptr() noexcept
	{
		return &m_condition;
	}

	[[nodiscard]] tac_ptr *next_double_ptr() noexcept
	{
		return &m_next;
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

	[[nodiscard]] const std::vector<vregister_type> &operands() const
	{
		return m_operands;
	}
};
} // namespace intermediate_representation

#endif // KIVI_IR_CODE_HH
