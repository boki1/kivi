#ifndef KIVI_IR_PRINTER_HH
#define KIVI_IR_PRINTER_HH

#include <ir_generation/ir_code.hh>
#include <iostream>

namespace printer {
    void print_ir(intermediate_representation::tac &code, std::ostream &os);

};

#endif //KIVI_IR_PRINTER_HH
