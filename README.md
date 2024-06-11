# CppCodeQualityTool User Guide

## Introduction

CppCodeQualityTool is a command-line tool designed to analyze and improve the quality of C++ code. It detects long functions and classes and splits them into smaller ones using a Large Language Model (LLM) from OpenAI. The tool is intended to evolve and be able to detect various other code smells, such as long functions, primitive obsession, and more.CppCodeQualityTool is a command-line tool designed to analyze and improve the quality of C++ code. It detects long functions and splits them into smaller ones using a Large Language Model (LLM) from OpenAI.

## Potential Extensibility

Currently, the tool supports breaking long functions apart but can obviously be extended to cover more code smells and refactoring patterns. The design is modular, allowing for easy addition of new detection and refactoring capabilities.

## Potential Integrations

CppCodeQualityTool can be used as a standalone refactoring tool. Additionally, it has the potential to be integrated into various development environments and workflows:

* **IDE Integration** : Can be integrated into Visual Studio (VS2022) or Visual Studio Code (VSCode) for real-time code analysis and refactoring suggestions.
* **PR Review Hook** : Can be used as a hook in Pull Request (PR) reviews to automatically analyze and suggest improvements to the code being reviewed.

## Future Development

The overall idea of the CppCodeQualityTool is to evolve and detect various code smells beyond long functions. Potential code smells to be detected include:

* **Primitive Obsession** : Overuse of primitive data types instead of small objects.
* **Large Classes** : Classes that have grown too large and do too much.
* **Duplicated Code** : Identical or very similar code present in multiple places.
* **Long Parameter Lists** : Functions that take too many parameters.
* etc

---

## Installation

1. Clone the repository:

   ```sh
   git clone <repository-url>
   ```
2. Build the project:

   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

## Configuration

Before using the tool, you need to set up the OpenAI API key. This key is required for the tool to interact with the OpenAI LLM.

1. Obtain your OpenAI API key from the [OpenAI website](https://www.openai.com/).
2. Set the `OPENAI_API_KEY` environment variable with your API key:

   ```sh
   export OPENAI_API_KEY=<your-api-key>
   ```

## Usage

```sh
CppCodeQualityTool --input <path-to-input-file> [--output <path-to-output-file>] [--function <function-name>] [--class <class-name>] [--backup] [--help]
```

**Options**

* `--input` or`-i`: Specify the path to the input file (required).
* `--output` or`-o`: Specify the path to the output file (optional). If not provided, the input file will be overwritten.
* `--function` or`-f`: Specify the name of the function to refactor (optional).
* `--backup` or`-b`: Optionally create a backup file of the output file before overwriting it with a`.bak` extension.
* `--help` or`-h`: Display the help message

## Example

To refactor a specific function and create a backup of the input file:
```sh
CppCodeQualityTool --input example.cpp --output output.cpp --function myFunction --backup
```

To refactor a specific class and create a backup of the input file:
```sh
CppCodeQualityTool --input example.cpp --output output.cpp --class MyClass --backup
```

To refactor a specific function without creating a backup:

```sh
CppCodeQualityTool --input example.cpp --output output.cpp --function myFunction
```

To overwrite the input file with the refactored code without creating a backup:

```sh
CppCodeQualityTool --input example.cpp --function myFunction
```

## Help

To display the help message, use the `--help` or `-h` flag:

```sh
CppCodeQualityTool --help
```

## Backup

If the `--backup` option is provided, the tool will create a backup of the input file with a `.bak` extension before making any modifications. For example, if the input file is `example.cpp`, the backup file will be `example.cpp.bak`.
