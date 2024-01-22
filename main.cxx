// Include necessary C++ standard library headers.
#include <cmath>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>

// Conditional compilation based on ENABLE_TESTS macro.
#ifdef ENABLE_TESTS
#include <cassert>
#endif

// Abstract Syntax Tree (AST) Node base class
class ASTNode {
  public:
    // Enumeration defining different types of AST nodes.
    enum class Type {
        Constant,   // Represents a constant numerical value.
        Identifier, // Represents a variable identifier.
        Unary,      // Represents a unary operation.
        UnaryPlus,  // Represents a unary plus operation.
        UnaryMinus, // Represents a unary minus operation.
        Binary,     // Represents a binary operation.
        Add,        // Represents an addition operation.
        Subtract,   // Represents a subtraction operation.
        Multiply,   // Represents a multiplication operation.
        Divide,     // Represents a division operation.
        Power       // Represents a power/exponentiation operation.
    };

    // Virtual functions for evaluation and type retrieval.
    virtual double evaluate() const = 0;
    virtual ASTNode::Type getType() const = 0;
    virtual ~ASTNode() = default;
};

// Constant Node class
class Constant : public ASTNode {
  private:
    double value;

  public:
    // Constructor for Constant node.
    explicit Constant(double val) : value(val) {}

    // Implementation of getType for Constant node.
    ASTNode::Type getType() const override { return ASTNode::Type::Constant; }

    // Implementation of evaluate for Constant node.
    double evaluate() const override { return value; }

    // Getter function for the constant value.
    double getValue() const { return value; }
};

// Identifier Node class
class Identifier : public ASTNode {
  private:
    std::string identifier;
    static std::unordered_map<std::string, double> variableTable;

  public:
    // Constructor for Identifier node.
    explicit Identifier(const std::string &id) : identifier(id) {}

    // Implementation of getType for Identifier node.
    ASTNode::Type getType() const override { return ASTNode::Type::Identifier; }

    // Implementation of evaluate for Identifier node.
    double evaluate() const override {
        try {
            return variableTable.at(identifier);
        } catch (const std::out_of_range) {
            std::cerr << "Error: Undefined variable '" << identifier << ".'\n";
            return 0.0;
        }
    }

    // Static function to set a variable in the variableTable.
    static void setVariable(const std::string &id, double value) { variableTable[id] = value; }

    // Static function to clear all variables in the variableTable.
    static void clearVariables() { variableTable.clear(); }
};

// Unary Node base class
class Unary : public ASTNode {
  protected:
    std::unique_ptr<const ASTNode> operand;

  public:
    // Constructor for Unary node.
    explicit Unary(std::unique_ptr<const ASTNode> operand) : operand(std::move(operand)) {}

    // Implementation of getType for Unary node.
    ASTNode::Type getType() const = 0;

    // Getter function to access the operand.
    const ASTNode &getInput() { return *operand; }

    // Function to release ownership of the operand.
    std::unique_ptr<const ASTNode> releaseInput() { return std::move(operand); }

    // Virtual destructor for Unary node.
    virtual ~Unary() = default;
};

// UnaryPlus Node class
class UnaryPlus : public Unary {
  public:
    using Unary::Unary;

    // Implementation of getType for UnaryPlus node.
    ASTNode::Type getType() const override { return ASTNode::Type::UnaryPlus; }

    // Implementation of evaluate for UnaryPlus node.
    double evaluate() const override { return operand->evaluate(); }
};

// UnaryMinus Node class
class UnaryMinus : public Unary {
  public:
    using Unary::Unary;

    // Implementation of getType for UnaryMinus node.
    ASTNode::Type getType() const override { return ASTNode::Type::UnaryMinus; }

    // Implementation of evaluate for UnaryMinus node.
    double evaluate() const override { return -operand->evaluate(); }
};

// Binary Node base class
class Binary : public ASTNode {
  protected:
    std::unique_ptr<const ASTNode> left;
    std::unique_ptr<const ASTNode> right;

  public:
    // Constructor for Binary node.
    Binary(std::unique_ptr<const ASTNode> left, std::unique_ptr<const ASTNode> right)
        : left(std::move(left)), right(std::move(right)) {}

    // Getter functions to access left and right operands.
    const ASTNode &getLeft() { return *left; }
    const ASTNode &getRight() { return *right; }

    // Functions to release ownership of left and right operands.
    std::unique_ptr<const ASTNode> releaseLeft() { return std::move(left); }
    std::unique_ptr<const ASTNode> releaseRight() { return std::move(right); }

