/**
 * @file semantics.hh
 * @brief Defines the semantic errors which may occur during compilation
 */
#ifndef _KIVI_SEMANTIC_ERRORS_H
#define _KIVI_SEMANTIC_ERRORS_H

#include <exception>
#include <string>
#include <sstream>

using std::move;

namespace semantics
{

class undefined_function_called : std::exception
{
private:
    std::string m_fun;
    int m_params;
    int m_expected_params;

public:
    undefined_function_called(std::string fun_name, int params = 0, int expected_params = 0)
        : m_fun(move(fun_name)),
          m_params(params),
          m_expected_params(expected_params)
    {
    }

    const char *what() const noexcept
    {
        return "Undefined function called";
    }

    int params() const noexcept { return m_params; }
    int params_expected() const noexcept { return m_expected_params; }
    const std::string & fun() const noexcept { return m_fun; }
};

}

#endif // _KIVI_SEMANTIC_ERRORS_H