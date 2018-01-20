#include "program.h"

program::program(){

}

void program::runJSRFToWav(std::string path){
    nPath = path;
    load(); //Loads JSRF SE.dat
    parse(); //Parses it
    decode(); //writes the wav files
}

void program::runWavToJSRF(std::string path){
    nPath = path;
    load();  //Loads JSRF SE.dat
    parse();  //Parses it
    replace(); //loads the User's wavs and replaces the JSRF wavs in memory
    writeJSRF(); //Writes the new JSRF File
}

void program::decode(){
    //Writes JSRF Wav files to Disk

    int TotalWav = 0;
    for (int i = 0; i < nChunks.size(); i++){
        if (nChunks.at(i).type == ChunkType::WAVFILE){
            TotalWav++;
        }
    }

    std::cout << "Total Wav Files: " << TotalWav << std::endl;

    int wavCounter = 0;
    std::string wavFileName;
    std::string wavFileNumber;
    for (int i = 0; i < nChunks.size(); i++){
        if (nChunks.at(i).type == ChunkType::WAVFILE){
            wavCounter++;


            wavFileName = "WavOutput/" + nPath.substr(0, nPath.length() - 4) + "_" + std::to_string(wavCounter) + ".wav";


            std::ofstream JSRFwav(wavFileName, std::ios::out | std::ios::binary);

            if (JSRFwav.fail()){
                std::cout << "unable to create wav file " << wavFileName << std::endl << "Does The folder \"WavOutput\" Exist?" << std::endl;
            }

            //Nested For Loops!
            //There's a better way to do this but ¯\_(ツ)_/¯
            //In fact, there are multiple better ways to do this, invlovling buffers or iterating thigs or whatever
            //BUT IT WORKS
            std::cout << "Writing Chunk " << i << " Wav File # " << wavCounter << " Chunk Type ";
            listType(i);
            std::cout << std::endl;

            for (int b = 0; b < nChunks.at(i).chunkContents.size(); b++){
               JSRFwav.put(nChunks.at(i).chunkContents.at(b));
            }
        }
    }
}

void program::parse(){
    //VERY bad parsing method implimentation
    //Splits the file into chunks for each wav file, and also the JSRF header
    // This function must be called after load()

     //JSRF File header present in all SE files, so it's hardcoded
    std::vector<unsigned char> parser;
    for(int i = 0; i < 32; i++){
        parser.resize(32);
        parser.at(i) = nJSRFFileContents.at(i);
    }    

    nChunks.push_back(*(new chunk));
    nChunks.at(0).type = ChunkType::HEADER;
    nChunks.at(0).filePos = 0;
    nChunks.at(0).chunkContents.resize(32);

    for(int i=0; i < 32; i++){
        nChunks.at(0).chunkContents.at(i) = nJSRFFileContents.at(i);
    }

    nChunks.push_back(*(new chunk));


    ChunkType currentChunkType = ChunkType::WAVFILE;
    int currentChunk = 0;

    bool secondRiff = false;
    bool firstTime = true; //This is a bad fix to make it work the first time Around
    for(int i=0; i < nJSRFFileContents.size() - 32; i++){

        if(nJSRFFileContents.at(i+32) == 'R' && nJSRFFileContents.at(i+33) == 'I' && nJSRFFileContents.at(i+34) == 'F' && nJSRFFileContents.at(i+35) == 'F' && currentChunkType == ChunkType::SPACER && secondRiff == true || firstTime == true){
            currentChunk++;
            currentChunkType = ChunkType::WAVFILE;
            secondRiff = false;         
            firstTime = false;

            nChunks.push_back(*(new chunk));
            nChunks.at(currentChunk).filePos = (i + 20);
            nChunks.at(currentChunk).type = ChunkType::WAVFILE;

        }
        else if(nJSRFFileContents.at(i+32) == 'R' && nJSRFFileContents.at(i+33) == 'I' &&nJSRFFileContents.at(i+34) == 'F' && nJSRFFileContents.at(i+35) == 'F' && currentChunkType == ChunkType::SPACER && secondRiff == false /*&& badfix == false*/){
            secondRiff = true;
        }
        else if(nJSRFFileContents.at(i+32) == 'w' && nJSRFFileContents.at(i+33) == 's' && nJSRFFileContents.at(i+34) == 'm' && nJSRFFileContents.at(i+35) == 'p' && nJSRFFileContents.at(i+36) == '$' && currentChunkType == ChunkType::WAVFILE){

            currentChunk++;
            currentChunkType = ChunkType::SPACER;

            nChunks.push_back(*(new chunk));
            nChunks.at(currentChunk).filePos = (i + 32);
            nChunks.at(currentChunk).type = ChunkType::SPACER;
        }


        nChunks.at(currentChunk).chunkContents.push_back(nJSRFFileContents.at(i + 32));

    }


    std::cout << "Total Chunks: " << nChunks.size() << std::endl;

    for (int i = 0; i < nChunks.size(); i++){
        if (nChunks.at(i).type == ChunkType::WAVFILE){
            nTotalWav++;
        }
    }

    std::cout << "Total Wav Files: " << nTotalWav << std::endl;

    //for(int i =0; i < nChunks.at(1).chunkContents.size(); i++){
 //       std::cout << std::hex << (int) nChunks.at(1).chunkContents.at(i) << " ";
   // }
    // The above bit of code displays one of the loaded files in hex. Was used froe debugging

    for (int i = 0; i < nChunks.size(); i++){
        std::cout << "Chunk number: " << i << " Chunk Type: ";
        listType(i);
        std::cout << std::endl;
    }




}

