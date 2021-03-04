BUILD_DIR=build
TEST_DIR=test

rm -rf "$BUILD_DIR"
rm -f *.dot
rm -f *.output

make clean -C "$TEST_DIR"

echo 'Cleaned'
