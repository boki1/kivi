#ifndef KIVI_LEXER_H
#define KIVI_LEXER_H

#include "../autogen/location.hh"
#include "../autogen/stack.hh"

#include <list>
#include <map>
#include <utility>
#include <vector>

enum class identifier_type
{
    UNDEFINED,
    FUNCTION,
    PARAMETER,
    LOCAL
};

class identifier
{
  public:
    identifier () = default;
    identifier (identifier_type type, std::size_t index_within,
		std::string name)
	: m_type (type), m_index_within (index_within), m_name (std::move(name))
    {
    }

  public:
    [[nodiscard]] const std::string &
    get_name () const
    {
	return m_name;
    }
    [[nodiscard]] std::size_t
    get_index_within () const
    {
	return m_index_within;
    }
    [[nodiscard]] identifier_type
    get_ident_type () const
    {
	return m_type;
    }

  private:
    identifier_type m_type = identifier_type::UNDEFINED;
    std::size_t m_index_within = 0;
    std::string m_name;
};
#define EXPRESSION_TYPES(o)                                                   \
    o (nop) o (string) o (number) o (identifier) o (addition) o (negation)    \
	o (equality) o (multiplication) o (division) o (compare_and)          \
	    o (compare_loop) o (function_call) o (copy)                       \
		o (expression_sequence) o (retrn)

#define o(n) n,
enum class expression_type
{
    EXPRESSION_TYPES (o)
};
#undef o

class expression
{
  public:
    template <typename... T>
    expression (expression_type t, T &&...args)
	: m_type (t), m_parameters{ std::forward<T> (args)... }
    {
    }

    expression () : m_type (expression_type::nop) {}

    expression (identifier i)
	: m_type (expression_type::identifier), m_identifier (std::move(i))
    {
    }

    expression (identifier &&i)
	: m_type (expression_type::identifier), m_identifier (std::move (i))
    {
    }

    explicit expression (std::string &&s)
	: m_type (expression_type::string), m_str_value (std::move (s))
    {
    }

    explicit expression (long v)
	: m_type (expression_type::number), m_number_val (v)
    {
    }

    expression_type get_type() const;

    const identifier &get_identifier() const;

    const std::string &get_str_value() const;

    long get_number_val() const;

    const std::list<expression> &get_parameters() const;

public:
    // Takes an rvalue `this` argument
    expression
    move_expr (expression &&b) &&
    {
	//                                ---^
	return expression (expression_type::copy, std::move (b),
			   std::move (*this));
    }

    void
    add_parameter (expression &&param)
    {
	m_parameters.push_back (param);
    }
    void splice_parameter_list_with (expression &&other);

  private:
    expression_type m_type;
    identifier m_identifier{};
    std::string m_str_value{};
    long m_number_val = 0;
    std::list<expression> m_parameters;
};

struct function
{
    std::string name;
    expression code;
    unsigned num_locals = 0;
    unsigned num_parameters = 0;
};

#define o(n)                                                                  \
    template <typename... T> inline expression new_##n##_expr (T &&...args)   \
    {                                                                         \
	return expression (expression_type::n, std::forward<T> (args)...);    \
    }
EXPRESSION_TYPES (o)
#undef o

class parsing_context
{
  private:
    std::vector<std::map<std::string, identifier> > m_scope_list;
    std::vector<function> m_function_list;

    // The number of the pseudo register in the following code generation step
    unsigned m_register_counter = 0;
    function m_current_function;

  public:
    const char *lexer_cursor;
    yy::location location;

  public:
    parsing_context (const char *code, const std::string *filename)
	: lexer_cursor (code)
    {
    // TODO: change filename constness
	location.begin.filename = location.end.filename = const_cast<std::string *>(filename);
//	location.begin.filename = location.end.filename = filename;
    }

  public:
    [[nodiscard]] const std::vector<function> &
    get_function_list () const
    {
	return m_function_list;
    }

  public:
    const identifier &define_identifier (const std::string &name,
					 identifier &&f);

    expression define_local (const std::string &name);

    expression define_function (const std::string &name);

    expression define_parameter (const std::string &name);

    expression new_register_variable ();

    [[nodiscard]] expression use_identifier (const std::string &name) const;

    void add_function_with_block (std::string &&name, expression &&code);

    void enter_scope ();

    void exit_scope ();
};


#endif
