## Details

Here are some of the details regarding the design and implementation of the kivi compiler.

> Stages of compiling

First, there are 4 major stages involved in the processing of source files.

![Stages](https://i.ibb.co/WP7TxWm/Kivi-Compiler-Stages.png)

> The what, how and why of the stages

These components form what's called _lexical_ and _syntactical_ analysis. There key functionalities are to process the given text (marked as  "Source File") and to construct what is called [abstract syntax tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree).
As it is shown on the schematic, the lexer understands and forms a list of tokens - composed of type (e.g Identifier, Function, etc.) and an associated value. The next step is to transform these lexemes into a tree structure which denotes the order of execution of
the individual _syntactic structures_ (e.g expression := number | string literal | etc.). Having taken in account every aspect of the language _grammar_, the next step is to perform semantic analysis on the tree. Since Kivi does not have any types (only integers) the
so-called semantic analysis is pretty-straight forward - are the functions that get called actually defined -- well that's not hard :smile:.
The intermediate representation component translates the AST generated before in a assembly-looking language which is independent of architecture and easier to translates to actual assembly. Lastly, the intermediate representation get translated to the specified assembly language.

## Design

> Syntax analyzer

![UML diagram]()

> Intermediate code generation

**TODO: This is going to be added soon :). Stay tuned.**
>
![UML diagram]()

> Code generation

**TODO: This is going to be added soon :). Stay tuned.**

![UML diagram]()    
