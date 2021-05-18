#ifndef KIVI_IR_PRINTER_HH
#define KIVI_IR_PRINTER_HH

#include <ir_generation/ir_code.hh>
#include <iostream>
#include <ir_generation/generation_unit.hh>

namespace printer {
        void print_ir(std::shared_ptr<intermediate_representation::tac> &code, std::ostream &os);
        void print_ir(intermediate_representation::generation_unit &gunit, std::ostream &os);
};

#endif //KIVI_IR_PRINTER_HH
