#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;

// Structure to represent a quadruple
struct Quadruple {
    string op;
    string arg1;
    string arg2;
    string result;
};

vector<Quadruple> quadruples;
int tempCount = 1;  // To generate temporary variables like t1, t2, t3...

// Function to generate a new temporary variable
string newTemp() {
    return "t" + to_string(tempCount++);
}

// Function to print the quadruple table
void printQuadruples() {
    cout << "Operator\tOperand 1\tOperand 2\tResult" << endl;
    for (const auto& quad : quadruples) {
        cout << quad.op << "\t" << quad.arg1 << "\t" << quad.arg2 << "\t" << quad.result << endl;
    }
}

// Function to parse and evaluate the expression according to the grammar
string parseFactor(const string& expr, int& index);
string parseTerm(const string& expr, int& index);
string parseExpression(const string& expr, int& index);

// Function to handle parsing of a factor (F → (E) | digit)
string parseFactor(const string& expr, int& index) {
    if (expr[index] == '(') {  // If it's an opening parenthesis, parse the expression inside it
        index++;  // Skip '('
        string result = parseExpression(expr, index);
        if (expr[index] == ')') {
            index++;  // Skip ')'
        } else {
            cerr << "Error: Expected closing parenthesis\n";
        }
        return result;
    } else if (isdigit(expr[index]) || expr[index] == '.') {  // If it's a digit, return it as a literal operand
        string operand = "";
        while (isdigit(expr[index]) || expr[index] == '.') {  // Handle decimal numbers too
            operand += expr[index++];
        }
        return operand;
    }
    return "";
}

// Function to handle parsing of terms (T → T * F | T / F | F)
string parseTerm(const string& expr, int& index) {
    string result = parseFactor(expr, index);  // Start by parsing a factor
    while (expr[index] == '*' || expr[index] == '/') {  // Look for * or /
        char op = expr[index++];
        string operand2 = parseFactor(expr, index);  // Parse another factor
        string temp = newTemp();
        quadruples.push_back({string(1, op), result, operand2, temp});  // Generate a quadruple for the operation
        result = temp;  // The result of the operation becomes the new result
    }
    return result;
}

// Function to handle parsing of expressions (E → E + T | E – T | T)
string parseExpression(const string& expr, int& index) {
    string result = parseTerm(expr, index);  // Start by parsing a term
    while (expr[index] == '+' || expr[index] == '-') {  // Look for + or -
        char op = expr[index++];
        string operand2 = parseTerm(expr, index);  // Parse another term
        string temp = newTemp();
        quadruples.push_back({string(1, op), result, operand2, temp});  // Generate a quadruple for the operation
        result = temp;  // The result of the operation becomes the new result
    }
    return result;
}

// Function to evaluate the expression and generate the quadruple table
void evaluateExpression(const string& expr) {
    int index = 0;
    while (index < expr.length() && (expr[index] == ' ' || expr[index] == '\t')) {
        index++;  // Skip whitespace
    }
    parseExpression(expr, index);  // Parse the expression starting from index 0
}

// Main function
int main() {
    vector<string> testCases = {
        "9 + 42 * 8",
        "5 + 6 - 3",
        "7 - (8 * 2)",
        "(9 - 3) + (5 * 4 / 2)",
        "(3 + 5 * 2 - 8) / 4 - 2 + 6",
        "86 / 2 / 3"
    };

    // Process each test case
    for (const auto& expr : testCases) {
        cout << "Evaluating expression: " << expr << endl;
        quadruples.clear();  // Clear the previous quadruples
        evaluateExpression(expr);
        printQuadruples();
        cout << "---------------------------\n";
    }

    return 0;
}
