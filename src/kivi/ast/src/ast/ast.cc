#include "ast.hh"

namespace st = syntax_tree;

namespace syntax_tree
{
	ast_node ast::extract(const sa::function& fun)
	{
		return extract(fun.body());
	}

	ast_node ast::extract(const sa::I_statement& stmt)
	{

	}

	ast_node ast::extract(const sa::I_expression& expr)
	{
	}

	ast_node ast::extract(const sa::identifier& ident)
	{
		return ident.name();
	}

}