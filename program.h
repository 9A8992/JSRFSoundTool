#ifndef PROGRAM_H
#define PROGRAM_H


#include <string>
#include <iostream>
#include <fstream>
#include <vector>



enum class ChunkType {HEADER, WAVFILE, SPACER};

//Data chunks for parsing
struct chunk{
    int filePos;    //Not actually neccissary after all
    std::vector<unsigned char> chunkContents;
    ChunkType type;

};


class program{
public:
    program();
     void runJSRFToWav(std::string path);
     void runWavToJSRF(std::string path);

private:


    void load();
    void decode();
    void parse();
    void listType(int number);
    void writeAll(); //Debug Only
    void replace();
    void writeJSRF();

    long long int nFileSize = 0;
    int nTotalWav = 0;

    std::vector<unsigned char> nJSRFFileContents;
    std::vector<unsigned char> nNewJSRFFile;

    std::vector<chunk> nChunks;
    std::vector<chunk> nNewWav;


    std::string nPath = "default";
    std::string nReplacePath = "default";




};

#endif // PROGRAM_H
