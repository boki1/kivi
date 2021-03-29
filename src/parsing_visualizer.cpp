#include "include/parsing_visualizer.hpp"
#include "include/parser.hpp"
#include <vector>
#include "gvpp.hpp"
#include <iostream>
#include <fstream>

std::string stringify_op(const expression& expr, const char* sep, const char* delim, bool stmt, unsigned first, unsigned limit) {
//    std::string result("\n");
    std::string result(1, delim[0]);
//    result += "\n";
    const char *first_sep = "";
    for (const auto &p: expr.get_parameters()) {
        if (first) {
            --first;
            continue;
        }
        if (!limit--) break;
        result += first_sep;
        first_sep = sep;
        result += stringify(p, stmt);
    }
    if (stmt) result += sep;
    result += delim[1];
    return result;
}

std::string expect_one_param(const expression &expr) {
    if (expr.get_parameters().empty()) return "?";
    else if (expr.get_parameters().size() == 1) {
        return stringify(expr.get_parameters().front());
    } else return stringify_op(expr, "??", "()");
}

std::string stringify(const expression& expr, bool stmt) {
    switch (expr.get_type()) {
        case expression_type::nop    :
            return "";
        case expression_type::string :
            return "\"" + expr.get_str_value() + "\"";
        case expression_type::number :
            return std::to_string(expr.get_number_val());
        case expression_type::identifier  : {
            const char *ident_type[] = {"?", "Func", "Param", "Var", "Stmt"};
            return ident_type[(int) expr.get_identifier().get_ident_type()] +
                   std::to_string(expr.get_identifier().get_index_within()) + "\"" + expr.get_identifier().get_name() +
                   "\"";
        }
        case expression_type::addition    :
            return stringify_op(expr, " + ", "()");
        case expression_type::multiplication:
            return stringify_op(expr, " * ", "()");
        case expression_type::division:
            return stringify_op(expr, " / ", "()");
        case expression_type::equality     :
            return stringify_op(expr, " == ", "()");
        case expression_type::compare_and   :
            return stringify_op(expr, " && ", "()");
        case expression_type::expression_sequence  :
            return stmt ? stringify_op(expr, "; ", "{}", true) : stringify_op(expr, ", ", "()");
        case expression_type::negation    :
            return "-(" + expect_one_param(expr) + ")";
        case expression_type::copy   :
            return "(" + stringify(expr.get_parameters().back()) + " = " + stringify(expr.get_parameters().front()) + ")";
        case expression_type::function_call  :
            return "(" + (expr.get_parameters().empty() ? "?" : stringify(expr.get_parameters().front())) + ")" +
                   stringify_op(expr, ", ", "()", false, 1);
        case expression_type::compare_loop   :
            return "while " + stringify(expr.get_parameters().front()) + " " + stringify_op(expr, "; ", "{}", true, 1);
        case expression_type::retrn    :
            return "return " + expect_one_param(expr);
    }
    return "?";
}

std::string stringify(const function &f) {
    return stringify(f.code, true);
}

void visualize_parsing(std::vector<function> functions) {
}
