#ifndef KIVI_IR_CODE_HH
#define KIVI_IR_CODE_HH

#include <optional>
#include <memory>
#include <vector>
#include <string>
#include <variant>
#include <string_view>

namespace intermediate_representation
{
	/**
	 * @brief Three-Address Code
	 * @details Used to represent each individual "fake" instruction
	 */
	class tac
	{
	 public:
		typedef tac* tac_ptr;                     //< The type used for TAC chaining
		typedef int vregister_type;                          //< The indexes of the "fake" (virtual) registers
		typedef std::vector<vregister_type> operands_type;        //< Used to represent all virtual register operands for the current TAC


		/**
		 * @brief Enumeration class containing all the three-address codes
		 */
		enum class type
		{
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
		/// The type of the tac. Default value is type::Nop
		tac::type m_type{ type::Nop };

		/// Reference to function's name (label)
		/// @note empty = none
		std::string m_identifier{};

		/// Offset
		int m_value{};

		/// Pointer to next statement in the chain
		/// The end is marked with nullptr
		tac_ptr m_next{ nullptr };

		/// Used _only_ for the IfNotZero TAC
		/// if var[p0] <> 0, m_condition overrides next.
		std::optional<tac_ptr> m_condition{};

		/// Contains all virtual registers used
		tac::operands_type m_operands{};

	 public:    // Ctors

		/// Default construction
		tac() = default;

		/// Copy construction
		tac(const tac&) = default;

		/// Manual construction - all fields
		explicit tac(type tac_type,
			const operands_type& operands = {},
			int value = {},
			const std::string& i = {},
			const tac_ptr& next = { nullptr },
			const std::optional<tac_ptr>& condition = {});

		/// Init construction
		tac(const std::string& str, int value, const tac::operands_type& operands);

		tac(const std::string& i, const tac::operands_type& operands);

		/// IfNotZero _only_ construction
		tac(const tac_ptr& branch, const tac::operands_type& operands);

		/// Nop construction
		explicit tac(const tac::operands_type& operands);

	 public:    // Getters
		[[nodiscard]] tac::type
		get_type() const
		{
			return m_type;
		}

		[[nodiscard]] const std::string&
		identifier() const
		{
			return m_identifier;
		}

		[[nodiscard]] const int
		value() const
		{
			return m_value;
		}

		[[nodiscard]] const tac_ptr&
		next()
		{
			return m_next;
		}

		[[nodiscard]] /* mut */ tac_ptr&
		next_mut()
		{
			return m_next;
		}

		[[nodiscard]] const std::optional<tac_ptr>&
		condition()
		{
			return m_condition;
		}

		[[nodiscard]] /* mut */ std::optional<tac_ptr>&
		condition_mut()
		{
			return m_condition;
		}

		[[nodiscard]] const std::vector<vregister_type>&
		operands() const
		{
			return m_operands;
		}

		//!
		//! Concrete TAC "named constructors"
		//! @note `tac` stands for Three-Address Code

		[[nodiscard]] tac* tac_nop();

		[[nodiscard]] tac* tac_init(const std::string& ident_name, const tac::operands_type& operands);

		[[nodiscard]] tac* tac_add(const tac::operands_type& operands);

		[[nodiscard]] tac* tac_neg(const tac::operands_type& operands);

		[[nodiscard]] tac* tac_copy(const tac::operands_type& operands);

		[[nodiscard]] tac* tac_read(const tac::operands_type& operands);

		[[nodiscard]] tac* tac_write(const tac::operands_type& operands);

		[[nodiscard]] tac* tac_eq(const tac::operands_type& operands);

		[[nodiscard]] tac* tac_ifnz(const tac::operands_type& operands);

		[[nodiscard]] tac* tac_fcall(const tac::operands_type& operands);

		[[nodiscard]] tac* tac_return(const tac::operands_type& operands);
	};

}

#endif //KIVI_IR_CODE_HH
