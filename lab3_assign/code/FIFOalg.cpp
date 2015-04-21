#include "FIFOalg.h"

FIFOalg::FIFOalg(FrameTable* ft) : ReplaceAlg(ft){
    
}

FIFOalg::FIFOalg() : ReplaceAlg(){
    
}

int FIFOalg::GetReplacement(){
    return p_frames[0];
} 


void FIFOalg::MAP_Called(Instruction inst, int phys_frame){
    p_frames.push_back(phys_frame);
}

void FIFOalg::UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame){
    p_frames.erase(p_frames.begin());
}

