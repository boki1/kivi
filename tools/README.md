### Tools

Here are put some tools used for building, running and testing the project.

**NB:** All of them _have to_ be used from the root (e.g. `./tools/build.sh`).

------------

**Contents**

- `./tools/build.sh` Builds the project

- `./tools/run.sh <file.kv>` Runs the project with the specific file as an argument

- `./tools/test.sh` Executes the test cases

- `./tools/clean.sh` Cleans building information

- `./tools/doc.sh` Generates documentation w/ Doxygen. Additional arguments:
	+ `--upload` (or `-u`) Uploads the built documentation to the github pages
	+ `--open` (or `-o`) Opens the build documentation. If an upload was just made, it is opened directly by the url, otherwise - from local files.
