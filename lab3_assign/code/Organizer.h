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
#include "ReplaceAlg.h"
#include "FIFOalg.h"
#include "SCalg.h"
#include "VClockAlg.h"
#include "RandomAlg.h"
#include "LRUalg.h"
#include "NRUalg.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::reverse;
using std::getline;

class Organizer
{
    public:

        int total_map, total_unmap, total_in, 
             total_out, total_zero;
        unsigned long long total_cycles;
        ifstream stream; 

        ReplaceAlg* replacement_alg;
        FIFOalg fifo_alg;
        SCalg sc_alg;
        VClockAlg vc_alg;
        RandomAlg rand_alg;
        LRUalg lru_alg;
        NRUalg nru_alg;

        RandomNumberGrabber MrRandom;
        FrameTable frame_table;

        vector<Instruction> instructions;
        int frame_table_size;
        long current_inst;

        PageTableEntry page_table[64];
        bool option_O, option_P, option_F, option_S,
             option_p, option_f, option_a, is_o;
        
        string  options;

        // This should take the RandomNumber vector and also instruction vector
        Organizer(char* input_file, char* random_file, char* options, char* algorithm,
                    int num_of_frames);

        void SetOptions(char* options);
        void SetAlgorithm(char* algorithm);
        void SetIndivOption(string all_ops, char c, bool* option);
        void CreateInstructionVector(char* input_file);
        void CreateTables();
        void RunThroughInstructions();

        // Prints
        void PrintResults();
        void PrintFrameTable();
        void PrintPageTable();

        Instruction GetInstruction();
        void BringInstToRam(Instruction inst, int phys_frame_location);
        int FindDeletingVPage(int phys_frame);
        
        // Operations
        void UNMAP(Instruction inst, int phys_frame, int prev_v_frame);
        void MAP(Instruction inst, int phys_frame);
        void IN(Instruction inst, int phys_frame);
        void OUT(Instruction inst, int phys_frame, int prev_v_frame);
        void ZERO(Instruction inst, int phys_frame);
        void ACCESS(Instruction ints, int phys_frame);

        void ReadUntilInstruction();
        int ExtractNumber();
        void ReadUntilCharacter();
        bool PeekEnd();
        void ReadUntilNewline();

};

#endif
