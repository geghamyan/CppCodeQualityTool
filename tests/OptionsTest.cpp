#include "Options.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <vector>
#include <string>


class ParseCommandLineTest : public ::testing::Test {
protected:
	std::vector<const char*> argv_;
	int argc_;

	char** getArgv() {
		return const_cast<char**>(argv_.data());
	}

	int getArgc() {
		return argc_;
	}

	void SetUp() override {
		argv_.clear();
		argc_ = 0;
	}

	void addArgument(const char* arg) {
		argv_.push_back(arg);
		argc_ = static_cast<int>(argv_.size());
	}

	void addArguments(std::initializer_list<const char*> list) {
		argv_.insert(argv_.end(), list.begin(), list.end());
		argc_ = static_cast<int>(argv_.size());
	}
};

TEST_F(ParseCommandLineTest, ParseValidInput) {
	addArguments({
		"CppCodeQualityTool",
		"--input",
		"input.cpp",
		"--output",
		"output.cpp",
		"--function",
		"myFunction",
		"--backup" });

	auto options = parseCommandLine(argc_, getArgv());
	ASSERT_TRUE(options.has_value());

	EXPECT_EQ(options->inputFile, "input.cpp");
	EXPECT_EQ(options->outputFile, "output.cpp");
	EXPECT_TRUE(options->functionName.has_value());
	EXPECT_EQ(options->functionName.value(), "myFunction");
	EXPECT_TRUE(options->backup);
}

TEST_F(ParseCommandLineTest, ParseValidClassRefactoring) {
	addArguments({
		"CppCodeQualityTool",
		"--input",
		"input.cpp",
		"--output",
		"output.cpp",
		"--class",
		"MyClass",
		"--backup" });

	auto options = parseCommandLine(argc_, getArgv());
	ASSERT_TRUE(options.has_value());

	EXPECT_EQ(options->inputFile, "input.cpp");
	EXPECT_EQ(options->outputFile, "output.cpp");
	EXPECT_TRUE(options->className.has_value());
	EXPECT_EQ(options->className.value(), "MyClass");
	EXPECT_TRUE(options->backup);
}

TEST_F(ParseCommandLineTest, ParseMissingInputFile) {
	addArguments({
		"CppCodeQualityTool",
		"--output",
		"output.cpp"});

	EXPECT_THROW(parseCommandLine(getArgc(), getArgv()), std::invalid_argument);
}

TEST_F(ParseCommandLineTest, ParseDefaultOutputFile) {
	addArguments({
		"CppCodeQualityTool",
		"--input",
		"input.cpp"});

	auto options = parseCommandLine(getArgc(), getArgv());
	ASSERT_TRUE(options.has_value());

	EXPECT_EQ(options->inputFile, "input.cpp");
	EXPECT_EQ(options->outputFile, "input.cpp");
	EXPECT_FALSE(options->functionName.has_value());
	EXPECT_FALSE(options->backup);
}

TEST_F(ParseCommandLineTest, ParseHelpOption) {
	addArguments({
		"CppCodeQualityTool",
		"--help"});

	auto options = parseCommandLine(getArgc(), getArgv());
	EXPECT_FALSE(options.has_value());
}

TEST_F(ParseCommandLineTest, ParseBackupOption) {
	addArguments({
		"CppCodeQualityTool",
		"--input",
		"input.cpp",
		"--backup"});

	auto options = parseCommandLine(getArgc(), getArgv());
	ASSERT_TRUE(options.has_value());

	EXPECT_EQ(options->inputFile, "input.cpp");
	EXPECT_EQ(options->outputFile, "input.cpp");
	EXPECT_FALSE(options->functionName.has_value());
	EXPECT_TRUE(options->backup);
}
