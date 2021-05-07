#include <exception>
#include <catch2/catch2.hpp>

#include <ast/parsing_context.hh>   // syntax::analyzer::parsing_context

/**
 * @file example_test.cc
 * @brief Tests the parsing_context using the catch2 testing framework
 */

std::string fname = "pseudo.kv";
const char *code = "gcd:{}";
syntax_analyzer::parsing_context pars_cntx(code, &fname);

TEST_CASE("Parsing context", "[pc]")
{
    SECTION("regular scope enter") {
        unsigned long curr_scopes = pars_cntx.all_scopes().size();
        pars_cntx.enter_scope();
        REQUIRE(pars_cntx.all_scopes().size() == curr_scopes + 1);
    }

    SECTION("regular scope exit") {
        pars_cntx.all_scopes_mut().emplace_back();
        unsigned long curr_scopes = pars_cntx.all_scopes().size();
        pars_cntx.exit_scope();
        REQUIRE(pars_cntx.all_scopes().size() == curr_scopes - 1);
    }

    // TODO: test with exception requirement
//    SECTION("irregular scope exit - exit from 0 scopes") {
//        pars_cntx.all_scopes_mut().clear();
//        pars_cntx.exit_scope();
//        REQUIRE(pars_cntx.all_scopes().size() == );
//    }

}
