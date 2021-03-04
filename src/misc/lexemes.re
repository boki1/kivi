#include "kivi_parser.tab.hh"
#include "../include/parser.hpp"

namespace yy {

    yy::kivi_parser::symbol_type yylex(parsing_context &ctx)
    {
        const char* anchor = ctx.lexer_cursor;
        ctx.location.step();

    #define COL_DIF ctx.location.columns(ctx.lexer_cursor - anchor);
    using kivi = yy::kivi_parser;

    /*!re2c
    re2c:yyfill:enable   = 0;
    re2c:define:YYCTYPE  = "char";
    re2c:define:YYCURSOR = "ctx.lexer_cursor";

    // Keywords:
    "return"                { COL_DIF return kivi::make_RETURN(ctx.location); }
    "while"                 { COL_DIF return kivi::make_WHILE(ctx.location); }
    "auto"                  { COL_DIF return kivi::make_VAR(ctx.location); }
    "if"                    { COL_DIF return kivi::make_IF(ctx.location); }

    // Identifiers:
    [a-zA-Z_] [a-zA-Z_0-9]* { COL_DIF return kivi::make_IDENTIFIER(std::string(anchor,ctx.lexer_cursor), ctx.location); }

    // String and integer literals:
    "\"" [^"]* "\""         { COL_DIF return kivi::make_STRING_LITERAL(std::string(anchor+1, ctx.lexer_cursor-1), ctx.location); }
    [0-9]+                  { COL_DIF return kivi::make_NUMBER_LITERAL(std::stol(std::string(anchor,ctx.lexer_cursor)), ctx.location); }

    // Whitespace and comments:
    "\000"                  { COL_DIF return kivi::make_END(ctx.location); }
    "\r\n" | [\r\n]         { ctx.location.lines();   return yylex(ctx); }
    "//" [^\r\n]*           {                    return yylex(ctx); }
    [\t\v\b\f ]             { ctx.location.columns(); return yylex(ctx); }

    // Multi-char operators and any other character (either an operator or an invalid symbol):
    "<>"                    { COL_DIF return kivi::make_NE(ctx.location); }
    "=="                    { COL_DIF return kivi::make_EQ(ctx.location); }
    .                       { COL_DIF return kivi::symbol_type(kivi::token_type(ctx.lexer_cursor[-1]&0xFF), ctx.location); } // Return that character
    */

    #undef COL_DIF
    }

}

