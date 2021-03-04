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
#line 136 "src/autogen/kivi_parser.tab.cc"

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
#line 39 "src/misc/grammar.y"
    { ctx.enter_scope(); }
#line 660 "src/autogen/kivi_parser.tab.cc"
    break;

  case 3: // Program: $@1 Functions
#line 40 "src/misc/grammar.y"
                  {
        ctx.exit_scope();
    }
#line 668 "src/autogen/kivi_parser.tab.cc"
    break;

  case 6: // $@2: %empty
#line 50 "src/misc/grammar.y"
                  {
	ctx.define_function(yystack_[0].value.as < std::string > ());
	ctx.enter_scope();
  }
#line 677 "src/autogen/kivi_parser.tab.cc"
    break;

  case 7: // Single_function: Safe_identifier $@2 Parameter_list Safe_colon Safe_statement
#line 55 "src/misc/grammar.y"
                 {
	ctx.add_function_with_block(std::move(yystack_[4].value.as < std::string > ()), std::move(yystack_[0].value.as < expression > ()));
	ctx.exit_scope();
  }
#line 686 "src/autogen/kivi_parser.tab.cc"
    break;

  case 10: // Single_param: Single_param ',' Safe_identifier
#line 68 "src/misc/grammar.y"
        { ctx.define_parameter(yystack_[0].value.as < std::string > ()); }
#line 692 "src/autogen/kivi_parser.tab.cc"
    break;

  case 11: // Single_param: IDENTIFIER
#line 70 "src/misc/grammar.y"
        { ctx.define_parameter(yystack_[0].value.as < std::string > ()); }
#line 698 "src/autogen/kivi_parser.tab.cc"
    break;

  case 12: // Statement: Compound_statement Safe_closing_brace
#line 74 "src/misc/grammar.y"
                                        {
  	yylhs.value.as < expression > () = std::move(yystack_[1].value.as < expression > ());
 	ctx.exit_scope();
  }
#line 707 "src/autogen/kivi_parser.tab.cc"
    break;

  case 13: // Statement: "if" Safe_expression Safe_colon Safe_statement