    // Implementation of getType for Binary node.
    ASTNode::Type getType() const override { return ASTNode::Type::Binary; }

    // Virtual destructor for Binary node.
    virtual ~Binary() = default;
};

// Add Node class
class Add : public Binary {
  public:
    using Binary::Binary;

    // Implementation of getType for Add node.
    ASTNode::Type getType() const override { return ASTNode::Type::Add; }

    // Implementation of evaluate for Add node.
    double evaluate() const override { return left->evaluate() + right->evaluate(); }
};

// Subtract Node class
class Subtract : public Binary {
  public:
    using Binary::Binary;

    // Implementation of getType for Subtract node.
    ASTNode::Type getType() const override { return ASTNode::Type::Subtract; }

    // Implementation of evaluate for Subtract node.
    double evaluate() const override { return left->evaluate() - right->evaluate(); }
};

// Multiply Node class
class Multiply : public Binary {
  public:
    using Binary::Binary;

    // Implementation of getType for Multiply node.
    ASTNode::Type getType() const override { return ASTNode::Type::Multiply; }

    // Implementation of evaluate for Multiply node.
    double evaluate() const override { return left->evaluate() * right->evaluate(); }
};

// Divide Node class
class Divide : public Binary {
  public:
    using Binary::Binary;

    // Implementation of getType for Divide node.
    ASTNode::Type getType() const override { return ASTNode::Type::Divide; }

    // Implementation of evaluate for Divide node.
    double evaluate() const override {
        if (right->evaluate() == 0) {
            std::cerr << "Error: Division by zero.\n";
            return INFINITY;
        }
        return left->evaluate() / right->evaluate();
    }
};

// Power Node class
class Power : public Binary {
  public:
    using Binary::Binary;

    // Implementation of getType for Power node.
    ASTNode::Type getType() const override { return ASTNode::Type::Power; }

    // Implementation of evaluate for Power node.
    double evaluate() const override { return std::pow(left->evaluate(), right->evaluate()); }
};

// Static initialization of variableTable in Identifier class.
std::unordered_map<std::string, double> Identifier::variableTable;

#ifdef ENABLE_TESTS
// Function to run a test expression evaluation.
void runTest() {
    // Test with a complex expression: (2 * (a + b)) / (c - 1) ^ (d + 1)
    Identifier::setVariable("a", 3.0);
    Identifier::setVariable("b", 1.0);
    Identifier::setVariable("c", 5.0);
    Identifier::setVariable("d", 2.0);

    std::unique_ptr<const ASTNode> variableA = std::make_unique<Identifier>("a");
    std::unique_ptr<const ASTNode> variableB = std::make_unique<Identifier>("b");
    std::unique_ptr<const ASTNode> variableC = std::make_unique<Identifier>("c");
    std::unique_ptr<const ASTNode> variableD = std::make_unique<Identifier>("d");

    std::unique_ptr<const ASTNode> expression = std::make_unique<Divide>(
        std::make_unique<Multiply>(std::make_unique<Constant>(2.0),
                                   std::make_unique<Add>(std::move(variableA), std::move(variableB))),
        std::make_unique<Power>(std::make_unique<Subtract>(std::move(variableC), std::make_unique<Constant>(1.0)),
                                std::make_unique<Add>(std::move(variableD), std::make_unique<Constant>(1.0))));

    // Evaluate the expression
    double result = expression->evaluate();

    // Expected result: (2 * (3 + 1)) / (5 - 1) ^ (2 + 1) = 8 / 4 ^ 3 = 8 / 64 =
    // 0.125
    assert(result == 0.125);

    std::cout << "Test passed successfully. Result: " << result << std::endl;

    // Clear variables for the next test
    Identifier::clearVariables();
}
#endif // ENABLE_TESTS

// Function to print the help message.
void printHelpMessage(const char *programName) {
    std::cout << "Usage: " << programName << " [--run-test]\n"
              << "Options:\n"
              << "  --run-test  Run the test for the expression evaluation code.\n"
              << "              This option should be used without any additional "
                 "arguments.\n"
              << "              Example: " << programName << " --run-test\n";
}

// Main function
int main(int argc, char *argv[]) {
    // Check if the "--run-test" argument is provided
    if (argc == 2 && std::strcmp(argv[1], "--run-test") == 0) {
#ifdef ENABLE_TESTS
        // Run the test if ENABLE_TESTS is defined
        runTest();
#endif // ENABLE_TESTS
    } else {
        // Print help message if no valid arguments are provided
        printHelpMessage(argv[0]);
    }

    return 0;
}
