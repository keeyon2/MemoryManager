#include "VClockAlg.h"

VClockAlg::VClockAlg(FrameTable* ft) : ReplaceAlg(ft){
    last_v_frame = 0;
}

VClockAlg::VClockAlg() : ReplaceAlg(){
    last_v_frame = 0;
}

int VClockAlg::GetReplacement(){
    int pys_frame = 0, v_frame = 0;
    int check_number = 0, iterate = 0;

    while (true) 
    {
        check_number = (iterate + last_v_frame) % 64;
        if (frame_table->page_table[check_number].present == 1)
        {
            if (frame_table->page_table[check_number].ref == 0)
            {
                last_v_frame = check_number;
                return frame_table->page_table[check_number].page_index;
            }
            else
            {
                frame_table->page_table[check_number].ref = 0;
            }
        }
        iterate += 1;
    }
} 

void VClockAlg::MAP_Called(Instruction inst, int phys_frame){
    //p_frames.push_back(inst.virtual_frame);
}

void VClockAlg::UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame){
    //p_frames.erase(v_frames.begin());
}

void VClockAlg::ACCESS_Called(Instruction inst, int phys_frame){
}
