#ifndef VClockAlg_H
#define VClockAlg_H 

#include "ReplaceAlg.h"

class VClockAlg : public ReplaceAlg
{
    public:
        vector<int> v_frames;
        int last_v_frame;
        VClockAlg(FrameTable* ft);
        VClockAlg();
        int GetReplacement();
        void MAP_Called(Instruction inst, int phys_frame);
        void UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame);
        void ACCESS_Called(Instruction inst, int phys_frame);
};


#endif
