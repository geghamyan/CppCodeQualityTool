#include "OpenAILLMInterface.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <nlohmann/json.hpp>

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

const std::string splitFunctionPrompt = R"(You will act as an expert C++ refactoring tool. I will provide you with a C++ function's source code. Your task is to refactor the given function by splitting it into smaller, more manageable functions while maintaining the same functionality. Ensure that the new functions are grouped logically and follow the same naming conventions and style as the original function. Additionally, include comments before each new function describing their responsibilities to improve code readability and maintainability. Make sure that all necessary helper functions are generated regardless of brevity. The final result should be presented as pure C++ code without any additional explanations. The code will be enclosed in triple backticks (```), but the final result should not include these backticks.

Example Input:
```
void complexFunction() {
    // Some complex and lengthy C++ code
}
```

Example Output:
```
// This function handles the initialization process
inline void handleInitialization() {
    // Code responsible for initialization
}

// This function processes the data
inline void processData() {
    // Code responsible for processing data
}

// This function finalizes the results
inline void finalizeResults() {
    // Code responsible for finalizing the results
}

void complexFunction() {
    handleInitialization();
    processData();
    finalizeResults();
}
```
)";

OpenAILLMInterface::OpenAILLMInterface() {
	const char* env_api_key = std::getenv("OPENAI_API_KEY");
	if (env_api_key) {
		apiKey_ = env_api_key;
	}
	else {
		throw std::runtime_error("OPENAI_API_KEY environment variable is not set");
	}
}

std::string OpenAILLMInterface::splitFunction(const std::string& functionContent) {
	std::string prompt = createPrompt(functionContent);
	return sendRequest(prompt);
}

std::vector<FunctionInfo> OpenAILLMInterface::findAllFunctions(const std::string& fileName) {
	throw std::logic_error("The method or operation is not implemented.");
}

std::string OpenAILLMInterface::createPrompt(const std::string& functionCode) {
	return splitFunctionPrompt + "\n Input function:\n```" + functionCode + "\n```";
}

std::string OpenAILLMInterface::sendRequest(const std::string& prompt) {
	httplib::Client cli("https://api.openai.com");
    cli.set_read_timeout(std::chrono::minutes(5));

	cli.set_default_headers({
			{"Authorization", "Bearer " + apiKey_},
			{"Content-Type", "application/json"}
		});

	json jsonData;
	jsonData["model"] = "gpt-4o";
	jsonData["messages"] = {
		{{"role", "system"}, {"content", "You are a helpful assistant."}},
		{{"role", "user"}, {"content", prompt}}
	};

	std::string body = jsonData.dump();

	auto res = cli.Post("/v1/chat/completions", body, "application/json");

	if (res.error() != httplib::Error::Success)
	{
		if (res)
		{
			throw std::runtime_error("HTTP request failed: " + to_string(res.error()));
		}
		else
		{
			throw std::runtime_error("HTTP request failed: " + std::to_string(res->status) + " - " + res->body);
		}
	}

	json responseJson = json::parse(res->body);
	if (responseJson.contains("choices") && !responseJson["choices"].empty()) {
		return responseJson["choices"][0]["message"]["content"].get<std::string>();
	}

	throw std::runtime_error("Invalid response from OpenAI API");
}
