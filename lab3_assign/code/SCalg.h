#ifndef SCalg_H
#define SCalg_H 

#include "ReplaceAlg.h"

class SCalg : public ReplaceAlg
{
    public:
        vector<int> p_frames;

        SCalg(FrameTable* ft);
        SCalg();
        int GetReplacement();
        void MAP_Called(Instruction inst, int phys_frame);
        void UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame);
        void ACCESS_Called(Instruction inst, int phys_frame);
};


#endif
