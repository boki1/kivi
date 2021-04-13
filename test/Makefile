CPPC=g++
CPPFLAGS=-g -Wall -std=c++17
BUILD=../build
EXE_TEST=$(BUILD)/test
OUTPUT_TEST=$(BUILD)/test-results.txt
SCRIPT_TEST=test.sh

all: test.cpp
	$(CPPC) $(CPPFLAGS) $< -o $(EXE_TEST)
	./$(SCRIPT_TEST)

clean:
	rm -f $(OUTPUT_TEST)
	rm -f $(EXE_TEST)
