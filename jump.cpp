#include "jump.hpp"
#include "core.hpp"

namespace emu
{

emu_uchar*  nop        (emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    i++;
    if(i == e) return core->mem;
    return i;
}

emu_uchar*  jmp_rr     (emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 2) return mem;
    emu_uchar* reg = core->regm[i[1]];
    if(core->regt[i[1]] != UINT) return i + 1;
    return mem + *(emu_uint*)reg;
}
emu_uchar*  jmp_ir     (emu_uchar*, emu_uchar*, void*);
emu_uchar*   jz_rvrr   (emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 3) return mem;
    emu_uchar** regm = core->regm;
    emu_uchar* regt = core->regt;
    emu_uchar i1 = i[1];
    emu_uchar i2 = i[2];
    if(regt[i2] != UINT) return i + 3;
    emu_uchar* r1 = regm[i1];
    emu_uchar* r2 = regm[i2];
    emu_uchar t1 = regt[i1];
    bool doit;
    switch(t1)
    {
        case UCHAR:
            doit = !*(emu_uchar*)r1;
            break;
        case USHORT:
            doit = !*(emu_ushort*)r1;
            break;
        case UINT:
            doit = !*(emu_uint*)r1;
            break;
        case FLOAT:
            doit = !*(emu_float*)r1;
            break;
        default:
            doit = false;
            break;
    }
    if(!doit) return i + 3;
    return mem + *(emu_uint*)r2;
}
emu_uchar*  jz_rvir     (emu_uchar*, emu_uchar*, void*);
emu_uchar* jnz_rvrr     (emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 3) return mem;
    emu_uchar** regm = core->regm;
    emu_uchar* regt = core->regt;
    emu_uchar i1 = i[1];
    emu_uchar i2 = i[2];
    if(regt[i2] != UINT) return i + 3;
    emu_uchar* r1 = regm[i1];
    emu_uchar* r2 = regm[i2];
    emu_uchar t1 = regt[i1];
    bool doit;
    switch(t1)
    {
        case UCHAR:
            doit = *(emu_uchar*)r1;
            break;
        case USHORT:
            doit = *(emu_ushort*)r1;
            break;
        case UINT:
            doit = *(emu_uint*)r1;
            break;
        case FLOAT:
            doit = *(emu_float*)r1;
            break;
        default:
            doit = false;
            break;
    }
    if(!doit) return i + 3;
    return mem + *(emu_uint*)r2;
}
emu_uchar*  jnz_rvir   (emu_uchar*, emu_uchar*, void*);
emu_uchar*   jn_rvrr   (emu_uchar*, emu_uchar*, void*);
emu_uchar*   jn_rvir   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  jnn_rvrr   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  jnn_rvir   (emu_uchar*, emu_uchar*, void*);
emu_uchar* jmpr_rr     (emu_uchar*, emu_uchar*, void*)
{

}

emu_uchar* jmpr_ir     (emu_uchar*, emu_uchar*, void*)
{

}
emu_uchar*  jzr_rvrr   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  jzr_rvir   (emu_uchar*, emu_uchar*, void*);
emu_uchar* jnzr_rvrr   (emu_uchar*, emu_uchar*, void*);
emu_uchar* jnzr_rvir   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  jnr_rvrr   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  jnr_rvir   (emu_uchar*, emu_uchar*, void*);
emu_uchar* jnnr_rvrr   (emu_uchar*, emu_uchar*, void*);
emu_uchar* jnnr_rvir   (emu_uchar*, emu_uchar*, void*);

}

