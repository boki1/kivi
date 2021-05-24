/**
 * @file example_test.cc
 * @brief Tests the parsing_context using the catch2 testing framework
 */
#include <string>

#include <catch2/catch2.hpp>
#include <parser/parser.tab.hh>   //yy::kivi_parser::syntax_error
#include <parser/parsing_context.hh>

using std::move;

std::string fname = "pseudo.kv";
std::string code = "gcd:{}";
syntax_analyzer::parsing_context context(code.c_str(), &fname);

TEST_CASE("Parsing context", "[pc]")
{
	SECTION("Scope enter : regular")
	{
		unsigned long curr_scopes = context.scopes().size();
		context.enter_scope();
		REQUIRE(context.scopes().size() == curr_scopes + 1);
	}

	SECTION("Scope exit : regular")
	{
		context.scopes_mut().emplace_back();
		unsigned long curr_scopes = context.scopes().size();
		context.exit_scope();
		REQUIRE(context.scopes().size() == curr_scopes - 1);
	}

	SECTION("Scope exit _corner case_ : exit from 0 scopes")
	{
		context.scopes_mut().clear();
		REQUIRE_THROWS(context.exit_scope());
	}

	SECTION("Define identifier : regular")
	{
		REQUIRE_NOTHROW(context.define_parameter("foo"));

		REQUIRE(context.scopes().back().name() == "foo");
		REQUIRE(context.scopes().back().get_type() == sa::identifier::type::Parameter);
	}

	SECTION("Define identifier _corner case_ : duplication")
	{
		REQUIRE_NOTHROW(context.define_local("foo"));

		REQUIRE_THROWS_AS(
			context.define_local("foo"),
			yy::kivi_parser::syntax_error
		);
	}

	SECTION("Use identifier : regular)")
	{
		REQUIRE_NOTHROW (
			context.define_local("regular_ident")
		);

		REQUIRE_NOTHROW(
			context.use_identifier("regular_ident")
		);
	}

	SECTION("Use identifier _corner case_ : illegal case)")
	{
		REQUIRE_NOTHROW (
			context.define_local("haha")
		);

		REQUIRE_THROWS_AS (
			context.use_identifier("hahaha"),
			yy::kivi_parser::syntax_error
		);
	}

}
