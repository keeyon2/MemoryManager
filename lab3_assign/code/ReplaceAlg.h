#ifndef ReplaceAlg_H
#define ReplaceAlg_H

#include <vector>
#include "FrameTable.h"
#include "Instruction.h"

using std::vector;
using std::cout;
using std::endl;

class ReplaceAlg
{
    public:
        FrameTable* frame_table;
        ReplaceAlg();
        ReplaceAlg(FrameTable* ft);
        void SetFrameTable(FrameTable* ft); 
        int PresentVPageOfPhysFrame(int phys_frame);
        virtual int GetReplacement(); // This returns int of which frame Table Entry
        virtual void ACCESS_Called(Instruction inst, int phys_frame);
        virtual void MAP_Called(Instruction inst, int phys_frame);
        virtual void UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame);
        virtual void IN_Called(Instruction inst, int phys_frame);
        virtual void OUT_Called(Instruction inst, int phys_frame, int prev_v_frame);
        virtual void ZERO_Called(Instruction inst, int phys_frame);
};


#endif
