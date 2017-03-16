#include <iostream>
#include <fstream>
#include "lzwTools.h"

int main()
{
    std::string inputName;
    std::ifstream inputFile;
    do {
        std::cout << "Input file: ";
        std::cin >> inputName;
        inputFile.open(inputName.c_str(), std::fstream::binary);
    }while(!inputFile.is_open());
    std::ofstream outputFile(std::string(inputName + "_decoded.txt").c_str());
    std::string outputStr = lzwTools::decompressFixedWidth(12, inputFile);
    std::cout << outputStr;
    outputFile << outputStr;

    inputFile.close();
    outputFile.close();

    return 0;
}