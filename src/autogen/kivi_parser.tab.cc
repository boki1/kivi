// A Bison parser, made by GNU Bison 3.7.3.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "kivi_parser.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 136 "../autogen/kivi_parser.tab.cc"

  /// Build a parser object.
   kivi_parser :: kivi_parser  (parsing_context &ctx_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

   kivi_parser ::~ kivi_parser  ()
  {}

   kivi_parser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
   kivi_parser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   kivi_parser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   kivi_parser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   kivi_parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   kivi_parser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   kivi_parser ::symbol_kind_type
   kivi_parser ::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

   kivi_parser ::stack_symbol_type::stack_symbol_type ()
  {}

   kivi_parser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_Parameter_list: // Parameter_list
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Comma_sep_expressions: // Comma_sep_expressions
      case symbol_kind::S_Var_definition: // Var_definition
      case symbol_kind::S_Compound_statement: // Compound_statement
      case symbol_kind::S_Comparison_operation: // Comparison_operation
      case symbol_kind::S_Arithmetic_operation: // Arithmetic_operation
      case symbol_kind::S_Unary_operation: // Unary_operation
      case symbol_kind::S_Function_call_operation: // Function_call_operation
      case symbol_kind::S_Expressions: // Expressions
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Safe_statement: // Safe_statement
      case symbol_kind::S_Safe_expression: // Safe_expression
        value.YY_MOVE_OR_COPY< expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER_LITERAL: // NUMBER_LITERAL
        value.YY_MOVE_OR_COPY< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_Safe_identifier: // Safe_identifier
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   kivi_parser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_Parameter_list: // Parameter_list
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Comma_sep_expressions: // Comma_sep_expressions
      case symbol_kind::S_Var_definition: // Var_definition
      case symbol_kind::S_Compound_statement: // Compound_statement
      case symbol_kind::S_Comparison_operation: // Comparison_operation
      case symbol_kind::S_Arithmetic_operation: // Arithmetic_operation
      case symbol_kind::S_Unary_operation: // Unary_operation
      case symbol_kind::S_Function_call_operation: // Function_call_operation
      case symbol_kind::S_Expressions: // Expressions
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Safe_statement: // Safe_statement
      case symbol_kind::S_Safe_expression: // Safe_expression
        value.move< expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER_LITERAL: // NUMBER_LITERAL
        value.move< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_Safe_identifier: // Safe_identifier
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
   kivi_parser ::stack_symbol_type&
   kivi_parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_Parameter_list: // Parameter_list
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Comma_sep_expressions: // Comma_sep_expressions
      case symbol_kind::S_Var_definition: // Var_definition
      case symbol_kind::S_Compound_statement: // Compound_statement
      case symbol_kind::S_Comparison_operation: // Comparison_operation
      case symbol_kind::S_Arithmetic_operation: // Arithmetic_operation
      case symbol_kind::S_Unary_operation: // Unary_operation
      case symbol_kind::S_Function_call_operation: // Function_call_operation
      case symbol_kind::S_Expressions: // Expressions
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Safe_statement: // Safe_statement
      case symbol_kind::S_Safe_expression: // Safe_expression
        value.copy< expression > (that.value);
        break;

      case symbol_kind::S_NUMBER_LITERAL: // NUMBER_LITERAL
        value.copy< long > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_Safe_identifier: // Safe_identifier
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

   kivi_parser ::stack_symbol_type&
   kivi_parser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_Parameter_list: // Parameter_list
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Comma_sep_expressions: // Comma_sep_expressions
      case symbol_kind::S_Var_definition: // Var_definition
      case symbol_kind::S_Compound_statement: // Compound_statement
      case symbol_kind::S_Comparison_operation: // Comparison_operation
      case symbol_kind::S_Arithmetic_operation: // Arithmetic_operation
      case symbol_kind::S_Unary_operation: // Unary_operation
      case symbol_kind::S_Function_call_operation: // Function_call_operation
      case symbol_kind::S_Expressions: // Expressions
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Safe_statement: // Safe_statement
      case symbol_kind::S_Safe_expression: // Safe_expression
        value.move< expression > (that.value);
        break;

      case symbol_kind::S_NUMBER_LITERAL: // NUMBER_LITERAL
        value.move< long > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_Safe_identifier: // Safe_identifier
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   kivi_parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   kivi_parser ::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
   kivi_parser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   kivi_parser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   kivi_parser ::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   kivi_parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   kivi_parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   kivi_parser ::debug_level_type
   kivi_parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   kivi_parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   kivi_parser ::state_type
   kivi_parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
   kivi_parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   kivi_parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   kivi_parser ::operator() ()
  {
    return parse ();
  }

  int
   kivi_parser ::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_Parameter_list: // Parameter_list
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Comma_sep_expressions: // Comma_sep_expressions
      case symbol_kind::S_Var_definition: // Var_definition
      case symbol_kind::S_Compound_statement: // Compound_statement
      case symbol_kind::S_Comparison_operation: // Comparison_operation
      case symbol_kind::S_Arithmetic_operation: // Arithmetic_operation
      case symbol_kind::S_Unary_operation: // Unary_operation
      case symbol_kind::S_Function_call_operation: // Function_call_operation
      case symbol_kind::S_Expressions: // Expressions
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Safe_statement: // Safe_statement
      case symbol_kind::S_Safe_expression: // Safe_expression
        yylhs.value.emplace< expression > ();
        break;

      case symbol_kind::S_NUMBER_LITERAL: // NUMBER_LITERAL
        yylhs.value.emplace< long > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_Safe_identifier: // Safe_identifier
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // $@1: %empty
#line 39 "grammar.y"
    { ctx.enter_scope(); }
#line 660 "../autogen/kivi_parser.tab.cc"
    break;

  case 3: // Program: $@1 Functions
#line 40 "grammar.y"
                  {
        ctx.exit_scope();
    }
#line 668 "../autogen/kivi_parser.tab.cc"
    break;

  case 6: // $@2: %empty
#line 50 "grammar.y"
                  {
	ctx.define_function(yystack_[0].value.as < std::string > ());
	ctx.enter_scope();
  }
#line 677 "../autogen/kivi_parser.tab.cc"
    break;

  case 7: // Single_function: Safe_identifier $@2 Parameter_list Safe_colon Safe_statement
#line 55 "grammar.y"
                 {
	ctx.add_function_with_block(std::move(yystack_[4].value.as < std::string > ()), std::move(yystack_[0].value.as < expression > ()));
	ctx.exit_scope();
  }
#line 686 "../autogen/kivi_parser.tab.cc"
    break;

  case 10: // Single_param: Single_param ',' Safe_identifier
#line 68 "grammar.y"
        { ctx.define_parameter(yystack_[0].value.as < std::string > ()); }
#line 692 "../autogen/kivi_parser.tab.cc"
    break;

  case 11: // Single_param: IDENTIFIER
#line 70 "grammar.y"
        { ctx.define_parameter(yystack_[0].value.as < std::string > ()); }
#line 698 "../autogen/kivi_parser.tab.cc"
    break;

  case 12: // Statement: Compound_statement Safe_closing_brace
#line 74 "grammar.y"
                                        {
  	yylhs.value.as < expression > () = std::move(yystack_[1].value.as < expression > ());
 	ctx.exit_scope();
  }
#line 707 "../autogen/kivi_parser.tab.cc"
    break;

  case 13: // Statement: "if" Safe_expression Safe_colon Safe_statement
#line 78 "grammar.y"
                                               {
	yylhs.value.as < expression > () = new_compare_and_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 715 "../autogen/kivi_parser.tab.cc"
    break;

  case 14: // Statement: "while" Safe_expression ':' Safe_statement
#line 81 "grammar.y"
                                           {
	yylhs.value.as < expression > () = new_compare_loop_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 723 "../autogen/kivi_parser.tab.cc"
    break;

  case 15: // Statement: "return" Safe_expression Safe_semicolon
#line 84 "grammar.y"
                                        {
	yylhs.value.as < expression > () = new_retrn_expr(std::move(yystack_[1].value.as < expression > ()));
  }
#line 731 "../autogen/kivi_parser.tab.cc"
    break;

  case 16: // Statement: Expressions Safe_semicolon
#line 87 "grammar.y"
                             {
	yylhs.value.as < expression > () = std::move(yystack_[1].value.as < expression > ());
  }
#line 739 "../autogen/kivi_parser.tab.cc"
    break;

  case 17: // Statement: ';'
#line 90 "grammar.y"
      { }
#line 745 "../autogen/kivi_parser.tab.cc"
    break;

  case 18: // Comma_sep_expressions: Safe_expression
#line 94 "grammar.y"
                  {
    yylhs.value.as < expression > () = new_expression_sequence_expr(std::move(yystack_[0].value.as < expression > ()));
  }
#line 753 "../autogen/kivi_parser.tab.cc"
    break;

  case 19: // Comma_sep_expressions: Comma_sep_expressions ',' Safe_expression
#line 98 "grammar.y"
                                            { yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
    yylhs.value.as < expression > ().add_parameter(std::move(yystack_[0].value.as < expression > ()));
  }
#line 761 "../autogen/kivi_parser.tab.cc"
    break;

  case 20: // Var_definition: "auto" Safe_identifier '=' Safe_expression
#line 104 "grammar.y"
                                            {
        yylhs.value.as < expression > () = expression(ctx.define_local(yystack_[2].value.as < std::string > ())).move_expr(std::move(yystack_[0].value.as < expression > ()));
    }
#line 769 "../autogen/kivi_parser.tab.cc"
    break;

  case 21: // Compound_statement: '{'
#line 110 "grammar.y"
      {
	yylhs.value.as < expression > () = new_expression_sequence_expr();
	ctx.enter_scope();
  }
#line 778 "../autogen/kivi_parser.tab.cc"
    break;

  case 22: // Compound_statement: Compound_statement Statement
#line 114 "grammar.y"
                               {
	yylhs.value.as < expression > () = std::move(yystack_[1].value.as < expression > ());
	yylhs.value.as < expression > ().add_parameter(std::move(yystack_[0].value.as < expression > ()));
  }
#line 787 "../autogen/kivi_parser.tab.cc"
    break;

  case 23: // Comparison_operation: Expression "==" error
#line 121 "grammar.y"
                        {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 795 "../autogen/kivi_parser.tab.cc"
    break;

  case 24: // Comparison_operation: Expression "==" Expression
#line 124 "grammar.y"
                             {
    yylhs.value.as < expression > () = new_equality_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 803 "../autogen/kivi_parser.tab.cc"
    break;

  case 25: // Comparison_operation: Expression "<>" error
#line 127 "grammar.y"
                        {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 811 "../autogen/kivi_parser.tab.cc"
    break;

  case 26: // Comparison_operation: Expression "<>" Expression
#line 130 "grammar.y"
                             {
    yylhs.value.as < expression > () = new_equality_expr(new_equality_expr((std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()))), expression(0ul));
  }
#line 819 "../autogen/kivi_parser.tab.cc"
    break;

  case 27: // Arithmetic_operation: Expression '+' error
#line 136 "grammar.y"
                       {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 827 "../autogen/kivi_parser.tab.cc"
    break;

  case 28: // Arithmetic_operation: Expression '+' Expression
#line 139 "grammar.y"
                            {
    yylhs.value.as < expression > () = new_addition_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 835 "../autogen/kivi_parser.tab.cc"
    break;

  case 29: // Arithmetic_operation: Expression '-' error
#line 142 "grammar.y"
                       {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 843 "../autogen/kivi_parser.tab.cc"
    break;

  case 30: // Arithmetic_operation: Expression '-' Expression
#line 145 "grammar.y"
                                      {
    yylhs.value.as < expression > () = new_addition_expr(std::move(yystack_[2].value.as < expression > ()), new_negation_expr(std::move(yystack_[0].value.as < expression > ())));
  }
#line 851 "../autogen/kivi_parser.tab.cc"
    break;

  case 31: // Arithmetic_operation: Expression '*' error
#line 148 "grammar.y"
                       {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 859 "../autogen/kivi_parser.tab.cc"
    break;

  case 32: // Arithmetic_operation: Expression '*' Expression
#line 151 "grammar.y"
                            {
    yylhs.value.as < expression > () = new_multiplication_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 867 "../autogen/kivi_parser.tab.cc"
    break;

  case 33: // Arithmetic_operation: Expression '/' error
#line 158 "grammar.y"
                       {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 875 "../autogen/kivi_parser.tab.cc"
    break;

  case 34: // Arithmetic_operation: Expression '/' Expression
#line 161 "grammar.y"
                                      {
    yylhs.value.as < expression > () = new_division_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 883 "../autogen/kivi_parser.tab.cc"
    break;

  case 35: // Arithmetic_operation: Expression '%' Expression
#line 164 "grammar.y"
                                      {
    yylhs.value.as < expression > () = new_modular_division_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 891 "../autogen/kivi_parser.tab.cc"
    break;

  case 36: // Arithmetic_operation: Expression '%' error
#line 167 "grammar.y"
                       {
	yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 899 "../autogen/kivi_parser.tab.cc"
    break;

  case 37: // Arithmetic_operation: Expression '=' error
#line 170 "grammar.y"
                       {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 907 "../autogen/kivi_parser.tab.cc"
    break;

  case 38: // Arithmetic_operation: Expression '=' Expression
#line 173 "grammar.y"
                            {
    yylhs.value.as < expression > () = expression(std::move(yystack_[2].value.as < expression > ()).move_expr(std::move(yystack_[0].value.as < expression > ())));
  }
#line 915 "../autogen/kivi_parser.tab.cc"
    break;

  case 39: // Unary_operation: '-' Expression
#line 179 "grammar.y"
                 {
    yylhs.value.as < expression > () = new_negation_expr(std::move(yystack_[0].value.as < expression > ()));
  }
#line 923 "../autogen/kivi_parser.tab.cc"
    break;

  case 40: // Unary_operation: '-' error
#line 182 "grammar.y"
            { }
#line 929 "../autogen/kivi_parser.tab.cc"
    break;

  case 41: // Function_call_operation: Expression '(' ')'
#line 186 "grammar.y"
                     {
    yylhs.value.as < expression > () = new_function_call_expr(std::move(yystack_[2].value.as < expression > ()));
  }
#line 937 "../autogen/kivi_parser.tab.cc"
    break;

  case 42: // Function_call_operation: Expression '(' Comma_sep_expressions Safe_closing_parentesis
#line 189 "grammar.y"
                                                               {
    yylhs.value.as < expression > () = new_function_call_expr(std::move(yystack_[3].value.as < expression > ()));
    yylhs.value.as < expression > ().splice_parameter_list_with(std::move(yystack_[1].value.as < expression > ()));
  }
#line 946 "../autogen/kivi_parser.tab.cc"
    break;

  case 43: // Function_call_operation: '(' Comma_sep_expressions Safe_closing_parentesis
#line 193 "grammar.y"
                                                   {
    yylhs.value.as < expression > () = std::move(yystack_[1].value.as < expression > ());
  }
#line 954 "../autogen/kivi_parser.tab.cc"
    break;

  case 44: // Expressions: Var_definition
#line 199 "grammar.y"
                 {
    yylhs.value.as < expression > () = std::move(yystack_[0].value.as < expression > ());
  }
#line 962 "../autogen/kivi_parser.tab.cc"
    break;

  case 45: // Expressions: Expression
#line 202 "grammar.y"
             {
    yylhs.value.as < expression > () = std::move(yystack_[0].value.as < expression > ());
  }
#line 970 "../autogen/kivi_parser.tab.cc"
    break;

  case 46: // Expressions: Expression ',' Comma_sep_expressions
#line 205 "grammar.y"
                                       {
    yylhs.value.as < expression > () = new_expression_sequence_expr(std::move(yystack_[2].value.as < expression > ()));
    yylhs.value.as < expression > ().splice_parameter_list_with(std::move(yystack_[0].value.as < expression > ()));
  }
#line 979 "../autogen/kivi_parser.tab.cc"
    break;

  case 47: // Expression: STRING_LITERAL
#line 212 "grammar.y"
                 {
    yylhs.value.as < expression > () = expression(std::move(yystack_[0].value.as < std::string > ()));
  }
#line 987 "../autogen/kivi_parser.tab.cc"
    break;

  case 48: // Expression: NUMBER_LITERAL
#line 215 "grammar.y"
                 {
    yylhs.value.as < expression > () = expression(yystack_[0].value.as < long > ());
  }
#line 995 "../autogen/kivi_parser.tab.cc"
    break;

  case 49: // Expression: IDENTIFIER
#line 218 "grammar.y"
             {
    yylhs.value.as < expression > () = ctx.use_identifier(yystack_[0].value.as < std::string > ());
  }
#line 1003 "../autogen/kivi_parser.tab.cc"
    break;

  case 50: // Expression: Arithmetic_operation
#line 221 "grammar.y"
  { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 1009 "../autogen/kivi_parser.tab.cc"
    break;

  case 51: // Expression: Comparison_operation
#line 222 "grammar.y"
  { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 1015 "../autogen/kivi_parser.tab.cc"
    break;

  case 52: // Expression: Unary_operation
#line 223 "grammar.y"
  { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 1021 "../autogen/kivi_parser.tab.cc"
    break;

  case 53: // Expression: Function_call_operation
#line 224 "grammar.y"
  { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 1027 "../autogen/kivi_parser.tab.cc"
    break;

  case 54: // Safe_identifier: error
#line 232 "grammar.y"
        { }
#line 1033 "../autogen/kivi_parser.tab.cc"
    break;

  case 55: // Safe_identifier: IDENTIFIER
#line 233 "grammar.y"
             {
    yylhs.value.as < std::string > () = std::move(yystack_[0].value.as < std::string > ());
  }
#line 1041 "../autogen/kivi_parser.tab.cc"
    break;

  case 56: // Safe_colon: error
#line 239 "grammar.y"
        { }
#line 1047 "../autogen/kivi_parser.tab.cc"
    break;

  case 58: // Safe_semicolon: error
#line 244 "grammar.y"
        { }
#line 1053 "../autogen/kivi_parser.tab.cc"
    break;

  case 60: // Safe_closing_brace: error
#line 249 "grammar.y"
        { }
#line 1059 "../autogen/kivi_parser.tab.cc"
    break;

  case 62: // Safe_closing_parentesis: error
#line 254 "grammar.y"
        { }
#line 1065 "../autogen/kivi_parser.tab.cc"
    break;

  case 64: // Safe_statement: error
#line 259 "grammar.y"
        { }
#line 1071 "../autogen/kivi_parser.tab.cc"
    break;

  case 65: // Safe_statement: Statement
#line 260 "grammar.y"
            {
    yylhs.value.as < expression > () = std::move(yystack_[0].value.as < expression > ());
  }
#line 1079 "../autogen/kivi_parser.tab.cc"
    break;

  case 66: // Safe_expression: error
#line 266 "grammar.y"
        { }
#line 1085 "../autogen/kivi_parser.tab.cc"
    break;

  case 67: // Safe_expression: Expression
#line 267 "grammar.y"
             {
    yylhs.value.as < expression > () = std::move(yystack_[0].value.as < expression > ());
  }
#line 1093 "../autogen/kivi_parser.tab.cc"
    break;


#line 1097 "../autogen/kivi_parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   kivi_parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   kivi_parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
   kivi_parser ::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  //  kivi_parser ::context.
   kivi_parser ::context::context (const  kivi_parser & yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
   kivi_parser ::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
   kivi_parser ::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
   kivi_parser ::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  kivi_parser ::yypact_ninf_ = -53;

  const signed char  kivi_parser ::yytable_ninf_ = -4;

  const short
   kivi_parser ::yypact_[] =
  {
     -53,    12,   -53,   -53,    30,   -53,   -53,   -53,   -53,    -6,
     -53,     7,    13,   -53,   -53,    72,    27,   -53,    27,    81,
      81,    81,   -53,   -53,   -53,    94,    81,   -53,   -53,   -53,
     -53,    14,   -53,   -53,   -53,   -53,     5,   168,   -53,   -53,
      19,   -53,   178,     7,    21,     5,   -53,    45,     1,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,    97,   110,    81,
     113,   126,   129,   142,   145,   158,    51,    81,    72,    72,
     -53,   -53,    81,   -53,   -53,   -53,   184,   -53,   184,    32,
     -53,   178,   -53,    45,   -53,    45,   -53,    36,   -53,    36,
     -53,    36,   -53,     1,   -53,   -53,   -53,   -53,   -53
  };

  const signed char
   kivi_parser ::yydefact_[] =
  {
       2,     0,     4,     1,     0,    54,    55,     5,     6,     8,
      11,     0,     9,    56,    57,     0,     0,    64,     0,     0,
       0,     0,    49,    47,    48,     0,     0,    17,    21,    65,
      44,     0,    51,    50,    52,    53,     0,    45,     7,    10,
       0,    66,    67,     0,     0,     0,    40,    39,     0,    18,
      60,    61,    22,    12,    58,    59,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      15,    62,     0,    63,    43,    23,    24,    25,    26,    46,
      37,    38,    27,    28,    29,    30,    31,    32,    33,    34,
      36,    35,    41,     0,    20,    13,    14,    19,    42
  };

  const signed char
   kivi_parser ::yypgoto_[] =
  {
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,    26,   -52,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -15,    -7,    22,
      23,   -53,   -26,   -29,   -16
  };

  const signed char
   kivi_parser ::yydefgoto_[] =
  {
      -1,     1,     2,     4,     7,     9,    11,    12,    29,    48,
      30,    31,    32,    33,    34,    35,    36,    42,     8,    15,
      56,    53,    74,    38,    49
  };

  const signed char
   kivi_parser ::yytable_[] =
  {
      37,    10,    71,    43,    44,    45,    54,    79,    13,    39,
      47,    40,     3,    72,    93,    50,    37,    18,    19,    20,
      21,    22,    23,    24,    73,    16,    55,    14,     5,    25,
      -3,     5,    67,    26,     6,    27,    28,     6,    51,    95,
      96,    69,    76,    78,    72,    81,    83,    85,    87,    89,
      91,    94,    41,    37,    37,    66,    97,    52,    22,    23,
      24,    63,    64,    65,    66,    68,    25,    98,    70,     0,
      26,     0,     0,    17,    92,    18,    19,    20,    21,    22,
      23,    24,    41,     0,     0,     0,     0,    25,    22,    23,
      24,    26,     0,    27,    28,    46,    25,     0,    75,     0,
      26,    22,    23,    24,    22,    23,    24,     0,     0,    25,
       0,    77,    25,    26,    80,     0,    26,    22,    23,    24,
      22,    23,    24,     0,     0,    25,     0,    82,    25,    26,
      84,     0,    26,    22,    23,    24,    22,    23,    24,     0,
       0,    25,     0,    86,    25,    26,    88,     0,    26,    22,
      23,    24,    22,    23,    24,     0,     0,    25,     0,    90,
      25,    26,     0,     0,    26,    22,    23,    24,     0,     0,
       0,     0,     0,    25,     0,     0,     0,    26,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    57,    58,
       0,    60,    61,    62,    63,    64,    65,    66,    61,    62,
      63,    64,    65,    66
  };

  const signed char
   kivi_parser ::yycheck_[] =
  {
      15,     7,     1,    19,    20,    21,     1,    59,     1,    16,
      25,    18,     0,    12,    66,     1,    31,     3,     4,     5,
       6,     7,     8,     9,    23,    12,    21,    20,     1,    15,
       0,     1,    13,    19,     7,    21,    22,     7,    24,    68,
      69,    20,    57,    58,    12,    60,    61,    62,    63,    64,
      65,    67,     1,    68,    69,    19,    72,    31,     7,     8,
       9,    16,    17,    18,    19,    43,    15,    93,    45,    -1,
      19,    -1,    -1,     1,    23,     3,     4,     5,     6,     7,
       8,     9,     1,    -1,    -1,    -1,    -1,    15,     7,     8,
       9,    19,    -1,    21,    22,     1,    15,    -1,     1,    -1,
      19,     7,     8,     9,     7,     8,     9,    -1,    -1,    15,
      -1,     1,    15,    19,     1,    -1,    19,     7,     8,     9,
       7,     8,     9,    -1,    -1,    15,    -1,     1,    15,    19,
       1,    -1,    19,     7,     8,     9,     7,     8,     9,    -1,
      -1,    15,    -1,     1,    15,    19,     1,    -1,    19,     7,
       8,     9,     7,     8,     9,    -1,    -1,    15,    -1,     1,
      15,    19,    -1,    -1,    19,     7,     8,     9,    -1,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    19,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    19,    14,    15,
      16,    17,    18,    19
  };

  const signed char
   kivi_parser ::yystos_[] =
  {
       0,    26,    27,     0,    28,     1,     7,    29,    43,    30,
       7,    31,    32,     1,    20,    44,    12,     1,     3,     4,
       5,     6,     7,     8,     9,    15,    19,    21,    22,    33,
      35,    36,    37,    38,    39,    40,    41,    42,    48,    43,
      43,     1,    42,    49,    49,    49,     1,    42,    34,    49,
       1,    24,    33,    46,     1,    21,    45,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    13,    44,    20,
      45,     1,    12,    23,    47,     1,    42,     1,    42,    34,
       1,    42,     1,    42,     1,    42,     1,    42,     1,    42,
       1,    42,    23,    34,    49,    48,    48,    49,    47
  };

  const signed char
   kivi_parser ::yyr1_[] =
  {
       0,    25,    27,    26,    28,    28,    30,    29,    31,    31,
      32,    32,    33,    33,    33,    33,    33,    33,    34,    34,
      35,    36,    36,    37,    37,    37,    37,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    39,
      39,    40,    40,    40,    41,    41,    41,    42,    42,    42,
      42,    42,    42,    42,    43,    43,    44,    44,    45,    45,
      46,    46,    47,    47,    48,    48,    49,    49
  };

  const signed char
   kivi_parser ::yyr2_[] =
  {
       0,     2,     0,     2,     0,     2,     0,     5,     0,     1,
       3,     1,     2,     4,     4,     3,     2,     1,     1,     3,
       4,     1,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     4,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  kivi_parser ::yytname_[] =
  {
  "END", "error", "\"invalid token\"", "\"auto\"", "\"if\"", "\"while\"",
  "\"return\"", "IDENTIFIER", "STRING_LITERAL", "NUMBER_LITERAL", "\"==\"",
  "\"<>\"", "','", "'='", "'+'", "'-'", "'*'", "'/'", "'%'", "'('", "':'",
  "';'", "'{'", "')'", "'}'", "$accept", "Program", "$@1", "Functions",
  "Single_function", "$@2", "Parameter_list", "Single_param", "Statement",
  "Comma_sep_expressions", "Var_definition", "Compound_statement",
  "Comparison_operation", "Arithmetic_operation", "Unary_operation",
  "Function_call_operation", "Expressions", "Expression",
  "Safe_identifier", "Safe_colon", "Safe_semicolon", "Safe_closing_brace",
  "Safe_closing_parentesis", "Safe_statement", "Safe_expression", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
   kivi_parser ::yyrline_[] =
  {
       0,    39,    39,    39,    45,    47,    50,    50,    60,    62,
      67,    69,    74,    78,    81,    84,    87,    90,    94,    98,
     104,   110,   114,   121,   124,   127,   130,   136,   139,   142,
     145,   148,   151,   158,   161,   164,   167,   170,   173,   179,
     182,   186,   189,   193,   199,   202,   205,   212,   215,   218,
     221,   222,   223,   224,   232,   233,   239,   240,   244,   245,
     249,   250,   254,   255,   259,   260,   266,   267
  };

  void
   kivi_parser ::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
   kivi_parser ::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1650 "../autogen/kivi_parser.tab.cc"

