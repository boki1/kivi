#ifndef KIVI_PARSER_H
#define KIVI_PARSER_H

#include <string>

enum class identifier_type {
  UNDEFINED,
  FUNCTION,
  PARAMETER,
  LOCAL
};

class identifier {
public:
  identifier() = default;
  identifier(identifier_type type, std::size_t index_within,
             const std::string &name)
      : m_type(type), m_index_within(index_within), m_name(name) {}

public:
  const std::string &get_name() const { return m_name; }
  std::size_t get_index_within() const { return m_index_within; }
  identifier_type get_ident_type() const { return m_type; }

private:
  identifier_type m_type = identifier_type::UNDEFINED;
  std::size_t m_index_within = 0;
  std::string m_name;
};

#endif // KIVI_PARSER_H

