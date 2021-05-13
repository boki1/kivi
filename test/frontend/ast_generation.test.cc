/**
 * @file ast_generation.test.cc
 * @brief Tests the transition from sa::function objects
 */

#include <catch2/catch2.hpp>

#include <parser/syntax.hh>
#include <kivi_stmts/return.hh>
#include <ast/ast.hh>

namespace sa = syntax_analyzer;
namespace st = syntax_tree;

TEST_CASE("AST generation", "[ast]")
{
	SECTION("Generate a function from a text chunk")
	{
		sa::function fun{
			"foo",
			sa::return_stmt{}
		};

		st::ast tree{{ fun }};

		const auto& children = tree.root().children();
		const auto actual_node = children[0];
		const auto expected_node = st::ast::node{
			st::ast::node_kind::Function,
			fun
		};

		REQUIRE(actual_node == expected_node);

	};
}
