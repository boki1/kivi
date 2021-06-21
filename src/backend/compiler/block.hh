#ifndef __KIVI_BLOCK_HH_
#define __KIVI_BLOCK_HH_

#include "emitter.hh"

namespace compiler
{
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

			basic_block() = default;
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


}

#endif // __KIVI_BLOCK_HH_
