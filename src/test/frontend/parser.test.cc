/**
 * @file parser.test.cc
 * @brief Tests the syntactical analysis stage of the compiler
 */

#include <memory>
#include <vector>

#include <catch2/catch2.hpp>
#include <parser/parser.tab.hh>
#include <parser/parsing_context.hh>

using std::make_shared;
using std::move;

using namespace syntax_analyzer;
using et = expression::type;

std::string fake_file = "fake";

TEST_CASE("Syntactical analysis", "[parser]")
{
	SECTION("Simple function parse : regular")
	{
		std::string code = "foo n: return 1;";
		parsing_context ctx(code.c_str(), &fake_file);
		yy::kivi_parser parser{ctx};

		REQUIRE(parser.parse() == 0);

		auto expected = sa::expression {et::Return, {expression(1)}};
		auto implicit = sa::expression {et::Return, {expression(0)}};
		const auto &fun = ctx.functions().at(0);

		REQUIRE(ctx.functions().size() == 1);
		REQUIRE(expected == fun.body().operands().at(0));
		REQUIRE(implicit == fun.body().operands().at(1));
		REQUIRE(fun.parameters() == 1);
		REQUIRE(fun.locals() == 0);
	}

	SECTION("Simple function parse : syntax error")
	{
		std::string code = "foo: { auto a = 3; auto a = 4; } ";
		parsing_context ctx(code.c_str(), &fake_file);
		yy::kivi_parser parser{ctx};

		REQUIRE(parser.parse() == 1);
	}
};