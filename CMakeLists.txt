# CMakeList.txt : CMake project for CppCodeQualityTool, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

message(STATUS "CMake version: ${CMAKE_VERSION}")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CppCodeQualityTool")
include_directories(src)

# Add source to this project's executable.
file(GLOB SOURCES "src/*.cpp" "src/*.h")
add_executable (CppCodeQualityTool ${SOURCES})

find_package(cxxopts CONFIG REQUIRED)
target_link_libraries(CppCodeQualityTool PRIVATE cxxopts::cxxopts)

find_package(httplib CONFIG REQUIRED)
target_link_libraries(CppCodeQualityTool PRIVATE httplib::httplib)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(CppCodeQualityTool PRIVATE nlohmann_json::nlohmann_json)

find_package(OpenSSL REQUIRED)
target_link_libraries(CppCodeQualityTool PRIVATE OpenSSL::SSL)
target_link_libraries(CppCodeQualityTool PRIVATE OpenSSL::Crypto)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CppCodeQualityTool PROPERTY CXX_STANDARD 20)
  set_property(TARGET CppCodeQualityTool PROPERTY CXX_STANDARD_REQUIRED ON)
endif()

# Google Test framework
enable_testing()

find_package(GTest CONFIG REQUIRED)

# Add test executable
file(GLOB TESTS_SOURCES "tests/*.cpp" "tests/*.h")
add_executable(runTests ${TESTS_SOURCES}
	src/FunctionAnalyzer.cpp
	src/Options.cpp
	src/FileUtils.cpp
)

# Be aware of https://github.com/google/googletest/issues/2157
target_link_libraries(runTests PRIVATE GTest::gtest GTest::gmock)
add_test(NAME runTests COMMAND runTests)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET runTests PROPERTY CXX_STANDARD 20)
  set_property(TARGET runTests PROPERTY CXX_STANDARD_REQUIRED ON)
endif()
