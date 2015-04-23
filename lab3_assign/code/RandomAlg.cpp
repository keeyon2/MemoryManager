#include "RandomAlg.h"

RandomAlg::RandomAlg(FrameTable* ft) : ReplaceAlg(ft){
}

RandomAlg::RandomAlg() : ReplaceAlg(){
}

int RandomAlg::GetReplacement(){
    return random_grabber->grab_random();
} 

void RandomAlg::MAP_Called(Instruction inst, int phys_frame){
    //p_frames.push_back(phys_frame);
}

void RandomAlg::UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame){
    //p_frames.erase(p_frames.begin());
}

void RandomAlg::ACCESS_Called(Instruction inst, int phys_frame){
}
