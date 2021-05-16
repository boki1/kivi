/**
 * @file parameter_list.hh
 * @brief Defines a class which represents a function parameter list
 */
#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_PARAMETER_LIST_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_PARAMETER_LIST_HH_

#include <utility>
#include <vector>

#include "parser/syntactic_structure.hh"

#include "sequence.hh"
#include "base.hh"

namespace syntax_analyzer
{

/**
 * @brief A function parameter list expression
 */
	class parameter_list_expr : public expression
	{
	 private:
		/// The parameters themselves. Each one is kept as a value instance
		std::vector<value> m_params;

	 public:
		parameter_list_expr()
			: expression(expression::kind::ParameterList)
		{
		}

		explicit parameter_list_expr(const value& param1)
			: m_params({ param1 }),
			  expression(expression::kind::ParameterList)
		{
		}

		explicit parameter_list_expr(std::vector<value> params)
			: m_params(std::move(params)),
			  expression(expression::kind::ParameterList)
		{
		}

		/**
		 * @brief Named constructor which maps a sequence onto parameter list
		 * @param seq	The sequence
		 * @return 		The parameter list
		 */
		static parameter_list_expr from_sequence(const sequence& seq)
		{
			std::vector<value> plist(seq.exprs().size());
			for (const auto& c: seq.exprs())
				plist.push_back(c);
			return parameter_list_expr{ plist };
		}

	 public:
		void append(const value& param)
		{
			m_params.push_back(param);
		}

	 public:
		[[nodiscard]] const std::vector<value>&
		params() const noexcept
		{
			return m_params;
		}

		[[nodiscard]] std::string to_string() const noexcept override
		{
			return "<unknown>";
		}
	};

}

#endif // KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_PARAMETER_LIST_HH_
