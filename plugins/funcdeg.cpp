#include <cmath>

extern "C" __declspec(dllexport)

double addFunction2Operators(double firstOperand, double secondOperand) {
	return pow(secondOperand,firstOperand);
}