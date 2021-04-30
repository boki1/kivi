%language "c++"
%define api.parser.class { kivi_parser }
%define api.value.type variant
%define parse.assert
%define parse.error verbose
%define api.token.constructor
%locations   // <--

%code requires {

#include "../kivi/parser.hh"

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
%left '*' '/' '%'
%left '('

%type<long>        NUMBER_LITERAL
%type<std::string> IDENTIFIER STRING_LITERAL
%type<std::string> Safe_identifier
%type<expression>  Statement Expression Expressions Comma_sep_expressions Var_definition Compound_statement Parameter_list
%type<expression>  Comparison_operation Arithmetic_operation Unary_operation Function_call_operation
%type<expression>  Safe_expression Safe_expressions Safe_statement Safe_parentesised_expression
%%

Program:
    { ctx.enter_scope(); }
	Functions {
        ctx.exit_scope();
    }
;

Functions:
  /* empty */
| Functions Single_function;

Single_function:
  Safe_identifier {
	ctx.define_function($1);
	ctx.enter_scope();
  }
  Parameter_list Safe_colon
  Safe_statement {
	ctx.add_function_with_block(std::move($1), std::move($5));
	ctx.exit_scope();
  };

Parameter_list:
  /* empty */
| Single_param
;

Single_param:
  // One or more; comma-delimited
  Single_param ',' Safe_identifier
  	{ ctx.define_parameter($3); }
| IDENTIFIER
	{ ctx.define_parameter($1); }
;

Statement:
  Compound_statement Safe_closing_brace {
  	$$ = std::move($1);
 	ctx.exit_scope();
  }
| IF Safe_expression Safe_colon Safe_statement {
	$$ = new_compare_and_expr(std::move($2), std::move($4));
  }
| WHILE Safe_expression ':' Safe_statement {
	$$ = new_compare_loop_expr(std::move($2), std::move($4));
  }
| RETURN Safe_expression Safe_semicolon {
	$$ = new_retrn_expr(std::move($2));
  }
| Expressions Safe_semicolon {
	$$ = std::move($1);
  }
| ';' { }
;

Comma_sep_expressions:
  Safe_expression {
    $$ = new_expression_sequence_expr(std::move($1));
  }
  // One or more; comma-delimited
| Comma_sep_expressions ',' Safe_expression { $$ = std::move($1);
    $$.add_parameter(std::move($3));
  }
;

Var_definition:
    VAR Safe_identifier '=' Safe_expression {
        $$ = expression(ctx.define_local($2)).move_expr(std::move($4));
    }
;

Compound_statement:
  '{' {
	$$ = new_expression_sequence_expr();
	ctx.enter_scope();
  }
| Compound_statement Statement {
	$$ = std::move($1);
	$$.add_parameter(std::move($2));
  }
;

Comparison_operation:
  Expression "==" error {
    $$ = std::move($1);
  }
| Expression "==" Expression {
    $$ = new_equality_expr(std::move($1), std::move($3));
  }
| Expression "<>" error {
    $$ = std::move($1);
  }
| Expression "<>" Expression {
    $$ = new_equality_expr(new_equality_expr((std::move($1), std::move($3))), expression(0ul));
  }
;

Arithmetic_operation:
  Expression '+' error {
    $$ = std::move($1);
  }
| Expression '+' Expression {
    $$ = new_addition_expr(std::move($1), std::move($3));
  }
| Expression '-' error {
    $$ = std::move($1);
  }
| Expression '-' Expression %prec '+' {
    $$ = new_addition_expr(std::move($1), new_negation_expr(std::move($3)));
  }
| Expression '*' error {
    $$ = std::move($1);
  }
| Expression '*' Expression {
    $$ = new_multiplication_expr(std::move($1), std::move($3));
  }
//
// TODO:
// Make division by 0 a compiler time error
//
| Expression '/' error {
    $$ = std::move($1);
  }
| Expression '/' Expression %prec '*' {
    $$ = new_division_expr(std::move($1), std::move($3));
  }
| Expression '%' Expression %prec '*' {
    $$ = new_modular_division_expr(std::move($1), std::move($3));
  }
| Expression '%' error {
	$$ = std::move($1);
  }
| Expression '=' error {
    $$ = std::move($1);
  }
| Expression '=' Expression {
    $$ = expression(std::move($1).move_expr(std::move($3)));
  }
;

Unary_operation:
  '-' Expression {
    $$ = new_negation_expr(std::move($2));
  }
| '-' error { }
;

Function_call_operation:
  Expression '(' ')' {
    $$ = new_function_call_expr(std::move($1));
  }
| Expression '(' Comma_sep_expressions Safe_closing_parentesis {
    $$ = new_function_call_expr(std::move($1));
    $$.splice_parameter_list_with(std::move($3));
  }
| '(' Comma_sep_expressions Safe_closing_parentesis{
    $$ = std::move($2);
  }
;

Expressions:
  Var_definition {
    $$ = std::move($1);
  }
| Expression {
    $$ = std::move($1);
  }
| Expression ',' Comma_sep_expressions {
    $$ = new_expression_sequence_expr(std::move($1));
    $$.splice_parameter_list_with(std::move($3));
  }
;

Expression:
  STRING_LITERAL {
    $$ = expression(std::move($1));
  }
| NUMBER_LITERAL {
    $$ = expression($1);
  }
| IDENTIFIER {
    $$ = ctx.use_identifier($1);
  }
| Arithmetic_operation
| Comparison_operation
| Unary_operation
| Function_call_operation
;

//
// Error handling and correction
//

Safe_identifier:
  error { }
| IDENTIFIER {
    $$ = std::move($1);
  }
;

Safe_colon:
  error { }
| ':'
;

Safe_semicolon:
  error { }
| ';'
;

Safe_closing_brace:
  error { }
| '}'
;

Safe_closing_parentesis:
  error { }
| ')'
;

Safe_statement:
  error { }
| Statement {
    $$ = std::move($1);
  }
;

Safe_expression:
  error { }
| Expression {
    $$ = std::move($1);
  }
;

Safe_expressions:
  error { }
| Expressions {
    $$ = std::move($1);
  }
;

Safe_parentesised_expression:
  error { }
| '(' Safe_expressions Safe_closing_parentesis {
    $$ = std::move($2);
  }
;
