#include "ir_printer.hh"
#include <ir_generation/ir_code.hh>
#include <iostream>


namespace ir = intermediate_representation;

namespace printer {
    void print_ir(ir::tac &tac_code, std::ostream &os) {
        switch (tac_code.type()) {
            case ir::tac::tac_type::Nop:
                os << "\t" << "nop" << "\t";
                break;
            case ir::tac::tac_type::Init:
                os << "\t" << "init" << "\t";
                break;
            case ir::tac::tac_type::Add:
                os << "\t" << "add" << "\t";
                break;
            case ir::tac::tac_type::Negate:
                os << "\t" << "neg" << "\t";
                break;
            case ir::tac::tac_type::Copy:
                os << "\t" << "copy" << "\t";
                break;
            case ir::tac::tac_type::Read:
                os << "\t" << "read" << "\t";
                break;
            case ir::tac::tac_type::Write:
                os << "\t" << "write" << "\t";
                break;
            case ir::tac::tac_type::Equals:
                os << "\t" << "eq" << "\t";
                break;
            case ir::tac::tac_type::IfNotZero:
                os << "\t" << "ifnz" << "\t";
                break;
            case ir::tac::tac_type::FunctionCall:
                os << "\t" << "fcall" << "\t";
                break;
            case ir::tac::tac_type::Return:
                os << "\t" << "rtrn" << "\t";
                break;
        }
        for (auto u: tac_code.operands()) {
            os << " R" << u;
        }
        if (tac_code.type() == ir::tac::tac_type::Init) {
            os << "\"" << tac_code.identifier() << "\"" << tac_code.value();
        }
    }
}