/**
 * @file example_test.cc
 * @brief Makes sure that all features used in the example usages provided by the KIVI developers are well tested
 * and that all examples work properly.
 */

#include <exception>
#include <parser/parser.tab.hh>
#include <catch2/catch2.hpp>
#include <fstream>

TEST_CASE("Parameters", "[params]")
{
    SECTION("No parameters")
    {
        std::string fake_file = "fake.kv";
        std::string code = "foo: return 1;";
        syntax_analyzer::parsing_context ctx(code.c_str(), &fake_file);
        yy::kivi_parser parser{ctx};
        parser.parse();

        REQUIRE(ctx.functions().at(0).parameters() == 0);
    }

    SECTION("Many parameters")
    {
        std::string filename = "fun.kv";
        std::string code = "fun p, q, param: {}";
        syntax_analyzer::parsing_context fun_kv_ctx(code.c_str(), &filename);
        yy::kivi_parser parser{fun_kv_ctx};
        parser.parse();
        REQUIRE(fun_kv_ctx.functions().at(0).parameters() == 3);
    }

    SECTION("Locals")
    {
        std::string filename = "fun.kv";
        std::string code = "fun p, q, param: { auto var = 3; }";
        syntax_analyzer::parsing_context fun_kv_ctx(code.c_str(), &filename);
        yy::kivi_parser parser{fun_kv_ctx};
        REQUIRE(parser.parse() == 0);
        REQUIRE(fun_kv_ctx.functions().at(0).locals() == 1);
    }
}
