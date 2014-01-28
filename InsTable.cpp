#include "InsTable.hpp"
using namespace emu;

InsTable::InsTable()
{
    itable = new Instruction[256];
    for(int i = 0; i < 256; i++) itable[i] = Instruction();
}

InsTable::~InsTable()
{
    delete[] itable;
}

