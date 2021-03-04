SRC_DIR=src
INC_DIR="$SRC_DIR"/include
TEST_DIR=test
BUILD_DIR=build
EXE_FILE="$BUILD_DIR"/kivi

THIS_OUTPUT="$TEST_DIR"/ACTUAL.txt
truncate -s0 "$THIS_OUTPUT"

if [ ! -e "$EXE_FILE" ]
then
	./build.sh
fi

for test_case in "$TEST_DIR"/*
do
	case "$test_case" in
	*.kv)
		echo '----------------------------------' >> "$THIS_OUTPUT"
		echo "$test_case" >> "$THIS_OUTPUT"
		echo '----------------------------------' >> "$THIS_OUTPUT"
		./"$EXE_FILE" "$test_case" >> "$THIS_OUTPUT" 2>&1
		echo '----------------------------------' >> "$THIS_OUTPUT"
		echo '' >> "$THIS_OUTPUT"

		# echo '----------------------------------'
		# echo "$test_case"
		# echo '----------------------------------'
		# ./"$EXE_FILE" "$test_case"
		# echo '----------------------------------'
	;;
	esac
done

CORRECT_OUTPUT="$TEST_DIR"/CORRECT.txt
make -C "$TEST_DIR" -s &&
	diff -sy --width=120 --suppress-common-lines "$CORRECT_OUTPUT" "$THIS_OUTPUT" | less

