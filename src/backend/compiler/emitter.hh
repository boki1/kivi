#ifndef KIVI_EMITTER_HH
#define KIVI_EMITTER_HH

#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include "machine_target.hh"

using mt = compiler::machine_target;
using std::move;

namespace compiler
{

	class emitter
	{
	public:
		struct basic_block; //< Forward declaration

	private:
		/// Resulting output file which contains the assembly of the program
		std::string m_output_file;

		/// Result assembly
		std::stringstream m_sstr{};

		/// Concrete machine architecture
		machine_target m_strategy;

		/// Program
		std::vector<instruction> m_program{};

		/// Additional info for debugging during development
		struct meta
		{
			std::unordered_map<ir::tac::vregister_type, std::string_view> functions;
			std::vector<instruction> after_instruction_selection;
			std::vector<basic_block> last_formed_blocks;
		} debug_meta;

		/// Input program in IR form
		const std::vector<ir::tac>& m_three_address_code;

	public:
		explicit emitter(machine_target&& target, const std::vector<ir::tac>& t_tacs, std::string output_file = "a.asm")
			: m_strategy{ move(target) }, m_output_file{ std::move(output_file) }, m_three_address_code{ t_tacs },
			  debug_meta{}
		{
		}

	public:

		/**
		 * @brief Performs the whole compilation phase unless one of the stages fails
		 * @return bool -- True on success and false on error; Fetch the output by calling `fetch_result`
		 */
		bool compile()
		{
			return (select_instructions() && allocate_registers() && prepare_runtime());
		}

		const std::stringstream& fetch_result()
		{
			return m_sstr;
		}

		std::unique_ptr<std::ofstream> commit_and_fetch_result()
		{
			auto fstr = std::make_unique<std::ofstream>(m_output_file);
			if (fstr) *fstr << m_sstr.rdbuf();
			return fstr;
		}

		struct basic_block
		{
			using stmt_ptr = std::vector<instruction>::const_iterator;

			/// The beginning of the basic block
			stmt_ptr begin;

			/// The end of the basic block non-including the pointer to element
			stmt_ptr end;

			///
			int begin_line;
			int end_line;

			static inline int id_counter = 0;

			/// Id of this basic block
			int id = id_counter++;

			basic_block(const stmt_ptr& t_begin, const stmt_ptr& t_end, int t_begin_line, int t_end_line)
				: begin{ t_begin }, end{ t_end }, begin_line{ t_begin_line }, end_line{ t_end_line }
			{
			}
		};

		/**
		 * @brief Find leaders of IR program
		 * @return Collection with all leaders in the program
		 */
		std::queue<basic_block::stmt_ptr> find_leaders();

		/**
		 * @brief Split program into basic blocks
		 * @return Collection of the basic blocks forming the program
		 */
		std::vector<basic_block> form_basic_blocks();

		/**
		 * @brief Performs instruction selection algorithm on the given program
		 * @note Ran _first_
		 * @return true Successfull execution
		 * @return false Failed
		 */
		bool select_instructions()
		{
			m_strategy.selector_mut().select_for(m_three_address_code);
			const auto[program, functions] = m_strategy.selector().fetch_selected_output();

			debug_meta.after_instruction_selection = program;
			debug_meta.functions = functions;
			m_program = program;

			return true;
		}

		/**
		 * @brief Performs register allocation algorithm on the given program
		 * @note Ran _after_ `select_instructions()`
		 * @return true
		 * @return false
		 */
		bool allocate_registers()
		{
			return false;
		}

		/// TODO:
		bool prepare_runtime()
		{
			return false;
		}

	public:
		const std::string& output_file() const
		{
			return m_output_file;
		}
		const std::stringstream& sstr() const
		{
			return m_sstr;
		}
		const machine_target& strategy() const
		{
			return m_strategy;
		}
		const std::vector<instruction>& program() const
		{
			return m_program;
		}
		const std::vector<ir::tac>& three_address_code() const
		{
			return m_three_address_code;
		}
		const auto& debug() const
		{
			return debug_meta;
		}
	};

} // namespace compiler

#endif // KIVI_EMITTER_HH
