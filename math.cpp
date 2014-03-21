#include "math.hpp"
#include "core.hpp"

namespace emu
{

emu_uchar* add_rvrv(emu_uchar* i, emu_uchar* e, void* c)
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
            *r2 = *r1 + *r2;
            break;
        case UCHARXUSHORT:
            *(emu_ushort*)r2 = *r1 + *(emu_ushort*)r2;
            break;
        case UCHARXUINT:
            *(emu_uint*)r2 = *r1 + *(emu_uint*)r2;
            break;
        case UCHARXFLOAT:
            *(emu_float*)r2 = *r1 + *(emu_float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(emu_ushort*)r1 + *r2;
            break;
        case USHORTXUSHORT:
            *(emu_ushort*)r2 = *(emu_ushort*)r1 + *(emu_ushort*)r2;
            break;
        case USHORTXUINT:
            *(emu_uint*)r2 = *(emu_ushort*)r1 + *(emu_uint*)r2;
            break;
        case USHORTXFLOAT:
            *(emu_float*)r2 = *(emu_ushort*)r1 + *(emu_float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(emu_ushort*)r1 + *r2;
            break;
        case UINTXUSHORT:
            *(emu_ushort*)r2 = *(emu_uint*)r1 + *(emu_ushort*)r2;
            break;
        case UINTXUINT:
            *(emu_uint*)r2 = *(emu_uint*)r1 + *(emu_uint*)r2;
            break;
        case UINTXFLOAT:
            *(emu_float*)r2 = *(emu_uint*)r1 + *(emu_float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(emu_float*)r1 + *r2;
            break;
        case FLOATXUSHORT:
            *(emu_ushort*)r2 = *(emu_float*)r1 + *(emu_ushort*)r2;
            break;
        case FLOATXUINT:
            *(emu_uint*)r2 = *(emu_float*)r1 + *(emu_uint*)r2;
            break;
        case FLOATXFLOAT:
            *(emu_float*)r2 = *(emu_float*)r1 + *(emu_float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
emu_uchar*  add_ivrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar* sub_rvrv(emu_uchar* i, emu_uchar* e, void* c)
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
            *r2 = *r1 - *r2;
            break;
        case UCHARXUSHORT:
            *(emu_ushort*)r2 = *r1 - *(emu_ushort*)r2;
            break;
        case UCHARXUINT:
            *(emu_uint*)r2 = *r1 - *(emu_uint*)r2;
            break;
        case UCHARXFLOAT:
            *(emu_float*)r2 = *r1 - *(emu_float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(emu_ushort*)r1 - *r2;
            break;
        case USHORTXUSHORT:
            *(emu_ushort*)r2 = *(emu_ushort*)r1 - *(emu_ushort*)r2;
            break;
        case USHORTXUINT:
            *(emu_uint*)r2 = *(emu_ushort*)r1 - *(emu_uint*)r2;
            break;
        case USHORTXFLOAT:
            *(emu_float*)r2 = *(emu_ushort*)r1 - *(emu_float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(emu_ushort*)r1 - *r2;
            break;
        case UINTXUSHORT:
            *(emu_ushort*)r2 = *(emu_uint*)r1 - *(emu_ushort*)r2;
            break;
        case UINTXUINT:
            *(emu_uint*)r2 = *(emu_uint*)r1 - *(emu_uint*)r2;
            break;
        case UINTXFLOAT:
            *(emu_float*)r2 = *(emu_uint*)r1 - *(emu_float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(emu_float*)r1 - *r2;
            break;
        case FLOATXUSHORT:
            *(emu_ushort*)r2 = *(emu_float*)r1 - *(emu_ushort*)r2;
            break;
        case FLOATXUINT:
            *(emu_uint*)r2 = *(emu_float*)r1 - *(emu_uint*)r2;
            break;
        case FLOATXFLOAT:
            *(emu_float*)r2 = *(emu_float*)r1 - *(emu_float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
emu_uchar*  sub_ivrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar* inc_rv(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 2) return mem;
    emu_uchar* reg = core->regm[i[1]];
    emu_uchar type = core->regt[i[1]];
    switch(type)
    {
        case UCHAR:
            ++*reg;
            break;
        case USHORT:
            ++*(emu_ushort*)reg;
            break;
        case UINT:
            ++*(emu_uint*)reg;
            break;
        case FLOAT:
            *(emu_float*)reg = *(emu_float*)reg + 1.f;
            break;
            
        default:
            break;
    }
    return i + 2;
}
emu_uchar* dec_rv(emu_uchar* i, emu_uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    emu_uchar* mem = core->mem;
    if(e - i < 2) return mem;
    emu_uchar* reg = core->regm[i[1]];
    emu_uchar type = core->regt[i[1]];
    switch(type)
    {
        case UCHAR:
            --*reg;
            break;
        case USHORT:
            --*(emu_ushort*)reg;
            break;
        case UINT:
            --*(emu_uint*)reg;
            break;
        case FLOAT:
            *(emu_float*)reg = *(emu_float*)reg - 1.f;
            break;
            
        default:
            break;
    }
    return i + 2;
}
emu_uchar* mul_rvrv(emu_uchar* i, emu_uchar* e, void* c)
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
            *r2 = *r1 * *r2;
            break;
        case UCHARXUSHORT:
            *(emu_ushort*)r2 = *r1 * *(emu_ushort*)r2;
            break;
        case UCHARXUINT:
            *(emu_uint*)r2 = *r1 * *(emu_uint*)r2;
            break;
        case UCHARXFLOAT:
            *(emu_float*)r2 = *r1 * *(emu_float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(emu_ushort*)r1 * *r2;
            break;
        case USHORTXUSHORT:
            *(emu_ushort*)r2 = *(emu_ushort*)r1 * *(emu_ushort*)r2;
            break;
        case USHORTXUINT:
            *(emu_uint*)r2 = *(emu_ushort*)r1 * *(emu_uint*)r2;
            break;
        case USHORTXFLOAT:
            *(emu_float*)r2 = *(emu_ushort*)r1 * *(emu_float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(emu_ushort*)r1 * *r2;
            break;
        case UINTXUSHORT:
            *(emu_ushort*)r2 = *(emu_uint*)r1 * *(emu_ushort*)r2;
            break;
        case UINTXUINT:
            *(emu_uint*)r2 = *(emu_uint*)r1 * *(emu_uint*)r2;
            break;
        case UINTXFLOAT:
            *(emu_float*)r2 = *(emu_uint*)r1 * *(emu_float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(emu_float*)r1 * *r2;
            break;
        case FLOATXUSHORT:
            *(emu_ushort*)r2 = *(emu_float*)r1 * *(emu_ushort*)r2;
            break;
        case FLOATXUINT:
            *(emu_uint*)r2 = *(emu_float*)r1 * *(emu_uint*)r2;
            break;
        case FLOATXFLOAT:
            *(emu_float*)r2 = *(emu_float*)r1 * *(emu_float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
emu_uchar*  mul_ivrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar* div_rvrv(emu_uchar* i, emu_uchar* e, void* c)
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
            *r2 = *r1 / *r2;
            break;
        case UCHARXUSHORT:
            *(emu_ushort*)r2 = *r1 / *(emu_ushort*)r2;
            break;
        case UCHARXUINT:
            *(emu_uint*)r2 = *r1 / *(emu_uint*)r2;
            break;
        case UCHARXFLOAT:
            *(emu_float*)r2 = *r1 / *(emu_float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(emu_ushort*)r1 / *r2;
            break;
        case USHORTXUSHORT:
            *(emu_ushort*)r2 = *(emu_ushort*)r1 / *(emu_ushort*)r2;
            break;
        case USHORTXUINT:
            *(emu_uint*)r2 = *(emu_ushort*)r1 / *(emu_uint*)r2;
            break;
        case USHORTXFLOAT:
            *(emu_float*)r2 = *(emu_ushort*)r1 / *(emu_float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(emu_ushort*)r1 / *r2;
            break;
        case UINTXUSHORT:
            *(emu_ushort*)r2 = *(emu_uint*)r1 / *(emu_ushort*)r2;
            break;
        case UINTXUINT:
            *(emu_uint*)r2 = *(emu_uint*)r1 / *(emu_uint*)r2;
            break;
        case UINTXFLOAT:
            *(emu_float*)r2 = *(emu_uint*)r1 / *(emu_float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(emu_float*)r1 / *r2;
            break;
        case FLOATXUSHORT:
            *(emu_ushort*)r2 = *(emu_float*)r1 / *(emu_ushort*)r2;
            break;
        case FLOATXUINT:
            *(emu_uint*)r2 = *(emu_float*)r1 / *(emu_uint*)r2;
            break;
        case FLOATXFLOAT:
            *(emu_float*)r2 = *(emu_float*)r1 / *(emu_float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
emu_uchar*  div_ivrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  mod_rvrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  mod_ivrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  pow_rvrv   (emu_uchar*, emu_uchar*, void*);
emu_uchar*  pow_ivrv   (emu_uchar*, emu_uchar*, void*);

}

