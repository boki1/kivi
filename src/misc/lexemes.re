#include "kivi_parser/kivi_parser.tab.hh"
#include "parser/parsing_context.hh"

// Namespace shortcuts
namespace sa = syntax_analyzer;
using kp = yy::kivi_parser;

namespace yy
{

kp::symbol_type
yylex (sa::parsing_context &ctx)
{
    const char *anchor = ctx.lexer_cursor;
    ctx.yy_location.step ();

    auto make_token = [&] (auto fun, auto &&...params) {
		ctx.yy_location.columns (ctx.lexer_cursor - anchor);
		return fun (params..., ctx.yy_location);
    };

    /*!re2c
    re2c:yyfill:enable   = 0;
    re2c:define:YYCTYPE  = "char";
    re2c:define:YYCURSOR = "ctx.lexer_cursor";

    // Keywords
    "return"                { return make_token(kp::make_RETURN); }
    "while"                 { return make_token(kp::make_WHILE); }
    "auto"                  { return make_token(kp::make_VAR); }
    "if"                    { return make_token(kp::make_IF); }

    /// Identifiers
    [a-zA-Z_] [a-zA-Z_0-9]* { return make_token(kp::make_IDENTIFIER, std::move(std::string(anchor, ctx.lexer_cursor))); }

    /// String and integer literals:
    "\"" [^"]* "\"" 		{ return make_token(kp::make_STRING_LITERAL, std::move(std::string(anchor + 1, ctx.lexer_cursor - 1))); }
	[0-9]+          		{ return make_token(kp::make_NUMBER_LITERAL, std::move(std::stol(std::string(anchor, ctx.lexer_cursor)))); }

    /// Whitespace and comments:
    "\000"                  { return make_token(kp::make_END); }
    "\r\n" | [\r\n]         { ctx.yy_location.lines(); return yylex(ctx); }
    "//" [^\r\n]*           { return yylex(ctx); }
    [\t\v\b\f ]             { ctx.yy_location.columns(); return yylex(ctx); }

    /// Multi-char operators and any other character (either an operator or an
    "<>"                    { return make_token(kp::make_NE); }
    "=="                    { return make_token(kp::make_EQ); }
    .                       { return make_token([] (auto...s) { return kp::symbol_type(s...); }, kp::token_type(ctx.lexer_cursor[-1] & 0xFF)); }
    */
}

}

