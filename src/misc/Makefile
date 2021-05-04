AUTOGEN_DIR=../autogen/kivi_parser

GRAMMAR_FILE=grammar.y
BISON_FLAGS=-d -Wnone

LEXEMES_FILE=lexemes.re
RE2C_FLAGS=-is

all: grammar lexemes

grammar: $(GRAMMAR_FILE)
	bison $(GRAMMAR_FILE) -b$(AUTOGEN_DIR)/kivi_parser $(BISON_FLAGS)
	sed -i '/} \/\/ yy/i kivi_parser::symbol_type yylex (sa::parsing_context &ctx);\n' $(AUTOGEN_DIR)/kivi_parser.tab.hh

lexemes:
	re2c $(RE2C_FLAGS) -o $(AUTOGEN_DIR)/kivi_lexer.tab.cc $(LEXEMES_FILE)

PHONY: all
