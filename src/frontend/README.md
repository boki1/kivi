### Frontend

This directory contains the source code related to the implementation of the frontend of KIVI compiler.

-------------

**Contents**

- `parser/` In this folder resides the implementation of the syntactical analyzer used in the first stages of the compilation process

- `ir_generation/` This directory is used for the implementation of the stage which is responsible for "translating" the already generated AST into a more assembly-like architecture-independent simplistic language called _intermediate representation_

----------------

For the next steps of the compilation process check the `backend/` directory.
