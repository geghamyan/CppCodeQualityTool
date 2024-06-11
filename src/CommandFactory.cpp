#include "CommandFactory.h"
#include "Options.h"
#include <stdexcept>

Command::Ptr CommandFactory::createCommand(const Options& options)
{
	if (options.functionName)
	{
		return std::make_unique<SplitFunctionCommand>(options);
	}
	else if (options.className)
	{
		return std::make_unique<SplitClassCommand>(options);
	}
	else
	{
		throw std::runtime_error("Unknown command");
	}
}
