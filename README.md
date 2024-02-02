

# Mathematical Expression Calculator
A command-line calculator application that evaluates mathematical expressions using a two-phase approach. It includes tokenization, lexical analysis, parsing, and calculation functionalities.

## Project Overview
This project implements a mathematical expression calculator with the following components:

## Phase 1: Mathematical Expression Evaluation
### Tokenization (Token):

Identifies and categorizes elements (e.g., numbers, parentheses, operators) in the expression.
Validations ensure correct token types.
### Lexer:

Transforms the expression into a vector of tokens.
Ensures the presence of numeric characters and valid characters.
### Parser:

Converts the expression into postfix notation using the Shunting Yard algorithm.
Validates the logical correctness of the expression.
### Calculator:

Calculates the result of the postfix expression.
Handles mathematical validations (e.g., division by zero, square root of a negative number).
## Phase 2: Menu-driven Options
### Option Management (Option):

Manages available functions through a menu-driven approach.
Includes options like stop, change mode, file operations, and calculations.
### Menu Types:

Supports different menu types (input from keyboard, input from file, output to screen or file).
Switches between modes and manages user input.
Binary File Calculator:

Serializes and deserializes results for persistent storage.
Features
Mathematical expression evaluation.
Tokenization, lexical analysis, and parsing.
Command-line interface with menu-driven options.
Support for various menu types (input from keyboard, input from file, output to screen or file).
Binary file serialization for result persistence.
Usage

- stop: Stops the application.
- changeMode: Switches between menu types.
- binaryFile: Serializes the current calculation result into a binary file.
- displayBinaryFile: Deserializes and displays the last result saved in the binary file.
- calculus: Performs a calculation.

### Project Structure
The project is organized into the following components:

- Token: Represents elements in the expression with properties like type, value, and precedence.
- Lexer: Transforms expressions into vectors of tokens.
- Parser: Converts expressions into postfix notation using the Shunting Yard algorithm.
- Calculator: Evaluates mathematical expressions and handles result persistence.
- Option: Manages menu-driven options.
- Menu: Abstract class representing the base class for different menu types.
## Dependencies
The project has no external dependencies. It is implemented in C++ and utilizes standard libraries.

## Contributing
Feel free to contribute to the project by opening issues or pull requests. 
