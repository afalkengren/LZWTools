//
// Created by Alex on 14-Mar-17.
//

#ifndef LZW_LZWCOMPRESS_H
#define LZW_LZWCOMPRESS_H

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>


class lzwTools
{
public:
    // decompresses LZW encoded string with fixed bit width
    static std::string decompressFixedWidth(size_t width, std::ifstream &inputFile);
};

#endif //LZW_LZWCOMPRESS_H
