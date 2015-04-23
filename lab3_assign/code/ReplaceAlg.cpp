#include "ReplaceAlg.h"

ReplaceAlg::ReplaceAlg(){
}

ReplaceAlg::ReplaceAlg(FrameTable* ft){
    frame_table = ft;
}

void ReplaceAlg::SetFrameTable(FrameTable* ft){
    frame_table = ft;
}

void ReplaceAlg::SetFrameAndRandom(FrameTable* ft, RandomNumberGrabber* rg){
    frame_table = ft;
    random_grabber = rg;
}


int ReplaceAlg::GetReplacement(){
    cout << "Please Don't Print this" << endl;
    return -1;
}

int ReplaceAlg::PresentVPageOfPhysFrame(int phys_frame)
{
    int size = 64;
    int present;
    int page_index;
    for (int i = 0; i < size; i++)
    {
        present = frame_table->page_table[i].present; 
        page_index = frame_table->page_table[i].page_index;
        if (page_index == phys_frame && present == 1)
            return i;
    } 
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
