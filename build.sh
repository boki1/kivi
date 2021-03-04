SRC_DIR=src
INC_DIR="$SRC_DIR"/include
MISC_DIR="$SRC_DIR"/misc
AUTOGEN_DIR="$SRC_DIR"/autogen

BUILD_DIR=build
EXE_FILE=kivi
mkdir -p "$BUILD_DIR"

# Generate lexer
LEXEMES="$MISC_DIR"/lexemes.re
re2c -is -o "$AUTOGEN_DIR"/kivi_lexer.tab.cc "$LEXEMES"

## Generate parser
GRAMMAR="$MISC_DIR"/grammar.y
bison "$GRAMMAR" -b"$AUTOGEN_DIR"/kivi_parser -d -Wother
# Hack to declare yylex()
sed -i '/} \/\/ yy/i kivi_parser::symbol_type yylex (parsing_context &ctx);\n' "$AUTOGEN_DIR"/kivi_parser.tab.hh 

# Build code
cmake -S "$SRC_DIR" -B "$BUILD_DIR" -Wdev && make -C "$BUILD_DIR" && echo 'Project built'

