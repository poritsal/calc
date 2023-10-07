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
    std::map<std::string, std::function<double(double, double)>> operationFunctions;
    DllReader reader;

    std::vector<std::string> standardizeExpression(const std::string& expression);
    bool isOperator(char c);
    void performStep();
    bool isNumber(const std::string& str);
    bool isStandardFunction(const std::string& str);
    void clearStack(std::stack<double>& stack);
    void clearStack(std::stack<std::string>& stack);
};

#endif
