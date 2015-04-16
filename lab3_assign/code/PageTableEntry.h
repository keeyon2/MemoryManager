#ifndef PageTableEntry_H
#define PageTableEntry_H

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct PageTableEntry
{
    unsigned ref:1;
    unsigned mod:1;
    unsigned present:1;
    unsigned page_index:6;
    unsigned :7;
}
