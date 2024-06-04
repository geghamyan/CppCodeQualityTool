#include "FunctionAnalyzer.h"
#include "LLMInterface.h"
#include "FileUtils.h"

#include <regex>
#include <fstream>
#include <sstream>
#include <tuple>


FunctionAnalyzer::FunctionAnalyzer(LLMInterface* llm)
	: llm_(llm)
{
	if (llm_ == nullptr) {
		throw std::invalid_argument("llm is null");
	}
}

int FunctionAnalyzer::countLongFunctions(const std::string& content) {
    std::regex functionRegex(R"(\b\w+\s+\w+\s*\([^)]*\)\s*\{)");
    std::sregex_iterator iter(content.begin(), content.end(), functionRegex);
    std::sregex_iterator end;

    int longFunctionCount = 0;
    while (iter != end) {
        ++longFunctionCount;
        ++iter;
    }

    return longFunctionCount;
}

std::string FunctionAnalyzer::getFunctionCode(const std::string& fileContent, const std::string& functionName)
{
	auto [startPos, endPos] = findFunctionPositions(fileContent, functionName);

	return fileContent.substr(startPos, endPos - startPos);
}

void FunctionAnalyzer::splitFunction(std::string& fileContent, const std::string& functionName)
{
	auto [startPos, endPos] = findFunctionPositions(fileContent, functionName);
	auto code = fileContent.substr(startPos, endPos - startPos);
	if (code.empty()) {
		throw std::runtime_error("Function not found: " + functionName);
	}
	auto newCode = llm_->splitFunction(code);
	fileContent.replace(startPos, endPos - startPos, newCode);
}

std::tuple<int, int> FunctionAnalyzer::findFunctionPositions(const std::string& fileContent, const std::string& functionName)
{
	// Find the function to replace
	std::string functionSignature = functionName + "(";
	size_t startPos = fileContent.find(functionSignature);
	if (startPos == std::string::npos) {
		throw std::runtime_error("Function not found: " + functionName);
	}

	// Find the end of the function
	size_t braceCount = 0;
	size_t endPos = startPos;
	bool inFunction = false;
	for (size_t i = startPos; i < fileContent.length(); ++i) {
		if (fileContent[i] == '{') {
			if (!inFunction) {
				inFunction = true;
			}
			braceCount++;
		}
		else if (fileContent[i] == '}') {
			braceCount--;
			if (braceCount == 0 && inFunction) {
				endPos = i + 1;
				break;
			}
		}
	}

	if (!(inFunction && endPos > startPos)) {
		throw std::runtime_error("Error finding the end of the function: " + functionName);
	}

	// Extend the start position to the beginning of the line
	while (startPos > 1 && fileContent[startPos - 1] != '\n') {
		--startPos;
	}

	// Extend the end position to the end of the line
	if (endPos < fileContent.length() && fileContent[endPos] == '\n') {
		++endPos;
	}

	return { startPos, endPos };
}
