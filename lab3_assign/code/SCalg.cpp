#include "SCalg.h"

SCalg::SCalg(FrameTable* ft) : ReplaceAlg(ft){
}

SCalg::SCalg() : ReplaceAlg(){
}

int SCalg::GetReplacement(){
    int pys_frame = 0, v_frame = 0;
    while (true)
    {
        pys_frame = p_frames[0];
        v_frame = PresentVPageOfPhysFrame(pys_frame);
        if (frame_table->page_table[v_frame].ref == 0)
        {
            return p_frames[0];
        }
        else
        {
            frame_table->page_table[v_frame].ref = 0;
            p_frames.push_back(pys_frame);
            p_frames.erase(p_frames.begin());            
        }
    }
} 

void SCalg::MAP_Called(Instruction inst, int phys_frame){
    p_frames.push_back(phys_frame);
}

void SCalg::UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame){
    p_frames.erase(p_frames.begin());
}

void SCalg::ACCESS_Called(Instruction inst, int phys_frame){
}
