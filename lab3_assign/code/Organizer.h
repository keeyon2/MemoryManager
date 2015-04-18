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
#include "PageTableEntry.h"
#include "FrameTable.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::reverse;

class Organizer
{
    public:

        long total_map, total_unmap, total_in, 
             total_out, total_zero, total_cycles;
        ifstream stream; 
        RandomNumberGrabber MrRandom;
        vector<Instruction> instructions;
        int frame_table_size;
        int current_inst = -1;
        PageTableEntry page_table[64];
        FrameTable frame_table;
        bool option_O, option_P, option_F, option_S,
             option_p, option_f, option_a, is_o;
        
        string  options;

        // This should take the RandomNumber vector and also instruction vector
        Organizer(char* input_file, char* random_file, char* options, char* algorithm,
                    int num_of_frames);

        void SetOptions(char* options);
        void SetIndivOption(string all_ops, char c, bool* option);
        void CreateInstructionVector(char* input_file);
        void CreateTables();
        void RunThroughInstructions();
        Instruction GetInstruction();

        // Operations
        void UNMAP(Instruction inst);
        void MAP(Instruction inst, int phys_frame);
        void IN(Instruction inst);
        void OUT(Instruction inst);
        void ZERO(Instruction inst, int phys_frame);
        void ACCESS(Instruction ints);

        void ReadUntilInstruction();
        int ExtractNumber();
        void ReadUntilCharacter();
        bool PeekEnd();
        void ReadUntilNewline();

};

#endif
