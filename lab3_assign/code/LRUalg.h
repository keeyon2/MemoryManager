#ifndef LRUalg_H
#define LRUalg_H 

#include "ReplaceAlg.h"

class LRUalg : public ReplaceAlg
{
    public:
        vector<int> p_frames;
        int last_replaced;
        
        LRUalg(FrameTable* ft);
        LRUalg();
        int GetReplacement();
        void MAP_Called(Instruction inst, int phys_frame);
        void UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame);
        void ACCESS_Called(Instruction inst, int phys_frame);
};


#endif
