#include <cmath>

extern "C" __declspec(dllexport)

double addFunction(double number) {
	return cos(number);
}