#include "DllReader.h"
#include <exception>
#include <stdexcept>

DllReader::DllReader(const std::string& folderPath) {
    WIN32_FIND_DATAA detection;
    dllFolderPath = folderPath;
    HANDLE detect = FindFirstFileA((dllFolderPath + std::string("*.dll")).c_str(), &detection);
    if (detect == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("DLL files not found in the specified directory.");
    }
    else {
        do {
            std::string dllFileName(detection.cFileName);
            HMODULE dllHandle = LoadLibraryA((dllFolderPath + dllFileName).c_str());
            if (!dllHandle) throw std::exception();

            std::string functionName = dllFileName.substr(0, dllFileName.find(".dll"));

            auto functionPtr = (double(*)(double))GetProcAddress(dllHandle, "addFunction");

            if (functionPtr) {
                loadedFunctions.insert(std::pair<std::string, double(*)(double)>(functionName, functionPtr));
            }
            else {
                throw std::exception();
            }
        } while (FindNextFileA(detect, &detection) != NULL);
    }
}

double DllReader::executeFunction(std::string functionName, double input) {
    return loadedFunctions["func" + functionName](input);
}

bool DllReader::isFunctionAvailable(std::string functionName) {
    return (loadedFunctions.find("func" + functionName) != loadedFunctions.end());
}
