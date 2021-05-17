#include <utility>

#include "ir_code.hh"

namespace intermediate_representation {
    tac::tac(const tac_type tac_type) : m_type(tac_type) {}

    tac::tac(const tac_type tac_type, std::vector<fake_register_type> operands) : m_type(tac_type),
                                                                                         m_operands(std::move(operands)) {}

    tac::tac(const std::string_view ident_str, const int val, const std::vector<fake_register_type> &operands) : tac(tac_type::Init,
                                                                                                                     operands) {
        m_identifier = ident_str;
        m_value = val;
    }

    tac::tac(std::shared_ptr<tac> b, std::vector<fake_register_type> operands,
             tac::tac_type type /* = tac_type::IfNotZero */) :
            m_condition(std::move(b)), m_operands(std::move(operands)), m_type(type) {}

    tac::tac(std::vector<fake_register_type> operands) : m_operands(std::move(operands)) {}

    tac::tac(const std::string ident_name, std::vector<fake_register_type> operands) : m_identifier(), m_operands(std::move(operands)) {}


    tac::tac_type tac::type() const {
        return m_type;
    }

    std::string tac::identifier() const {
        return m_identifier;
    }

    off_t tac::value() const {
        return m_value;
    }

    std::shared_ptr<tac> &tac::next() {
        return m_next;
    }

    std::shared_ptr<tac> & tac::condition() {
        return m_condition;
    }

    const std::vector<tac::fake_register_type> &tac::operands() const {
        return m_operands;
    }
}


