#pragma once
#include <string>
#include <vector>

/**
 * @struct FunctionInfo
 * @brief A structure to hold information about a function in the source code.
 */
struct FunctionInfo {
    std::string name;   ///< The name of the function.
    int loc;            ///< The number of lines of code in the function.
};

/**
 * @class LLMInterface
 * @brief An abstract class for interfacing with a language model.
 */
class LLMInterface {
public:
    /**
     * @brief Splits a given function into smaller functions.
     *
     * This method sends the content of a function to the language model
     * and retrieves the split functions.
     *
     * @param functionContent The content of the function to be split.
     * @return A string containing the split functions.
     */
    virtual std::string splitFunction(const std::string& functionContent) = 0;

    /**
     * @brief Finds all functions in the specified file.
     *
     * This method analyzes the specified file and retrieves information
     * about all the functions present in the file.
     *
     * @param fileName The name of the file to analyze.
     * @return A vector of FunctionInfo structures containing information about the functions in the file.
     */
    virtual std::vector<FunctionInfo> findAllFunctions(const std::string& fileName) = 0;
};
