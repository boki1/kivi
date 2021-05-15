#include <utility>
#include <sstream>

#include "ast_printer.hh"

using et = sa::expression::type;

using std::make_pair;

namespace printer
{
	//!
	//! The next couple of functions are required by the graph drawing utility
	//!

	/**
	 * @brief Creates vertex in the graph
	 * @return The created vertex
	 * @note Required by the 2D graph drawing utility
	 */
	static std::string create_vertex(const sa::expression& expr)
	{
		std::string str = print(expr);

		std::string type_str;
		switch (expr.get_type())
		{
		case et::Nop:
			type_str = "Nop";
			break;
		case et::String:
			type_str = "String";
			break;
		case et::Number:
			type_str = "Number";
			break;
		case et::Identifier:
			type_str = "Identifier";
			break;
		case et::Addition:
			type_str = "Addition";
			break;
		case et::Negation:
			type_str = "Negation";
			break;
		case et::Multiplication:
			type_str = "Multiplication";
			break;
		case et::Division:
			type_str = "Division";
			break;
		case et::Equality:
			type_str = "Equality";
			break;
		case et::ModularDivision:
			type_str = "Modulo";
			break;
		case et::Copy:
			type_str = "Copy";
			break;
		case et::If:
			type_str = "If";
			break;
		case et::While:
			type_str = "While";
			break;
		case et::FunctionCall:
			type_str = "FunctionCall";
			break;
		case et::Sequence:
			type_str = "Sequence";
			break;
		case et::Return:
			type_str = "Return";
			break;
		}

		if (expr.operands().empty())
			return type_str + ' ' + str;
		return type_str;
	}

	/**
	 * @brief Checks whether the atom is simple or not
	 * @return true / false
	 * @note Required by the 2D graph drawing utility
	 */
	static bool is_simple(const sa::expression& e)
	{
		return true;
	}

	/**
	 * @brief Whether the first item has to be separated by its children
	 * @return true / false
	 * @note Required by the 2D graph drawing utility
	 */
	static bool should_separate_first(const sa::expression& e)
	{
		return e.get_type() == et::While;
	}

	/**
	 * @brief Whether the full graph of this vertex is a one liner
	 * @return true / false
	 * @note Required by the 2D graph drawing utility
	 */
	static bool isnot_oneliner(const sa::expression& e)
	{
		return !e.operands().empty();
	}

	/**
	 * @brief Gets the children of this vertex
	 * @return Pair with iterator being and end
	 * @note Required by the 2D graph drawing utility
	 */
	static auto vertex_children(const sa::expression& e)
	{
		return make_pair(e.operands().cbegin(), e.operands().cend());
	};

	std::string print(const std::vector<sa::function>& functions) noexcept
	{
		std::stringstream ast_stream;

		for (const auto& fun : functions)
		{
			textbox graph;
			graph.putbox(0, 0, create_tree_graph(
				/* vertex data */ fun.body(),
				/* line limit */ 100,
				create_vertex,
				vertex_children,
				isnot_oneliner,
				is_simple,
				should_separate_first
			));

			ast_stream << "[function] " << fun.name() + ":\n";
			ast_stream << print(fun) + "\n\n\n" << graph.to_string();
		}

		return ast_stream.str();
	}

	std::string print(const sa::function& fun) noexcept
	{
		return print(fun.body(), /* is_statement = */ true);
	}

	// Declare this for later usage
	static std::string next_expression(const sa::expression& expr);

	std::string print(const sa::expression& expr, bool is_statement /* = false */ ) noexcept
	{
		// Iterators pointing to the first and last expression in `expr.operands()`
		const auto& front = expr.operands().cbegin();
		const auto& back = expr.operands().cend();

		switch (expr.get_type())
		{
		case et::Nop:
			return "";
		case et::String:
			return "\"" + std::get<std::string>(expr.terminal()) + "\"";
		case et::Number:
			return std::to_string(std::get<int>(expr.terminal()));
		case et::Identifier:
			return print(std::get<sa::identifier>(expr.terminal()));
		case et::Addition:
			return print(expr, " + ", "()");
		case et::Multiplication:
			return print(expr, " * ", "()");
		case et::Division:
			return print(expr, " / ", "()");
		case et::Equality:
			return print(expr, " == ", "()");
		case et::ModularDivision:
			return print(expr, " % ", "()");
		case et::If:
			return print(expr, " if ", "()");
		case et::Negation:
			return "-(" + next_expression(expr) + ")";
		case et::Sequence:
			if (is_statement)
				return print(expr, "; ", "{}", true);
			else
				return print(expr, ", ", "()");
		case et::Copy:
		{
			if (expr.operands().empty())
				return "??";
			return "(" + print(*back) + " = " + print(*front) + ")";
		}
		case et::While:
		{
			const std::string& condition = print(*expr.peculiar().value());
			const std::string& body = print(expr, ", ", "()", false, 1);
			return "while " + condition + " " + body;
		}
		case et::FunctionCall:
		{
			if (expr.operands().empty())
				return "??";
			return "( " + print(*front) + " )" + print(expr, ", ", "()", false, 1);
		}
		case et::Return:
			return "return ( " + next_expression(expr) + " )";
		}
		return "????";
	}

	std::string print(const sa::identifier& ident) noexcept
	{
		static std::string prefixes = "??FPV";
		std::stringstream sstr{};
		sstr << prefixes[static_cast<int>(ident.get_type())] << std::to_string(ident.index());
		sstr << "\"" << ident.name() << "\"";

		return sstr.str();
	}

	std::string print(const sa::expression& expr,
		const std::string& oper,
		const std::string& separator,
		bool is_statement /* = false */ ,
		unsigned skip_first_n /* = 0 */) noexcept
	{
		bool is_first_iteration = true;
		std::stringstream sstr;
		sstr << separator.at(0);

		for (const auto& operand : expr.operands())
		{
			if (skip_first_n > 0)
			{
				skip_first_n--;
				continue;
			}

			if (!is_first_iteration)
			{
				sstr << oper;
				sstr << print(operand, is_statement);
			}

			is_first_iteration = false;
		}

		if (is_statement)
			sstr << oper;

		sstr << separator.at(1);

		return sstr.str();
	}

	static std::string next_expression(const sa::expression& expr)
	{
		if (expr.operands().empty())
		{
			return "?";
		}

		if (expr.operands().size() == 1)
		{
			return print(expr.operands().front());
		}

		return print(expr, "???", "()");
	}
}
