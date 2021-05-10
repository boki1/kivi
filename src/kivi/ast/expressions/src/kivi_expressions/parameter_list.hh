/**
 * @file parameter_list.hh
 * @brief Defines a class which represents a function parameter list
 */
#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_PARAMETER_LIST_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_PARAMETER_LIST_HH_

#include <utility>
#include <vector>

#include <ast/syntactic_structure.hh>

#include "base.hh"

namespace syntax_analyzer
{

/**
 * @brief A function parameter list expression
 */
	class parameter_list_expr : public I_expression
	{
	 private:
		/// The parameters themselves. Each one is kept as a value instance
		std::vector<value> m_params;

	 public:
		parameter_list_expr() = default;

		explicit parameter_list_expr(const value& param1)
			: m_params({ param1 })
		{
		}

		explicit parameter_list_expr(std::vector<value> params)
			: m_params(std::move(params))
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
		const std::vector<value>&
		params() const noexcept
		{
			return m_params;
		}
	};

}

#endif // KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_PARAMETER_LIST_HH_
