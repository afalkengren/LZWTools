//
// Created by Alex on 14-Mar-17.
//
#include "lzwCompress.h"

std::string lzwTools::decompressFixedWidth(size_t width, std::ifstream &inputFile)
{
    std::unordered_map<unsigned, std::string> dict;

    // initialize dictionary
    for (int i=0; i<256; ++i){
        dict.insert( {i, std::string(1, (char)i)} );
    }

    bool fileEnd = false;
    char byte1, byte2, byte3;
    std::string prevConj = "";   // conjecture for next dictionary entry
    std::string outputStr = "";  // final string
    //every iteration (other than the first) we enter a new entry at i
    for(int i=255; !fileEnd; ++i){
        if (i==1111){
            volatile int e = 9;
        }
        // read 16 bits of data
        if (!inputFile.get(byte1) ){
            break;  // end of file
        }
        if (!inputFile.get(byte2) ){
            throw "Incorrect encoding";
        }
        if (!inputFile.get(byte3) ){
            fileEnd = true;
        }

        if(i > 4095)
            i = 256;

        unsigned code1 = (unsigned char)byte1;
        unsigned code2 = (unsigned char)byte2;

        unsigned curCode = 0;

        if (fileEnd) {
            curCode = code1 >> 4 + code2;
        }
        else {
            curCode = code2 >> 4; // get 4 MSB
            curCode += code1 << 4;
        }

        if(dict.find(curCode) != dict.end()){
            outputStr += dict[curCode];
        }
        else{
            throw "Error. Invalid encoding";
        }

        if(!prevConj.empty()){
            dict[i] = prevConj+dict[curCode][0];
        }
        prevConj = dict[curCode];

        if(!fileEnd){

            if(++i > 4095)
                i = 256;

            unsigned code3 = (unsigned char)byte3;
            curCode = (code2 % 16) << 8;
            curCode += code3;

            if(dict.find(curCode) != dict.end()){
                outputStr += dict[curCode];
            }
            else{
                throw "Error. Invalid encoding";
            }

            if(!prevConj.empty()){
                dict[i] = prevConj+dict[curCode][0];
            }
            prevConj = dict[curCode];
        }
    }
    return outputStr;
}
