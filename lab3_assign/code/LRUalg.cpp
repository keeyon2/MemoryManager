#include "LRUalg.h"

LRUalg::LRUalg(FrameTable* ft) : ReplaceAlg(ft){
}

LRUalg::LRUalg() : ReplaceAlg(){
    last_replaced = 0;
}

int LRUalg::GetReplacement(){
    return p_frames[0];
} 

void LRUalg::MAP_Called(Instruction inst, int phys_frame){
    p_frames.push_back(phys_frame);
}

void LRUalg::UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame){
    p_frames.erase(p_frames.begin());
}

void LRUalg::ACCESS_Called(Instruction inst, int phys_frame){
    for (int i = 0; i < p_frames.size(); i++)
    {
        if (p_frames[i] == phys_frame)
        {
            p_frames.erase(p_frames.begin() + i);
            p_frames.push_back(phys_frame);
        }
    }
}
