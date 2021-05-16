#include <variant>
#include <vector>
#include "ir_code.hh"

#include <parser/parser.tab.hh>

namespace intermediate_representation {
    tac::type tac::tac_type() const {
        return m_type;
    }

    const tac::atom_type &tac::atom() const {
        return m_atom;
    }

    const std::shared_ptr<tac> &tac::next() const {
        return m_next;
    }

    const std::optional<std::shared_ptr<tac>> &tac::condition() const {
        return m_condition;
    }

    const std::vector <tac::fake_register_type> &tac::operands() const {
        return m_operands;
    }
};


