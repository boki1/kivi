#include "include/parsing_visualizer.hpp"
#include "include/parser.hpp"
#include <utility>
#include <vector>
#include "gvpp.hpp"
#include <iostream>
#include <fstream>

namespace process_visualization {
    std::string stringify_op(const expression &expr, const char *sep, const char *delim, bool stmt, unsigned first,
                             unsigned limit) {
        std::string result(1, delim[0]);
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

    std::string stringify(const expression &expr, bool stmt) {
        switch (expr.get_type()) {
            case expression_type::nop    :
                return "";
            case expression_type::string :
                return "\\\"" + expr.get_str_value() + "\\\"";
            case expression_type::number :
                return std::to_string(expr.get_number_val());
            case expression_type::identifier  : {
                std::string ident_type[] = {"?", "Func", "Param", "Var", "Stmt"};
                return ident_type[(int) expr.get_identifier().get_ident_type()] +
                       std::to_string(expr.get_identifier().get_index_within()) + "\\\"" +
                       expr.get_identifier().get_name() +
                       "\\\"";
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
                return "-(" + process_visualization::expect_one_param(expr) + ")";
            case expression_type::copy   :
                return "(" + stringify(expr.get_parameters().back()) + " = " +
                       stringify(expr.get_parameters().front()) + ")";
            case expression_type::function_call  :
                return "(" + (expr.get_parameters().empty() ? "?" :
                    stringify(expr.get_parameters().front())) + ")" + stringify_op(expr, ", ", "()", false, 1);
            case expression_type::compare_loop   :
                return "while " + stringify(expr.get_parameters().front()) + " " +
                       stringify_op(expr, "; ", "{}", true, 1);
            case expression_type::retrn    :
                return "return " + process_visualization::expect_one_param(expr);
        }
        return "?";
    }

    std::string stringify(const function &f) {
        return process_visualization::stringify(f.code, true);
    }

    std::string get_next_node_token(const std::string &string, unsigned &start_idx) {
        if (start_idx >= string.size()) {
            return "";
        }

        // Loop till non-space character appear
        for (unsigned i = start_idx; i < string.size(); ++i) {
            if (string[i] == ' ' || string[i] == ';') {
                continue;
            }
            start_idx = i;
            break;
        }

        unsigned end_idx;
        for (end_idx = start_idx; end_idx < string.size(); ++end_idx) {
            if (string[end_idx] == '{' || string[end_idx] == '}') {
                if (start_idx == end_idx) {
                    ++end_idx;
                }
                break;
            }
            if (string[end_idx] == ';') {
                ++end_idx;
                break;
            }
        }
        return string.substr(start_idx, end_idx - start_idx);
    }

    void visualize_parsing(const std::vector<function>& functions) {
        for (const auto &f : functions) {
            std::cout << stringify(f) << "\n";
        }

        gvpp::Graph<> g(true, "parsing_tree_graph");

        unsigned node_id = 0;

        for (const auto& f: functions) {
            gvpp::SubGraph<> &sg = g.addSubGraph(f.name, true);
//        sg.set("bgcolor", "lightyellow");

            gvpp::Node<> &function_start = sg.addNode(std::to_string(node_id), "Start: " + f.name);
            function_start.set("fillcolor", "forestgreen");
            function_start.set("fontcolor", "white");
            function_start.set("shape", "tripleoctagon");

            ++node_id;
            std::string stringified = stringify(f);
            unsigned start_idx = 0;

            std::string prev_node_str = get_next_node_token(stringified, start_idx);
            std::string current_node_str;

            gvpp::Node<> *prev = &sg.addNode(std::to_string(node_id), prev_node_str);
            start_idx += prev_node_str.size();
            ++node_id;

            g.addEdge(function_start, *prev);

            while (!(current_node_str = get_next_node_token(stringified, start_idx)).empty()) {
                gvpp::Node<> &curr = sg.addNode(std::to_string(node_id), current_node_str);
                start_idx += current_node_str.size();
                ++node_id;
                g.addEdge(*prev, curr);
                prev = &curr;
            }

            gvpp::Node<> &function_end = sg.addNode(std::to_string(node_id), "End");
            function_end.set("fillcolor", "forestgreen");
            function_end.set("fontcolor", "white");
            function_end.set("shape", "tripleoctagon");
            ++node_id;
            g.addEdge( *prev, function_end);

        }

        g.set(gvpp::AttrType::GRAPH, "ranksep", ".5");
        g.set(gvpp::AttrType::GRAPH, "bgcolor", "white");
        g.set(gvpp::AttrType::EDGE, "style", "dashed");
        g.set(gvpp::AttrType::NODE, "style", "filled");
        g.set(gvpp::AttrType::NODE, "shape", "oval");
        g.set(gvpp::AttrType::NODE, "fillcolor", "lightgreen");

        std::ofstream file("dot_file.gv", std::ios::out);
        if (!file) {
            std::cout << "error opening output file\n";
        }
        file << g;
        renderToFile(g, "dot", "gtk");
    }
}