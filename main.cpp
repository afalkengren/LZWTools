#include <iostream>
#include <fstream>
#include "lzwCompress.h"

int main()
{
    std::string inputName;
    std::ifstream inputFile;
    do {
        std::cout << "Input file: ";
        std::cin >> inputName;
        inputFile.open(inputName, std::fstream::binary);
    }while(!inputFile.is_open());
    std::ofstream outputFile(inputName + "_decoded.txt");
    outputFile << lzwTools::decompressFixedWidth(12, inputFile);

    inputFile.close();
    outputFile.close();

    return 0;
}