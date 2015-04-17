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
using std::string::npos;

class Organizer
{
    public:

        ifstream stream; 
        RandomNumberGrabber MrRandom;
        vector<Instruction> instructions;
        bool option_O, option_P, option_F, option_S,
             optoin_p, option_f, option_a, is_o;
        
        char* options;

        // This should take the RandomNumber vector and also instruction vector
        Organizer(char* input_file, char* random_file, char* options, char* algorithm,
                    int num_of_frames);

        void SetOptions(char* options);
        void SetIndivOption(string all_ops, char c, bool* option)
        void CreateInstructionVector();
        Instruction PopNextInstruction();

        void ReadUntilInstruction();
        int ExtractNumber();
        void ReadUntilCharacter();
        bool PeekEnd();
        void ReadUntilNewline();

};

#endif
