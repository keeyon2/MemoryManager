#ifndef RandomAlg_H
#define RandomAlg_H 

#include "ReplaceAlg.h"

class RandomAlg : public ReplaceAlg
{
    public:
        vector<int> p_frames;

        RandomAlg(FrameTable* ft);
        RandomAlg();
        int GetReplacement();
        void MAP_Called(Instruction inst, int phys_frame);
        void UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame);
        void ACCESS_Called(Instruction inst, int phys_frame);
};


#endif
