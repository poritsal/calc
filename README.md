# Calculator with support for custom plugins
This project is a simple calculator written in C++, with the possibility of using custom plugins to expand its functionality.
# Creating custom plugins
You can create custom plugins to extend the functionality of the calculator. Here's how to do it:
1. Create a new file with the function you want to add and export it. For example, funcplugin.cpp:
'''cpp
#include <cmath>

extern "C" __declspec(dllexport)
double addFunction(double number) {
    // function code
    return result;
}
2. Compile this file as a DLL using your development environment.
3. Place the resulting DLL file in the plugins directory at the root of the project.
4. Restart the calculator and your function will be available for use.
