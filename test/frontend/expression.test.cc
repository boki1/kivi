/**
 * @file expression.test.cc
 * @brief Tests the expression class used by the parser
 */

#include <catch2/catch2.hpp>
#include <parser/syntax.hh>

using std::make_shared;
using std::move;

using namespace syntax_analyzer;
using et = expression::type;

TEST_CASE("Expression class", "[expression]")
{
	SECTION("operator== : regular")
	{
		expression expr1{et::Addition, {expression(1), expression(2)}};
		expression expr2{expr1};

		REQUIRE(expr1 == expr2);
	}

	SECTION("operator== : regular peculiar")
	{
		// expr1 <=> if 1: return 1;
		expression expr1 = expression{expression::type::If,
									  {move(expression(expression(1))), move(expression(et::Return, {expression(1)}))}};

		expression expr2{expr1};

		REQUIRE(expr1 == expr2);
	}

	SECTION("operator== : negative peculiar")
	{
		// expr1 <=> if 1: return 1;
		expression expr1 = expression{expression::type::If,
									  {move(expression(expression(1))), move(expression(et::Return, {expression(1)}))}};

		// expr2 <=> if 1: return 3;
		expression expr2 = expression{expression::type::If,
									  {move(expression(expression(1))), move(expression(et::Return, {expression(3)}))}};

		REQUIRE(expr1 != expr2);
	}
}
