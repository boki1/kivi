#include <kivi_expressions/binary_operation.hh>
#include <kivi_expressions/unary_operation.hh>
#include <kivi_expressions/function_call.hh>
#include <kivi_stmts/if.hh>
#include <kivi_stmts/var.hh>
#include <kivi_stmts/expression.hh>
#include <kivi_stmts/compound.hh>
#include <kivi_stmts/return.hh>
#include "ast.hh"
#include "kivi_stmts/while.hh"

namespace st = syntax_tree;

using nod = st::ast::node;

namespace syntax_tree
{
	//!
	//! Extract overloads accepting syntactic structures
	//!

	nod::node(const sa::function& fun) :
		m_kind(node_kind::Function),
		m_value(fun),
		m_str(fun.to_string())
	{

		proceed_with(fun.body());

		// TODO:
		// proceed_with(fun.parameter_list());
	}

	nod::node(const sa::statement& stmt) :
		m_kind(stmt.get_kind()),
		m_value(stmt),
		m_str(stmt.to_string())
	{
		using s = sa::statement::kind;
		switch (stmt.get_kind())
		{
		case s::WhileStmt:
		{
			auto s = dynamic_cast<const sa::while_stmt&>(stmt);
			proceed_with(s.than_body());
			proceed_with(s.condition());
			break;
		}
		case s::IfStmt:
		{
			auto s = dynamic_cast<const sa::if_stmt&>(stmt);
			proceed_with(s.than_body());
			proceed_with(s.condition());
			break;
		}
		case s::VarStmt:
		{
			auto s = dynamic_cast<const sa::var_stmt&>(stmt);
			proceed_with(sa::identifier(sa::identifier_class::Local, s.var()));
			proceed_with(s.val());
			break;
		}
		case s::ReturnStmt:
		{
			auto s = dynamic_cast<const sa::return_stmt&>(stmt);
			proceed_with(s.retval());
			break;
		}
		case s::CompoundStmt:
		{
			auto s = dynamic_cast<const sa::compound_stmt&>(stmt);
			// TODO:
			// It might be clearer just to do not note it in any printable way
			// Consider some sort of "sticky" bottom which changes parents until its turn doesn't come up
			break;
		}
		case s::ExpressionStmt:
		{
			auto s = dynamic_cast<const sa::expression_stmt&>(stmt);
			proceed_with(s.expr());
			break;
		}
		case s::Illegal:
			break;
		}

	}

	[[noreturn]] nod::node(const sa::expression& expr) :
		m_kind(expr.get_kind()),
		m_value(expr),
		m_str(expr.to_string())
	{
		using e = sa::expression::kind;
		switch (expr.get_kind())
		{
			// Binary operations
		case e::AdditionOper:
		case e::SubtractionOper:
		case e::DivisionOper:
		case e::MultiplicationOper:
		case e::ModularDivisionOper:
		case e::AssignmentOper:
		case e::EqualityOper:
		case e::InequalityOper:
		{
			auto bin_oper = dynamic_cast<const sa::binary_operation&> (expr);
			proceed_with(bin_oper.left());
			proceed_with(bin_oper.right());
			break;
		}

			// Unary operations
		case e::NegationOper:
		{
			auto unary_oper = dynamic_cast<const sa::unary_operation&>(expr);
			proceed_with(unary_oper.operand());
			break;
		}

			// Terminals
		case e::NopOper:
		case e::StringLiteral:
		case e::NumberLiteral:
		case e::IdentifierExpr:
			// Do nothing - no additional child nodes exist.
			break;

			// Function calls
		case e::FunctionCallExpr:
		{
			auto funcall = dynamic_cast<const sa::function_call_expr&>(expr);
			proceed_with(funcall.params());
			break;
		}

		case e::Illegal:
		case e::ParameterList:
			// Parameter list cannot be met by itself, it is always directly contained in a function call expression, so
			// if one is met we can directly treat is as an illegal expression.
			break;
		}

	}

	nod::node(const sa::identifier& ident) :
		m_kind(node_kind::Identifier),
		m_value(ident),
		m_str(ident.to_string()),
		m_children(/* empty */ )
	{
		// Empty
	}

	void nod::proceed_with(const sa::I_syntactic_structure& str)
	{
	}

	void nod::proceed_with(ast::node&& child)
	{

	}

	bool operator==(const ast::postorder_iterator&, const ast::postorder_iterator&)
	{

	}

	bool operator!=(const ast::postorder_iterator&, const ast::postorder_iterator&)
	{

	}

}