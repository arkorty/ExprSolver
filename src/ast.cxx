#include "ast.hxx"
#include <cstring>

#ifdef ENABLE_TESTS

// Static initialization of variableTable in Identifier class.
std::unordered_map<std::string, double> Identifier::variableTable;

// Include the header file with ASTNode classes here

#define ASSERT_EQUAL(expected, actual)                                                                                 \
    do {                                                                                                               \
        if ((expected) != (actual)) {                                                                                  \
            std::cerr << "Test: " << #actual << " ... Failed at line " << __LINE__ << " (expected: " << (expected)     \
                      << " but got " << (actual) << ").\n";                                                            \
            std::exit(1);                                                                                              \
        } else {                                                                                                       \
            std::cout << "Test: " << #actual << " ... Passed.\n";                                                      \
        }                                                                                                              \
    } while (0)

// Test Constant Node
void testConstant() {
    Constant constantNode(5.0);
    ASSERT_EQUAL(5.0, constantNode.evaluate());
}

// Test Identifier Node
void testIdentifier() {
    Identifier::setVariable("x", 10.0);
    Identifier identifierNode("x");
    ASSERT_EQUAL(10.0, identifierNode.evaluate());
}

// Test UnaryPlus Node
void testUnaryPlus() {
    Constant constantNode(7.0);
    UnaryPlus unaryPlusNode(std::make_unique<Constant>(constantNode));
    ASSERT_EQUAL(7.0, unaryPlusNode.evaluate());
}

// Test UnaryMinus Node
void testUnaryMinus() {
    Constant constantNode(8.0);
    UnaryMinus unaryMinusNode(std::make_unique<Constant>(constantNode));
    ASSERT_EQUAL(-8.0, unaryMinusNode.evaluate());
}

// Test Add Node
void testAdd() {
    Constant constantNode1(3.0);
    Constant constantNode2(4.0);
    Add addNode(std::make_unique<Constant>(constantNode1), std::make_unique<Constant>(constantNode2));
    ASSERT_EQUAL(7.0, addNode.evaluate());
}

// Test Subtract Node
void testSubtract() {
    Constant constantNode1(9.0);
    Constant constantNode2(5.0);
    Subtract subtractNode(std::make_unique<Constant>(constantNode1), std::make_unique<Constant>(constantNode2));
    ASSERT_EQUAL(4.0, subtractNode.evaluate());
}

// Test Multiply Node
void testMultiply() {
    Constant constantNode1(2.0);
    Constant constantNode2(6.0);
    Multiply multiplyNode(std::make_unique<Constant>(constantNode1), std::make_unique<Constant>(constantNode2));
    ASSERT_EQUAL(12.0, multiplyNode.evaluate());
}

// Test Divide Node
void testDivide() {
    Constant constantNode1(8.0);
    Constant constantNode2(2.0);
    Divide divideNode(std::make_unique<Constant>(constantNode1), std::make_unique<Constant>(constantNode2));
    ASSERT_EQUAL(4.0, divideNode.evaluate());
}

// Test Power Node
void testPower() {
    Constant constantNode1(2.0);
    Constant constantNode2(3.0);
    Power powerNode(std::make_unique<Constant>(constantNode1), std::make_unique<Constant>(constantNode2));
    ASSERT_EQUAL(8.0, powerNode.evaluate());
}

// Additional tests for Identifier with undefined variable
void testIdentifierUndefinedVariable() {
    Identifier::clearVariables(); // Clear variables to make sure 'y' is undefined
    Identifier identifierNode("y");
    ASSERT_EQUAL(0.0, identifierNode.evaluate());
    // Note: The error message is not captured in this simple example.
}

int runTests() {
    // Run the tests
    testConstant();
    testIdentifier();
    testUnaryPlus();
    testUnaryMinus();
    testAdd();
    testSubtract();
    testMultiply();
    testDivide();
    testPower();
    testIdentifierUndefinedVariable();

    std::cout << "All tests passed successfully.\n";

    return 0;
}

#endif // ENABLE_TESTS

// Function to print the help message.
void printHelpMessage(const char *programName) {
    std::cout << "Usage: " << programName << " [--run-tests]\n"
              << "Options:\n"
              << "  --run-tests  Run the test for the expression evaluation code.\n"
              << "              This option should be used without any additional "
                 "arguments.\n"
              << "              Example: " << programName << " --run-tests\n";
}

// Main function
int main(int argc, char *argv[]) {
    // Check if the "--run-tests" argument is provided
    if (argc == 2 && std::strcmp(argv[1], "--run-tests") == 0) {
#ifdef ENABLE_TESTS
        // Run the test if ENABLE_TESTS is defined
        runTests();
#endif // ENABLE_TESTS
    } else {
        // Print help message if no valid arguments are provided
        printHelpMessage(argv[0]);
    }

    return 0;
}
