#ifndef KIVI_SRC_KIVI_SYNTACTIC_STRUCTURE_HH_
#define KIVI_SRC_KIVI_SYNTACTIC_STRUCTURE_HH_
/*
 * @file syntactic_structure.hh
 *
 * Defines an interface which all syntactic structures supported by
 * the parser implement. It does not define any methods.
 */

namespace syntax_analyzer
{

	/**
	 * An interface which all syntactic structures implement.
	 */
	class I_syntactic_structure
	{
	 public:
		virtual ~I_syntactic_structure() = default;
	};

}

#endif //KIVI_SRC_KIVI_SYNTACTIC_STRUCTURE_HH_
