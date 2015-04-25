#ifndef NRUalg_H
#define NRUalg_H 

#include "ReplaceAlg.h"

class NRUalg : public ReplaceAlg
{
    public:
        vector<int> p_frames;
        vector<int> Class_0;
        vector<int> Class_1;
        vector<int> Class_2;
        vector<int> Class_3;
        int reset_counter;
        int last_replaced;

        NRUalg(FrameTable* ft);
        NRUalg();
        int GetReplacement();
        void MAP_Called(Instruction inst, int phys_frame);
        void UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame);
        void ACCESS_Called(Instruction inst, int phys_frame);
        void ResetReferenceBits();
        void ClassifyFrames();
};


#endif
