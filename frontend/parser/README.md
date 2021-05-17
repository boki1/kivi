### Parser

Here resides the implementation of the first two stages of the compilation process: lexer and parser.

Additional tools used here are `bison>=3.7` and `re2c`.

----------------

**Contents**

> `lexemes.re`\
This file enlists all supported tokens in the language and provides a skeleton which `re2c` uses in order to generate a lexer

> `grammar.y`\
This file describes the grammar which will be later imposed on a given source file in order to produce a valid AST

> `error.cc`\
This file implements the error recovery function required by `bison`

> `syntax.hh`\
This file provides definitions of all syntactic structures used by the internal representation of the AST (`function`, `identifier`, etc.)

> `syntax.cc`\
This file implements the functions in the classes in `syntax.hh` 

> `parsing_context.hh`\
This file defines a structure which keeps track of all contextual information required during the syntactical analysis

> `parsing_context.cc`
Implements the API defined in `parsing_context.hh`

> `syntactical_structures.hh`\
Declares concrete "constructors" for all expressions and statements

> `expressions.cc`\
Defines all "constructors" for expressions declared in `syntactical_structures.hh`

> `statements.cc`\
Defines all "constructors" for statements declared in `syntactical_structures.hh`

**Auotmatically generated files by `bison` and `re2c`**
> `parser.tab.hh`\
Parser API

> `location.hh`\
Location class used by the parser

> `parser.tab.cc`\
 Parser implementation
 
 > `lexer.tab.cc`\
 Lexer implementation

