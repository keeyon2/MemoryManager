#ifndef Organizer_H
#define Organizer_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Instruction.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;

class Organizer
{
    public:

        ifstream stream; 
        RandomNumberGrabber MrRandom;
        vector<Instruction> instructions;


        // This should take the RandomNumber vector and also instruction vector
        Organizer(char* input_file, char* random_file, char* options, char* algorithm,
                    int num_of_frames);

        void CreateInstructionVector();
        void ReadUntilInstruction();
        int ExtractNumber();
        void ReadUntilCharacter();
        bool PeekEnd();
        void ReadUntilNewline();
};

#endif
