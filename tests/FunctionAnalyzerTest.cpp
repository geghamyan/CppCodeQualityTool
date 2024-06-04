#include "FunctionAnalyzer.h"
#include "LLMInterface.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <stdexcept>


class MockLLMInterface : public LLMInterface {
public:
	MOCK_METHOD(std::string, splitFunction, (const std::string& functionContent), (override));
	MOCK_METHOD(std::vector<FunctionInfo>, findAllFunctions, (const std::string& fileName), (override));
};

class FunctionAnalyzerTest : public ::testing::Test {
protected:
	// Helper functions to call private methods
	int countLongFunctions(const std::string& content) {
		return analyzer->countLongFunctions(content);
	}

	void SetUp() override {
		mockLLM = std::make_unique<MockLLMInterface>();
		analyzer = std::make_unique<FunctionAnalyzer>(mockLLM.get());
	}

	void TearDown() override {
		analyzer.reset();
		mockLLM.reset();
	}

	std::unique_ptr<MockLLMInterface> mockLLM;
	std::unique_ptr<FunctionAnalyzer> analyzer;
};

TEST_F(FunctionAnalyzerTest, ConstructorThrowsWhenLLMIsNull) {
	EXPECT_THROW(FunctionAnalyzer(nullptr), std::invalid_argument);
}

TEST_F(FunctionAnalyzerTest, GetFunctionCodeReturnsCorrectCode) {
	std::string fileContent = "int main() {\n  return 0;\n}\nvoid test() {\n  // test function\n}\n";
	std::string functionName = "test";
	std::string expectedCode = "void test() {\n  // test function\n}\n";
	EXPECT_EQ(analyzer->getFunctionCode(fileContent, functionName), expectedCode);
}

TEST_F(FunctionAnalyzerTest, GetFunctionCodeThrowsWhenFunctionNotFound) {
	std::string fileContent = "int main() {\n  return 0;\n}\n";
	std::string functionName = "test";
	EXPECT_THROW(analyzer->getFunctionCode(fileContent, functionName), std::runtime_error);
}

TEST_F(FunctionAnalyzerTest, SplitFunctionUpdatesFileContent) {
	std::string fileContent = "int main() {\n  return 0;\n}\nvoid test() {\n  // test function\n}\n";
	std::string functionName = "test";
	std::string newCode = "void testPart1() {\n  // part 1\n}\nvoid testPart2() {\n  // part 2\n}\n";

	EXPECT_CALL(*mockLLM, splitFunction(::testing::_)).WillOnce(::testing::Return(newCode));

	analyzer->splitFunction(fileContent, functionName);
	EXPECT_NE(fileContent.find("testPart1"), std::string::npos);
	EXPECT_NE(fileContent.find("testPart2"), std::string::npos);
}

TEST_F(FunctionAnalyzerTest, SplitFunctionThrowsWhenFunctionNotFound) {
	std::string fileContent = "int main() {\n  return 0;\n}\n";
	std::string functionName = "test";
	EXPECT_THROW(analyzer->splitFunction(fileContent, functionName), std::runtime_error);
}

TEST_F(FunctionAnalyzerTest, CountLongFunctionsReturnsCorrectCount) {
	std::string fileContent = "void func1() {}\nvoid func2() {}\nvoid func3() {}\n";
	EXPECT_EQ(countLongFunctions(fileContent), 3);
}

TEST_F(FunctionAnalyzerTest, CountLongFunctionsReturnsZeroForNoFunctions) {
	std::string fileContent = "int x = 10;\n";
	EXPECT_EQ(countLongFunctions(fileContent), 0);
}
