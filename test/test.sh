BUILD=../build

TESTCASES=testcases

THIS_OUTPUT=test-this-output.txt
CORRECT_OUTPUT=test-correct-results.txt
OUTPUT="$BUILD"/test-results.txt

TEST_EXE_FILE="$BUILD"/test
TEST_EXE_PARAMS="$CORRECT_OUTPUT"

BUILD_EXE_FILE="$BUILD"/kivi

truncate -s0 "$THIS_OUTPUT"
truncate -s0 "$CORRECT_OUTPUT"
truncate -s0 "$OUTPUT"

# Loop over each testcase kv file and execute it with the built version of `kivi` in build
# Store the results in `THIS_OUTPUT`
for test_case in ./"$TESTCASES"/*
do
	case "$test_case" in
	*.kv)
		echo '----------------------------------' >> "$THIS_OUTPUT"
		echo "$test_case" >> "$THIS_OUTPUT"
		echo '----------------------------------' >> "$THIS_OUTPUT"
		./"$BUILD_EXE_FILE" "$test_case" >> "$THIS_OUTPUT" 2>&1
		echo '----------------------------------' >> "$THIS_OUTPUT"
		echo '' >> "$THIS_OUTPUT"
	;;
	esac
done

# Generate correct output and store it in `CORRECT_OUTPUT`
./"$TEST_EXE_FILE" "$TEST_EXE_PARAMS" >> "$OUTPUT" 2>&1

# Compare `THIS_OUTPUT` and `CORRECT_OUTPUT` and store it in `OUTPUT`
diff -sy --width=120 "$CORRECT_OUTPUT" "$THIS_OUTPUT" > "$OUTPUT"

rm "$THIS_OUTPUT"
rm "$CORRECT_OUTPUT"
less "$OUTPUT"
