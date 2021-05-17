#include "ir_printer.hh"
#include <ir_generation/ir_code.hh>
#include <iostream>
#include <list>

namespace ir = intermediate_representation;

namespace printer {
    void print_ir(std::shared_ptr<ir::tac> &tac_code, std::ostream &os) {
        switch (tac_code->type()) {
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
        for (auto u: tac_code->operands()) {
            os << " R" << u;
        }
        if (tac_code->type() == ir::tac::tac_type::Init) {
            os << "\"" << tac_code->identifier() << "\"" << tac_code->value();
        }
    }

    void print_ir(intermediate_representation::generation_unit &code, std::ostream &os) {
        struct data {
            std::vector<std::string> labels{};
            bool done{};
            std::size_t referred{};
        };

        std::map<std::shared_ptr<ir::tac>, data> statistics;
        std::list<ir::tac> remaining_statements;

        auto add_label = [l = 0lu](data &d) mutable { d.labels.push_back('L' + std::to_string(l++)); };

        for (const auto &entry_point : code.entry_points()) {
            remaining_statements.push_back(*entry_point.second);
            statistics[entry_point.second].labels.push_back(entry_point.first);
        }

        for (const auto &tac: code.all_tacs()) {
            if (tac->next()) {
                auto &t = statistics[tac->next()];

                if (t.labels.empty() && t.referred++) {
                    add_label(t);
                }

            }
            if (tac->condition()) {
                auto &t = statistics[*(tac->condition())];

                if (t.labels.empty()) {
                    add_label(t);
                }
            }
        }

        while (!remaining_statements.empty()) {
            std::shared_ptr<ir::tac> chain = remaining_statements.front();
            remaining_statements.pop_front();
            for (bool needs_jmp = false; chain != nullptr; chain = chain->next(), needs_jmp = true) {
                auto &stats = statistics[chain];
                if (!stats.done) {
                    if (needs_jmp) {
                        os << "\tJMP " << stats.labels.front() << '\n';
                    }
                    stats.done = true;
                    break;
                }

                for (const auto &l: stats.labels) os << l << ":\n";
                print_ir(chain, os);
                if (chain->condition()) {
                    auto &branch_stats = statistics[*chain->condition()];
                    os << ", JMP " << branch_stats.labels.front();
                    if (!branch_stats.done) { remaining_statements.push_front(**chain->condition()); }
                }
                os << '\n';
            }

        }
    }
}