#include "ReplaceAlg.h"

ReplaceAlg::ReplaceAlg(){
}

ReplaceAlg::ReplaceAlg(FrameTable* ft){
    frame_table = ft;
}

void ReplaceAlg::SetFrameTable(FrameTable* ft){
    frame_table = ft;
}

int ReplaceAlg::GetReplacement(){
    cout << "Please Don't Print this" << endl;
    return -1;
}

void ReplaceAlg::ACCESS_Called(Instruction inst, int phys_frame){
}

void ReplaceAlg::MAP_Called(Instruction inst, int phys_frame){
}

void ReplaceAlg::UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame){
}

void ReplaceAlg::IN_Called(Instruction inst, int phys_frame){
}

void ReplaceAlg::OUT_Called(Instruction inst, int phys_frame, int prev_v_frame){
}

void ReplaceAlg::ZERO_Called(Instruction inst, int phys_frame){
}
