#include "debug.hpp"
#include "core.hpp"
#include <cstdio>

namespace emu
{

emu_uchar* prt_rv(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 2) return mem;
    emu_uchar i1 = i[1];
    emu_uchar* reg = core->regm[i[1]];
    emu_uchar type = core->regt[i[1]];
    switch(type)
    {
        case UCHAR:
            printf("reg[%x] = %2x\n", i1, *reg);
            break;
        case USHORT:
            printf("reg[%x] = %4x\n", i1, *(emu_ushort*)reg);
            break;
        case UINT:
            printf("reg[%x] = %8x\n", i1, *(emu_uint*)reg);
            break;
        case FLOAT:
            printf("reg[%x] = %f\n", i1, *(emu_float*)reg);
            break;
    }
    return i + 2;
}
emu_uchar*  prt_ir     (emu_uchar*, emu_uchar*, void*);
emu_uchar*  prt_rr     (emu_uchar*, emu_uchar*, void*);

}

