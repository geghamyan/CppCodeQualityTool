#include <iostream>
#include <cxxopts.hpp>

#include "Options.h"

std::optional<Options> parseCommandLine(int argc, char** argv)
{
	cxxopts::Options options("CppCodeQualityTool", "A tool to analyze and improve C++ code quality");

	options.add_options()
		("i,input", "Input file path", cxxopts::value<std::string>())
		("o,output", "Output file path", cxxopts::value<std::string>()->default_value(""))
		("f,function", "Function name to refactor", cxxopts::value<std::string>())
		("b,backup", "Create a backup file", cxxopts::value<bool>()->default_value("false"))
		("h,help", "Print usage");

	const auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::cout << options.help() << std::endl;
		return std::nullopt;
	}

	if (!result.count("input")) {
		std::cout << options.help() << std::endl;
		throw std::invalid_argument("Input file path is required");
	}

	auto inputFile = result["input"].as<std::string>();
	auto outputFile = result["output"].as<std::string>();
	std::optional<std::string> functionName;
	if (result.count("function")) {
		functionName = result["function"].as<std::string>();
	}

	bool backup = result["backup"].as<bool>();

	if (outputFile.empty()) {
		outputFile = inputFile;
	}

	return Options{ inputFile, outputFile, functionName, backup };
}
