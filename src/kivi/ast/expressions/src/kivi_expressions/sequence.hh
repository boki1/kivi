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
	/**
	 * @brief A data structure which holds "a couple of expressions"
	 * @note This is not an expression. In the current design this is "marked" as such by a implicit case but in reality
	 * it does not evaluate to value
	 * @todo Remove the implicit cast and define it as a not-expression
	 */
	class sequence
	{
	 private:
		std::vector<I_expression> m_exprs;

	 public:
		sequence() = default;

		template<typename ...T>
		explicit sequence(T&& ... args)
			: m_exprs({std::forward<T>(args)...})
		{
		}

	 public:

		/**
		 * @brief A cast operator to expression
		 * @note This function "makes" sequence an expression. In reality it is more of a function related only statement.
		 * @return Either the last _contained_ expression inside the sequence or an empty one
		 */
		operator I_expression() const noexcept {
			if (!m_exprs.empty()) {
				return I_expression(m_exprs.back());
			}

			return I_expression();
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
