REPO_ROOT=..
DOCS_DIR=.

SRC_DIR="$REPO_ROOT"/src
BUILD_DIR="$REPO_ROOT"/build
TEST_DIR="$REPO_ROOT"/test
EXECUTABLE=./"$BUILD_DIR"/kivi

THIS_OUTPUT_MD="$DOCS_DIR"/docs.md
truncate -s0 "$THIS_OUTPUT_MD"

mkdir -p "$DOCS_DIR"
THIS_OUTPUT_PDF="$DOCS_DIR"/docs.pdf
rm -f "$THIS_OUTPUT_PDF"

if [ ! -e "$EXECUTABLE" ]
then
	make all -C $(REPO_ROOT) && echo "Successful build"
fi

#
# Extract lines which begin with "///"
#

function dfs_traverse() {
	for source_code_file in "$1"/*
	do
		if [[ ! -d "$source_code_file" ]];
		then
			grep "///" "$source_code_file" >> "$THIS_OUTPUT_MD"
		else
			dfs_traverse "$source_code_file"
		fi
	done
}

# Generate `md` file
dfs_traverse "$SRC_DIR"

# Remove empty comments
sed -i -e 's/\/\/\/ //g' "$THIS_OUTPUT_MD"

# Add line breaks
sed -i -e 's/$/<br \/>/' "$THIS_OUTPUT_MD"

# Remove space from the beginning
sed -i -e 's/^ *//' "$THIS_OUTPUT_MD"


if ! command -v md2pdf &> /dev/null
then
	echo "Please install the `md2pdf` package to continue."
	echo "Repo: https://aur.archlinux.org/packages/md2pdf/"
    exit
fi

md2pdf "$THIS_OUTPUT_MD" -o "$THIS_OUTPUT_PDF"
