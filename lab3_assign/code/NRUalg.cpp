#include "NRUalg.h"

NRUalg::NRUalg(FrameTable* ft) : ReplaceAlg(ft){
}

NRUalg::NRUalg() : ReplaceAlg(){
    reset_counter = 0;
    last_replaced = 0;
}

int NRUalg::GetReplacement(){
    reset_counter += 1;

    ClassifyFrames();
    if (reset_counter == 10)
        ResetReferenceBits();

    int random_num = 0, return_v_frame = 0;
    if (!Class_0.empty())
    {
        random_num = random_grabber->myrandom(Class_0.size());
        return_v_frame = Class_0[random_num];

        if (option_a)
        {
            cout << "@@ lowest_class=0: selinx=" << random_num << 
                " from";
            for (int i = 0; i < Class_0.size(); i++)
            {
                cout << " " << Class_0[i];
            }
            cout << endl;
        }
    }

    else if (!Class_1.empty())
    {
        random_num = random_grabber->myrandom(Class_1.size());
        return_v_frame = Class_1[random_num];

        if (option_a)
        {
            cout << "@@ lowest_class=1: selinx=" << random_num << 
                " from";
            for (int i = 0; i < Class_1.size(); i++)
            {
                cout << " " << Class_1[i];
            }
            cout << endl;
        }
    }

    else if (!Class_2.empty())
    {
        random_num = random_grabber->myrandom(Class_2.size());
        return_v_frame = Class_2[random_num];

        if (option_a)
        {
            cout << "@@ lowest_class=2: selinx=" << random_num << 
                " from";
            for (int i = 0; i < Class_2.size(); i++)
            {
                cout << " " << Class_2[i];
            }
            cout << endl;
        }
    }

    //else if (!Class_3.empty())
    else
    {
        random_num = random_grabber->myrandom(Class_3.size());
        return_v_frame = Class_3[random_num];

        if (option_a)
        {
            cout << "@@ lowest_class=3: selinx=" << random_num << 
                " from";
            for (int i = 0; i < Class_3.size(); i++)
            {
                cout << " " << Class_3[i];
            }
            cout << endl;
        }
    }

    return frame_table->page_table[return_v_frame].page_index;
} 

void NRUalg::MAP_Called(Instruction inst, int phys_frame){
    //p_frames.push_back(phys_frame);
}

void NRUalg::UNMAP_Called(Instruction inst, int phys_frame, int prev_v_frame){
    //p_frames.erase(p_frames.begin() + last_replaced);
}

void NRUalg::ACCESS_Called(Instruction inst, int phys_frame){
}

void NRUalg::ResetReferenceBits() {
    reset_counter = 0;
    int v_page;
    
    for (int i = 0; i < 64; i++)
    {
        frame_table->page_table[i].ref = 0;
    }

    if (option_a)
    {
        cout << "@@ reset NRU refbits while walking PTE" << endl;
    }
}

void NRUalg::ClassifyFrames() {
    // First need to empty out all the classifications, then add everything.
    Class_0.clear();
    Class_1.clear();
    Class_2.clear();
    Class_3.clear();

    int ref = 0, mod = 0, v_page = 0;
    
    // Need to add things into correct class
    for (int i = 0; i < 64; i++)
    {
        if (frame_table->page_table[i].present == 1)
        {
            ref = frame_table->page_table[i].ref;
            mod = frame_table->page_table[i].mod;

            if (ref == 0 && mod == 0)
            {
               Class_0.push_back(i);
            }

            else if(ref == 0 && mod == 1)
            {
               Class_1.push_back(i);
            }

            else if(ref == 1 && mod == 0)
            {
               Class_2.push_back(i);
            }

            else if(ref == 1 && mod == 1)
            {
               Class_3.push_back(i);
            }
        }
    }
}
