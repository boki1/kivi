/**
 * @file generation_unit.hh
 * @brief Defines an class which represents an IR generation unit
 */
#ifndef KIVI_CONCRETE_CODES_HH
#define KIVI_CONCRETE_CODES_HH

#include <vector>
#include <memory>
#include <map>
#include "ir_code.hh"
#include <parser/syntax.hh>

using std::unique_ptr;

namespace intermediate_representation
{
	/**
	 * @brief Unit which is responsible for translating a given AST into a sequence of TAC's (Three-Address Code)
	 */
	class generation_unit
	{
	 public:
		typedef std::map<std::string, tac*> label_entries_type;            //< Used for mapping labels (functions) and their associated _first_ TAC
		typedef std::map<std::string, std::size_t> parameter_count_type;    //< Used for mapping the number of parameters to their function

	 private:
		/// All three address codes used in a unit to be generated
		std::vector<unique_ptr<tac>> m_tacs{};

		/// Number of parameters in each function
		parameter_count_type m_function_parameters{};

		/// The entry point address of each function
		label_entries_type m_entry_points{};

	 public:
		/**
		 * @brief This class keeps track of all additional information used during the process of IR generation
		 * @note Full definition in generation_context.hh
		 */
		class generation_context;

	 public:

		/// Default construction only required

	 public:

		/// Instantiates a context for the given function and returns it
		generation_unit::generation_context
		prepare_context(const syntax_analyzer::function& function);

	 public: // Concrete generators (concrete_generators.cc)

		void generate_sequence(const syntax_analyzer::expression& e, generation_context& gtx);
//		void generate_addition(const syntax_analyzer::expression& e, generation_context& gtx);
//		void generate_multiplication(const syntax_analyzer::expression& e, generation_context& gtx);
//		void generate_division(const syntax_analyzer::expression& e, generation_context& gtx);
//		void generate_modulo(const syntax_analyzer::expression& e, generation_context& gtx);
//		void generate_equality(const syntax_analyzer::expression& e, generation_context& gtx);

		void generate_copy(const syntax_analyzer::expression& e, generation_context& gtx);
		void generate_funcall(const syntax_analyzer::expression& expr, generation_context& gtx);
		void generate_number(const syntax_analyzer::expression& e, generation_context& gtx);
		void generate_return(const syntax_analyzer::expression& expr, generation_context& gtx);
		void generate_nop(const syntax_analyzer::expression& e, generation_context& gtx);
		void generate_negation(const syntax_analyzer::expression& expr, generation_context& gtx);
		void generate_identifier(const syntax_analyzer::expression& e, generation_context& gtx);

		void generate_conditional(const syntax_analyzer::expression& expr, generation_context& gtx);
//		void generate_if(const syntax_analyzer::expression& e, generation_context& gtx);
//		void generate_while(const syntax_analyzer::expression& e, generation_context& gtx);

	 public: // TAC concrete constructors (codes.cc)
		[[nodiscard]] tac* tac_nop();
		[[nodiscard]] tac* tac_init(tac::vregister_type value, const std::string& ident, unsigned operand);
		[[nodiscard]] tac* tac_add(const tac::operands_type& operands);
		[[nodiscard]] tac* tac_neg(const tac::operands_type& operands);
		[[nodiscard]] tac* tac_copy(const tac::operands_type& operands);
		[[nodiscard]] tac* tac_read(const tac::operands_type& operands);
		[[nodiscard]] tac* tac_write(const tac::operands_type& operands);
		[[nodiscard]] tac* tac_eq(const tac::operands_type& operands);
		[[nodiscard]] tac* tac_ifnz(const tac::operands_type& operands);
		[[nodiscard]] tac* tac_fcall(const tac::operands_type& operands);
		[[nodiscard]] tac* tac_return(const tac::operands_type& operands);

		/*
		 * The definitions of the three address code instructions and their operands
		 */
		tac*
		define_tac(const tac& code);

		tac::vregister_type
		generate_ir(const syntax_analyzer::expression& code, generation_context& ctx);

		void
		generate_function(const syntax_analyzer::function& function);

		void
		generate(const std::vector<syntax_analyzer::function>& ctx_functions);

	 public: // Getters
		[[nodiscard]] const std::vector<unique_ptr<tac>>&
		tacs()
		{
			return m_tacs;
		}

		[[nodiscard]] /* mut */ parameter_count_type&
		function_parameters_mut()
		{
			return m_function_parameters;
		}

		[[nodiscard]] /* mut */ label_entries_type&
		entry_points_mut()
		{
			return m_entry_points;
		}

		[[nodiscard]] const label_entries_type&
		entry_points()
		{
			return m_entry_points;
		}
	};
}
#endif //KIVI_CONCRETE_CODES_HH
