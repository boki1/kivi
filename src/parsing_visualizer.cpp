#include "include/parsing_visualizer.hpp"
#include "../depen/gvpp/src/gvpp.hpp"
#include "include/parser.hpp"
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

namespace process_visualization
{
std::string
stringify_operation (const expression &expr, const std::string &sep,
		     const std::string &delim, bool stmt, unsigned first,
		     unsigned limit)
{
    // TODO: throw exception
    if (delim.size () < 2)
	return "";
    std::string result (1, delim[0]);
    std::string first_sep;
    for (const auto &p : expr.get_parameters ())
	{
	    if (first)
		{
		    --first;
		    continue;
		}
	    if (!limit--)
		break;
	    result += first_sep;
	    first_sep = sep;
	    result += stringify (p, stmt);
	}
    if (stmt)
	result += sep;
    result += delim[1];
    return result;
}

std::string
expect_one_param (const expression &expr)
{
    if (expr.get_parameters ().empty ())
	return "?";
    else if (expr.get_parameters ().size () == 1)
	{
	    return stringify (expr.get_parameters ().front ());
	}
    else
	return stringify_operation (expr, "??", "()");
}

std::string
stringify (const expression &expr, bool stmt)
{
    auto expr_params = expr.get_parameters ();
    switch (expr.get_type ())
	{
	case expression_type::nop:
	    return "";
	case expression_type::string:
	    return "\\\"" + expr.get_str_value () + "\\\"";
	case expression_type::number:
	    return std::to_string (expr.get_number_val ());
	case expression_type::identifier:
	    {
		std::string ident_type[]
		    = { "?", "Func", "Param", "Var", "Stmt" };
		return ident_type[(int)expr.get_identifier ()
				      .get_ident_type ()]
		       + std::to_string (
			   expr.get_identifier ().get_index_within ())
		       + "\\\"" + expr.get_identifier ().get_name () + "\\\"";
	    }
	case expression_type::addition:
	    return stringify_operation (expr, " + ", "()");
	case expression_type::multiplication:
	    return stringify_operation (expr, " * ", "()");
	case expression_type::division:
	    return stringify_operation (expr, " / ", "()");
	case expression_type::equality:
	    return stringify_operation (expr, " == ", "()");
	case expression_type::compare_and:
	    return stringify_operation (expr, " && ", "()");
	case expression_type::expression_sequence:
	    return stmt ? stringify_operation (expr, "; ", "{}", true)
			: stringify_operation (expr, ", ", "()");
	case expression_type::negation:
	    return "-(" + process_visualization::expect_one_param (expr) + ")";
	case expression_type::copy:
	    return "(" + stringify (expr_params.back ()) + " = "
		   + stringify (expr_params.front ()) + ")";
	case expression_type::function_call:
	    return "("
		   + (expr_params.empty () ? "?"
					   : stringify (expr_params.front ()))
		   + ")" + stringify_operation (expr, ", ", "()", false, 1);
	case expression_type::compare_loop:
	    return "while " + stringify (expr_params.front ()) + " "
		   + stringify_operation (expr, "; ", "{}", true, 1);
	case expression_type::retrn:
	    return "return " + process_visualization::expect_one_param (expr);
	}
    return "?";
}

std::string
stringify (const function &f)
{
    return process_visualization::stringify (f.code, true);
}

std::string
get_next_node_token (const std::string &string, unsigned &start_idx)
{
    if (start_idx >= string.size ())
	{
	    return "";
	}

    // Loop till non-space character appear
    for (unsigned i = start_idx; i < string.size (); ++i)
	{
	    if (string[i] == ' ' || string[i] == ';')
		{
		    continue;
		}
	    start_idx = i;
	    break;
	}

    unsigned end_idx;
    for (end_idx = start_idx; end_idx < string.size (); ++end_idx)
	{
	    if (string[end_idx] == '{' || string[end_idx] == '}')
		{
		    if (start_idx == end_idx)
			{
			    ++end_idx;
			}
		    break;
		}
	    if (string[end_idx] == ';')
		{
		    ++end_idx;
		    break;
		}
	}
    return string.substr (start_idx, end_idx - start_idx);
}

void
visualize_parsing (const std::vector<function> &functions)
{
    graphStyle::graphStyle style;
    for (const auto &f : functions)
	{
	    std::cout << stringify (f) << "\n";
	}

    gvpp::Graph<> g (true, "parsing_tree_graph");

    unsigned node_id = 0;

    for (const auto &f : functions)
	{
	    gvpp::SubGraph<> &sg = g.addSubGraph (f.name, true);

	    gvpp::Node<> &function_start
		= sg.addNode (std::to_string (node_id), "Start: " + f.name);

	    for (const std::pair<std::string, std::string> &
		     start_node_style_attr : style.getFunctionStartNodeAttr ())
		{
		    function_start.set (start_node_style_attr.first,
					start_node_style_attr.second);
		}

	    ++node_id;
	    std::string stringified = stringify (f);
	    unsigned start_idx = 0;

	    std::string prev_node_str
		= get_next_node_token (stringified, start_idx);
	    std::string current_node_str;

	    gvpp::Node<> *prev
		= &sg.addNode (std::to_string (node_id), prev_node_str);
	    start_idx += prev_node_str.size ();
	    ++node_id;

	    g.addEdge (function_start, *prev);

	    while (!(current_node_str
		     = get_next_node_token (stringified, start_idx))
			.empty ())
		{
		    gvpp::Node<> &curr = sg.addNode (std::to_string (node_id),
						     current_node_str);
		    start_idx += current_node_str.size ();
		    ++node_id;
		    g.addEdge (*prev, curr);
		    prev = &curr;
		}

	    gvpp::Node<> &function_end
		= sg.addNode (std::to_string (node_id), "End");

	    for (const std::pair<std::string, std::string>
		     &end_node_style_attr : style.getFunctionEndNodeAttr ())
		{
		    function_end.set (end_node_style_attr.first,
				      end_node_style_attr.second);
		}
	    ++node_id;
	    g.addEdge (*prev, function_end);
	}

    for (const std::pair<std::string, std::string> &graph_style_attr :
	 style.getGraphAttr ())
	{
	    g.set (gvpp::AttrType::GRAPH, graph_style_attr.first,
		   graph_style_attr.second);
	}

    for (const std::pair<std::string, std::string> &edge_style_attr :
	 style.getEdgeAttr ())
	{
	    g.set (gvpp::AttrType::EDGE, edge_style_attr.first,
		   edge_style_attr.second);
	}

    for (const std::pair<std::string, std::string> &node_style_attr :
	 style.getRegularNodeAttr ())
	{
	    g.set (gvpp::AttrType::NODE, node_style_attr.first,
		   node_style_attr.second);
	}

    std::ofstream file ("dot_file.gv", std::ios::out);
    if (!file)
	{
	    std::cout << "error opening output file\n";
	}
    file << g;
    renderToFile (g, "dot", "gtk");
}
}
