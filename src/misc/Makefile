AUTOGEN_DIR=../autogen

GRAMMAR_FILE=grammar.y
BISON_FLAGS=-d -Wother

LEXEMES_FILE=lexemes.re
RE2C_FLAGS=-is

all: grammar lexemes

grammar: $(GRAMMAR_FILE)
	echo 'Building ... grammar'
	bison $(GRAMMAR_FILE) -b$(AUTOGEN_DIR)/kivi_parser $(BISON_FLAGS)

	# TODO: Fix this
	# Hack to declare yylex()
	sed -i '/} \/\/ yy/i kivi_parser::symbol_type yylex (parsing_context &ctx);\n' $(AUTOGEN_DIR)/kivi_parser.tab.hh

	echo 'Built grammar'

lexemes:
	echo 'Building ... lexemes'
	re2c $(RE2C_FLAGS) -o $(AUTOGEN_DIR)/kivi_lexer.tab.cc $(LEXEMES_FILE)
	echo 'Built lexemes'
