#include "ir_code.hh"

namespace intermediate_representation {
    tac::tac(tac::tac_type type) : m_type(type) {}

    tac::tac(tac::tac_type type, std::vector<fake_register_type> &operands) : m_type(type),
                                                                              m_operands(std::move(operands)) {}

    tac::tac(std::string_view ident_str, int val, std::vector<fake_register_type> &operands) : tac(tac_type::Init,
                                                                                                   operands) {
        m_identifier = ident_str;
        m_value = val;
    }

    tac::tac(std::unique_ptr<tac> &b, std::vector<fake_register_type> &operands,
             tac::tac_type type /* = tac_type::IfNotZero */) :
            m_condition(std::move(b)), m_operands(std::move(operands)), m_type(type) {}


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

}


