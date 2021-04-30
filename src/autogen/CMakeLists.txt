add_library(
	kivi_parser
	kivi_parser/kivi_parser.tab.hh
	kivi_parser/kivi_parser.tab.cc
	kivi_parser/kivi_lexer.tab.cc
	kivi_parser/location.hh
	kivi_parser/position.hh
	kivi_parser/stack.hh
)

target_include_directories(kivi_parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
