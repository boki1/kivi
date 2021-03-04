DOCS_DIR=docs/
SRC_DIR=src
BUILD_DIR=build
TEST_DIR=test
EXECUTABLE=./"$BUILD_DIR"/kivi

THIS_OUTPUT_MD="$BUILD_DIR"/docs.md
truncate -s0 "$THIS_OUTPUT_MD"

mkdir -p "$DOCS_DIR"
THIS_OUTPUT_PDF="$DOCS_DIR"/docs.pdf
rm -f "$THIS_OUTPUT_PDF"

if [ ! -e "$EXECUTABLE" ]
then
	./build.sh && echo "Successful build"
fi

#
# Extract lines which begin with "///"
#

function dfs_traverse() {
	for source_code_file in "$1"/*
	do
		if [[ ! -d "$source_code_file" ]];
		then
			grep "^///" "$source_code_file" >> "$THIS_OUTPUT_MD"
		else
			dfs_traverse "$source_code_file"
		fi
	done
}

dfs_traverse "$SRC_DIR"

sed -i -e 's/\/\/\/ //g' "$THIS_OUTPUT_MD"

if ! command -v md2pdf &> /dev/null
then
	echo "Please install the `md2pdf` package to continue."
	echo "Repo: https://aur.archlinux.org/packages/md2pdf/"
    exit
fi

md2pdf "$THIS_OUTPUT_MD" -o "$THIS_OUTPUT_PDF"

