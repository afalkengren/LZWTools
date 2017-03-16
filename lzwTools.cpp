//
// Created by Alex on 14-Mar-17.
//
#include "lzwTools.h"

std::string lzwTools::decompressFixedWidth(size_t width, std::ifstream &inputFile, bool strictParsing)
{
    // initialize dictionary. we know the size so use a fixed size vector to avoid fragmentation
    std::vector<std::string> dict(static_cast<unsigned>(pow(2, width)));
    unsigned dictSize = 255;
    for (int i=0; i<256; ++i){
        dict[i] = std::string(1, static_cast<char>(i));
    }

    std::string prevConj = "";      // conjecture for next dictionary entry
    std::string outputStr = "";     // final string
    unsigned prevBufferSize = 0;    // size of unused bits from last iteration
    unsigned prevBuffer = 0;        // buffer for unused bits
    std::vector<char> readBuffer(static_cast<unsigned>(ceil(width/8.0))); // max bytes we need to store one code

    while(inputFile.peek() != EOF) {

        unsigned bytesNeeded = ceil( (width-prevBufferSize) /8.0);    // how many bytes do we need to read
        for (unsigned i = 0; i < bytesNeeded; ++i) {
            char c;
            if (inputFile.get(c)) {
                readBuffer[i] = c;
            } else {
                throw "Invalid encoding";
            }
        }

        unsigned curCode = 0;

        // if not last byte, process as normal
        if(inputFile.peek() != EOF) {

            curCode = prevBuffer << (width - prevBufferSize);     // add unused bits from buffer
            unsigned leftOver = (width - prevBufferSize) % 8;   // how many bits do we need from the last byte
            if (leftOver == 0) leftOver = 8;    // if there is no leftover, we need all 8

            for (unsigned i = 0; i < bytesNeeded; ++i) {
                int shiftVal = (bytesNeeded - i - 2)*8 + leftOver;
                if (shiftVal >= 0)  // negative shifts are unfortunately undefined, so manually do it
                    curCode += static_cast<unsigned char>(readBuffer[i]) << shiftVal;
                else
                    curCode += static_cast<unsigned char>(readBuffer[i]) >> -shiftVal;
            }

            // keep the unused bits in a buffer
            prevBufferSize = 8 - leftOver;
            prevBuffer = static_cast<unsigned char>(readBuffer[bytesNeeded - 1])
                            % static_cast<unsigned>(pow(2, prevBufferSize)); // keep unused bits
        }
        else{   // if it's end of file, then we need to pad the current code
            curCode = prevBuffer << bytesNeeded*8;
            for (unsigned i = 0; i < bytesNeeded; ++i) {
                curCode += static_cast<unsigned char>(readBuffer[i]) << (bytesNeeded-i-1)*8;
            }
        }

        if(dictSize >= pow(2,width)-1)    // we can only have 2^width - 1 dictionary entries
            dictSize = 255;

        // since decoder is one entry behind encoder, we can predict the next code as the prev entry + its first letter
        if(!prevConj.empty()){
            dict[dictSize] = (++dictSize == curCode) ? prevConj+prevConj[0] : prevConj+dict[curCode][0];
        }
        prevConj = dict[curCode];

        if (curCode <= dictSize){
            outputStr += dict[curCode];
        }
        else{
            if(strictParsing)
                throw "Error. Invalid encoding";
            else
                fprintf(stderr, "Failed to get dict entry: requested entry %d, but size is %d\n", curCode, dictSize );
        }

    }
    return outputStr;
}