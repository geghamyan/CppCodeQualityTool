#pragma once
#include <string>
#include <tuple>

// Forward declarations
class LLMInterface;
class FunctionAnalyzerTest;

/**
 * @class FunctionAnalyzer
 * @brief A class for analyzing and refactoring functions in source code files.
 *
 * This class provides functionality to find, analyze, and refactor functions in
 * source code files using a language model interface.
 */
class FunctionAnalyzer
{
public:
    /**
     * @brief Constructs a FunctionAnalyzer object.
     *
     * Initializes the FunctionAnalyzer with a given language model interface.
     *
     * @param llm A pointer to the language model interface.
     * @throw std::invalid_argument if the llm pointer is null.
     */
    explicit FunctionAnalyzer(LLMInterface* llm);

    /**
     * @brief Finds a specific function in a file and returns its content.
     *
     * Searches the file content for a function with the given name and returns its code.
     *
     * @param fileContent The content of the file to search.
     * @param functionName The name of the function to find.
     * @return A string containing the code of the found function.
     */
    std::string getFunctionCode(const std::string& fileContent, const std::string& functionName);

    /**
     * @brief Splits a function into smaller functions.
     *
     * Uses the language model interface to split a function into smaller functions and
     * updates the file content with the new code.
     *
     * @param fileContent The content of the file to update.
     * @param functionName The name of the function to split.
     * @throw std::runtime_error if the function is not found or the split operation fails.
     */
    void splitFunction(std::string& fileContent, const std::string& functionName);

private:
    friend class FunctionAnalyzerTest;

    LLMInterface* const llm_; ///< The language model interface used for refactoring functions.

    /**
     * @brief Finds the start and end positions of a function in the file content.
     *
     * Searches the file content for the start and end positions of a function with the given name.
     *
     * @param fileContent The content of the file to search.
     * @param functionName The name of the function to find.
     * @return A tuple containing the start and end positions of the function.
     * @throw std::runtime_error if the function is not found or the end position cannot be determined.
     */
    std::tuple<int, int> findFunctionPositions(const std::string& fileContent, const std::string& functionName);

    /**
     * @brief Counts the number of long functions in the content.
     *
     * Analyzes the content to count the number of long functions based on a predefined criterion.
     *
     * @param content The content to analyze.
     * @return The number of long functions found.
     */
    int countLongFunctions(const std::string& content);
};
