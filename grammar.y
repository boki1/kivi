%language "c++"
%define parser_class_name  { kivi_parser }
%define api.value.type variant
%define parse.assert
%define parse.error verbose
%define api.token.constructor
%locations   // <--

%code requires {

} //%code requires

%token END 0
%token LET "let" IF "if" WHILE "while" RETURN "return"
%token IDENTIFIER STRING_LITERAL NUMBER_LITERAL
%token EQ "==" NE "<>"

// Precedence and associativity
%left ','
%right '='
%left "<>" "=="
%left '+' '-'
%left '*' '/'
%left '('
%%

program: functions

functions:
  /* empty */
| functions single_function;

single_function: IDENTIFIER parameter_list ':' statement;

parameter_list:
  /* empty */
| single_param
;

single_param:
  single_param ',' IDENTIFIER		// One or more; comma-delimited
| IDENTIFIER
;

statement:
  compound_statement '}'
| IF expression ':' statement
| WHILE expression ':' statement
| RETURN expression ';'
| expressions ';'
| ';'
;

expressions:
  var_definition
| expression
| comma_sep_expressions ',' expression
;

comma_sep_expressions:
  expression
| comma_sep_expressions ',' expression    // One or more; comma-delimited
;

var_definition:  LET IDENTIFIER '=' expression
;

compound_statement: '{'
| compound_statement statement
;

expression: STRING_LITERAL
| NUMBER_LITERAL
| IDENTIFIER
| '(' expressions ')'
| expression '(' ')'
| expression '(' comma_sep_expressions')'
| expression '+' expression
| expression '-' expression %prec '+'
| expression '*' expression
| expression '/' expression %prec '*'
| expression "==" expression
| expression "<>" expression
;

