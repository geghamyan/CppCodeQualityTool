#pragma once
#include "LLMInterface.h"
#include <string>
#include <vector>

/**
 * @class OpenAILLMInterface
 * @brief A class for interfacing with the OpenAI API
 *
 * This class implements the LLMInterface to interact with the OpenAI API
 */
class OpenAILLMInterface : public LLMInterface {
public:
    /**
     * @brief Constructs an OpenAILLMInterface object.
     *
     * Initializes the API key from the environment variable "OPENAI_API_KEY".
     *
     * @throw std::runtime_error if the "OPENAI_API_KEY" environment variable is not set.
     */
    OpenAILLMInterface();

    /**
     * @brief Splits a given function into smaller functions.
     *
     * Sends a request to the OpenAI API to split the given function content
     * into smaller functions.
     *
     * @param functionContent The content of the function to be split.
     * @return A string containing the split functions.
     */
    std::string splitFunction(const std::string& functionContent) override;

    /**
     * @brief Finds all functions in the specified file.
     *
     * This method is not implemented and will throw a logic error if called.
     *
     * @param fileName The name of the file to analyze.
     * @return A vector of FunctionInfo structures containing information about the functions in the file.
     * @throw std::logic_error Always throws as this method is not implemented.
     */
    std::vector<FunctionInfo> findAllFunctions(const std::string& fileName) override;

private:
    std::string apiKey_; ///< The API key for accessing the OpenAI API.

    /**
     * @brief Sends a request to the OpenAI API.
     *
     * Constructs and sends a request to the OpenAI API with the given prompt.
     *
     * @param prompt The prompt to send to the OpenAI API.
     * @return The response from the OpenAI API.
     * @throw std::runtime_error if the HTTP request fails or the response is invalid.
     */
    std::string sendRequest(const std::string& prompt);

    /**
     * @brief Creates a prompt for the OpenAI API request.
     *
     * Constructs a prompt for splitting the given function code into smaller functions.
     *
     * @param functionCode The content of the function to be split.
     * @return The constructed prompt.
     */
    std::string createPrompt(const std::string& functionCode);
};
