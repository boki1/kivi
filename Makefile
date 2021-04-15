BUILD_DIR=build
TEST_DIR=test
SRC_DIR=src
INC_DIR=$(SRC_DIR)/include
MISC_DIR=$(SRC_DIR)/misc
AUTOGEN_DIR=$(SRC_DIR)/autogen

all: prep lexemes grammar core
	echo 'Buidling...'
	echo 'Built'

lexemes:
	(cd $(MISC_DIR); make lexemes)

grammar:
	(cd $(MISC_DIR); make grammar)

core:
	cmake -S $(SRC_DIR) -B $(BUILD_DIR)
	(cd $(BUILD_DIR); make)

prep:
	mkdir -p $(BUILD_DIR)

test: prep all
	(cd $(TEST_DIR); make all)

clean:
	echo 'Cleaning ...'
	(cd $(MISC_DIR); make clean)
	(cd $(SRC_DIR); make clean)
	echo 'Cleaned'
