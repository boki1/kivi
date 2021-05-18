/**
 * @file generation_context.hh
 * @brief Defines the class which keeps track of the contextual data used during IR generation
 */
#ifndef KIVI_GENERATION_CONTEXT_HH
#define KIVI_GENERATION_CONTEXT_HH

#include <map>

#include "ir_code.hh"
#include "generation_unit.hh"

namespace intermediate_representation
{
	/**
	 * @brief This class keeps track of all additional information used during the process of IR generation
	 */
	class generation_unit::generation_context
	{
	 public:
		typedef std::map<std::size_t, tac::vregister_type> variable_index_type;
	 private:
		/// The number of the next register
		tac::vregister_type m_counter;

		/// The previous virtual register
		tac::vregister_type m_vreg{ -1 };

		/// Pointer to the next instruction address
		tac** m_target;

		/// Relation between AST variables and their register indexes
		variable_index_type m_map;

	 public:

		/// Complete manual construction
		generation_context(tac::vregister_type c, tac** target, const variable_index_type& index = {})
			: m_counter{ c },
			  m_target{ target },
			  m_map{ index }
		{
		}

	 public:
		/* discarding is fine */ tac::vregister_type
		store_vreg(tac::vregister_type vreg)
		{
			return m_vreg = vreg;
		}

		[[nodiscard]] tac::vregister_type
		load_vreg() noexcept
		{
			return m_vreg;
		}

		[[nodiscard]] tac::vregister_type
		counter() const noexcept
		{
			return m_counter;
		}

		[[nodiscard]] tac**
		target() const noexcept
		{
			return m_target;
		}

		[[nodiscard]] const variable_index_type&
		map() const noexcept
		{
			return m_map;
		}

		[[nodiscard]] /* mut */ variable_index_type&
		map_mut() noexcept
		{
			return m_map;
		}

		[[nodiscard]] tac::vregister_type
		increase_counter() noexcept
		{
			return m_counter++;
		}
	};

}

#endif //KIVI_GENERATION_CONTEXT_HH
