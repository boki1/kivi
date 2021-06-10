#ifndef KIVI_SRC_UTILS_ASM_PRINTER_ASM_PRINTER_HH_
#define KIVI_SRC_UTILS_ASM_PRINTER_ASM_PRINTER_HH_

#include <compiler/emitter.hh>

namespace printer
{

	/**
	 * @brief Prints the generated pseudo-assembly code after the instruction selection phase
	 * @param os The output stream
	 * @param emitter The concrete emitter where the program is stored
	 */
	void print_instruction_selection(std::ostream& os, const compiler::emitter& emitter);

	void print_basic_block(std::ostream& os, const compiler::emitter& emitter);
}

#endif //KIVI_SRC_UTILS_ASM_PRINTER_ASM_PRINTER_HH_
