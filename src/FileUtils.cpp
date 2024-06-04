#include "FileUtils.h"

#include <fstream>
#include <sstream>

using namespace FileUtils;

static void copyFile(const std::string& sourcePath, const std::string& destinationPath) {
	std::ifstream source(sourcePath, std::ios::binary);
	if (!source.is_open()) {
		throw std::runtime_error("Error opening source file: " + sourcePath);
	}
	std::ofstream destination(destinationPath, std::ios::binary);
	if (!destination.is_open()) {
		throw std::runtime_error("Error opening destination file: " + destinationPath);
	}

	destination << source.rdbuf();
}

std::string FileUtils::readFile(const std::string& filePath)
{
	std::ifstream inputFile(filePath);
	if (!inputFile.is_open()) {
		throw std::runtime_error("Error opening file: " + filePath);
	}

	std::stringstream buffer;
	buffer << inputFile.rdbuf();
	std::string fileContent = buffer.str();
	inputFile.close();

	return fileContent;
}

void FileUtils::writeFile(const std::string& filePath, const std::string& fileContent)
{
	std::ofstream outputFile(filePath);
	if (!outputFile.is_open()) {
		throw std::runtime_error("Error opening file for writing: " + filePath);
	}
	outputFile << fileContent;
	outputFile.close();
}

void FileUtils::backupFile(const std::string& filePath)
{
	std::string backupPath = filePath + ".bak";
	copyFile(filePath, backupPath);
}

