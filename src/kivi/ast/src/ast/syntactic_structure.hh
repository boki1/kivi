#ifndef KIVI_SRC_KIVI_SYNTACTIC_STRUCTURE_HH_
#define KIVI_SRC_KIVI_SYNTACTIC_STRUCTURE_HH_
/*
 * @file syntactic_structure.hh
 *
 * Defines an interface which all syntactic structures supported by
 * the parser implement. It does not define any methods.
 *
 * Defines an interface which all _evaluable_ syntactic structures implement.
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

	/**
	 * An interface which marks the implementor as a syntactic structure
	 * which evaluates to a value -- evaluable.
	 */
	class I_evaluable_syntactic_structure : I_syntactic_structure
	{
	 public:
		virtual ~I_evaluable_syntactic_structure() = default;
	};

	/**
	 * Since the name of the interface is waaay too long a shorter one is set ;)
	 */
	typedef I_evaluable_syntactic_structure value;

}

#endif //KIVI_SRC_KIVI_SYNTACTIC_STRUCTURE_HH_
