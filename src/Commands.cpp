#include "Commands.h"
#include "Options.h"
#include "FileUtils.h"
#include "OpenAILLMInterface.h"
#include "FunctionAnalyzer.h"
#include <stdexcept>


FileCommand::FileCommand(const Options& options) :
	inputFile_(options.inputFile),
	outputFile_(options.outputFile),
	backup_(options.backup)
{
}

void FileCommand::execute()
{
	// Read file content
	auto content = FileUtils::readFile(inputFile_);

	refactorContent(content);

	if (backup_) {
		FileUtils::backupFile(outputFile_);
	}
	FileUtils::writeFile(outputFile_, content);
}

SplitFunctionCommand::SplitFunctionCommand(const Options& options)
	: FileCommand(options), functionName_(options.functionName.value())
{
}

void SplitFunctionCommand::execute()
{
	FileCommand::execute();
}

void SplitFunctionCommand::refactorContent(std::string content)
{
	// Analyze file content
	OpenAILLMInterface llMInterface;
	FunctionAnalyzer analyzer(&llMInterface);

	analyzer.splitFunction(content, functionName_);
}

SplitClassCommand::SplitClassCommand(const Options& options)
	: FileCommand(options), className_(options.className.value())
{
}

void SplitClassCommand::execute()
{
	FileCommand::execute();
}

void SplitClassCommand::refactorContent(std::string content)
{
	throw std::runtime_error("Not implemented");
}
