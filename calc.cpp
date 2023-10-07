#include "Calculator.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "Welcome to the Calculator!" << std::endl;
    std::cout << "Enter 'back' to exit." << std::endl;
    //Enter the custom DLL folder path (f.e. D:\\AppVS\\calc\\plugins\\)
    std::string customDllFolderPath = "D:\\AppVS\\calc\\plugins\\";
    Calculator calculator(customDllFolderPath);

    while (true) {
        std::string input;
        std::cout << "Enter an expression: ";
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Empty input. Please enter an expression." << std::endl;
            continue;
        }

        if (input == "back") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }

        try {
            double result = calculator.calculateExpression(input);
            std::cout << "Result: " << result << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Runtime error: " << e.what() << std::endl;
        }
    }
}
