#ifndef FrameTable_H
#define FrameTable_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include "PageTableEntry.h"

using std::vector;

class FrameTable 
{
    public:
        vector<bool> entries;
        PageTableEntry* page_table;
        FrameTable();
        void SetTable(int size, PageTableEntry *PT);
};

#endif