void program::listType(int number){
    //Debug Feature
    switch(nChunks.at(number).type){
        case ChunkType::HEADER:
            std::cout << " Header ";
        case ChunkType::SPACER:
            std::cout << " Spacer ";
        case ChunkType::WAVFILE:
            std::cout << " Wav file ";
    }

}

void program::writeAll(){
    //Only for debug - Writes all chunks instead of just the Wavs
    int wavCounter = 0;
    std::string wavFileName;
    std::string wavFileNumber;
    for (int i = 0; i < nChunks.size(); i++){
        if (nChunks.at(i).type == ChunkType::WAVFILE){
            wavCounter++;


            wavFileName = nPath.substr(0, nPath.length() - 4) + "_" + std::to_string(i) + ".wav";


            std::ofstream JSRFwav(wavFileName, std::ios::out | std::ios::binary);

            if (JSRFwav.fail()){
                std::cout << "unable to create wav file " << wavFileName << std::endl;
            }

            //Nested For Loops!
            //There's a better way to do this but ¯\_(ツ)_/¯
            //In fact, there are multiple better ways to do this, invlovling buffers or iterating thigs or whatever
            //BUT IT WORKS
            std::cout << "Writing Chunk " << i << " Wav File # " << wavCounter << " Chunk Type ";
            listType(i);
            std::cout << std::endl;

            for (int b = 0; b < nChunks.at(i).chunkContents.size(); b++){
               JSRFwav.put(nChunks.at(i).chunkContents.at(b));
            }

        }
        else{


            wavFileName = nPath.substr(0, nPath.length() - 4) + "_" + std::to_string(i) + ".wa";


            std::ofstream JSRFwav(wavFileName, std::ios::out | std::ios::binary);

            if (JSRFwav.fail()){
                std::cout << "unable to create wav file " << wavFileName << std::endl;
            }

            //Nested For Loops!
            //There's a better way to do this but ¯\_(ツ)_/¯
            //In fact, there are multiple better ways to do this, invlovling buffers or iterating thigs or whatever
            //BUT IT WORKS
            std::cout << "Writing Chunk " << i << "Chunk Type";
            listType(i);
            std::cout << std::endl;

            for (int b = 0; b < nChunks.at(i).chunkContents.size(); b++){
               JSRFwav.put(nChunks.at(i).chunkContents.at(b));
            }

        }
    }
}

