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
private:
    std::string dllFolderPath;
    std::map<std::string, double(*)(double)> loadedFunctions;
};

#endif