#include <cstdio>
#include "EmuCore.hpp"

using namespace emu;
using namespace std;
///////////////////////////////////////////////////////////////////////////////
static uchar*   nop   (uchar* i, uchar* e, void* m); //done
static uchar*   set   (uchar* i, uchar* e, void* m); //done
static uchar*   mov   (uchar* i, uchar* e, void* m); //done
static uchar*   put   (uchar* i, uchar* e, void* m); //done
static uchar*   get   (uchar* i, uchar* e, void* m); //done
static uchar*   add   (uchar* i, uchar* e, void* m); //done
static uchar*   sub   (uchar* i, uchar* e, void* m); //done
static uchar*   dec   (uchar* i, uchar* e, void* m); //done
static uchar*   inc   (uchar* i, uchar* e, void* m); //done
static uchar*   mul   (uchar* i, uchar* e, void* m); //done
static uchar*   div   (uchar* i, uchar* e, void* m); //done
static uchar*   mod   (uchar* i, uchar* e, void* m);
static uchar*   pow   (uchar* i, uchar* e, void* m);
static uchar*   lg    (uchar* i, uchar* e, void* m);
static uchar*   ln    (uchar* i, uchar* e, void* m);
static uchar*   lsh   (uchar* i, uchar* e, void* m);
static uchar*   rsh   (uchar* i, uchar* e, void* m);
static uchar*   ars   (uchar* i, uchar* e, void* m);
static uchar*   push  (uchar* i, uchar* e, void* m);
static uchar*   pop   (uchar* i, uchar* e, void* m);
static uchar*   sin   (uchar* i, uchar* e, void* m);
static uchar*   cos   (uchar* i, uchar* e, void* m);
static uchar*   tan   (uchar* i, uchar* e, void* m);
static uchar*   asin  (uchar* i, uchar* e, void* m);
static uchar*   acos  (uchar* i, uchar* e, void* m);
static uchar*   atan  (uchar* i, uchar* e, void* m);
static uchar*   sec   (uchar* i, uchar* e, void* m);
static uchar*   csc   (uchar* i, uchar* e, void* m);
static uchar*   ctan  (uchar* i, uchar* e, void* m);
static uchar*   inot  (uchar* i, uchar* e, void* m); //done
static uchar*   iand  (uchar* i, uchar* e, void* m); //done
static uchar*   ior   (uchar* i, uchar* e, void* m); //done
static uchar*   ixor  (uchar* i, uchar* e, void* m); //done
static uchar*   jmp   (uchar* i, uchar* e, void* m); //done
static uchar*   jz    (uchar* i, uchar* e, void* m); //done
static uchar*   jnz   (uchar* i, uchar* e, void* m); //done
static uchar*   prt   (uchar* i, uchar* e, void* m); //done
///////////////////////////////////////////////////////////////////////////////
static const uchar UCHAR  = 0;
static const uchar USHORT = 1;
static const uchar UINT   = 2;
static const uchar FLOAT  = 3;
///////////////////////////////////////////////////////////////////////////////
static const uchar UCHARXUCHAR   = 0 ;
static const uchar UCHARXUSHORT  = 1 ;
static const uchar UCHARXUINT    = 2 ;
static const uchar UCHARXFLOAT   = 3 ;

static const uchar USHORTXUCHAR  = 4 ;
static const uchar USHORTXUSHORT = 5 ;
static const uchar USHORTXUINT   = 6 ;
static const uchar USHORTXFLOAT  = 7 ;

static const uchar UINTXUCHAR    = 8 ;
static const uchar UINTXUSHORT   = 9 ;
static const uchar UINTXUINT     = 10;
static const uchar UINTXFLOAT    = 11;

