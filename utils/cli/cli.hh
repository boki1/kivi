/**
 * @file cli/cli.hh
 * @brief This file provides the blueprint of the command line interface where all utilities
 * needed for it are placed. It is used for flags such as -h, --help, -v, --version, etc.
 */

#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <bitset>

namespace cli {
    class options_set {
        /// enum class giving the compile stage options:
        /// - ASM: to assembly;
        /// - O: to object.
        enum class CompileToStage {
            ASM, O
        };

        /// The number of shifts to be made in order to get the visualisation flag you need:
        /// @note The visualisation flags consists of the bit flags, contained in the
        /// VisualizeFlagShift, reading from the most significant bit to the least one.
        /// These are as follows:
        ///  - AST: Abstract Syntax Tree
        ///  - IR: Intermediate (code) Generation
        enum class VisualizeFlagShift {
            AST, IR
        };
        static const int VISUALIZATION_TYPES = 2;

        CompileToStage compile_to = CompileToStage::O;

        /**
            * @brief The flags for what type of visualization should be done
            * @note The visualisation flags consists of the bit flags, contained in the
            * VisualizeFlagShift, reading from the most significant bit to the least one.
            * See enum class VisualizeFlagShift.
         */
        std::bitset<VISUALIZATION_TYPES> vis_flags{0};

        /**
         * @brief Describes the cli usage
         * @note Used when -h or --help flag is given or when the cli is not used correctly
         */
        static void
        usage();

        /**
         * @brief Sets the compile_to member field
         * @param compileStage - the value to be set
         */
        void set_compile_to(options_set::CompileToStage compileStage);

        /**
         * @briev After recognising there is a compile-to stage, recognize_compil_stage gets
         * the exact stage and sets it using the set_compile_to.
         * @param arg - the argument to be recognised
         * @note The argument is the part _after_ the equals sign. For instance, instead of
         * `--compile-to=ASM`, it looks only for the ASM part.
         * @note The argument is valid regardless of the capitalization (__ASM__ and __asm__
         * both will __work__, however `AsM` will not be recognized as a valid command)
         */
        void recognize_compil_stage(std::string &&arg);

        /**
         * @brief Sets the vis_flags member field bit
         * @param vis_flag_shift - which bit to be set (the shift left number)
         */
        void set_visualization_flags(options_set::VisualizeFlagShift vis_flag_shift);

        /**
         * @brief After recognising there is a vis flag set on the command line,
         * recognize_visualization gets all the exact stages and sets their flags by the
         * set_visualization_flags function.
         * @param arg - the argument to be recognized
         * @note The argument is valid regardless of the capitalization (__AST__ and __ast__
         * both will __work__, however `AsT` will not be recognized as a valid command)
         */
        void recognize_visualization(std::string &&arg);

    public:
        /**
         * @brief Processes a single option
         * @param arg - the string containing an option
         * @return 0 if success; 1 if the execution of the whole program should be stopped
         * (e.g. when --help flag is enabled).
         */
        bool process_options(const std::string &&arg);
    };

    /**
        * @brief The 'main' of the cli which should be called in order to process all the
        * flags enabled on the command line.
        * @param argc - the number of arguments
        * @param argv - the arguments
        * @return 0 if success; 1 if fail
     */
    bool
    argument_parser(int argc, char *argv[]);
}

#endif //CLI_H
