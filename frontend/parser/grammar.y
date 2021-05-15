%language "c++"
%define api.parser.class { kivi_parser }
%define api.value.type variant
%define api.token.constructor
%define parse.assert
%define parse.error verbose
%require "3.7"
%locations // <--

%code requires {

#include "syntactical_structures.hh"
#include "parsing_context.hh"
#include "syntax.hh"

namespace sa = syntax_analyzer;

using std::move;

} //%code requires


%param { syntax_analyzer::parsing_context &ctx }

%token END 0
%token VAR "auto" IF "if" WHILE "while" RETURN "return"
%token IDENTIFIER STRING_LITERAL NUMBER_LITERAL
%token EQ "==" NE "<>"

// Precedence and associativity
// Note: There is no need to specify precendence and associativity for `,` and `(` -
// bison automatically sets it correctly

%right '='
%left "<>" "=="
%left '+' '-'
%left '*' '/' '%'

%type<int> 					NUMBER_LITERAL
%type<std::string> 				STRING_LITERAL
%type<std::string> 				IDENTIFIER Safe_identifier
%type<syntax_analyzer::expression> 		Statement Expression Comma_sep_expressions
%type<syntax_analyzer::expression> 		Safe_statement Safe_expression Parameter_list
%type<syntax_analyzer::expression>           	Compound_statement Function_call Single_param
%type<syntax_analyzer::expression>           	Comparison_operation Arithmetic_operation
//%type<syntax_analyzer::expression>         	Unary_operation
%%

Program: 					{ ctx.enter_scope (); }
	Functions 				{ ctx.exit_scope (); }
;

Functions :
  %empty
| Functions Single_function;

Single_function:
  Safe_identifier {
    ctx.define_function ($1);
    ctx.enter_scope ();
  }
  Parameter_list
  Safe_colon
  Safe_statement {
    ctx.define_function_body ($1, move ($5));
    ctx.exit_scope ();
  }
;

Parameter_list:
  %empty {}
| Single_param
;

Single_param:
  Single_param ',' Safe_identifier    		{ ctx.define_parameter (move($3)); }
| IDENTIFIER                            	{ ctx.define_parameter (move($1)); }
;

Statement:
  Compound_statement Safe_closing_brace 	{ $$ = move ($1); ctx.exit_scope (); }
| RETURN Safe_expression Safe_semicolon 	{ $$ = syntax_analyzer::return_stmt (move($2)); }
| IF Safe_expression Safe_colon Safe_statement 	{ $$ = syntax_analyzer::if_stmt (move($2), move($4)); }
| WHILE Safe_expression ':' Safe_statement 	{ $$ = syntax_analyzer::while_stmt (move($2), move($4)); }
| VAR Safe_identifier '=' Safe_expression 	{ $$ = ctx.define_local(move($2)).assign(move($4)); }
| Expression Safe_semicolon 			{ $$ = move($1); }
| ';' 						{ }
;

Comma_sep_expressions:
  Safe_expression 				{ $$ = syntax_analyzer::sequence_expr (move($1)); }
| Comma_sep_expressions ',' Safe_expression 	{ $$ = move ($1); $$.append (move ($3)); }
;

Compound_statement:
  '{'                             		{ $$ = syntax_analyzer::compound_stmt (); ctx.enter_scope (); }
| Compound_statement Statement    		{ $$ = std::move ($1); $$.append (std::move ($2)); }
;

Comparison_operation:
  Expression "==" error 			{ $$ = std::move ($1); }
| Expression "==" Expression 			{ $$ = syntax_analyzer::equality_expr (std::move ($1), std::move ($3)); }
| Expression "<>" error 			{ $$ = std::move ($1); }
| Expression "<>" Expression 			{ $$ = syntax_analyzer::inequality_expr (std::move ($1), std::move ($3)); }
;

Arithmetic_operation:
  Expression '+' error 				{ $$ = move ($1); }
| Expression '+' Expression 	        	{ $$ = syntax_analyzer::addition_expr (move($1), move($3)); }
| Expression '-' error 	    %prec '+' 		{ $$ = move ($1); }
| Expression '-' Expression %prec '+' 		{ $$ = syntax_analyzer::addition_expr (move($1), syntax_analyzer::negation_expr (move($3))); }
| Expression '*' error 				{ $$ = move ($1); }
| Expression '*' Expression 			{ $$ = syntax_analyzer::multiplication_expr (move($1), move($3));}
| Expression '/' error  			{ $$ = move ($1); }
| Expression '/' Expression %prec '*' 		{ $$ = syntax_analyzer::division_expr (move($1), move($3)); }
| Expression '%' error 				{ $$ = move ($1); }
| Expression '%' Expression %prec '*' 		{ $$ = syntax_analyzer::modular_division_expr (move($1), move($3)); }
| Expression '=' error 				{ $$ = move ($1); }
| Expression '=' Expression 			{ $$ = syntax_analyzer::assignment_expr (move($1), move($3)); }
;

//Unary_operation:
//  '-' Expression 				{ $$ = syntax_analyzer::negation_expr (move ($2)); }
//| '-' error 	 				{  }
//;

Function_call:
  IDENTIFIER '(' ')' 				{ $$ = syntax_analyzer::function_call_expr (move($1)); }
| IDENTIFIER '(' Comma_sep_expressions
	Safe_closing_parenthesis		{ $$ = syntax_analyzer::function_call_expr (move($1), move ($3)); }
;

Function_call:
  IDENTIFIER '(' ')' 				{ }
| IDENTIFIER '(' Comma_sep_expressions
	Safe_closing_parenthesis		{ }
;

Expression:
  STRING_LITERAL 				{ $$ = syntax_analyzer::string_literal (std::move ($1)); }
| NUMBER_LITERAL 				{ $$ = syntax_analyzer::number_literal ($1); }
| IDENTIFIER 					{ $$ = ctx.use_identifier ($1); }
| Function_call         			{ $$ = move($1); }
| Arithmetic_operation  			{ $$ = move($1); }
| Comparison_operation  			{ $$ = move($1); }
//| Unary_operation       			{ $$ = move($1); }
;


//
// Error handling and correction
//

Safe_identifier:
  error						{ }
| IDENTIFIER 					{ $$ = move ($1); };

Safe_colon:
  error 					{ }
| ':';

Safe_semicolon:
  error						{ }
| ';';

Safe_closing_brace:
  error						{ }
| '}';

Safe_closing_parenthesis:
  error 					{ }
| ')';

Safe_statement:
  error						{ }
| Statement 					{ $$ = move ($1); };

Safe_expression:
  error						{ }
| Expression 					{ $$ = move ($1); };


%code provides {

namespace yy
{
    yy::kivi_parser::symbol_type yylex(syntax_analyzer::parsing_context &);
}

};

%%

