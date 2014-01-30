#include <cstdio>
#include "EmuCore.hpp"

using namespace emu;
using namespace std;
///////////////////////////////////////////////////////////////////////////////
static uchar*  nop        (uchar*, uchar*, void*); //done
static uchar*  set_ivrv   (uchar*, uchar*, void*); //done
static uchar*  set_ivrr   (uchar*, uchar*, void*);
static uchar*  set_ivir   (uchar*, uchar*, void*);
static uchar*  mov_rvrv   (uchar*, uchar*, void*); //done
static uchar*  get_irrv   (uchar*, uchar*, void*);
static uchar*  get_rrrv   (uchar*, uchar*, void*); //done
static uchar*  put_rvir   (uchar*, uchar*, void*);
static uchar*  put_rvrr   (uchar*, uchar*, void*); //done
static uchar* push_rrrv   (uchar*, uchar*, void*);
static uchar* push_irrv   (uchar*, uchar*, void*);
static uchar*  pop_rrrv   (uchar*, uchar*, void*);
static uchar*  pop_irrv   (uchar*, uchar*, void*);
static uchar*  lea_rrivrv (uchar*, uchar*, void*);
static uchar*  lea_rrrvrv (uchar*, uchar*, void*);
static uchar*  lea_irivrv (uchar*, uchar*, void*);
static uchar*  add_rvrv   (uchar*, uchar*, void*); //done
static uchar*  add_ivrv   (uchar*, uchar*, void*);
static uchar*  sub_rvrv   (uchar*, uchar*, void*); //done
static uchar*  sub_ivrv   (uchar*, uchar*, void*);
static uchar*  inc_rv     (uchar*, uchar*, void*); //done
static uchar*  dec_rv     (uchar*, uchar*, void*); //done
static uchar*  mul_rvrv   (uchar*, uchar*, void*); //done
static uchar*  mul_ivrv   (uchar*, uchar*, void*);
static uchar*  div_rvrv   (uchar*, uchar*, void*); //done
static uchar*  div_ivrv   (uchar*, uchar*, void*);
static uchar*  mod_rvrv   (uchar*, uchar*, void*);
static uchar*  mod_ivrv   (uchar*, uchar*, void*);
static uchar*  pow_rvrv   (uchar*, uchar*, void*);
static uchar*  pow_ivrv   (uchar*, uchar*, void*);
static uchar*  neg_rv     (uchar*, uchar*, void*);
static uchar* sqrt_rv     (uchar*, uchar*, void*);
static uchar*  not_rv     (uchar*, uchar*, void*); //done
static uchar*  and_rvrv   (uchar*, uchar*, void*); //done
static uchar*  and_ivrv   (uchar*, uchar*, void*);
static uchar*   or_rvrv   (uchar*, uchar*, void*); //done
static uchar*   or_ivrv   (uchar*, uchar*, void*);
static uchar*  xor_rvrv   (uchar*, uchar*, void*); //done
static uchar*  xor_ivrv   (uchar*, uchar*, void*);
static uchar*   lg_rv     (uchar*, uchar*, void*);
static uchar*  lsh_rvrv   (uchar*, uchar*, void*);
static uchar*  lsh_ivrv   (uchar*, uchar*, void*);
static uchar*  rsh_rvrv   (uchar*, uchar*, void*);
static uchar*  rsh_ivrv   (uchar*, uchar*, void*);
static uchar*  ars_rvrv   (uchar*, uchar*, void*);
static uchar*  ars_ivrv   (uchar*, uchar*, void*);
static uchar*  jmp_rr     (uchar*, uchar*, void*); //done
static uchar*  jmp_ir     (uchar*, uchar*, void*);
static uchar*   jz_rvrr   (uchar*, uchar*, void*); //done
static uchar*   jz_rvir   (uchar*, uchar*, void*);
static uchar*  jnz_rvrr   (uchar*, uchar*, void*); //done
static uchar*  jnz_rvir   (uchar*, uchar*, void*);
static uchar*   jn_rvrr   (uchar*, uchar*, void*);
static uchar*   jn_rvir   (uchar*, uchar*, void*);
static uchar*  jnn_rvrr   (uchar*, uchar*, void*);
static uchar*  jnn_rvir   (uchar*, uchar*, void*);
static uchar* jmpr_rr     (uchar*, uchar*, void*);
static uchar* jmpr_ir     (uchar*, uchar*, void*);
static uchar*  jzr_rvrr   (uchar*, uchar*, void*);
static uchar*  jzr_rvir   (uchar*, uchar*, void*);
static uchar* jnzr_rvrr   (uchar*, uchar*, void*);
static uchar* jnzr_rvir   (uchar*, uchar*, void*);
static uchar*  jnr_rvrr   (uchar*, uchar*, void*);
static uchar*  jnr_rvir   (uchar*, uchar*, void*);
static uchar* jnnr_rvrr   (uchar*, uchar*, void*);
static uchar* jnnr_rvir   (uchar*, uchar*, void*);
static uchar*  prt_rv     (uchar*, uchar*, void*); //done
static uchar*  prt_ir     (uchar*, uchar*, void*);
static uchar*  prt_rr     (uchar*, uchar*, void*);
//  BASIC TYPES  //////////////////////////////////////////////////////////////
static const uchar UCHAR  = 0;
static const uchar USHORT = 1;
static const uchar UINT   = 2;
static const uchar FLOAT  = 3;
//  SIZES OF BASIC TYPES
static const uint sizes [4] = {1, 2, 4, 4};
//  CORRESPONDS TO 'dual' (below)  ////////////////////////////////////////////
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
static const uchar  uchars  [4] = {0 , 1 , 2 , 3 };
static const uchar  ushorts [4] = {4 , 5 , 6 , 7 };
static const uchar  uints   [4] = {8 , 9 , 10, 11};
static const uchar  floats  [4] = {12, 13, 14, 15};
static const uchar* dual    [4] = {uchars, ushorts, uints, floats};
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
    
    itable[0x00] =  nop        ;
    itable[0x01] =  set_ivrv   ;
    //itable[0x02] =  set_ivir   ;
    //itable[0x03] =  set_ivrr   ;
    itable[0x04] =  mov_rvrv   ;
    //itable[0x05] =  get_irrv   ;
    itable[0x06] =  get_rrrv   ;
    //itable[0x07] =  put_rvir   ;
    itable[0x08] =  put_rvrr   ;
    //itable[0x09] = push_rrrv   ;
    //itable[0x0A] = push_irrv   ;
    //itable[0x0B] =  pop_rrrv   ;
    //itable[0x0C] =  pop_irrv   ;
    //itable[0x0D] =  lea_rrivrv ;
    //itable[0x0E] =  lea_rrrvrv ;
    //itable[0x0F] =  lea_irivrv ;
    //itable[0x10] =  add_ivrv   ;
    itable[0x11] =  add_rvrv   ;
    //itable[0x12] =  sub_ivrv   ;
    itable[0x13] =  sub_rvrv   ;
    itable[0x14] =  inc_rv     ;
    itable[0x15] =  dec_rv     ;
    //itable[0x16] =  mul_ivrv   ;
    itable[0x17] =  mul_rvrv   ;
    //itable[0x18] =  neg_rv     ;
    //itable[0x19] =  div_ivrv   ;
    itable[0x1A] =  div_rvrv   ;
    //itable[0x1B] =  mod_ivrv   ;
    //itable[0x1C] =  mod_rvrv   ;
    //itable[0x1D] =  pow_ivrv   ;
    //itable[0x1E] =  pow_rvrv   ;
    //itable[0x1F] = sqrt_rv     ;
    itable[0x20] =  not_rv     ;
    //itable[0x21] =  and_ivrv   ;
    itable[0x22] =  and_rvrv   ;
    //itable[0x23] =   or_ivrv   ;
    itable[0x24] =   or_rvrv   ;
    //itable[0x25] =  xor_ivrv   ;
    itable[0x26] =  xor_rvrv   ;
    //itable[0x27] =   lg_rv     ;
    //itable[0x28] =  lsh_ivrv   ;
    //itable[0x29] =  lsh_rvrv   ;
    //itable[0x2A] =  rsh_ivrv   ;
    //itable[0x2B] =  rsh_rvrv   ;
    //itable[0x2C] =  ars_ivrv   ;
    //itable[0x2D] =  ars_rvrv   ;
    itable[0x2E] =  jmp_rr     ;
    itable[0x2F] =   jz_rvrr   ;
    itable[0x30] =  jnz_rvrr   ;
    itable[0x31] =  prt_rv     ;
    for(int i = 0x32; i < 0x100; i++)
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
static uchar* set_ivrv(uchar* i, uchar* e, void* c)
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
static uchar*  set_ivrr   (uchar*, uchar*, void*);
static uchar*  set_ivir   (uchar*, uchar*, void*);
//register-to-register: src, tgt
static uchar* mov_rvrv(uchar* i, uchar* e, void* c)
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
static uchar*  get_irrv   (uchar*, uchar*, void*);
//memory-to-register
static uchar* get_rrrv(uchar* i, uchar* e, void* c)
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
static uchar*  put_rvir   (uchar*, uchar*, void*);
//register-to-memory: value, target
static uchar* put_rvrr(uchar* i, uchar* e, void* c)
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
static uchar* push_rrrv   (uchar*, uchar*, void*);
static uchar* push_irrv   (uchar*, uchar*, void*);
static uchar*  pop_rrrv   (uchar*, uchar*, void*);
static uchar*  pop_irrv   (uchar*, uchar*, void*);
static uchar*  lea_rrivrv (uchar*, uchar*, void*);
static uchar*  lea_rrrvrv (uchar*, uchar*, void*);
static uchar*  lea_irivrv (uchar*, uchar*, void*);
//add reg1 to reg2, store in reg2. dst determines type of operation
static uchar* add_rvrv(uchar* i, uchar* e, void* c)
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
static uchar*  add_ivrv   (uchar*, uchar*, void*);
static uchar* sub_rvrv(uchar* i, uchar* e, void* c)
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
static uchar*  sub_ivrv   (uchar*, uchar*, void*);
static uchar* inc_rv(uchar* i, uchar* e, void* c)
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
static uchar* dec_rv(uchar* i, uchar* e, void* c)
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
static uchar* mul_rvrv(uchar* i, uchar* e, void* c)
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
static uchar*  mul_ivrv   (uchar*, uchar*, void*);
static uchar* div_rvrv(uchar* i, uchar* e, void* c)
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
static uchar*  div_ivrv   (uchar*, uchar*, void*);
static uchar*  mod_rvrv   (uchar*, uchar*, void*);
static uchar*  mod_ivrv   (uchar*, uchar*, void*);
static uchar*  pow_rvrv   (uchar*, uchar*, void*);
static uchar*  pow_ivrv   (uchar*, uchar*, void*);
static uchar* not_rv(uchar* i, uchar* e, void* c)
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
static uchar* and_rvrv(uchar* i, uchar* e, void* c)
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
static uchar*  and_ivrv   (uchar*, uchar*, void*);
static uchar* or_rvrv(uchar* i, uchar* e, void* c)
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
static uchar*   or_ivrv   (uchar*, uchar*, void*);
static uchar* xor_rvrv(uchar* i, uchar* e, void* c)
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
static uchar*  xor_ivrv   (uchar*, uchar*, void*);
static uchar*   lg_rv     (uchar*, uchar*, void*);
static uchar*  lsh_rvrv   (uchar*, uchar*, void*);
static uchar*  lsh_ivrv   (uchar*, uchar*, void*);
static uchar*  rsh_rvrv   (uchar*, uchar*, void*);
static uchar*  rsh_ivrv   (uchar*, uchar*, void*);
static uchar*  ars_rvrv   (uchar*, uchar*, void*);
static uchar*  ars_ivrv   (uchar*, uchar*, void*);
static uchar* jmp_rr(uchar* i, uchar* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uchar* mem = core->getMem();
    if(e - i < 2) return mem;
    uchar* reg = core->getRegm()[i[1]];
    if(core->getRegt()[i[1]] != UINT) return i + 1;
    return mem + *(uint*)reg;
}
static uchar*  jmp_ir     (uchar*, uchar*, void*);
static uchar* jz_rvrr(uchar* i, uchar* e, void* c)
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
static uchar*  jz_rvir     (uchar*, uchar*, void*);
static uchar* jnz_rvrr(uchar* i, uchar* e, void* c)
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
static uchar*  jnz_rvir   (uchar*, uchar*, void*);
static uchar*   jn_rvrr   (uchar*, uchar*, void*);
static uchar*   jn_rvir   (uchar*, uchar*, void*);
static uchar*  jnn_rvrr   (uchar*, uchar*, void*);
static uchar*  jnn_rvir   (uchar*, uchar*, void*);
static uchar* jmpr_rr     (uchar*, uchar*, void*);
static uchar* jmpr_ir     (uchar*, uchar*, void*);
static uchar*  jzr_rvrr   (uchar*, uchar*, void*);
static uchar*  jzr_rvir   (uchar*, uchar*, void*);
static uchar* jnzr_rvrr   (uchar*, uchar*, void*);
static uchar* jnzr_rvir   (uchar*, uchar*, void*);
static uchar*  jnr_rvrr   (uchar*, uchar*, void*);
static uchar*  jnr_rvir   (uchar*, uchar*, void*);
static uchar* jnnr_rvrr   (uchar*, uchar*, void*);
static uchar* jnnr_rvir   (uchar*, uchar*, void*);
static uchar* prt_rv(uchar* i, uchar* e, void* c)
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
static uchar*  prt_ir     (uchar*, uchar*, void*);
static uchar*  prt_rr     (uchar*, uchar*, void*);
