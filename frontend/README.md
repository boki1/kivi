### Frontend

This directory contains the source code related to the implementation of the frontend of Kivi compiler.

-------------

**Contents**

- `grammar.y` This is the grammar used by `bison` in order to generate an actual state machine-based parser.

- `lexemes.re` This file lists the lexemes/tokens used by `re2c` (in combination with `bison`) in order to generate the code for lexical analysis stage
