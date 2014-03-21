#include "mem.hpp"
#include "core.hpp"

namespace emu
{

static inline void copystuff(emu_uchar* src, emu_uchar* dst, emu_uchar type)
{
    switch(type)
    {
        case UCHAR:
            *dst = *src;
            break;
        case USHORT:
            *(emu_ushort*)dst = *(emu_ushort*)src;
            break;
        case UINT:
            *(emu_uint*)dst = *(emu_uint*)src;
            break;
        case FLOAT:
            *(emu_float*)dst = *(emu_float*)src;
            break;
        default:
            break;
    }
}
static inline void copystuff(emu_uchar* src, emu_uchar* dst, emu_uchar type1, emu_uchar type2)
{
    if(type1 > type2) type1 = type2;
    copystuff(src, dst, type1);
}

//constant-to-register
emu_uchar* set_ivrv(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uint diff = e - i;
    if(diff < 3) return core->mem;
    emu_uchar* reg = core->regm[i[1]];
    emu_uchar type = core->regt[i[1]];
    emu_uint sz = sizes[type];
    emu_uint req = sz + 2;
    if(diff < req) return core->mem;
    copystuff(i + 2, reg, type, type);
    return i + req;
}
emu_uchar*  set_ivrr   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  set_ivir   (emu_uchar*, emu_uchar*, void*);
//register-to-register: src, tgt
emu_uchar* mov_rvrv(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 3) return mem;
    emu_uchar** regm = core->regm;
    emu_uchar* src = regm[i[1]];
    emu_uchar* dst = regm[i[2]];
    emu_uchar* regt = core->regt;
    emu_uchar srct = regt[i[1]];
    emu_uchar dstt = regt[i[2]];
    copystuff(src, dst, srct, dstt);
    return i + 3;
}
emu_uchar*  get_irrv   (emu_uchar*, emu_uchar*, void*);
//memory-to-register
emu_uchar* get_rrrv(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 3) return mem;
    emu_uchar i1 = i[1];
    emu_uchar i2 = i[2];
    emu_uchar** regm = core->regm;
    emu_uchar* r1 = regm[i1];
    emu_uchar* r2 = regm[i2];
    emu_uchar* regt = core->regt;
    emu_uchar t1 = regt[i1];
    emu_uchar t2 = regt[i2];
    if(t1 != UINT) return i + 3;
    emu_uchar* tgt = mem + *(emu_uint*)r1;
    copystuff(tgt, r2, t2, t2);
    return i + 3;
}
emu_uchar*  put_rvir   (emu_uchar*, emu_uchar*, void*);
//register-to-memory: value, target
emu_uchar* put_rvrr(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 3) return mem;
    emu_uchar i1 = i[1];
    emu_uchar i2 = i[2];
    emu_uchar** regm = core->regm;
    emu_uchar* r1 = regm[i1];
    emu_uchar* r2 = regm[i2];
    emu_uchar* regt = core->regt;
    emu_uchar t1 = regt[i1];
    emu_uchar t2 = regt[i2];
    if(t2 != UINT) return i + 3;
    emu_uchar* tgt = mem + *(emu_uint*)r2;
    copystuff(r1, tgt, t1, t1);
    return i + 3;
}
emu_uchar* push_rrrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar* push_irrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  pop_rrrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  pop_irrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  lea_rrivrv (emu_uchar*, emu_uchar*, void*);
emu_uchar*  lea_rrrvrv (emu_uchar*, emu_uchar*, void*);
emu_uchar*  lea_irivrv (emu_uchar*, emu_uchar*, void*);

}

