INCLUDE_DIR=include
AUTOGEN=autogen

CPPC=g++
CPPFLAGS=-g -Wall -std=c++17
OBJECTS=$(BUILD)/main.o $(BUILD)/parser.o $(BUILD)/kivi_parser.tab.o $(BUILD)/kivi_lexer.tab.o
BUILD=../build
EXE=$(BUILD)/kivi

AUTOGEN_PARSER_DEPS=$(AUTOGEN)/kivi_parser.tab.cc $(AUTOGEN)/kivi_parser.tab.hh $(AUTOGEN)/location.hh $(AUTOGEN)/position.hh $(AUTOGEN)/stack.hh
AUTOGEN_LEXER_DEPS=$(AUTOGEN)/kivi_lexer.tab.cc

all: $(OBJECTS)
	echo 'Building core ...'
	$(CPPC) $(OBJECTS) -o $(EXE)
	echo 'Built core'

$(BUILD)/main.o: main.cpp parser.cpp $(INCLUDE_DIR)/parser.hpp
	$(CPPC) $(CPPFLAGS) $< -c -o $@

$(BUILD)/parser.o: parser.cpp $(INCLUDE_DIR)/parser.hpp
	$(CPPC) $(CPPFLAGS) $< -c -o $@

$(BUILD)/kivi_parser.tab.o: $(AUTOGEN_PARSER_DEPS)
	$(CPPC) $(CPPFLAGS) $< -c -o $@

$(BUILD)/kivi_lexer.tab.o: $(AUTOGEN_LEXER_DEPS)
	$(CPPC) $(CPPFLAGS) $< -c -o $@

clean:
	rm -f kivi
	rm -f *core*
	rm -f *.o
	rm -f $(BUILD)/*.o

PHONY: all clean