#line 78 "src/misc/grammar.y"
                                               {
	yylhs.value.as < expression > () = new_compare_and_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 715 "src/autogen/kivi_parser.tab.cc"
    break;

  case 14: // Statement: "while" Safe_expression ':' Safe_statement
#line 81 "src/misc/grammar.y"
                                           {
	yylhs.value.as < expression > () = new_compare_loop_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 723 "src/autogen/kivi_parser.tab.cc"
    break;

  case 15: // Statement: "return" Safe_expression Safe_semicolon
#line 84 "src/misc/grammar.y"
                                        {
	yylhs.value.as < expression > () = new_retrn_expr(std::move(yystack_[1].value.as < expression > ()));
  }
#line 731 "src/autogen/kivi_parser.tab.cc"
    break;

  case 16: // Statement: Expressions Safe_semicolon
#line 87 "src/misc/grammar.y"
                             {
	yylhs.value.as < expression > () = std::move(yystack_[1].value.as < expression > ());
  }
#line 739 "src/autogen/kivi_parser.tab.cc"
    break;

  case 17: // Statement: ';'
#line 90 "src/misc/grammar.y"
      { }
#line 745 "src/autogen/kivi_parser.tab.cc"
    break;

  case 18: // Comma_sep_expressions: Safe_expression
#line 94 "src/misc/grammar.y"
                  {
    yylhs.value.as < expression > () = new_expression_sequence_expr(std::move(yystack_[0].value.as < expression > ()));
  }
#line 753 "src/autogen/kivi_parser.tab.cc"
    break;

  case 19: // Comma_sep_expressions: Comma_sep_expressions ',' Safe_expression
#line 98 "src/misc/grammar.y"
                                            { yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
    yylhs.value.as < expression > ().add_parameter(std::move(yystack_[0].value.as < expression > ()));
  }
#line 761 "src/autogen/kivi_parser.tab.cc"
    break;

  case 20: // Var_definition: "auto" Safe_identifier '=' Safe_expression
#line 104 "src/misc/grammar.y"
                                            {
        yylhs.value.as < expression > () = expression(ctx.define_local(yystack_[2].value.as < std::string > ())).move_expr(std::move(yystack_[0].value.as < expression > ()));
    }
#line 769 "src/autogen/kivi_parser.tab.cc"
    break;

  case 21: // Compound_statement: '{'
#line 110 "src/misc/grammar.y"
      {
	yylhs.value.as < expression > () = new_expression_sequence_expr();
	ctx.enter_scope();
  }
#line 778 "src/autogen/kivi_parser.tab.cc"
    break;

  case 22: // Compound_statement: Compound_statement Statement
#line 114 "src/misc/grammar.y"
                               {
	yylhs.value.as < expression > () = std::move(yystack_[1].value.as < expression > ());
	yylhs.value.as < expression > ().add_parameter(std::move(yystack_[0].value.as < expression > ()));
  }
#line 787 "src/autogen/kivi_parser.tab.cc"
    break;

  case 23: // Comparison_operation: Expression "==" error
#line 121 "src/misc/grammar.y"
                        {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 795 "src/autogen/kivi_parser.tab.cc"
    break;

  case 24: // Comparison_operation: Expression "==" Expression
#line 124 "src/misc/grammar.y"
                             {
    yylhs.value.as < expression > () = new_equality_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 803 "src/autogen/kivi_parser.tab.cc"
    break;

  case 25: // Comparison_operation: Expression "<>" error
#line 127 "src/misc/grammar.y"
                        {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 811 "src/autogen/kivi_parser.tab.cc"
    break;

  case 26: // Comparison_operation: Expression "<>" Expression
#line 130 "src/misc/grammar.y"
                             {
    yylhs.value.as < expression > () = new_equality_expr(new_equality_expr((std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()))), expression(0ul));
  }
#line 819 "src/autogen/kivi_parser.tab.cc"
    break;

  case 27: // Arithmetic_operation: Expression '+' error
#line 136 "src/misc/grammar.y"
                       {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 827 "src/autogen/kivi_parser.tab.cc"
    break;

  case 28: // Arithmetic_operation: Expression '+' Expression
#line 139 "src/misc/grammar.y"
                            {
    yylhs.value.as < expression > () = new_addition_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 835 "src/autogen/kivi_parser.tab.cc"
    break;

  case 29: // Arithmetic_operation: Expression '-' error
#line 142 "src/misc/grammar.y"
                       {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 843 "src/autogen/kivi_parser.tab.cc"
    break;

  case 30: // Arithmetic_operation: Expression '-' Expression
#line 145 "src/misc/grammar.y"
                                      {
    yylhs.value.as < expression > () = new_addition_expr(std::move(yystack_[2].value.as < expression > ()), new_negation_expr(std::move(yystack_[0].value.as < expression > ())));
  }
#line 851 "src/autogen/kivi_parser.tab.cc"
    break;

  case 31: // Arithmetic_operation: Expression '*' error
#line 148 "src/misc/grammar.y"
                       {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 859 "src/autogen/kivi_parser.tab.cc"
    break;

  case 32: // Arithmetic_operation: Expression '*' Expression
#line 151 "src/misc/grammar.y"
                            {
    yylhs.value.as < expression > () = new_multiplication_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 867 "src/autogen/kivi_parser.tab.cc"
    break;

  case 33: // Arithmetic_operation: Expression '/' error
#line 158 "src/misc/grammar.y"
                       {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 875 "src/autogen/kivi_parser.tab.cc"
    break;

  case 34: // Arithmetic_operation: Expression '/' Expression
#line 161 "src/misc/grammar.y"
                                      {
    yylhs.value.as < expression > () = new_division_expr(std::move(yystack_[2].value.as < expression > ()), std::move(yystack_[0].value.as < expression > ()));
  }
#line 883 "src/autogen/kivi_parser.tab.cc"
    break;

  case 35: // Arithmetic_operation: Expression '=' error
#line 164 "src/misc/grammar.y"
                       {
    yylhs.value.as < expression > () = std::move(yystack_[2].value.as < expression > ());
  }
#line 891 "src/autogen/kivi_parser.tab.cc"
    break;

  case 36: // Arithmetic_operation: Expression '=' Expression
#line 167 "src/misc/grammar.y"
                            {
    yylhs.value.as < expression > () = expression(std::move(yystack_[2].value.as < expression > ()).move_expr(std::move(yystack_[0].value.as < expression > ())));
  }
#line 899 "src/autogen/kivi_parser.tab.cc"
    break;

  case 37: // Unary_operation: '-' Expression
#line 173 "src/misc/grammar.y"
                 {
    yylhs.value.as < expression > () = new_negation_expr(std::move(yystack_[0].value.as < expression > ()));
  }
#line 907 "src/autogen/kivi_parser.tab.cc"
    break;

  case 38: // Unary_operation: '-' error
#line 176 "src/misc/grammar.y"
            { }
#line 913 "src/autogen/kivi_parser.tab.cc"
    break;

  case 39: // Function_call_operation: Expression '(' ')'
#line 180 "src/misc/grammar.y"
                     {
    yylhs.value.as < expression > () = new_function_call_expr(std::move(yystack_[2].value.as < expression > ()));
  }
#line 921 "src/autogen/kivi_parser.tab.cc"
    break;

  case 40: // Function_call_operation: Expression '(' Comma_sep_expressions Safe_closing_parentesis
#line 183 "src/misc/grammar.y"
                                                               {
    yylhs.value.as < expression > () = new_function_call_expr(std::move(yystack_[3].value.as < expression > ()));
    yylhs.value.as < expression > ().splice_parameter_list_with(std::move(yystack_[1].value.as < expression > ()));
  }
#line 930 "src/autogen/kivi_parser.tab.cc"
    break;

  case 41: // Function_call_operation: '(' Comma_sep_expressions Safe_closing_parentesis
#line 187 "src/misc/grammar.y"
                                                   {
    yylhs.value.as < expression > () = std::move(yystack_[1].value.as < expression > ());
  }
#line 938 "src/autogen/kivi_parser.tab.cc"
    break;

  case 42: // Expressions: Var_definition
#line 193 "src/misc/grammar.y"
                 {
    yylhs.value.as < expression > () = std::move(yystack_[0].value.as < expression > ());
  }
#line 946 "src/autogen/kivi_parser.tab.cc"
    break;

  case 43: // Expressions: Expression
#line 196 "src/misc/grammar.y"
             {
    yylhs.value.as < expression > () = std::move(yystack_[0].value.as < expression > ());
  }
#line 954 "src/autogen/kivi_parser.tab.cc"
    break;

  case 44: // Expressions: Expression ',' Comma_sep_expressions
#line 199 "src/misc/grammar.y"
                                       {
    yylhs.value.as < expression > () = new_expression_sequence_expr(std::move(yystack_[2].value.as < expression > ()));
    yylhs.value.as < expression > ().splice_parameter_list_with(std::move(yystack_[0].value.as < expression > ()));
  }
#line 963 "src/autogen/kivi_parser.tab.cc"
    break;

  case 45: // Expression: STRING_LITERAL
#line 206 "src/misc/grammar.y"
                 {
    yylhs.value.as < expression > () = expression(std::move(yystack_[0].value.as < std::string > ()));
  }
#line 971 "src/autogen/kivi_parser.tab.cc"
    break;

  case 46: // Expression: NUMBER_LITERAL
#line 209 "src/misc/grammar.y"
                 {
    yylhs.value.as < expression > () = expression(yystack_[0].value.as < long > ());
  }
#line 979 "src/autogen/kivi_parser.tab.cc"
    break;

  case 47: // Expression: IDENTIFIER
#line 212 "src/misc/grammar.y"
             {
    yylhs.value.as < expression > () = ctx.use_identifier(yystack_[0].value.as < std::string > ());
  }
#line 987 "src/autogen/kivi_parser.tab.cc"
    break;

  case 48: // Expression: Arithmetic_operation
#line 215 "src/misc/grammar.y"
  { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 993 "src/autogen/kivi_parser.tab.cc"
    break;

  case 49: // Expression: Comparison_operation
#line 216 "src/misc/grammar.y"
  { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 999 "src/autogen/kivi_parser.tab.cc"
    break;

  case 50: // Expression: Unary_operation
#line 217 "src/misc/grammar.y"
  { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 1005 "src/autogen/kivi_parser.tab.cc"
    break;

  case 51: // Expression: Function_call_operation
#line 218 "src/misc/grammar.y"
  { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 1011 "src/autogen/kivi_parser.tab.cc"
    break;

  case 52: // Safe_identifier: error
#line 226 "src/misc/grammar.y"
        { }
#line 1017 "src/autogen/kivi_parser.tab.cc"
    break;

  case 53: // Safe_identifier: IDENTIFIER
#line 227 "src/misc/grammar.y"
             {
    yylhs.value.as < std::string > () = std::move(yystack_[0].value.as < std::string > ());
  }
#line 1025 "src/autogen/kivi_parser.tab.cc"
    break;

  case 54: // Safe_colon: error
#line 233 "src/misc/grammar.y"
        { }
#line 1031 "src/autogen/kivi_parser.tab.cc"
    break;

  case 56: // Safe_semicolon: error
#line 238 "src/misc/grammar.y"
        { }
#line 1037 "src/autogen/kivi_parser.tab.cc"
    break;

  case 58: // Safe_closing_brace: error
#line 243 "src/misc/grammar.y"
        { }
#line 1043 "src/autogen/kivi_parser.tab.cc"
    break;

  case 60: // Safe_closing_parentesis: error
#line 248 "src/misc/grammar.y"
        { }
#line 1049 "src/autogen/kivi_parser.tab.cc"
    break;

  case 62: // Safe_statement: error
#line 253 "src/misc/grammar.y"
        { }
#line 1055 "src/autogen/kivi_parser.tab.cc"
    break;

  case 63: // Safe_statement: Statement
#line 254 "src/misc/grammar.y"
            {
    yylhs.value.as < expression > () = std::move(yystack_[0].value.as < expression > ());
  }
#line 1063 "src/autogen/kivi_parser.tab.cc"
    break;

  case 64: // Safe_expression: error
#line 260 "src/misc/grammar.y"
        { }
#line 1069 "src/autogen/kivi_parser.tab.cc"
    break;

  case 65: // Safe_expression: Expression
#line 261 "src/misc/grammar.y"
             {
    yylhs.value.as < expression > () = std::move(yystack_[0].value.as < expression > ());
  }
#line 1077 "src/autogen/kivi_parser.tab.cc"
    break;


#line 1081 "src/autogen/kivi_parser.tab.cc"

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


  const signed char  kivi_parser ::yypact_ninf_ = -41;

  const signed char  kivi_parser ::yytable_ninf_ = -4;

  const short
   kivi_parser ::yypact_[] =
  {
     -41,     2,   -41,   -41,    60,   -41,   -41,   -41,   -41,    24,
     -41,     7,    -3,   -41,   -41,    70,     0,   -41,     0,    85,
      85,    85,   -41,   -41,   -41,    97,    85,   -41,   -41,   -41,
     -41,    14,   -41,   -41,   -41,   -41,     5,   158,   -41,   -41,
       1,   -41,   167,     7,    21,     5,   -41,    -5,    32,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   101,   113,    85,
     117,   129,   133,   145,   149,    50,    85,    70,    70,   -41,
     -41,    85,   -41,   -41,   -41,    66,   -41,    66,    27,   -41,
     167,   -41,    -5,   -41,    -5,   -41,    23,   -41,    23,   -41,
      32,   -41,   -41,   -41,   -41,   -41
  };

  const signed char
   kivi_parser ::yydefact_[] =
  {
       2,     0,     4,     1,     0,    52,    53,     5,     6,     8,
      11,     0,     9,    54,    55,     0,     0,    62,     0,     0,
       0,     0,    47,    45,    46,     0,     0,    17,    21,    63,
      42,     0,    49,    48,    50,    51,     0,    43,     7,    10,
       0,    64,    65,     0,     0,     0,    38,    37,     0,    18,
      58,    59,    22,    12,    56,    57,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
      60,     0,    61,    41,    23,    24,    25,    26,    44,    35,
      36,    27,    28,    29,    30,    31,    32,    33,    34,    39,
       0,    20,    13,    14,    19,    40
  };

  const signed char
   kivi_parser ::yypgoto_[] =
  {
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,    25,   -35,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -15,    20,    19,
      18,   -41,   -26,   -40,   -16
  };

  const signed char
   kivi_parser ::yydefgoto_[] =
  {
      -1,     1,     2,     4,     7,     9,    11,    12,    29,    48,
      30,    31,    32,    33,    34,    35,    36,    42,     8,    15,
      56,    53,    73,    38,    49
  };

  const signed char
   kivi_parser ::yytable_[] =
  {
      37,     5,     3,    43,    44,    45,    54,     6,    13,    16,
      47,    63,    64,    65,    66,    50,    37,    18,    19,    20,
      21,    22,    23,    24,    78,    55,    14,    92,    93,    25,
      90,    10,    26,    70,    27,    28,    39,    51,    40,    71,
      68,    65,    75,    77,    71,    80,    82,    84,    86,    88,
      91,    41,    37,    37,    72,    94,    52,    22,    23,    24,
      -3,     5,    67,    69,    95,    25,     0,     6,    26,     0,
       0,    17,    89,    18,    19,    20,    21,    22,    23,    24,
      61,    62,    63,    64,    65,    25,    41,     0,    26,     0,
      27,    28,    22,    23,    24,     0,     0,     0,    46,     0,
      25,     0,    74,    26,    22,    23,    24,     0,    22,    23,
      24,     0,    25,     0,    76,    26,    25,     0,    79,    26,
      22,    23,    24,     0,    22,    23,    24,     0,    25,     0,
      81,    26,    25,     0,    83,    26,    22,    23,    24,     0,
      22,    23,    24,     0,    25,     0,    85,    26,    25,     0,
      87,    26,    22,    23,    24,     0,    22,    23,    24,     0,
      25,     0,     0,    26,    25,     0,     0,    26,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    57,    58,     0,
      60,    61,    62,    63,    64,    65
  };

  const signed char
   kivi_parser ::yycheck_[] =
  {
      15,     1,     0,    19,    20,    21,     1,     7,     1,    12,
      25,    16,    17,    18,    13,     1,    31,     3,     4,     5,
       6,     7,     8,     9,    59,    20,    19,    67,    68,    15,
      65,     7,    18,     1,    20,    21,    16,    23,    18,    12,
      19,    18,    57,    58,    12,    60,    61,    62,    63,    64,
      66,     1,    67,    68,    22,    71,    31,     7,     8,     9,
       0,     1,    43,    45,    90,    15,    -1,     7,    18,    -1,
      -1,     1,    22,     3,     4,     5,     6,     7,     8,     9,
      14,    15,    16,    17,    18,    15,     1,    -1,    18,    -1,
      20,    21,     7,     8,     9,    -1,    -1,    -1,     1,    -1,
      15,    -1,     1,    18,     7,     8,     9,    -1,     7,     8,
       9,    -1,    15,    -1,     1,    18,    15,    -1,     1,    18,
       7,     8,     9,    -1,     7,     8,     9,    -1,    15,    -1,
       1,    18,    15,    -1,     1,    18,     7,     8,     9,    -1,
       7,     8,     9,    -1,    15,    -1,     1,    18,    15,    -1,
       1,    18,     7,     8,     9,    -1,     7,     8,     9,    -1,
      15,    -1,    -1,    18,    15,    -1,    -1,    18,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    10,    11,    -1,
      13,    14,    15,    16,    17,    18
  };

  const signed char
   kivi_parser ::yystos_[] =
  {
       0,    25,    26,     0,    27,     1,     7,    28,    42,    29,
       7,    30,    31,     1,    19,    43,    12,     1,     3,     4,
       5,     6,     7,     8,     9,    15,    18,    20,    21,    32,
      34,    35,    36,    37,    38,    39,    40,    41,    47,    42,
      42,     1,    41,    48,    48,    48,     1,    41,    33,    48,
       1,    23,    32,    45,     1,    20,    44,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    13,    43,    19,    44,
       1,    12,    22,    46,     1,    41,     1,    41,    33,     1,
      41,     1,    41,     1,    41,     1,    41,     1,    41,    22,
      33,    48,    47,    47,    48,    46
  };

  const signed char
   kivi_parser ::yyr1_[] =
  {
       0,    24,    26,    25,    27,    27,    29,    28,    30,    30,
      31,    31,    32,    32,    32,    32,    32,    32,    33,    33,
      34,    35,    35,    36,    36,    36,    36,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    38,    38,    39,
      39,    39,    40,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    42,    42,    43,    43,    44,    44,    45,    45,
      46,    46,    47,    47,    48,    48
  };

  const signed char
   kivi_parser ::yyr2_[] =
  {
       0,     2,     0,     2,     0,     2,     0,     5,     0,     1,
       3,     1,     2,     4,     4,     3,     2,     1,     1,     3,
       4,     1,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       4,     3,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  kivi_parser ::yytname_[] =
  {
  "END", "error", "\"invalid token\"", "\"auto\"", "\"if\"", "\"while\"",
  "\"return\"", "IDENTIFIER", "STRING_LITERAL", "NUMBER_LITERAL", "\"==\"",
  "\"<>\"", "','", "'='", "'+'", "'-'", "'*'", "'/'", "'('", "':'", "';'",
  "'{'", "')'", "'}'", "$accept", "Program", "$@1", "Functions",
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
     145,   148,   151,   158,   161,   164,   167,   173,   176,   180,
     183,   187,   193,   196,   199,   206,   209,   212,   215,   216,
     217,   218,   226,   227,   233,   234,   238,   239,   243,   244,
     248,   249,   253,   254,   260,   261
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
#line 1630 "src/autogen/kivi_parser.tab.cc"

