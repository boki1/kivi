BUILD_DIR=build
EXE_FILE=kivi

./build.sh

[ -f "$BUILD_DIR"/$EXE_FILE ] && ./"$BUILD_DIR"/"$EXE_FILE"
