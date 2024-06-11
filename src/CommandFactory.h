#pragma once
#include "Commands.h"

struct Options;

/**
 * @class CommandFactory
 * @brief Factory class for creating commands based on options.
 *
 * This class provides a method to create specific command instances based on
 * the provided command-line options.
 */
class CommandFactory
{
public:
    /**
     * @brief Creates a command based on the provided options.
     *
     * This method inspects the options and creates an appropriate command
     * instance (e.g., SplitFunctionCommand, SplitClassCommand).
     *
     * @param options The command-line options.
     * @return A unique pointer to the created command.
     */
    Command::Ptr createCommand(const Options& options);
};
