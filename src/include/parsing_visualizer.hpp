#include <iostream>
#include <vector>
#include "parser.hpp"


namespace process_visualization {
    std::string
    stringify(const expression &expr, bool stmt = false);

    std::string
    stringify_operation(const expression &expr, const std::string &sep, const std::string &delim, bool stmt = false, unsigned first = 0,
                        unsigned limit = ~0u);

    std::string expect_one_param(const expression &expr);

    std::string stringify(const expression &expr, bool stmt);

    std::string stringify(const function &f);

    namespace graphStyle {
        class graphStyle {
            std::vector<std::pair<std::string, std::string>> graph_attr;
            std::vector<std::pair<std::string, std::string>> regular_node_attr;
            std::vector<std::pair<std::string, std::string>> edge_attr;
            std::vector<std::pair<std::string, std::string>> subgraph_attr;
            std::vector<std::pair<std::string, std::string>> function_start_node_attr;
            std::vector<std::pair<std::string, std::string>> function_end_node_attr;

            void set_defaults() {
                graph_attr = {{"ranksep", ".5"}, {"bgcolor", "white"}};

                regular_node_attr = {{"style", "filled"},
                                     {"shape", "oval"},
                                     {"fillcolor", "lightgreen"}};

                edge_attr = {{"style", "dashed"}};

                function_end_node_attr = function_start_node_attr =
                        {{"fillcolor", "forestgreen"},
                         {"fontcolor", "white"},
                         {"shape", "tripleoctagon"}};
            }

        public:
            graphStyle() {
                set_defaults();
            }

            void set_graph(std::vector<std::pair<std::string, std::string>> &new_attr) { graph_attr = new_attr; }
            void set_node(std::vector<std::pair<std::string, std::string>> &new_attr) { regular_node_attr = new_attr; }
            void set_edge(std::vector<std::pair<std::string, std::string>> &new_attr) { edge_attr = new_attr; }
            void set_subgraph(std::vector<std::pair<std::string, std::string>> &new_attr) { subgraph_attr = new_attr; }
            void set_start_node(std::vector<std::pair<std::string, std::string>> &new_attr) { function_start_node_attr = new_attr; }
            void set_end_node(std::vector<std::pair<std::string, std::string>> &new_attr) { function_end_node_attr = new_attr; }

            [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &getGraphAttr() const { return graph_attr; }
            [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &getRegularNodeAttr() const { return regular_node_attr; }
            [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &getEdgeAttr() const { return edge_attr; }
            [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &getSubgraphAttr() const { return subgraph_attr; }
            [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &getFunctionStartNodeAttr() const { return function_start_node_attr; }
            [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &getFunctionEndNodeAttr() const { return function_end_node_attr; }
        };
    }
    void visualize_parsing(const std::vector<function> &functions);
}