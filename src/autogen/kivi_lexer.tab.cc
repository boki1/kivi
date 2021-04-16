/* Generated by re2c 2.0.3 on Fri Apr 16 08:13:08 2021 */
#include "kivi_parser.tab.hh"
#include "../include/parser.hpp"

namespace yy {

    yy::kivi_parser::symbol_type yylex(parsing_context &ctx)
    {
        const char* anchor = ctx.lexer_cursor;
        ctx.location.step();

	#define COL_DIF ctx.location.columns(ctx.lexer_cursor - anchor);
    using kivi = yy::kivi_parser;

    
{
	char yych;
	yych = *ctx.lexer_cursor;
	if (yych <= '<') {
		if (yych <= 0x1F) {
			if (yych <= '\t') {
				if (yych <= 0x00) goto yy2;
				if (yych <= 0x07) goto yy4;
				goto yy6;
			} else {
				if (yych <= '\n') goto yy8;
				if (yych <= '\f') goto yy6;
				if (yych <= '\r') goto yy10;
				goto yy4;
			}
		} else {
			if (yych <= '.') {
				if (yych <= ' ') goto yy6;
				if (yych == '"') goto yy11;
				goto yy4;
			} else {
				if (yych <= '/') goto yy13;
				if (yych <= '9') goto yy14;
				if (yych <= ';') goto yy4;
				goto yy17;
			}
		}
	} else {
		if (yych <= 'a') {
			if (yych <= 'Z') {
				if (yych <= '=') goto yy18;
				if (yych <= '@') goto yy4;
				goto yy19;
			} else {
				if (yych == '_') goto yy19;
				if (yych <= '`') goto yy4;
				goto yy22;
			}
		} else {
			if (yych <= 'r') {
				if (yych == 'i') goto yy23;
				if (yych <= 'q') goto yy19;
				goto yy24;
			} else {
				if (yych == 'w') goto yy25;
				if (yych <= 'z') goto yy19;
				goto yy4;
			}
		}
	}
yy2:
	++ctx.lexer_cursor;
	{ COL_DIF return kivi::make_END(ctx.location); }
yy4:
	++ctx.lexer_cursor;
yy5:
	{ COL_DIF return kivi::symbol_type(kivi::token_type(ctx.lexer_cursor[-1]&0xFF), ctx.location); }
yy6:
	++ctx.lexer_cursor;
	{ ctx.location.columns(); return yylex(ctx); }
yy8:
	++ctx.lexer_cursor;
yy9:
	{ ctx.location.lines();   return yylex(ctx); }
yy10:
	yych = *++ctx.lexer_cursor;
	if (yych == '\n') goto yy8;
	goto yy9;
yy11:
	yych = *++ctx.lexer_cursor;
	if (yych == '"') goto yy26;
	goto yy11;
yy13:
	yych = *++ctx.lexer_cursor;
	if (yych == '/') goto yy28;
	goto yy5;
yy14:
	yych = *++ctx.lexer_cursor;
	if (yych <= '/') goto yy16;
	if (yych <= '9') goto yy14;
yy16:
	{ COL_DIF return kivi::make_NUMBER_LITERAL(std::stol(std::string(anchor,ctx.lexer_cursor)), ctx.location); }
yy17:
	yych = *++ctx.lexer_cursor;
	if (yych == '>') goto yy31;
	goto yy5;
yy18:
	yych = *++ctx.lexer_cursor;
	if (yych == '=') goto yy33;
	goto yy5;
yy19:
	yych = *++ctx.lexer_cursor;
yy20:
	if (yych <= 'Z') {
		if (yych <= '/') goto yy21;
		if (yych <= '9') goto yy19;
		if (yych >= 'A') goto yy19;
	} else {
		if (yych <= '_') {
			if (yych >= '_') goto yy19;
		} else {
			if (yych <= '`') goto yy21;
			if (yych <= 'z') goto yy19;
		}
	}
yy21:
	{ COL_DIF return kivi::make_IDENTIFIER(std::string(anchor,ctx.lexer_cursor), ctx.location); }
yy22:
	yych = *++ctx.lexer_cursor;
	if (yych == 'u') goto yy35;
	goto yy20;
yy23:
	yych = *++ctx.lexer_cursor;
	if (yych == 'f') goto yy36;
	goto yy20;
yy24:
	yych = *++ctx.lexer_cursor;
	if (yych == 'e') goto yy38;
	goto yy20;
yy25:
	yych = *++ctx.lexer_cursor;
	if (yych == 'h') goto yy39;
	goto yy20;
yy26:
	++ctx.lexer_cursor;
	{ COL_DIF return kivi::make_STRING_LITERAL(std::string(anchor+1, ctx.lexer_cursor-1), ctx.location); }
yy28:
	yych = *++ctx.lexer_cursor;
	if (yych == '\n') goto yy30;
	if (yych != '\r') goto yy28;
yy30:
	{                    return yylex(ctx); }
yy31:
	++ctx.lexer_cursor;
	{ COL_DIF return kivi::make_NE(ctx.location); }
yy33:
	++ctx.lexer_cursor;
	{ COL_DIF return kivi::make_EQ(ctx.location); }
yy35:
	yych = *++ctx.lexer_cursor;
	if (yych == 't') goto yy40;
	goto yy20;
yy36:
	yych = *++ctx.lexer_cursor;
	if (yych <= 'Z') {
		if (yych <= '/') goto yy37;
		if (yych <= '9') goto yy19;
		if (yych >= 'A') goto yy19;
	} else {
		if (yych <= '_') {
			if (yych >= '_') goto yy19;
		} else {
			if (yych <= '`') goto yy37;
			if (yych <= 'z') goto yy19;
		}
	}
yy37:
	{ COL_DIF return kivi::make_IF(ctx.location); }
yy38:
	yych = *++ctx.lexer_cursor;
	if (yych == 't') goto yy41;
	goto yy20;
yy39:
	yych = *++ctx.lexer_cursor;
	if (yych == 'i') goto yy42;
	goto yy20;
yy40:
	yych = *++ctx.lexer_cursor;
	if (yych == 'o') goto yy43;
	goto yy20;
yy41:
	yych = *++ctx.lexer_cursor;
	if (yych == 'u') goto yy45;
	goto yy20;
yy42:
	yych = *++ctx.lexer_cursor;
	if (yych == 'l') goto yy46;
	goto yy20;
yy43:
	yych = *++ctx.lexer_cursor;
	if (yych <= 'Z') {
		if (yych <= '/') goto yy44;
		if (yych <= '9') goto yy19;
		if (yych >= 'A') goto yy19;
	} else {
		if (yych <= '_') {
			if (yych >= '_') goto yy19;
		} else {
			if (yych <= '`') goto yy44;
			if (yych <= 'z') goto yy19;
		}
	}
yy44:
	{ COL_DIF return kivi::make_VAR(ctx.location); }
yy45:
	yych = *++ctx.lexer_cursor;
	if (yych == 'r') goto yy47;
	goto yy20;
yy46:
	yych = *++ctx.lexer_cursor;
	if (yych == 'e') goto yy48;
	goto yy20;
yy47:
	yych = *++ctx.lexer_cursor;
	if (yych == 'n') goto yy50;
	goto yy20;
yy48:
	yych = *++ctx.lexer_cursor;
	if (yych <= 'Z') {
		if (yych <= '/') goto yy49;
		if (yych <= '9') goto yy19;
		if (yych >= 'A') goto yy19;
	} else {
		if (yych <= '_') {
			if (yych >= '_') goto yy19;
		} else {
			if (yych <= '`') goto yy49;
			if (yych <= 'z') goto yy19;
		}
	}
yy49:
	{ COL_DIF return kivi::make_WHILE(ctx.location); }
yy50:
	yych = *++ctx.lexer_cursor;
	if (yych <= 'Z') {
		if (yych <= '/') goto yy51;
		if (yych <= '9') goto yy19;
		if (yych >= 'A') goto yy19;
	} else {
		if (yych <= '_') {
			if (yych >= '_') goto yy19;
		} else {
			if (yych <= '`') goto yy51;
			if (yych <= 'z') goto yy19;
		}
	}
yy51:
	{ COL_DIF return kivi::make_RETURN(ctx.location); }
}


    #undef COL_DIF
    }

}

