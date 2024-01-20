# Arithmetic AST & Evaluator

This C++ program provides a simple mathematical expression evaluator using an Abstract Syntax Tree (AST). The AST is constructed from different types of nodes, such as constants, identifiers, unary operators (plus and minus), and binary operators (addition, subtraction, multiplication, division, and power). The program allows for the evaluation of mathematical expressions involving variables and basic operations.

## Table of Contents

- [Introduction](#introduction)
- [Usage](#usage)
- [ASTNode Hierarchy](#astnode-hierarchy)
- [Example Usage](#example-usage)
- [Error Handling](#error-handling)
- [Variable Assignment](#variable-assignment)
- [Cleaning Variables](#cleaning-variables)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The program defines a hierarchy of classes representing different types of AST nodes. Each node has a specific type and implements the `evaluate` method to perform the corresponding mathematical operation. The AST is utilized to evaluate complex mathematical expressions composed of constants, variables, and various operators.

## Usage

To use the expression evaluator, follow these steps:

1. **Variable Assignment:** Use the `Identifier::setVariable` method to assign values to variables.
2. **Expression Creation:** Construct the expression using the provided AST nodes and operators.
3. **Evaluation:** Call the `evaluate` method on the root node of the expression.
4. **Cleanup:** Release the allocated memory using `delete` and, if needed, clear assigned variables.

## ASTNode Hierarchy

The ASTNode hierarchy consists of the following classes:

- `Constant`: Represents a constant numerical value.
- `Identifier`: Represents a variable identified by a string.
- `Unary`: Abstract base class for unary operators.
  - `UnaryPlus`: Represents the unary plus operator.
  - `UnaryMinus`: Represents the unary minus operator.
- `Binary`: Abstract base class for binary operators.
  - `Add`: Represents the addition operator.
  - `Subtract`: Represents the subtraction operator.
  - `Multiply`: Represents the multiplication operator.
  - `Divide`: Represents the division operator.
  - `Power`: Represents the power operator.

## Example Usage

Execute the command below in a shell to run the example.

```bash
$ make run
```

In this example, the expression `-(Num1) + 2 * (4 - Num2)` is evaluated with variables `Num1` and `Num2` assigned specific values.

```cpp
// Example usage
Identifier::setVariable("Num1", 3.0);
Identifier::setVariable("Num2", 7.0);

ASTNode *expression = new Add(new UnaryMinus(new Identifier("Num1")),
                              new Multiply(new Constant(2), new Subtract(new Constant(4), new Identifier("Num2"))));
double result = expression->evaluate();

std::cout << "Result: " << result << std::endl;

delete expression; // Free the memory
Identifier::clearVariables();
```

## Error Handling

The program includes basic error handling. For example, attempting to divide by zero will result in an error message printed to `std::cerr`, and the division operation will return infinity to indicate an error.

## Variable Assignment

Variables are assigned values using the `Identifier::setVariable` method. If an undefined variable is encountered during evaluation, an error message is printed, and the default value of `0.0` is returned.

## Cleaning Variables

To clean up assigned variables and release allocated memory, use the `Identifier::clearVariables` method. This ensures a clean slate for subsequent expressions.

## Contributing

Feel free to contribute to the project by opening issues, suggesting improvements, or submitting pull requests. Your contributions are highly appreciated.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
