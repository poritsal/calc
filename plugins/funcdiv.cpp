#include <stdexcept>

extern "C" __declspec(dllexport)

double addFunction2Operators(double firstOperand, double secondOperand) {
    if (firstOperand == 0) {
        throw std::runtime_error("Division by zero is not allowed.");
    }
    return secondOperand / firstOperand;
}
