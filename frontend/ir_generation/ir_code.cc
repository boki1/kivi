#include "ir_code.hh"

#include <parser/parser.tab.hh>

namespace intermediate_representation {
    tac::tac(tac::tac_type &type, std::vector<fake_register_type> &operands) : m_type(type),
                                                                               m_operands(std::move(operands)) {}

    tac::tac(tac::tac_type &type, std::string_view str /*  = nullptr */, int i /*  = 0 */) : m_type(type){

    }

    tac::tac(std::shared_ptr<tac> b, std::vector<fake_register_type> &operands,
             tac::tac_type type /* = tac_type::IfNotZero */) :
            m_condition(b), m_operands(std::move(operands)), m_type(type) {}


    tac::tac(std::vector<fake_register_type> &operands) : m_operands(std::move(operands)) {}

    tac::tac_type tac::type() const {
        return m_type;
    }

    std::string tac::identifier() const {
        return m_identifier;
    }

    off_t tac::value() const {
        return m_value;
    }

    const std::shared_ptr<tac> &tac::next() const {
        return m_next;
    }

    const std::optional<std::shared_ptr<tac>> &tac::condition() const {
        return m_condition;
    }

    const std::vector<tac::fake_register_type> &tac::operands() const {
        return m_operands;
    }


};


