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
	(cd $(SRC_DIR); make all)

prep:
	mkdir -p $(BUILD_DIR)

clean:
	echo 'Cleaning ...'
	(cd $(MISC_DIR); make clean)
	(cd $(SRC_DIR); make clean)
	echo 'Cleaned'
