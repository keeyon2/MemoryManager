#ifndef Instruction_H
#define Instruction_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;

class Instruction
{
    public:
        int virtual_frame;
        bool read;
        bool write;
        Instruction(int read_write, int virtual_frame); 
};

#endif
