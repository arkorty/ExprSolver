# Arithmetic Expression Evaluator

This C++ program provides a simple arithmetic expression evaluator based on Abstract Syntax Trees (AST). It supports constants, variables, unary operations (unary plus and unary minus), and binary operations (addition, subtraction, multiplication, division, and exponentiation).

## Table of Contents

- [Features](#features)
- [AST Node Hierarchy](#ast-node-hierarchy)
- [Examples](#examples)
- [Concepts](#concepts)
- [Memory Management](#memory-management)
- [Testing](#testing)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features

- Evaluate arithmetic expressions with constants and variables.
- Handle unary operations (unary plus and unary minus).
- Support binary operations: addition, subtraction, multiplication, division, and exponentiation.
- Variable management with a variable table.
- Error handling for undefined variables and division by zero.

## AST Node Hierarchy

The program defines a hierarchy of AST nodes, including:

- `Constant`: Represents a constant numerical value.
- `Identifier`: Represents a variable identifier.
- `UnaryPlus` and `UnaryMinus`: Represent unary plus and unary minus operations.
- `Add`, `Subtract`, `Multiply`, `Divide`, and `Power`: Represent binary operations.

## Examples

```cpp
// Example 1: Simple Addition
auto additionNode = std::make_unique<Add>(
    std::make_unique<Constant>(2.0),
    std::make_unique<Constant>(3.0)
);
double result = additionNode->evaluate();  // Result: 5.0

// Example 2: Variable and Unary Minus
auto variableX = std::make_unique<Identifier>("x");
auto unaryMinusNode = std::make_unique<UnaryMinus>(std::move(variableX));
Identifier::setVariable("x", 7.0);
result = unaryMinusNode->evaluate();  // Result: -7.0
```

## Concepts

This arithmetic expression evaluator leverages Object-Oriented Programming (OOP) principles to provide a modular, extensible, and maintainable solution. The use of OOP concepts enhances the clarity of the code and facilitates the implementation of complex mathematical expressions.

### 1. **Abstraction through Classes and Inheritance:**

The program defines a hierarchy of classes for AST nodes, encapsulating different types of nodes with a common base class `ASTNode`. This abstraction allows the representation of various elements in an arithmetic expression (constants, variables, unary, and binary operations) in a unified manner. Subclasses like `Constant`, `Identifier`, `Unary`, and `Binary` extend the functionality while inheriting common attributes and behaviors.

### 2. **Encapsulation:**

Each AST node class encapsulates its specific behavior and properties. For example:

- The `Constant` class encapsulates the value of a constant.
- The `Identifier` class encapsulates the handling of variables through a static variable table.
- The `Unary` and `Binary` classes encapsulate the structure of unary and binary operations, respectively.

This encapsulation promotes code organization and limits access to internal details, enhancing the program's maintainability.

### 3. **Polymorphism:**

Polymorphism is employed through virtual functions in the `ASTNode` class. The `evaluate` and `getType` functions are declared as virtual, allowing each derived class to provide its implementation. This enables a consistent interface for evaluating and retrieving the type of different AST nodes, simplifying the code that works with these nodes.

### 4. **Dynamic Memory Management:**

Dynamic memory management is utilized through the use of `std::unique_ptr` to represent ownership of AST node pointers. This helps in efficient memory usage and ensures proper memory deallocation when nodes are no longer needed, avoiding memory leaks.

### 5. **Ease of Extension:**

New node types can be easily added by creating subclasses of `Unary` or `Binary` and implementing their specific behaviors. This extensibility allows the program to accommodate additional mathematical operations without significantly modifying the existing codebase.

### 6. **Error Handling and Information Hiding:**

Error handling for undefined variables and division by zero is localized within the `Identifier` and `Divide` classes, respectively. This localized approach enhances information hiding and makes it easier to manage and extend error-handling mechanisms in the future.

In summary, the use of OOP principles in this arithmetic expression evaluator contributes to code organization, maintainability, and extensibility. It provides a foundation for easily incorporating new features, handling different node types, and adapting to evolving requirements in a systematic manner.

## Memory Management

The arithmetic expression evaluator makes deliberate memory management choices to ensure efficient resource usage and proper handling of dynamic memory. The primary memory management features include the use of smart pointers and dynamic memory allocation.

### 1. **Smart Pointers for Ownership:**

The program extensively uses `std::unique_ptr` for managing ownership of dynamically allocated AST nodes. Smart pointers help in:

- **Ownership Transfer:** Each AST node, whether it's a constant, identifier, or operation, is wrapped in a `std::unique_ptr`. This choice ensures that ownership of the nodes is transferred when nodes are moved or released.

- **Automatic Deallocation:** When a `std::unique_ptr` goes out of scope, it automatically deallocates the associated memory. This feature helps prevent memory leaks by ensuring that dynamically allocated nodes are properly released.

```cpp
std::unique_ptr<ASTNode> constantNode = std::make_unique<Constant>(42.0);
```

### 2. **Dynamic Memory Allocation for Flexibility:**

Dynamic memory allocation is utilized for creating AST nodes and managing their lifetime. This approach provides flexibility in handling varying expression complexities and enables the creation of nodes at runtime.

- **Creating Nodes Dynamically:**
  
  ```cpp
  auto addNode = std::make_unique<Add>(
      std::make_unique<Constant>(2.0),
      std::make_unique<Constant>(3.0)
  );
  ```

- **Reducing Resource Consumption:**
  Dynamic memory allocation allows for efficient resource usage, especially when dealing with a large number of nodes in complex expressions. Memory is allocated only for the nodes that are needed.

### 3. **Virtual Destructors for Proper Cleanup:**

The base class `ASTNode` includes a virtual destructor. This ensures that when a derived class object is deleted through a base class pointer, the appropriate derived class destructor is called. This is crucial for proper cleanup of resources, especially when working with polymorphism.

```cpp
virtual ~ASTNode() = default;
```

### 4. **Static Variable Table for Identifier Nodes:**

The `Identifier` class uses a static unordered map (`variableTable`) to store variable values. This design choice allows variable values to persist across multiple instances of `Identifier` nodes. The use of static variables in this context simplifies memory management for variable storage.

```cpp
static std::unordered_map<std::string, double> variableTable;
```

These memory management choices aim to strike a balance between efficiency, flexibility, and proper resource cleanup. Smart pointers and dynamic memory allocation enable the creation and manipulation of complex expression trees while helping prevent common memory-related issues. The use of virtual destructors ensures that resources are released appropriately, contributing to the overall robustness of the program.

## Testing

The provided code includes a test harness for the arithmetic expression evaluator, enabling the verification of the functionality of different AST nodes and expressions. The testing approach is centered around individual components and functionalities of the arithmetic expression evaluator. Each relevant aspect, such as constant nodes, identifier nodes, unary operations, binary operations, and error handling, is tested independently.

### Test Harness Structure

#### 1. **Testing Macro and Assertions:**

The `ASSERT_EQUAL` macro is defined to simplify test assertions. It compares the expected and actual values and outputs the result of the test, printing an error message if the assertion fails. This macro enhances readability and reduces boilerplate code in each test function.

```cpp
#define ASSERT_EQUAL(expected, actual) \
    do { /* ... */ } while (0)
```

#### 2. **Individual Test Functions:**

There are individual test functions for each major component of the AST nodes, such as `testConstant`, `testIdentifier`, `testUnaryPlus`, and so on. These functions instantiate instances of the corresponding AST nodes, perform evaluations, and use assertions to verify the expected outcomes.

```cpp
void testConstant() {
    // ... test logic ...
    ASSERT_EQUAL(expectedValue, actualValue);
}
```

#### 3. **Test Runner Function:**

The `runTests` function invokes each individual test function and prints the result of each test. If all tests pass, a success message is displayed.

```cpp
int runTests() {
    // ... run individual test functions ...
    std::cout << "All tests passed successfully.\n";
    return 0;
}
```

#### 4. **Main Function for Test Execution:**

The `main` function serves as the entry point for executing the tests. If the command-line argument `--run-tests` is provided, the test harness runs. Otherwise, a help message is displayed to guide users on using the program.

```cpp
int main(int argc, char *argv[]) {
    if (argc == 2 && std::strcmp(argv[1], "--run-tests") == 0) {
        // Run tests if --run-tests is specified
        runTests();
    } else {
        // Display help message for usage guidance
        printHelpMessage(argv[0]);
    }
    return 0;
}
```

### Enabling and Disabling Tests

The testing code is conditionally compiled based on the `ENABLE_TESTS` macro. When `ENABLE_TESTS` is defined, the testing-related code is included. This modular approach allows developers to easily enable or disable tests as needed.

### Running Tests

To run the tests, execute the program with the `--run-tests` command-line argument. For example:

```bash
./your_program_name --run-tests
```

This will trigger the execution of the test harness, providing feedback on the success or failure of each individual test.

## Usage

To build the project, run:

```bash
make
```

To run tests, run:

```bash
make test
```

To clean the project, run:

```bash
make clean
```

To clean and rebuild the project, run:

```bash
make rebuild
```

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests. Please follow the existing coding style and provide appropriate test cases for new features.

## License

This program is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute it as per the terms of the license.