static const uchar FLOATXUCHAR   = 12;
static const uchar FLOATXUSHORT  = 13;
static const uchar FLOATXUINT    = 14;
static const uchar FLOATXFLOAT   = 15;
///////////////////////////////////////////////////////////////////////////////
static const uchar uchars[4]  = {0 , 1 , 2 , 3 };
static const uchar ushorts[4] = {4 , 5 , 6 , 7 };
static const uchar uints[4]   = {8 , 9 , 10, 11};
static const uchar floats[4]  = {12, 13, 14, 15};
static const uchar* dual[4] = {uchars, ushorts, uints, floats};
static const uint sizes[4] = {1, 1, 2, 4};
///////////////////////////////////////////////////////////////////////////////
static inline void copystuff(uchar* src, uchar* dst, uchar type)
{
    switch(type)
    {
        case UCHAR:
            *dst = *src;
            break;
        case USHORT:
            *(ushort*)dst = *(ushort*)src;
            break;
        case UINT:
            *(uint*)dst = *(uint*)src;
            break;
        case FLOAT:
            *(float*)dst = *(float*)src;
            break;
        default:
            break;
    }
}
static inline void copystuff(uchar* src, uchar* dst, uchar type1, uchar type2)
{
    if(type1 > type2) type1 = type2;
    copystuff(src, dst, type1);
}
//7:bits, 3:flgs, 3:oflo
static const uint regsize = 128;

EmuCore::EmuCore()
{
    mem = new uchar[4096];
    ip = 0;
    end = mem + 4096;
    
    itable[0x00] = nop  ;
    itable[0x01] = set  ;
    itable[0x02] = mov  ;
    itable[0x03] = put  ;
    itable[0x04] = get  ;
    itable[0x05] = add  ;
    itable[0x06] = sub  ;
    itable[0x07] = inc  ;
    itable[0x08] = dec  ;
    itable[0x09] = mul  ;
    itable[0x0a] = div  ;
    itable[0x0b] = inot ;
    itable[0x0c] = iand ;
    itable[0x0d] = ior  ;
    itable[0x0e] = ixor ;
    itable[0x0f] = jmp  ;
    itable[0x10] = jz   ;
    itable[0x11] = jnz  ;
    itable[0x12] = prt  ;
    for(int i = 0x13; i < 0x100; i++)
    {
        itable[i] = nop;
    }
    
    regs = new uchar[regsize];
    regm = new uchar*[0x100];
    regt = new uchar[0x100];
    uchar* c = regs;
    for(int i = 0; i < 0x100; i += 8)
    {
        regm[i] = c;
        regt[i] = UINT;
        regm[i + 1] = c;
        regt[i + 1] = FLOAT;
        regm[i + 2] = c;
        regt[i + 2] = USHORT;
        regm[i + 3] = c + 2;
        regt[i + 3] = USHORT;
        regm[i + 4] = c;
        regt[i + 4] = UCHAR;
        regm[i + 5] = c + 1;
        regt[i + 5] = UCHAR;
        regm[i + 6] = c + 2;
        regt[i + 6] = UCHAR;
        regm[i + 7] = c + 3;
        regt[i + 7] = UCHAR;
        
        c += 4;
    }
}

EmuCore::~EmuCore()
{
    delete[] mem;
    delete[] regs;
    delete[] regm;
    delete[] regt;
}

