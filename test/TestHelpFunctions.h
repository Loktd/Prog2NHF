#include <iostream>
#include <string>

void clearFileContent(const std::string& fileName) {
    std::ofstream file;
    file.open(fileName, std::ostream::out | std::ostream::trunc);
    file.close();
}