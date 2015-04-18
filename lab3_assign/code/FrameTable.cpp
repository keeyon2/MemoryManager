#include "FrameTable.h"

FrameTable::FrameTable()
{
}

void FrameTable::SetTable(int size, PageTableEntry* PT)
{
    for (int i = 0; i < size; i++)
    {
        entries.push_back(false);
    }
    
    page_table = PT; 
    //page_table[0].present = 1;
}
