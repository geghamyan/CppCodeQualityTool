#include "gtest/gtest.h"
#include "FileUtils.h"
#include <fstream>
#include <stdexcept>
#include <cstdio>

class FileUtilsTest : public ::testing::Test {
protected:
	std::string testFileName = "testFile.txt";
	std::string backupFileName = "testFile.txt.bak";
	std::string fileContent = "This is a test file.";

	void SetUp() override {
		std::ofstream testFile(testFileName);
		testFile << fileContent;
		testFile.close();
	}

	void TearDown() override {
		std::remove(testFileName.c_str());
		std::remove(backupFileName.c_str());
	}
};

TEST_F(FileUtilsTest, ReadFile) {
	std::string content = FileUtils::readFile(testFileName);
	EXPECT_EQ(content, fileContent);
}

TEST_F(FileUtilsTest, ReadFileThrowsIfFileNotFound) {
	EXPECT_THROW(FileUtils::readFile("nonexistent.txt"), std::runtime_error);
}

TEST_F(FileUtilsTest, WriteFile) {
	std::string newContent = "New content for the file.";
	FileUtils::writeFile(testFileName, newContent);

	auto content = FileUtils::readFile(testFileName);
	EXPECT_EQ(content, newContent);
}

TEST_F(FileUtilsTest, WriteFileThrowsIfCannotOpen) {
	EXPECT_THROW(FileUtils::writeFile("/invalid/path/to/file.txt", fileContent), std::runtime_error);
}

TEST_F(FileUtilsTest, BackupFile) {
	FileUtils::backupFile(testFileName);

	auto content = FileUtils::readFile(backupFileName);
	EXPECT_EQ(content, fileContent);
}

TEST_F(FileUtilsTest, BackupFileThrowsIfSourceFileNotFound) {
	EXPECT_THROW(FileUtils::backupFile("nonexistent.txt"), std::runtime_error);
}
