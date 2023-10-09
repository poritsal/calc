#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <map>
#include <functional>
#include <string>
#include <stack>
#include "DllReader.h"

class Calculator {
public:
    Calculator(const std::string& dllFolderPath);
    double calculateExpression(const std::string& expression);
private:
    std::stack<double> numbersStack;
    std::stack<std::string> operatorsStack;
    std::map<std::string, int> operatorPriorities;
    std::map<std::string, std::string> operatorToName;
    DllReader reader;

    std::vector<std::string> standardizeExpression(const std::string& expression);
    bool isOperator(char c);
    void executeBinaryOperator(const std::string& operatorName);
    void executeUnaryFunction(const std::string& functionName);
    void performStep();
    bool isNumber(const std::string& str);
    bool isStandardFunction(const std::string& str);
};

#endif
