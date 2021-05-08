/**
 * @file base.hh
 *
 * The files defines the expression interface which all valid
 * expressions implement.
 */

#ifndef KIVI_SRC_KIVI_BASE_HH_
#define KIVI_SRC_KIVI_BASE_HH_

#include <string>

#include <ast/syntactic_structure.hh>

namespace syntax_analyzer
{
	/*
	 * An abstract class from which all concrete implementations of
	 * expression derive.
	 */
	class expression : public I_evaluable_syntactic_structure
	{
	 public:
		/**
		 * @brief Lists all legal kinds of expression
		 */
		enum class kind
		{
			AdditionOper,
			SubtractionOper,
			DivisionOper,
			MultiplicationOper,
			ModularDivisionOper,
			EqualityOper,
			InequalityOper,
			AssignmentOper,
			NegationOper,
			NopOper,
			StringLiteral,
			NumberLiteral,
			IdentifierExpr,
			Illegal,
			FunctionCallExpr,
			ParameterList
		};

	 private:
		/// Stores the concrete type of expression
		kind m_kind;

	 public:
		/// Construction
		expression() :
			m_kind(kind::Illegal)
		{
		}

		expression(kind kind_) :
			m_kind(kind_)
		{
		}

		virtual ~expression() = default;

		/**
		 * @brief Returns the string representation of the concrete expression
		 * @return String representation
		 */
		virtual std::string to_string() const noexcept
		{
			return "<unknown>";
		};

	 public:
		expression::kind get_kind() const noexcept
		{
			return m_kind;
		}

	};

}

#endif //KIVI_SRC_KIVI_BASE_HH_