//do nothing
static uchar* nop(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    i++;
    if(i == e)
    {
        EmuCore* core = (EmuCore*)c;
        return mem;
    }
    return i;
}
//constant-to-register
static uchar* set(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    uint diff = e - i;
    if(diff < 3) return mem;
    uchar* reg = core->getRegm()[i[1]];
    uchar type = core->getRegt()[i[1]];
    uint sz = sizes[type];
    uint req = sz + 2;
    if(diff < req) return mem;
    copystuff(i + 2, reg, type, type);
    return i + req;
}
//register-to-register: src, tgt
static uchar* mov(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar** regm = core->getRegm();
    uchar* src = regm[i[1]];
    uchar* dst = regm[i[2]];
    uchar* regt = core->getRegt();
    uchar srct = regt[i[1]];
    uchar dstt = regt[i[2]];
    copystuff(src, dst, srct, dstt);
    return i + 3;
}
//register-to-memory: value, target
static uchar* put(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar i1 = i[1];
    uchar i2 = i[2];
    uchar** regm = core->getRegm();
    uchar* r1 = regm[i1];
    uchar* r2 = regm[i2];
    uchar* regt = core->getRegt();
    uchar t1 = regt[i1];
    uchar t2 = regt[i2];
    if(t2 != UINT) return i + 3;
    uchar* tgt = mem + *(uint*)r2;
    copystuff(r1, tgt, t1, t1);
    return i + 3;
}
//memory-to-register: addr, reg
static uchar* get(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar i1 = i[1];
    uchar i2 = i[2];
    uchar** regm = core->getRegm();
    uchar* r1 = regm[i1];
    uchar* r2 = regm[i2];
    uchar* regt = core->getRegt();
    uchar t1 = regt[i1];
    uchar t2 = regt[i2];
    if(t1 != UINT) return i + 3;
    uchar* tgt = mem + *(uint*)r1;
    copystuff(tgt, r2, t2, t2);
    return i + 3;
}
//add reg1 to reg2, store in reg2. dst determines type of operation
static uchar* add(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar** regm = core->getRegm();
    uchar* r1 = regm[i[1]];
    uchar* r2 = regm[i[2]];
    uchar* regt = core->getRegt();
    uchar t1 = regt[i[1]];
    uchar t2 = regt[i[2]];
    uchar t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 + *r2;
            break;
        case UCHARXUSHORT:
            *(ushort*)r2 = *r1 + *(ushort*)r2;
            break;
        case UCHARXUINT:
            *(uint*)r2 = *r1 + *(uint*)r2;
            break;
        case UCHARXFLOAT:
            *(float*)r2 = *r1 + *(float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(ushort*)r1 + *r2;
            break;
        case USHORTXUSHORT:
            *(ushort*)r2 = *(ushort*)r1 + *(ushort*)r2;
            break;
        case USHORTXUINT:
            *(uint*)r2 = *(ushort*)r1 + *(uint*)r2;
            break;
        case USHORTXFLOAT:
            *(float*)r2 = *(ushort*)r1 + *(float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(ushort*)r1 + *r2;
            break;
        case UINTXUSHORT:
            *(ushort*)r2 = *(uint*)r1 + *(ushort*)r2;
            break;
        case UINTXUINT:
            *(uint*)r2 = *(uint*)r1 + *(uint*)r2;
            break;
        case UINTXFLOAT:
            *(float*)r2 = *(uint*)r1 + *(float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(float*)r1 + *r2;
            break;
        case FLOATXUSHORT:
            *(ushort*)r2 = *(float*)r1 + *(ushort*)r2;
            break;
        case FLOATXUINT:
            *(uint*)r2 = *(float*)r1 + *(uint*)r2;
            break;
        case FLOATXFLOAT:
            *(float*)r2 = *(float*)r1 + *(float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uchar* sub(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar** regm = core->getRegm();
    uchar* r1 = regm[i[1]];
    uchar* r2 = regm[i[2]];
    uchar* regt = core->getRegt();
    uchar t1 = regt[i[1]];
    uchar t2 = regt[i[2]];
    uchar t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 - *r2;
            break;
        case UCHARXUSHORT:
            *(ushort*)r2 = *r1 - *(ushort*)r2;
            break;
        case UCHARXUINT:
            *(uint*)r2 = *r1 - *(uint*)r2;
            break;
        case UCHARXFLOAT:
            *(float*)r2 = *r1 - *(float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(ushort*)r1 - *r2;
            break;
        case USHORTXUSHORT:
            *(ushort*)r2 = *(ushort*)r1 - *(ushort*)r2;
            break;
        case USHORTXUINT:
            *(uint*)r2 = *(ushort*)r1 - *(uint*)r2;
            break;
        case USHORTXFLOAT:
            *(float*)r2 = *(ushort*)r1 - *(float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(ushort*)r1 - *r2;
            break;
        case UINTXUSHORT:
            *(ushort*)r2 = *(uint*)r1 - *(ushort*)r2;
            break;
        case UINTXUINT:
            *(uint*)r2 = *(uint*)r1 - *(uint*)r2;
            break;
        case UINTXFLOAT:
            *(float*)r2 = *(uint*)r1 - *(float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(float*)r1 - *r2;
            break;
        case FLOATXUSHORT:
            *(ushort*)r2 = *(float*)r1 - *(ushort*)r2;
            break;
        case FLOATXUINT:
            *(uint*)r2 = *(float*)r1 - *(uint*)r2;
            break;
        case FLOATXFLOAT:
            *(float*)r2 = *(float*)r1 - *(float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uchar* inc(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 2) return mem;
    uchar* reg = core->getRegm()[i[1]];
    uchar type = core->getRegt()[i[1]];
    switch(type)
    {
        case UCHAR:
            ++*reg;
            break;
        case USHORT:
            ++*(ushort*)reg;
            break;
        case UINT:
            ++*(uint*)reg;
            break;
        case FLOAT:
            *(float*)reg = *(float*)reg + 1.f;
            break;
            
        default:
            break;
    }
    return i + 2;
}
static uchar* dec(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 2) return mem;
    uchar* reg = core->getRegm()[i[1]];
    uchar type = core->getRegt()[i[1]];
    switch(type)
    {
        case UCHAR:
            --*reg;
            break;
        case USHORT:
            --*(ushort*)reg;
            break;
        case UINT:
            --*(uint*)reg;
            break;
        case FLOAT:
            *(float*)reg = *(float*)reg - 1.f;
            break;
            
        default:
            break;
    }
    return i + 2;
}
static uchar* mul(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar** regm = core->getRegm();
    uchar* r1 = regm[i[1]];
    uchar* r2 = regm[i[2]];
    uchar* regt = core->getRegt();
    uchar t1 = regt[i[1]];
    uchar t2 = regt[i[2]];
    uchar t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 * *r2;
            break;
        case UCHARXUSHORT:
            *(ushort*)r2 = *r1 * *(ushort*)r2;
            break;
        case UCHARXUINT:
            *(uint*)r2 = *r1 * *(uint*)r2;
            break;
        case UCHARXFLOAT:
            *(float*)r2 = *r1 * *(float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(ushort*)r1 * *r2;
            break;
        case USHORTXUSHORT:
            *(ushort*)r2 = *(ushort*)r1 * *(ushort*)r2;
            break;
        case USHORTXUINT:
            *(uint*)r2 = *(ushort*)r1 * *(uint*)r2;
            break;
        case USHORTXFLOAT:
            *(float*)r2 = *(ushort*)r1 * *(float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(ushort*)r1 * *r2;
            break;
        case UINTXUSHORT:
            *(ushort*)r2 = *(uint*)r1 * *(ushort*)r2;
            break;
        case UINTXUINT:
            *(uint*)r2 = *(uint*)r1 * *(uint*)r2;
            break;
        case UINTXFLOAT:
            *(float*)r2 = *(uint*)r1 * *(float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(float*)r1 * *r2;
            break;
        case FLOATXUSHORT:
            *(ushort*)r2 = *(float*)r1 * *(ushort*)r2;
            break;
        case FLOATXUINT:
            *(uint*)r2 = *(float*)r1 * *(uint*)r2;
            break;
        case FLOATXFLOAT:
            *(float*)r2 = *(float*)r1 * *(float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uchar* div(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar** regm = core->getRegm();
    uchar* r1 = regm[i[1]];
    uchar* r2 = regm[i[2]];
    uchar* regt = core->getRegt();
    uchar t1 = regt[i[1]];
    uchar t2 = regt[i[2]];
    uchar t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 / *r2;
            break;
        case UCHARXUSHORT:
            *(ushort*)r2 = *r1 / *(ushort*)r2;
            break;
        case UCHARXUINT:
            *(uint*)r2 = *r1 / *(uint*)r2;
            break;
        case UCHARXFLOAT:
            *(float*)r2 = *r1 / *(float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(ushort*)r1 / *r2;
            break;
        case USHORTXUSHORT:
            *(ushort*)r2 = *(ushort*)r1 / *(ushort*)r2;
            break;
        case USHORTXUINT:
            *(uint*)r2 = *(ushort*)r1 / *(uint*)r2;
            break;
        case USHORTXFLOAT:
            *(float*)r2 = *(ushort*)r1 / *(float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(ushort*)r1 / *r2;
            break;
        case UINTXUSHORT:
            *(ushort*)r2 = *(uint*)r1 / *(ushort*)r2;
            break;
        case UINTXUINT:
            *(uint*)r2 = *(uint*)r1 / *(uint*)r2;
            break;
        case UINTXFLOAT:
            *(float*)r2 = *(uint*)r1 / *(float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(float*)r1 / *r2;
            break;
        case FLOATXUSHORT:
            *(ushort*)r2 = *(float*)r1 / *(ushort*)r2;
            break;
        case FLOATXUINT:
            *(uint*)r2 = *(float*)r1 / *(uint*)r2;
            break;
        case FLOATXFLOAT:
            *(float*)r2 = *(float*)r1 / *(float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uchar* inot(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar* reg = core->getRegm()[i[1]];
    uchar type = core->getRegt()[i[1]];
    switch(type)
    {
        case UCHAR:
            *(uchar*)reg = ~*(uchar*)reg;
            break;
        case USHORT:
            *(ushort*)reg = ~*(ushort*)reg;
            break;
        case UINT:
        case FLOAT:
            *(uint*)reg = ~*(uint*)reg;
            break;
    }
    return i + 3;
}
static uchar* iand(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar** regm = core->getRegm();
    uchar* r1 = regm[i[1]];
    uchar* r2 = regm[i[2]];
    uchar* regt = core->getRegt();
    uchar t1 = regt[i[1]];
    uchar t2 = regt[i[2]];
    uchar t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 & *r2;
            break;
        case UCHARXUSHORT:
            *(ushort*)r2 = *r1 & *(ushort*)r2;
            break;
        case UCHARXUINT:
        case UCHARXFLOAT:
            *(uint*)r2 = *r1 & *(uint*)r2;
            break;

        case USHORTXUCHAR:
            *r2 = *(ushort*)r1 & *r2;
            break;
        case USHORTXUSHORT:
            *(ushort*)r2 = *(ushort*)r1 & *(ushort*)r2;
            break;
        case USHORTXUINT:
        case USHORTXFLOAT:
            *(uint*)r2 = *(ushort*)r1 & *(uint*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(ushort*)r1 & *r2;
            break;
        case UINTXUSHORT:
            *(ushort*)r2 = *(uint*)r1 & *(ushort*)r2;
            break;
        case UINTXUINT:
        case UINTXFLOAT:
            *(uint*)r2 = *(uint*)r1 & *(uint*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(uint*)r1 & *r2;
            break;
        case FLOATXUSHORT:
            *(ushort*)r2 = *(uint*)r1 & *(ushort*)r2;
            break;
        case FLOATXUINT:
        case FLOATXFLOAT:
            *(uint*)r2 = *(uint*)r1 & *(uint*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uchar* ior(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar** regm = core->getRegm();
    uchar* r1 = regm[i[1]];
    uchar* r2 = regm[i[2]];
    uchar* regt = core->getRegt();
    uchar t1 = regt[i[1]];
    uchar t2 = regt[i[2]];
    uchar t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 | *r2;
            break;
        case UCHARXUSHORT:
            *(ushort*)r2 = *r1 | *(ushort*)r2;
            break;
        case UCHARXUINT:
        case UCHARXFLOAT:
            *(uint*)r2 = *r1 | *(uint*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(ushort*)r1 | *r2;
            break;
        case USHORTXUSHORT:
            *(ushort*)r2 = *(ushort*)r1 | *(ushort*)r2;
            break;
        case USHORTXUINT:
        case USHORTXFLOAT:
            *(uint*)r2 = *(ushort*)r1 | *(uint*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(ushort*)r1 | *r2;
            break;
        case UINTXUSHORT:
            *(ushort*)r2 = *(uint*)r1 | *(ushort*)r2;
            break;
        case UINTXUINT:
        case UINTXFLOAT:
            *(uint*)r2 = *(uint*)r1 | *(uint*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(uint*)r1 | *r2;
            break;
        case FLOATXUSHORT:
            *(ushort*)r2 = *(uint*)r1 | *(ushort*)r2;
            break;
        case FLOATXUINT:
        case FLOATXFLOAT:
            *(uint*)r2 = *(uint*)r1 | *(uint*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uchar* ixor(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar** regm = core->getRegm();
    uchar* r1 = regm[i[1]];
    uchar* r2 = regm[i[2]];
    uchar* regt = core->getRegt();
    uchar t1 = regt[i[1]];
    uchar t2 = regt[i[2]];
    uchar t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 ^ *r2;
            break;
        case UCHARXUSHORT:
            *(ushort*)r2 = *r1 ^ *(ushort*)r2;
            break;
        case UCHARXUINT:
        case UCHARXFLOAT:
            *(uint*)r2 = *r1 ^ *(uint*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(ushort*)r1 ^ *r2;
            break;
        case USHORTXUSHORT:
            *(ushort*)r2 = *(ushort*)r1 ^ *(ushort*)r2;
            break;
        case USHORTXUINT:
        case USHORTXFLOAT:
            *(uint*)r2 = *(ushort*)r1 ^ *(uint*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(ushort*)r1 ^ *r2;
            break;
        case UINTXUSHORT:
            *(ushort*)r2 = *(uint*)r1 ^ *(ushort*)r2;
            break;
        case UINTXUINT:
        case UINTXFLOAT:
            *(uint*)r2 = *(uint*)r1 ^ *(uint*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(uint*)r1 ^ *r2;
            break;
        case FLOATXUSHORT:
            *(ushort*)r2 = *(uint*)r1 ^ *(ushort*)r2;
            break;
        case FLOATXUINT:
        case FLOATXFLOAT:
            *(uint*)r2 = *(uint*)r1 ^ *(uint*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uchar* jmp(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 2) return mem;
    uchar* reg = core->getRegm()[i[1]];
    if(core->getRegt()[i[1]] != UINT) return i + 1;
    return mem + *(uint*)reg;
}
static uchar* jz(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar** regm = core->getRegm();
    uchar* regt = core->getRegt();
    uchar i1 = i[1];
    uchar i2 = i[2];
    if(regt[i2] != UINT) return i + 3;
    uchar* r1 = regm[i1];
    uchar* r2 = regm[i2];
    uchar t1 = regt[i1];
    bool doit;
    switch(t1)
    {
        case UCHAR:
            doit = !*(uchar*)r1;
            break;
        case USHORT:
            doit = !*(ushort*)r1;
            break;
        case UINT:
            doit = !*(uint*)r1;
            break;
        case FLOAT:
            doit = !*(float*)r1;
            break;
        default:
            doit = false;
            break;
    }
    if(!doit) return i + 3;
    return mem + *(uint*)r2;
}
static uchar* jnz(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 3) return mem;
    uchar** regm = core->getRegm();
    uchar* regt = core->getRegt();
    uchar i1 = i[1];
    uchar i2 = i[2];
    if(regt[i2] != UINT) return i + 3;
    uchar* r1 = regm[i1];
    uchar* r2 = regm[i2];
    uchar t1 = regt[i1];
    bool doit;
    switch(t1)
    {
        case UCHAR:
            doit = *(uchar*)r1;
            break;
        case USHORT:
            doit = *(ushort*)r1;
            break;
        case UINT:
            doit = *(uint*)r1;
            break;
        case FLOAT:
            doit = *(float*)r1;
            break;
        default:
            doit = false;
            break;
    }
    if(!doit) return i + 3;
    return mem + *(uint*)r2;
}
static uchar* prt(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 2) return mem;
    uchar i1 = i[1];
    uchar* reg = core->getRegm()[i[1]];
    uchar type = core->getRegt()[i[1]];
    switch(type)
    {
        case UCHAR:
            printf("reg[%x] = %2x\n", i1, *reg);
            break;
        case USHORT:
            printf("reg[%x] = %4x\n", i1, *(ushort*)reg);
            break;
        case UINT:
            printf("reg[%x] = %8x\n", i1, *(uint*)reg);
            break;
        case FLOAT:
            printf("reg[%x] = %f\n", i1, *(float*)reg);
            break;
    }
    return i + 2;
}

