#include <cmath>
#include <stdexcept>

extern "C" __declspec(dllexport)

double addFunction(double number) {
    if (number < 0) {
        throw std::runtime_error("The factorial is not defined for negative numbers.");
    }

    return std::tgamma(number + 1);
}