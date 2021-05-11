#include <exception>
#include <catch2/catch2.hpp>

#include <ast/parsing_context.hh>           // syntax::analyzer::parsing_context
#include <kivi_parser/kivi_parser.tab.hh>   //yy::kivi_parser::syntax_error

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

    SECTION("irregular scope exit - exit from 0 scopes") {
        pars_cntx.all_scopes_mut().clear();
        REQUIRE_THROWS_AS(pars_cntx.exit_scope(), syntax_analyzer::cannot_pop_out_of_empty_exception);
    }

    SECTION("define two identical identifiers") {
        pars_cntx.all_scopes_mut().emplace_back();
        const std::string name = "var1";
        pars_cntx.define_identifier(name, sa::identifier(sa::identifier_class::Parameter, name));
        REQUIRE_THROWS_AS(pars_cntx.define_identifier(name, sa::identifier(sa::identifier_class::Parameter, name)), yy::kivi_parser::syntax_error);
    }
}
