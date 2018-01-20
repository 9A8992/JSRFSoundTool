#include <iostream>
#include "program.h"

using namespace std;

int main(int argc, char** argv){

    program myJSRFProgram;

    if(argc != 3){
        std::cout << "Incorrect usage. The correct usage is \"JSRFSoundTool [split/join] pv_gum.dat\" (And so on for other sound files)" << std::endl << "Please read the readme for full details." << std::endl;
        exit (EXIT_FAILURE);
    }


    std::string fileName = argv[2];
    std::string command = argv[1];


    if(fileName.substr(0, 3) != "pv_" && fileName.substr(0, 3) != "se_" && fileName.substr(0, 2) != "e_"){
        std::cout << "Incorrect usage. The correct usage is \"JSRFSoundTool [split/join] pv_gum.dat\" (And so on for other sound files)" << std::endl << "Please read the readme for full details." << std::endl;
        exit (EXIT_FAILURE);

    }
    else if(fileName.substr(fileName.size() - 4, fileName.size()) != ".dat"){
        std::cout << "Incorrect usage. The correct usage is \"JSRFSoundTool [split/join] pv_gum.dat\" (And so on for other sound files)" << std::endl << "Please read the readme for full details." << std::endl;
        exit (EXIT_FAILURE);    }



    if(command == "split"){
            myJSRFProgram.runJSRFToWav(fileName);
        }
    else if(command == "join"){
            myJSRFProgram.runWavToJSRF(fileName);
        }

    return 0;
}
