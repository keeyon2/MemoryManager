#ifndef FIFOalg_H
#define FIFOalg_H

#include "ReplaceAlg.h"

class FIFOalg : public ReplaceAlg
{
    public:
        vector<int> p_frames;

        FIFOalg(FrameTable* ft);
        FIFOalg();
        int GetReplacement();
        void MAP_Called(Instruction inst, int phys_frame);
        void UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame);
};


#endif
