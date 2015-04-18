#ifndef Organizer_H
#define Organizer_H

#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Instruction.h"
#include "RandomNumberGrabber.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::reverse;

class Organizer
{
    public:

        ifstream stream; 
        RandomNumberGrabber MrRandom;
        vector<Instruction> instructions;
        bool option_O, option_P, option_F, option_S,
             option_p, option_f, option_a, is_o;
        
        string  options;

        // This should take the RandomNumber vector and also instruction vector
        Organizer(char* input_file, char* random_file, char* options, char* algorithm,
                    int num_of_frames);

        void SetOptions(char* options);
        void SetIndivOption(string all_ops, char c, bool* option);
        void CreateInstructionVector(char* input_file);
        Instruction PopNextInstruction();

        void ReadUntilInstruction();
        int ExtractNumber();
        void ReadUntilCharacter();
        bool PeekEnd();
        void ReadUntilNewline();

};

#endif
