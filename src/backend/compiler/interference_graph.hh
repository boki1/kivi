#ifndef KIVI_INTERFERENCE_GRAPH_HH
#define KIVI_INTERFERENCE_GRAPH_HH

#include <unordered_map>
#include <vector>

#include "liveness_analyzer.hh"
#include "common.hh"

namespace compiler
{
	class interference_graph
	{
	 public:
		using colour_type = unsigned long int;
	 private:
		const std::vector<rregister>& registers;
		liveness_analyzer m_liveness_analyzer;
		std::vector<colour_type> m_colours;
	 public:
		void add_element();
		void build();
		std::unordered_map<rregister, colour_type> paint();
	};
}

#endif //KIVI_INTERFERENCE_GRAPH_HH
