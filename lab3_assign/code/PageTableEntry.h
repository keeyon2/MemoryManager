#ifndef PageTableEntry_H
#define PageTableEntry_H

struct PageTableEntry
{
    unsigned ref:1;
    unsigned mod:1;
    unsigned present:1;
    unsigned p_out:1;
    unsigned page_index:6;
    unsigned :6;
};

#endif
