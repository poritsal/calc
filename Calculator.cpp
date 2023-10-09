#include "Calculator.h"
#include <cmath>
#include <exception>
#include <stdexcept>

Calculator::Calculator(const std::string& dllFolderPath) : reader(dllFolderPath) {
    operatorPriorities = {
        {"+", 0},
        {"-", 0},
        {"*", 1},
        {"/", 1},
        {"^", 2}
    };

    operatorToName = {
    {"+", "add"},
    {"-", "sub"},
    {"*", "mult"},
    {"/", "div"},
    {"^", "deg"}
    };
}

bool Calculator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

std::vector<std::string> Calculator::standardizeExpression(const std::string& expression) {
    std::vector<std::string> result;
    std::string currentToken;
    char previousChar = '(';

    for (char currentChar : expression) {
        if (previousChar == '(' && currentChar == '-') {
            result.push_back("0");
            result.push_back(std::string(1, currentChar));
            previousChar = currentChar;
        }
        else if (isOperator(currentChar) || currentChar == '(' || currentChar == ')') {
            if (!currentToken.empty()) {
                result.push_back(currentToken);
                currentToken.clear();
            }
            result.push_back(std::string(1, currentChar));
        }
        else if (std::isdigit(currentChar) || currentChar == '.') {
            currentToken.push_back(currentChar);
            previousChar = currentChar;
        }
        else if (std::isalpha(currentChar)) {
            currentToken.push_back(currentChar);
            previousChar = currentChar;
        }
        else if (std::isspace(currentChar)) {
            previousChar = currentChar;
        }
        else {
            throw std::invalid_argument("Invalid character in expression");
        }
    }

    if (!currentToken.empty()) {
        result.push_back(currentToken);
    }

    return result;

}

void Calculator::executeBinaryOperator(const std::string& operatorName) {
    double firstOperand = numbersStack.top();
    numbersStack.pop();
    double secondOperand = numbersStack.top();
    numbersStack.pop();

    if (reader.isFunctionAvailable2Operators(operatorName)) {
        double result = reader.executeFunction2Operators(operatorName, firstOperand, secondOperand);
        numbersStack.push(result);
    }
    else {
        throw std::runtime_error("Invalid input: " + operatorName);
    }
}

void Calculator::executeUnaryFunction(const std::string& functionName) {
    if (reader.isFunctionAvailable(functionName)) {
        double firstOperand = numbersStack.top();
        numbersStack.pop();
        double result = reader.executeFunction(functionName, firstOperand);
        numbersStack.push(result);
    }
    else {
        throw std::runtime_error("Invalid input: " + functionName);
    }
}

void Calculator::performStep() {
    std::string currentOperator = operatorsStack.top();
    operatorsStack.pop();

    if (isStandardFunction(currentOperator)) {
        switch (currentOperator[0])
        {
        case '+':
            executeBinaryOperator(operatorToName[currentOperator]);
            return;
        case '-':
            executeBinaryOperator(operatorToName[currentOperator]);
            return;
        case '*':
            executeBinaryOperator(operatorToName[currentOperator]);
            return;
        case '/':
            executeBinaryOperator(operatorToName[currentOperator]);
            return;
        case '^':
            executeBinaryOperator(operatorToName[currentOperator]);
            return;
        default:
            throw std::runtime_error("Unexpected behavior");
            return;
        }
    }

    executeUnaryFunction(currentOperator);
}

bool Calculator::isNumber(const std::string& str) {
    for (char ch : str) {
        if (!std::isdigit(ch) && ch != '.') {
            return false;
        }
    }
    return true;
}

bool Calculator::isStandardFunction(const std::string& str) {
    return (operatorPriorities.find(str) != operatorPriorities.end());
}

double Calculator::calculateExpression(const std::string& expression) {
    numbersStack = std::stack<double>();
    operatorsStack = std::stack<std::string>();
    std::vector<std::string> buffer = standardizeExpression(expression);
    for (size_t i = 0; i < buffer.size(); i++)
    {
        if (isNumber(buffer[i])) {
            numbersStack.push(std::stod(buffer[i]));
        }
        else {
            if (operatorsStack.empty()) {
                operatorsStack.push(buffer[i]);
                continue;
            }

            if (buffer[i] == ")") {
                while (operatorsStack.top() != "(") {
                    performStep();
                }
                operatorsStack.pop();
                continue;
            }

            if (buffer[i] == "(") {
                operatorsStack.push(buffer[i]);
                continue;
            }

            if (!isStandardFunction(buffer[i])) {
                operatorsStack.push(buffer[i]);
                continue;
            }

            while (!operatorsStack.empty() && operatorsStack.top() != "(" && !isStandardFunction(operatorsStack.top())) {
                performStep();
            }

            while (!operatorsStack.empty() && operatorsStack.top() != "(" && operatorPriorities[buffer[i]] <= operatorPriorities[operatorsStack.top()]) {
                performStep();
            }

            operatorsStack.push(buffer[i]);
        }
    }

    while (!operatorsStack.empty()) {
        performStep();
    }

    return numbersStack.top();
}