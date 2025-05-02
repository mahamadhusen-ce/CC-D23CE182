#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <cctype>
#include <vector>

using namespace std;

// Function to check if a string is a number
bool isNumber(const string &s) {
    for (char ch : s) {
        if (!isdigit(ch) && ch != '.') return false;
    }
    return true;
}

// Function to perform arithmetic operations
double evaluate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? (a / b) : 0; // Avoid division by zero
        default: return 0;
    }
}

// Operator precedence mapping
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to optimize an arithmetic expression
string optimizeExpression(const string &expr) {
    stringstream ss(expr);
    string token, optimizedExpr = "";
    stack<double> numStack;
    stack<char> opStack;
    stack<string> exprStack;

    while (ss >> token) {
        if (isNumber(token)) {
            numStack.push(stod(token));
            exprStack.push(token);
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(token[0])) {
                double b = numStack.top(); numStack.pop();
                double a = numStack.top(); numStack.pop();
                char op = opStack.top(); opStack.pop();

                double result = evaluate(a, b, op);
                numStack.push(result);

                exprStack.pop();
                exprStack.pop();
                exprStack.push(to_string(result));
            }
            opStack.push(token[0]);
        }
        else {
            optimizedExpr += token + " ";
        }
    }

    while (!opStack.empty()) {
        double b = numStack.top(); numStack.pop();
        double a = numStack.top(); numStack.pop();
        char op = opStack.top(); opStack.pop();

        numStack.push(evaluate(a, b, op));
    }

    if (!numStack.empty()) {
        optimizedExpr += to_string(numStack.top());
    }

    return optimizedExpr;
}

// Main function - Runs multiple test cases
int main() {
    vector<string> testCases = {
        "2 + 3 * 4 - 1",
        "x + (3 * 5) - 2",
        "( 22 / 7 ) * r * r"
    };

    cout << "Running all test cases...\n";
    cout << "==========================\n";

    for (const string &testCase : testCases) {
        cout << "Input: " << testCase << endl;
        cout << "Optimized Output: " << optimizeExpression(testCase) << endl;
        cout << "--------------------------\n";
    }

    return 0;
}
