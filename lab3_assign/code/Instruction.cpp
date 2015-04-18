#include "Instruction.h"

Instruction::Instruction(int read_write, int virtual_frame)
{
    if (read_write == 1)
    {
        read = false;
        write = true;
    }

    else 
    {
        read = true;
        write = false;
    } 

    this->virtual_frame = virtual_frame;
}

