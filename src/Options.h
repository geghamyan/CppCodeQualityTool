#pragma once

#include <string>
#include <optional>

/**
 * @struct Options
 * @brief A structure to hold command-line options.
 *
 * This structure contains the options provided through the command line,
 * including the input file, output file, function name, and backup flag.
 */
struct Options {
    std::string inputFile; ///< Path to the input file.
    std::string outputFile; ///< Path to the output file.
    std::optional<std::string> functionName; ///< Name of the function to refactor (optional).
    std::optional<std::string> className; ///< Name of the class to refactor (optional).
    bool backup = false; ///< Flag indicating whether to create a backup file.
};

/**
 * @brief Parses command-line arguments.
 *
 * Parses the command-line arguments to extract the input file path, output file path,
 * function name to refactor, and backup flag.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return An optional Options structure containing the parsed command-line options.
 * @retval std::nullopt if the help option is specified
 * @throw std::invalid_argument if the input file path is not provided.
 */
std::optional<Options> parseCommandLine(int argc, char** argv);
