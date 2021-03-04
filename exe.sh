BUILD_DIR=build
EXE_FILE="$BUILD_DIR"/kivi

if [ ! -e "$EXE_FILE" ]
then
	./build.sh
fi

echo "$1"

./"$EXE_FILE" $1
