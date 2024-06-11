#include "FunctionAnalyzer.h"
#include "Options.h"
#include "LLMInterface.h"
#include "OpenAILLMInterface.h"
#include "FileUtils.h"

#include <iostream>
#include <string>
#include "CommandFactory.h"


/**
 * @brief Executes the file processing workflow.
 *
 * @param options The command-line options
 * @throw std::runtime_error if file operations fail.
 */
static void executeFileProcessing(const Options& options)
{
	CommandFactory factory;
	auto command = factory.createCommand(options);
	command->execute();
}

/**
 * @brief The main entry point of the application.
 *
 * Parses command-line arguments, executes the file processing workflow,
 * and handles exceptions.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return int Returns 0 on success, or 1 on failure.
 */
int main(int argc, char* argv[])
{
	try
	{
		const auto& options = parseCommandLine(argc, argv);
		if (!options.has_value()) {
			return 0;
		}

		executeFileProcessing(options.value());
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

