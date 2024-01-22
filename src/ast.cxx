#include "ast.hxx"
#include <cstring>

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

    // Expected result: (2 * (3 + 1)) / (5 - 1) ^ (2 + 1) = 8 / 4 ^ 3 = 8 / 64 = 0.125
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
              << "              This option should be used without any additional arguments.\n"
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
