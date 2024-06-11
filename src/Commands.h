#pragma once
#include <memory>
#include <string>

struct Options;

/**
 * @class Command
 * @brief Abstract base class for commands.
 *
 * This class defines the interface for commands.
 */
class Command
{
public:
    using Ptr = std::unique_ptr<Command>; ///< Pointer type for commands.

    virtual ~Command() = default;

    /**
     * @brief Executes the command.
     */
    virtual void execute() = 0;
};

/**
 * @class FileCommand
 * @brief Abstract base class for file-related commands.
 *
 * This class provides common functionality for commands that operate on files.
 */
class FileCommand : public Command
{
public:
    /**
     * @brief Constructs a FileCommand with the specified options.
     *
     * @param options The command-line options.
     */
    explicit FileCommand(const Options& options);

    /**
     * @brief Executes the file-related command.
     */
    virtual void execute() override;

protected:
    /**
     * @brief Refactors the content of the file.
     *
     * This method must be implemented by derived classes to perform specific refactoring.
     *
     * @param content The content of the file to refactor.
     */
    virtual void refactorContent(std::string content) = 0;

private:
    std::string inputFile_;     ///< Path to the input file.
    std::string outputFile_;    ///< Path to the output file.
    bool backup_ = false;       ///< Flag indicating whether to create a backup file.
};

/**
 * @class SplitFunctionCommand
 * @brief Command to split long functions in a file.
 *
 * This class implements the functionality to split long functions in a file.
 */
class SplitFunctionCommand : public FileCommand
{
public:
    /**
     * @brief Constructs a SplitFunctionCommand with the specified options.
     *
     * @param options The command-line options.
     */
    explicit SplitFunctionCommand(const Options& options);

    /**
     * @brief Executes the command to split long functions.
     */
    virtual void execute() override;

protected:
    /**
     * @brief Refactors the content by splitting long functions.
     *
     * @param content The content of the file to refactor.
     */
    virtual void refactorContent(std::string content) override;

private:
    std::string functionName_; ///< Name of the function to split.
};

/**
 * @class SplitClassCommand
 * @brief Command to split large classes in a file.
 *
 * This class implements the functionality to split large classes in a file.
 */
class SplitClassCommand : public FileCommand
{
public:
    /**
     * @brief Constructs a SplitClassCommand with the specified options.
     *
     * @param options The command-line options.
     */
    explicit SplitClassCommand(const Options& options);

    /**
     * @brief Executes the command to split large classes.
     */
    virtual void execute() override;

protected:
    /**
     * @brief Refactors the content by splitting large classes.
     *
     * @param content The content of the file to refactor.
     */
    virtual void refactorContent(std::string content) override;

private:
    std::string className_; ///< Name of the class to split.
};
