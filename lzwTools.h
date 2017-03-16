//
// Created by Alex on 14-Mar-17.
//

#ifndef LZW_LZWCOMPRESS_H
#define LZW_LZWCOMPRESS_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>

class lzwTools
{
public:
    // decompresses LZW encoded string with fixed bit width
    // bit width, input file stream, strictParsing-> true=throw exception if code is unknown, false=ignore
    static std::string decompressFixedWidth(size_t width, std::ifstream &inputFile, bool strictParsing=true);
};

#endif //LZW_LZWCOMPRESS_H
