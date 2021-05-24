rm -rf build
rm -rf docs/build
rm -rf Testing
rm -rf Debug

PARSER_DIR=src/frontend/parser

rm -f $PARSER_DIR/*tab*
rm -f $PARSER_DIR/position.hh
rm -f $PARSER_DIR/location.hh
rm -f $PARSER_DIR/stack.hh
