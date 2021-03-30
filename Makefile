BUILD_DIR=build
TEST_DIR=test
SRC_DIR=src
INC_DIR=$(SRC_DIR)/include
MISC_DIR=$(SRC_DIR)/misc
AUTOGEN_DIR=$(SRC_DIR)/autogen

EXE_FILE=kivi

build: lexemes grammar core
	echo 'Buidling...'
	mkdir -p $(BUILD_DIR)
	echo 'Built'

lexemes:
	(cd $(MISC_DIR); make lexemes)

grammar:
	(cd $(MISC_DIR); make grammar)

core:
	(cd $(SRC_DIR); make core)

clear:
	echo 'Cleaning ...'
	echo 'Cleaned'

