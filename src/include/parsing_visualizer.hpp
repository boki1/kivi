#include <iostream>
#include <vector>
#include "parser.hpp"

std::string
stringify(const expression &expr, bool stmt = false);

std::string
stringify_op(const expression &expr, const char *sep, const char *delim, bool stmt = false, unsigned first = 0, unsigned limit = ~0u);

std::string expect_one_param(const expression &expr);
std::string stringify(const expression &expr, bool stmt);
std::string stringify(const function &f);

void visualize_parsing(std::vector<function> functions);