void program::replace(){
    //Loads the custom wavs and replaces the JSRF ones in memory
    //Must be called after loading the JSRF File
    nReplacePath = nPath.substr(0, nPath.length() - 4);
    long long int wavFileSize;

    for(int i = 1; i < nTotalWav+1; i++){
        std::string replaceFileName = "WavInput/" + nReplacePath + "_" + std::to_string(i) + ".wav";

        std::ifstream newWavFile(replaceFileName, std::ios::binary | std::ios::ate);
        if(newWavFile.fail()){
            std::cout << "Failed to load wav file " << replaceFileName << "Does the folder \"WavInput\" exist and is the file inside of it?" << std::endl;
        }

        wavFileSize = newWavFile.tellg();
        newWavFile.seekg(0, std::ios::beg);

        nNewWav.push_back(*(new chunk));
        nNewWav.at(i-1).type = ChunkType::WAVFILE;
        nNewWav.at(i-1).chunkContents.resize(wavFileSize);

        newWavFile.read((char*)&nNewWav.at(i-1).chunkContents[0], wavFileSize);

        std::cout << "Sucessfully read wav file " + replaceFileName << std::endl;

        newWavFile.close();
    }

    //Does the actual replacing
    int currentWavNumber = 0; //Iterates nNewWav
    for(int i = 0; i < nChunks.size(); i++){
        if(nChunks.at(i).type == ChunkType::WAVFILE){
            nChunks.at(i).chunkContents = nNewWav.at(currentWavNumber).chunkContents;
            currentWavNumber++;
        }
    }
}

//More nested loops because I'm bad
void program::writeJSRF(){
    for(int i = 0; i < nChunks.size(); i++){
        for(int b = 0; b < nChunks.at(i).chunkContents.size(); b++){
            nNewJSRFFile.push_back(nChunks.at(i).chunkContents.at(b));
        }
    }

    std::string outFileName = "JSRFOutput/" + nReplacePath + ".dat";
    std::ofstream JSRFout(outFileName, std::ios::binary | std::ios::ate);
    if(JSRFout.fail()){
        std::cout << "Failed to create JSRF SE File " << outFileName << std::endl << "Does the \"JSRFOutput\" Folder exist?" << std::endl;
        exit (EXIT_FAILURE);
    }

    for (int i = 0; i < nNewJSRFFile.size(); i++){
       JSRFout.put(nNewJSRFFile.at(i));
    }

    std::cout << "Successfully created JSRF SE File " << outFileName << std::endl;


}




void program::load(){
    //Loads the Original JSRF sound effect/player voice file, at the end of the file to get the size
    std::string JSRFpath = "JSRFInput/" + nPath;
    std::cout << JSRFpath << std::endl;
    std::ifstream JSRFFile(JSRFpath, std::ios::binary | std::ios::ate);

    if (JSRFFile.fail()){
        std::cout << "Failed to load JSRF Sound Effects file: " << nPath << std::endl << "Does the Folder \"JSRFInput\" exist and is the file in it?" << std::endl;
        exit (EXIT_FAILURE);
    }


    //get file size
    nFileSize = JSRFFile.tellg();
    //Go back to beginning of file
    JSRFFile.seekg(0, std::ios::beg);    

    nJSRFFileContents.resize(nFileSize);

    JSRFFile.read((char *)&(nJSRFFileContents[0]), nFileSize);
    JSRFFile.close();

    std::cout << "Loaded file " << nPath<< " Size " << nFileSize << std::endl;

   /* for (int i=0; i < nFileSize; i++){    Outputs the file in hex
        int n;

        if (n > 16){
            std::cout << std::hex << (int) nJSRFFileContents[i] << " " << std::endl;
            n = 0;
        }
        else{
            std::cout << std::hex << (int) nJSRFFileContents[i] << " ";
            n++;
        }
    }
    */



}
