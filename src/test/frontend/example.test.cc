/**
 * @file example_test.cc
 * @brief Makes sure that all features used in the example usages provided by the KIVI developers are well tested
 * and that all examples work properly.
 */

#include <exception>
#include <parser/parser.tab.hh>
#include <parser/syntax.hh>
#include <catch2/catch2.hpp>
#include <fstream>

//std::string filename = "fun.kv";
std::string filename = "fun.kv";

TEST_CASE("Parameters", "[params]")
{
    SECTION("No parameters")
    {
        std::string code = "foo: return 1;";
        syntax_analyzer::parsing_context ctx(code.c_str(), &filename);
        yy::kivi_parser parser{ctx};
        parser.parse();

        REQUIRE(ctx.functions().at(0).parameters() == 0);
    }

    SECTION("Many parameters")
    {
        std::string code = "fun p, q, param: {}";
        syntax_analyzer::parsing_context fun_kv_ctx(code.c_str(), &filename);
        yy::kivi_parser parser{fun_kv_ctx};
        parser.parse();
        REQUIRE(fun_kv_ctx.functions().at(0).parameters() == 3);
    }

    SECTION("Locals")
    {
        std::string code = "fun p, q, param: { auto var = 3; }";
        syntax_analyzer::parsing_context fun_kv_ctx(code.c_str(), &filename);
        yy::kivi_parser parser{fun_kv_ctx};
        REQUIRE(parser.parse() == 0);
        REQUIRE(fun_kv_ctx.functions().at(0).locals() == 1);
    }
}


TEST_CASE("General", "[general]")
{
    SECTION("Regular comments: check by locals")
    {
        std::string code = "fun p, q, param: { auto var = 3; //auto var2 = 3;\n }";
        syntax_analyzer::parsing_context fun_kv_ctx(code.c_str(), &filename);
        yy::kivi_parser parser{fun_kv_ctx};
        REQUIRE(parser.parse() == 0);
        REQUIRE(fun_kv_ctx.functions().at(0).locals() == 1);
    }

    SECTION("Duplicating var in comments")
    {
        std::string code = "fun p, q, param: { auto var = 3; //auto var = 3;\n }";
        syntax_analyzer::parsing_context fun_kv_ctx(code.c_str(), &filename);
        yy::kivi_parser parser{fun_kv_ctx};
        REQUIRE(parser.parse() == 0);
        REQUIRE(fun_kv_ctx.functions().at(0).locals() == 1);
    }
}

TEST_CASE("Syntax error", "[synt_err]")
{
    SECTION("Illegal comma separating params -- before param")
    {
        std::string code = "foo ,n: { auto a = 3; } ";
        syntax_analyzer::parsing_context ctx(code.c_str(), &filename);
        yy::kivi_parser parser{ ctx };

//        REQUIRE(parser.parse() --> syntax error);
    }

    SECTION("Illegal comma separating params -- after param")
    {
        std::string code = "foo n,: { auto a = 3; } ";
        syntax_analyzer::parsing_context ctx(code.c_str(), &filename);
        yy::kivi_parser parser{ ctx };

//        REQUIRE(parser.parse() --> syntax error);
    }

    SECTION("Comments without new line: `unexpected END` expected ")
    {
        std::string code = "fun p, q, param: { auto var = 3; //auto var = 3; }";
        syntax_analyzer::parsing_context fun_kv_ctx(code.c_str(), &filename);
        yy::kivi_parser parser{fun_kv_ctx};

        //        REQUIRE(parser.parse() --> syntax error);
    }
}

TEST_CASE("Statements", "[stmts]")
{
    SECTION("Regular use: addition")
    {
        std::string code = "foo n: { 1 + 2;}";
        syntax_analyzer::parsing_context ctx(code.c_str(), &filename);
        yy::kivi_parser parser{ ctx };

        REQUIRE(parser.parse() == 0);
        REQUIRE(ctx.functions().size() == 1);

//        ctx.functions().at(0);
//        syntax_analyzer::function expected{
//                "foo",
//                syntax_analyzer::expression {
//                        syntax_analyzer::expression::type::Addition,
//                        { syntax_analyzer::expression(1), syntax_analyzer::expression(2) }
//                },
//                0,
//                1
//        };
//        REQUIRE(expected == ctx.functions().at(0));
    }
}

TEST_CASE("Examples", "[examples]")
{
    std::string filepath = "../../examples/" + filename;
    std::ifstream fstr (filepath);
    std::string buffer (std::istreambuf_iterator<char> (fstr), {});

    sa::parsing_context ctx{ buffer.c_str (), &filename };
    yy::kivi_parser parser{ ctx };

    SECTION("Regular run: not syntax errors")
    {
        REQUIRE(parser.parse() == 0);
    }

    SECTION("Regular run: not endless loop")
    {

    }
}