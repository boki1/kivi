%language "c++"
%define parser_class_name { kivi_parser }
%define api.value.type variant
%define api.token.constructor
%define parse.assert
%define parse.error verbose
/* %require "3.7" */
%locations   // <--

%code requires {

#include "syntactical_structures.hh"
#include "parsing_context.hh"
#include "syntax.hh"

namespace sa = syntax_analyzer;
using std::move;

} //%code requires

%param { sa::parsing_context &ctx }

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

%type<int>         NUMBER_LITERAL
%type<std::string> IDENTIFIER STRING_LITERAL
%type<std::string> Safe_identifier
%type<sa::expression>  Statement Expression Comma_sep_expressions Compound_statement Parameter_list Safe_expressions Expressions
%type<sa::expression>  Comparison_operation Arithmetic_operation Unary_operation Function_call_operation
%type<sa::expression>  Safe_expression Safe_statement Safe_parentesised_expression Single_param

%%

Program:
    { ctx.enter_scope(); } Functions { ctx.exit_scope(); }
;

Functions:
  Functions Single_function
| %empty {}
;

Single_function:
  Safe_identifier {
	ctx.define_function($1);
	ctx.enter_scope();
  }
  Parameter_list Safe_colon
  Safe_statement {
	ctx.define_function_body($1, move($5));
	ctx.exit_scope();
  };

Parameter_list:
  Single_param
| %empty {}
;

Single_param:
  Single_param ',' Safe_identifier 				{ ctx.define_parameter(move($3)); }
| IDENTIFIER 							{ ctx.define_parameter(move($1)); }
;

Statement:
  Compound_statement Safe_closing_brace 		{ $$ = move($1); ctx.exit_scope(); }
| IF Safe_expression Safe_colon Safe_statement 		{ $$ = sa::if_stmt(move($2), move($4)); }
| WHILE Safe_expression ':' Safe_statement 		{ $$ = sa::while_stmt(move($2), move($4)); }
| RETURN Safe_expression Safe_semicolon 		{ $$ = sa::return_stmt(move($2)); }
| Expression Safe_semicolon 				{ $$ = move($1); }
| VAR Safe_identifier '=' Safe_expression 		{ $$ = ctx.define_local(move($2)).assign(move($4)); }
| ';' 							{ }
;

Comma_sep_expressions:
  Safe_expression 								{ $$ = sa::sequence_expr(move($1)); }
| Comma_sep_expressions ',' Safe_expression 	{ $$ = move($1); $$.front_add(move($3)); }
;

Compound_statement:
  '{' 											{ $$ = sa::compound_stmt(); ctx.enter_scope(); }
| Compound_statement Statement 					{ $$ = move($1); $$.add(move($2)); }
;

Comparison_operation:
  Expression "==" error 						{ $$ = move($1); }
| Expression "==" Expression 					{ $$ = sa::equality_expr(move($1), move($3)); }
| Expression "<>" error 						{ $$ = move($1); }
| Expression "<>" Expression 					{ $$ = sa::inequality_expr(move($1), move($3)); }
;

Arithmetic_operation:
  Expression '+' error 							{ $$ = move($1); }
| Expression '+' Expression 						{ $$ = sa::addition_expr(move($1), move($3)); }
| Expression '-' error 							{ $$ = move($1); }
| Expression '-' Expression %prec '+' 					{ $$ = sa::addition_expr(move($1), sa::negation_expr(move($3))); }
| Expression '*' error 							{ $$ = move($1); }
| Expression '*' Expression 						{ $$ = sa::multiplication_expr(move($1), move($3)); }
| Expression '/' error 							{ $$ = move($1); }
| Expression '/' Expression %prec '*' 					{ $$ = sa::division_expr(move($1), move($3)); }
| Expression '=' error 							{ $$ = move($1); }
| Expression '=' Expression 						{ $$ = sa::assignment_expr(move($1), move($3)); }
| Expression '%' Expression 						{ $$ = sa::modular_division_expr(move($1), move($3)); }
| Expression '%' error 							{ $$ = move($1); }
;

Unary_operation:
  '-' Expression 								{ $$ = sa::negation_expr(move($2)); }
| '-' error 									{ }
;

Function_call_operation:
  Safe_identifier '(' ')' 											{ $$ = sa::function_call_expr(move($1), ctx.functions()); }
| Safe_identifier '(' Comma_sep_expressions Safe_closing_parentesis 	{ $$ = sa::function_call_expr(move($1), ctx.functions(), move($3)); }
;

Expressions:
 Expression 									{ $$ = move($1); }
| Expression ',' Comma_sep_expressions 			{ $$ = sa::sequence_expr(move($1)); $$.extend(move($3)); }
;

Expression:
  STRING_LITERAL 								{ $$ = sa::string_literal(move($1)); }
| NUMBER_LITERAL 								{ $$ = sa::number_literal($1); }
| IDENTIFIER 									{ $$ = ctx.use_identifier($1); }
| Arithmetic_operation
| Comparison_operation
| Unary_operation
| Function_call_operation
;

Safe_identifier:
  error { } | IDENTIFIER { $$ = move($1); }
;

Safe_colon:
  error { } | ':'
;

Safe_semicolon:
  error { } | ';'
;

Safe_closing_brace:
  error { } | '}'
;

Safe_closing_parentesis:
  error { } | ')'
;

Safe_statement:
  error { } | Statement { $$ = move($1); }
;

Safe_expression:
  error { } | Expression { $$ = move($1); }
;

Safe_expressions:
  error { } | Expressions { $$ = move($1); }
;

Safe_parentesised_expression:
  error { } | '(' Safe_expressions Safe_closing_parentesis { $$ = move($2); }
;

%code provides {

namespace yy
{
    yy::kivi_parser::symbol_type yylex(sa::parsing_context &);
}

};

%%
