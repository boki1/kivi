/**
 * @file ir_generation.test.cc
 * @brief Tests the generation of intermediate representation by given AST
 */

#include <catch2/catch2.hpp>
#include <ir_generation/generation_context.hh>
#include <ir_generation/generation_unit.hh>

using std::make_shared;
using std::make_unique;
using std::move;

namespace sa = syntax_analyzer;
namespace ir = intermediate_representation;

// foo n: return 1; return 0;
sa::function foo{ "foo",
		  sa::expression{ sa::expression::type::Return,
				  { sa::expression (1) } },
		  0, 1 };
