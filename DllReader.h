#ifndef DLL_READER_H
#define DLL_READER_H

#include <string>
#include <map>
#include <Windows.h>

class DllReader {
public:
    DllReader(const std::string& folderPath);
    double executeFunction(std::string functionName, double input);
    bool isFunctionAvailable(std::string functionName);
    double executeFunction2Operators(std::string functionName, double firstOperand, double secondOperand);
    bool isFunctionAvailable2Operators(std::string functionName);
private:
    std::string dllFolderPath;
    std::map<std::string, double(*)(double)> loadedFunctions;
    std::map<std::string, double(*)(double, double)> loadedFunctions2Operators;
};

#endif