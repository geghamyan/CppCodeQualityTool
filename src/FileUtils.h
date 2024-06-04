#include <string>

/**
 * @namespace FileUtils
 * @brief Utility functions for file operations.
 *
 * This namespace contains utility functions for reading, writing, and backing up files.
 */
namespace FileUtils
{
    /**
     * @brief Reads the content of a file.
     *
     * Opens the specified file and reads its content into a string.
     *
     * @param filePath The path to the file to be read.
     * @return A string containing the content of the file.
     * @throw std::runtime_error if the file cannot be opened.
     */
    std::string readFile(const std::string& filePath);

    /**
     * @brief Writes content to a file.
     *
     * Opens the specified file and writes the provided content to it.
     *
     * @param filePath The path to the file to be written.
     * @param fileContent The content to write to the file.
     * @throw std::runtime_error if the file cannot be opened for writing.
     */
    void writeFile(const std::string& filePath, const std::string& fileContent);

    /**
     * @brief Creates a backup of a file.
     *
     * Creates a backup of the specified file by copying its content to a new file
     * with the same name and a ".bak" extension.
     *
     * @param filePath The path to the file to be backed up.
     * @throw std::runtime_error if the backup file cannot be created.
     */
    void backupFile(const std::string& filePath);
}