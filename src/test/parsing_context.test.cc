/**
 * @file example_test.cc
 * @brief Tests the parsing_context using the catch2 testing framework
 */
#include <string>
#include <catch2/catch2.hpp>

#include <kivi_parser/kivi_parser.tab.hh>   //yy::kivi_parser::syntax_error
#include <parser/parsing_context.hh>

// Executes for each section

std::string fname = "pseudo.kv";
std::string code = "gcd:{}";
syntax_analyzer::parsing_context context(code.c_str(), &fname);

//

TEST_CASE("Parsing context", "[pc]")
{
	SECTION("Scope enter : regular")
	{
		unsigned long curr_scopes = context.all_scopes().size();
		context.enter_scope();
		REQUIRE(context.all_scopes().size() == curr_scopes + 1);
	}

	SECTION("Scope exit : regular")
	{
		context.all_scopes_mut().emplace_back();
		unsigned long curr_scopes = context.all_scopes().size();
		context.exit_scope();
		REQUIRE(context.all_scopes().size() == curr_scopes - 1);
	}

	SECTION("Scope exit _corner case_ : exit from 0 scopes")
	{
		context.all_scopes_mut().clear();
		REQUIRE_THROWS(context.exit_scope());
	}

	SECTION("Define identifier : regular")
	{
		const std::string name = "varIsThis";

		REQUIRE_NOTHROW(
			context.define_parameter(name)
		);

		REQUIRE(context.all_scopes().back().name() == name);
		REQUIRE(context.all_scopes().back().type() == sa::identifier_class::Parameter);
	}

	SECTION("Define identifier _corner case_ : duplication")
	{
		const std::string n = "name";
		REQUIRE_NOTHROW(
			context.define_local(n)
		);

		REQUIRE_THROWS_AS(
			context.define_local(n),
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

		REQUIRE (
			context.use_identifier("name").ident() == sa::identifier(sa::identifier_class::Local, "name")
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
