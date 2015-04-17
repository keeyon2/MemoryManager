#include "Instruction.h"

Include::Include(int read_write, int virtual_frame)
{
    if (read_write == 1)
    {
        this.read = false;
        this.write = true;
    }

    else 
    {
        this.virtual_frame = virtual_frame;
    } 
}
