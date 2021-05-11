/**
 * @file util/common.hh
 * @brief Procvides definitions to useful commonly encounter utility macros, functions and structures which are not
 * directly related the project
 */
#ifndef KIVI_SRC_KIVI_UTIL_COMMON_HH_
#define KIVI_SRC_KIVI_UTIL_COMMON_HH_

#include <iostream>

/**
 * @brief Notify if a function marked as unimplemented is invoked and output helpful message
 * @note If unimplemented function is actually invoked the program outputs to `std::cerr`
 * @return void
 * @example
 * ```
 * void foo() {
 * 	   Unimplemented();
 * }
 */
#define Unimplemented() \
    do {                \
        std::cerr << std::endl << __FILE__ << ":" << __LINE__ << "Use of unimplemented function" << std::endl; \
    } while(0);

#endif //KIVI_SRC_KIVI_UTIL_COMMON_HH_
