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

		[[nodiscard]] virtual std::string to_string() const noexcept
		{
			return "<unknown>";
		}
	};

	/**
	 * An interface which marks the implementor as a syntactic structure
	 * which evaluates to a value -- evaluable.
	 */
	class I_evaluable_syntactic_structure : public I_syntactic_structure
	{
	 public:
		virtual ~I_evaluable_syntactic_structure() = default;

		explicit operator int() const noexcept;
	 public:

		int operator-(const I_evaluable_syntactic_structure& rhs) const noexcept;

		bool operator==(const I_evaluable_syntactic_structure& rhs) const noexcept;

		bool operator==(int rhs) const noexcept;
	};

}

#endif //KIVI_SRC_KIVI_SYNTACTIC_STRUCTURE_HH_
