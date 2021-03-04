%language "c++"
%define api.parser.class { kivi_parser }
%define api.value.type variant
%define parse.assert
%define parse.error verbose
%define api.token.constructor
%locations   // <--

%code requires {

	#include "../include/parser.hpp"

} //%code requires

%param { parsing_context &ctx }


%token END 0
%token VAR "auto" IF "if" WHILE "while" RETURN "return"
%token IDENTIFIER STRING_LITERAL NUMBER_LITERAL
%token EQ "==" NE "<>"

// Precedence and associativity
%left ','
%right '='
%left "<>" "=="
%left '+' '-'
%left '*' '/'
%left '('

%type<long>        NUMBER_LITERAL
%type<std::string> IDENTIFIER STRING_LITERAL
%type<std::string> Safe_identifier
%%

Program:
	Functions
;

Functions:
  /* empty */
| Functions Single_function;

Single_function:
  Safe_identifier
  Parameter_list Safe_colon
  Safe_statement
;

Parameter_list:
  /* empty */
| Single_param
;

Single_param:
  // One or more; comma-delimited
  Single_param ',' Safe_identifier
| IDENTIFIER
;

Statement:
  Compound_statement Safe_closing_brace
| IF Safe_expression Safe_colon Safe_statement
| WHILE Safe_expression ':' Safe_statement
| RETURN Safe_expression Safe_semicolon
| Expressions Safe_semicolon
| ';'
;

Comma_sep_expressions:
  Safe_expression
  // One or more; comma-delimited
| Comma_sep_expressions ',' Safe_expression
;

Var_definition:
    VAR Safe_identifier '=' Safe_expression
;

Compound_statement:
  '{'
| Compound_statement Statement
;

Comparison_operation:
  Expression "==" error
| Expression "==" Expression
| Expression "<>" error
| Expression "<>" Expression
;

Arithmetic_operation:
  Expression '+' error
| Expression '+' Expression
| Expression '-' error
| Expression '-' Expression %prec '+'
| Expression '*' error
| Expression '*' Expression
// TODO:
// Make division by 0 a compiler time error
| Expression '/' error
| Expression '/' Expression %prec '*'
| Expression '=' error
| Expression '=' Expression
;

Unary_operation:
  '-' Expression
| '-' error
;

Function_call_operation:
  Expression '(' ')'
| Expression '(' Comma_sep_expressions Safe_closing_parentesis
| '(' Comma_sep_expressions Safe_closing_parentesis
;

Expressions:
  Var_definition
| Expression
| Expression ',' Comma_sep_expressions
;

Expression:
  STRING_LITERAL
| NUMBER_LITERAL
| IDENTIFIER
| Arithmetic_operation
| Comparison_operation
| Unary_operation
| Function_call_operation
;

//
// Error handling and correction
Safe_identifier:
  error
| IDENTIFIER
;

Safe_colon:
  error
| ':'
;

Safe_semicolon:
  error
| ';'
;

Safe_closing_brace:
  error
| '}'
;

Safe_closing_parentesis:
  error
| ')'
;

Safe_statement:
  error
| Statement
;

Safe_expression:
  error
| Expression
;

Safe_expressions:
  error
| Expressions
;

Safe_parentesised_expression:
  error
| '(' Safe_expressions Safe_closing_parentesis
;

