#include "bits.hpp"
#include "core.hpp"

namespace emu
{

emu_uchar* not_rv(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 3) return mem;
    emu_uchar* reg = core->regm[i[1]];
    emu_uchar type = core->regt[i[1]];
    switch(type)
    {
        case UCHAR:
            *(emu_uchar*)reg = ~*(emu_uchar*)reg;
            break;
        case USHORT:
            *(emu_ushort*)reg = ~*(emu_ushort*)reg;
            break;
        case UINT:
        case FLOAT:
            *(emu_uint*)reg = ~*(emu_uint*)reg;
            break;
    }
    return i + 3;
}
emu_uchar* and_rvrv(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 3) return mem;
    emu_uchar** regm = core->regm;
    emu_uchar* r1 = regm[i[1]];
    emu_uchar* r2 = regm[i[2]];
    emu_uchar* regt = core->regt;
    emu_uchar t1 = regt[i[1]];
    emu_uchar t2 = regt[i[2]];
    emu_uchar t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 & *r2;
            break;
        case UCHARXUSHORT:
            *(emu_ushort*)r2 = *r1 & *(emu_ushort*)r2;
            break;
        case UCHARXUINT:
        case UCHARXFLOAT:
            *(emu_uint*)r2 = *r1 & *(emu_uint*)r2;
            break;

        case USHORTXUCHAR:
            *r2 = *(emu_ushort*)r1 & *r2;
            break;
        case USHORTXUSHORT:
            *(emu_ushort*)r2 = *(emu_ushort*)r1 & *(emu_ushort*)r2;
            break;
        case USHORTXUINT:
        case USHORTXFLOAT:
            *(emu_uint*)r2 = *(emu_ushort*)r1 & *(emu_uint*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(emu_ushort*)r1 & *r2;
            break;
        case UINTXUSHORT:
            *(emu_ushort*)r2 = *(emu_uint*)r1 & *(emu_ushort*)r2;
            break;
        case UINTXUINT:
        case UINTXFLOAT:
            *(emu_uint*)r2 = *(emu_uint*)r1 & *(emu_uint*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(emu_uint*)r1 & *r2;
            break;
        case FLOATXUSHORT:
            *(emu_ushort*)r2 = *(emu_uint*)r1 & *(emu_ushort*)r2;
            break;
        case FLOATXUINT:
        case FLOATXFLOAT:
            *(emu_uint*)r2 = *(emu_uint*)r1 & *(emu_uint*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
emu_uchar*  and_ivrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar* or_rvrv(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 3) return mem;
    emu_uchar** regm = core->regm;
    emu_uchar* r1 = regm[i[1]];
    emu_uchar* r2 = regm[i[2]];
    emu_uchar* regt = core->regt;
    emu_uchar t1 = regt[i[1]];
    emu_uchar t2 = regt[i[2]];
    emu_uchar t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 | *r2;
            break;
        case UCHARXUSHORT:
            *(emu_ushort*)r2 = *r1 | *(emu_ushort*)r2;
            break;
        case UCHARXUINT:
        case UCHARXFLOAT:
            *(emu_uint*)r2 = *r1 | *(emu_uint*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(emu_ushort*)r1 | *r2;
            break;
        case USHORTXUSHORT:
            *(emu_ushort*)r2 = *(emu_ushort*)r1 | *(emu_ushort*)r2;
            break;
        case USHORTXUINT:
        case USHORTXFLOAT:
            *(emu_uint*)r2 = *(emu_ushort*)r1 | *(emu_uint*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(emu_ushort*)r1 | *r2;
            break;
        case UINTXUSHORT:
            *(emu_ushort*)r2 = *(emu_uint*)r1 | *(emu_ushort*)r2;
            break;
        case UINTXUINT:
        case UINTXFLOAT:
            *(emu_uint*)r2 = *(emu_uint*)r1 | *(emu_uint*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(emu_uint*)r1 | *r2;
            break;
        case FLOATXUSHORT:
            *(emu_ushort*)r2 = *(emu_uint*)r1 | *(emu_ushort*)r2;
            break;
        case FLOATXUINT:
        case FLOATXFLOAT:
            *(emu_uint*)r2 = *(emu_uint*)r1 | *(emu_uint*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
emu_uchar*   or_ivrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar* xor_rvrv(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 3) return mem;
    emu_uchar** regm = core->regm;
    emu_uchar* r1 = regm[i[1]];
    emu_uchar* r2 = regm[i[2]];
    emu_uchar* regt = core->regt;
    emu_uchar t1 = regt[i[1]];
    emu_uchar t2 = regt[i[2]];
    emu_uchar t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 ^ *r2;
            break;
        case UCHARXUSHORT:
            *(emu_ushort*)r2 = *r1 ^ *(emu_ushort*)r2;
            break;
        case UCHARXUINT:
        case UCHARXFLOAT:
            *(emu_uint*)r2 = *r1 ^ *(emu_uint*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(emu_ushort*)r1 ^ *r2;
            break;
        case USHORTXUSHORT:
            *(emu_ushort*)r2 = *(emu_ushort*)r1 ^ *(emu_ushort*)r2;
            break;
        case USHORTXUINT:
        case USHORTXFLOAT:
            *(emu_uint*)r2 = *(emu_ushort*)r1 ^ *(emu_uint*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(emu_ushort*)r1 ^ *r2;
            break;
        case UINTXUSHORT:
            *(emu_ushort*)r2 = *(emu_uint*)r1 ^ *(emu_ushort*)r2;
            break;
        case UINTXUINT:
        case UINTXFLOAT:
            *(emu_uint*)r2 = *(emu_uint*)r1 ^ *(emu_uint*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(emu_uint*)r1 ^ *r2;
            break;
        case FLOATXUSHORT:
            *(emu_ushort*)r2 = *(emu_uint*)r1 ^ *(emu_ushort*)r2;
            break;
        case FLOATXUINT:
        case FLOATXFLOAT:
            *(emu_uint*)r2 = *(emu_uint*)r1 ^ *(emu_uint*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
emu_uchar*  xor_ivrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*   lg_rv     (emu_uchar*, emu_uchar*, void*);
emu_uchar*  lsh_rvrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  lsh_ivrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  rsh_rvrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  rsh_ivrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  ars_rvrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  ars_ivrv   (emu_uchar*, emu_uchar*, void*);

}

