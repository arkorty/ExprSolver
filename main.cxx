#include <cmath>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

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
    virtual ~ASTNode() {}
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
    const ASTNode *operand;

  public:
    // Constructor for Unary node.
    explicit Unary(const ASTNode *operand) : operand(operand) {}

    // Implementation of getType for Unary node.
    ASTNode::Type getType() const override { return ASTNode::Type::Unary; }

    // Virtual destructor for Unary node.
    virtual ~Unary() { delete operand; }
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
    const ASTNode *left;
    const ASTNode *right;

  public:
    // Constructor for Binary node.
    Binary(const ASTNode *left, const ASTNode *right) : left(left), right(right) {}

    // Implementation of getType for Binary node.
    ASTNode::Type getType() const override { return ASTNode::Type::Binary; }

    // Virtual destructor for Binary node.
    virtual ~Binary() {
        delete left;
        delete right;
    }
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

// Main function
int main() {
    // Setting variables in the variableTable.
    Identifier::setVariable("Num1", 3.0);
    Identifier::setVariable("Num2", 7.0);

    // Creating an expression tree.
    ASTNode *expression = new Add(new UnaryMinus(new Identifier("Num1")),
                                  new Multiply(new Constant(2), new Subtract(new Constant(4), new Identifier("Num2"))));

    // Evaluating the expression and printing the result.
    double result = expression->evaluate();
    std::cout << "Result: " << result << std::endl;

    // Deleting the expression and clearing variables.
    delete expression;
    Identifier::clearVariables();

    return 0;
}
