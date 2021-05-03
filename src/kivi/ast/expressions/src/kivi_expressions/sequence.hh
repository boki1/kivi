/**
 * @file sequence.hh
 * @brief Defines a structure which holds "a couple of expressions"
 */
#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_SEQUENCE_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_SEQUENCE_HH_

#include <vector>

#include "base.hh"

namespace syntax_analyzer
{
	class sequence
	{
	 private:
		std::vector<I_expression> m_exprs;

	 public:
		sequence() = default;

		template<typename ...T>
		explicit sequence(T&& ... args)
			: m_exprs(std::forward<T>(args)...)
		{
		}

	 public:
		void append(I_expression&& expr) noexcept
		{
			m_exprs.push_back(std::move(expr));
		}

	 public:
		const std::vector<I_expression>& exprs() const noexcept
		{
			return m_exprs;
		}

	};

}

#endif //KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_SEQUENCE_HH_
