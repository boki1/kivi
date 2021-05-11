%language "c++"
%define api.parser.class { kivi_parser }
%define api.value.type variant
%define api.token.constructor
%define parse.assert
%define parse.error verbose
%require "3.7"
%locations // <--

%code requires {

#include <parser/parsing_context.hh>
#include <kivi_expressions/base.hh>
#include <kivi_expressions/assignment.hh>
#include <kivi_expressions/sequence.hh>
#include <kivi_expressions/addition.hh>
#include <kivi_expressions/division.hh>
#include <kivi_expressions/modular_division.hh>
#include <kivi_expressions/multiplication.hh>
#include <kivi_expressions/negation.hh>
#include <kivi_expressions/equality.hh>
#include <kivi_expressions/inequality.hh>
#include <kivi_expressions/identifier.hh>
#include <kivi_expressions/nop.hh>
#include <kivi_expressions/numerical.hh>
#include <kivi_expressions/string.hh>
#include <kivi_expressions/function_call.hh>
#include <kivi_expressions/parameter_list.hh>
#include <kivi_stmts/compound.hh>
#include <kivi_stmts/expression.hh>
#include <kivi_stmts/if.hh>
#include <kivi_stmts/return.hh>
#include <kivi_stmts/statement.hh>
#include <kivi_stmts/while.hh>
#include <kivi_stmts/var.hh>

} //%code requires


%param { syntax_analyzer::parsing_context &ctx }

%token END 0
%token VAR "auto" IF "if" WHILE "while" RETURN "return"
%token IDENTIFIER STRING_LITERAL NUMBER_LITERAL
%token EQ "==" NE "<>"

// Precedence and associativity
%left ','
%right '='
%left "<>" "=="
%left '+' '-'
%left '*' '/' '%'
%left '('

/*
 * Note this "IDENTIFIER" __has nothing__ to do with the identifier class
 * defined in <ast/syntax.hh>
 * @bug ??? `type<syntax_analyzer::sequence> Comma_sep_expressions`
 */
%type<int> 					NUMBER_LITERAL
%type<std::string> 				STRING_LITERAL
%type<std::string> 				IDENTIFIER Safe_identifier
%type<syntax_analyzer::function_call_expr> 			Function_call
%type<syntax_analyzer::parameter_list_expr>  		Parameter_list
%type<syntax_analyzer::statement> 				Statement Safe_statement
%type<syntax_analyzer::expression> 				Expression Safe_expression
%type<syntax_analyzer::unary_operation> 			Unary_operation
%type<syntax_analyzer::compound_stmt> 			Compound_statement
%type<syntax_analyzer::comparison_operation> 		Comparison_operation
%type<syntax_analyzer::arithmetic_operation> 		Arithmetic_operation
%type<syntax_analyzer::parameter_list_expr> 			Parenthesised_expression Safe_parenthesised_expression
%type<syntax_analyzer::sequence> 				Comma_sep_expressions
%%

Program: 					{ ctx.enter_scope (); }
	Functions 				{ ctx.exit_scope (); }
;

Functions :
  /* empty */
| Functions Single_function;

Single_function:
	Safe_identifier 			{ ctx.define_function ($1); ctx.enter_scope (); }
	Parameter_list Safe_colon
		Safe_statement 			{ ctx.define_function_body (std::move ($1), std::move ($5)); ctx.exit_scope (); }
;

Parameter_list:
  /* empty */
| Single_param
;

Single_param:
  Single_param ',' Safe_identifier    		{ ctx.define_parameter ($3); }
| IDENTIFIER                            	{ ctx.define_parameter ($1); }
;

Statement:
  Compound_statement Safe_closing_brace 	{ $$ = std::move ($1); ctx.exit_scope (); }
| IF Safe_expression Safe_colon Safe_statement 	{ $$ = syntax_analyzer::if_stmt ($2, $4); }
| WHILE Safe_expression ':' Safe_statement 	{ $$ = syntax_analyzer::while_stmt ($2, $4); }
| RETURN Safe_expression Safe_semicolon 	{ $$ = syntax_analyzer::return_stmt ($2); }
| Expression Safe_semicolon 			{ $$ = syntax_analyzer::expression_stmt($1); }
| VAR Safe_identifier '=' Safe_expression 	{ ctx.define_local($2); $$ = syntax_analyzer::var_stmt($2, $4); }
| ';' 						{ }
;

Comma_sep_expressions:
  Safe_expression 				{ $$ = syntax_analyzer::sequence ($1); }
| Comma_sep_expressions ',' Safe_expression 	{ $$ = std::move ($1); $$.append (std::move ($3)); }
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
  Expression '+' error 				{ $$ = std::move ($1); }
| Expression '+' Expression 	        	{ $$ = syntax_analyzer::addition_expr ($1, $3); }
| Expression '-' error 				{ $$ = std::move ($1); }
| Expression '-' Expression %prec '+' 		{ $$ = syntax_analyzer::addition_expr ($1, syntax_analyzer::negation_expr ($3)); }
| Expression '*' error 				{ $$ = std::move ($1); }
| Expression '*' Expression 			{ $$ = syntax_analyzer::multiplication_expr ($1, $3);}
| Expression '/' error  			{ $$ = std::move ($1); }
| Expression '/' Expression %prec '*' 		{ $$ = syntax_analyzer::division_expr ($1, $3); }
| Expression '%' error 				{ $$ = std::move ($1); }
| Expression '%' Expression %prec '*' 		{ $$ = syntax_analyzer::modular_division_expr ($1, $3); }
| Expression '=' error 				{ $$ = std::move ($1); }
| Expression '=' Expression 			{ $$ = syntax_analyzer::assignment_expr ($1, $3); }
;

Unary_operation:
  '-' Expression 				{ $$ = syntax_analyzer::negation_expr (std::move ($2)); }
| '-' error 	 				{  }
;

/**
 * TODO: Should this be supported as a "Function_call"?
 *  '(' Comma_sep_expressions Safe_closing_parenthesis
 * { $$ = std::move ($2); }
 */

Function_call:
  IDENTIFIER '(' ')' 				{ $$ = syntax_analyzer::function_call_expr ($1); }
| IDENTIFIER Parenthesised_expression 		{ $$ = syntax_analyzer::function_call_expr ($1, std::move ($2)); }
;

Expression:
  STRING_LITERAL 				{ $$ = syntax_analyzer::string_lit (std::move ($1)); }
| NUMBER_LITERAL 				{ $$ = syntax_analyzer::numerical_lit ($1); }
| IDENTIFIER 					{ $$ = ctx.use_identifier ($1); }
| Function_call         			{ $$ = std::move($<syntax_analyzer::function_call_expr>1); }
| Arithmetic_operation  			{ $$ = std::move($1); }
| Comparison_operation  			{ $$ = std::move($1); }
| Unary_operation       			{ $$ = std::move($1); }
;


Parenthesised_expression:
  '(' Comma_sep_expressions
  	Safe_closing_parenthesis 		{ $$ = syntax_analyzer::parameter_list_expr::from_sequence($2); };

//
// Error handling and correction
//

Safe_identifier:
  error						{ }
| IDENTIFIER 					{ $$ = std::move ($1); };

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
| Statement 					{ $$ = std::move ($1); };

Safe_expression:
  error						{ }
| Expression 					{ $$ = std::move ($1); };

Safe_parenthesised_expression:
  error						{ }
| Parenthesised_expression   			{ $$ = std::move ($1); };

%code provides {
namespace yy
{
    yy::kivi_parser::symbol_type yylex(syntax_analyzer::parsing_context &);
}
};

%%

