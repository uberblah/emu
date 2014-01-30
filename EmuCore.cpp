#include <cstdio>
#include "EmuCore.hpp"

using namespace emu;
using namespace std;
///////////////////////////////////////////////////////////////////////////////
static uint8_t*  nop        (uint8_t*, uint8_t*, void*); //done
static uint8_t*  set_ivrv   (uint8_t*, uint8_t*, void*); //done
static uint8_t*  set_ivrr   (uint8_t*, uint8_t*, void*);
static uint8_t*  set_ivir   (uint8_t*, uint8_t*, void*);
static uint8_t*  mov_rvrv   (uint8_t*, uint8_t*, void*); //done
static uint8_t*  get_irrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  get_rrrv   (uint8_t*, uint8_t*, void*); //done
static uint8_t*  put_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t*  put_rvrr   (uint8_t*, uint8_t*, void*); //done
static uint8_t* push_rrrv   (uint8_t*, uint8_t*, void*);
static uint8_t* push_irrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  pop_rrrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  pop_irrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  lea_rrivrv (uint8_t*, uint8_t*, void*);
static uint8_t*  lea_rrrvrv (uint8_t*, uint8_t*, void*);
static uint8_t*  lea_irivrv (uint8_t*, uint8_t*, void*);
static uint8_t*  add_rvrv   (uint8_t*, uint8_t*, void*); //done
static uint8_t*  add_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  sub_rvrv   (uint8_t*, uint8_t*, void*); //done
static uint8_t*  sub_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  inc_rv     (uint8_t*, uint8_t*, void*); //done
static uint8_t*  dec_rv     (uint8_t*, uint8_t*, void*); //done
static uint8_t*  mul_rvrv   (uint8_t*, uint8_t*, void*); //done
static uint8_t*  mul_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  div_rvrv   (uint8_t*, uint8_t*, void*); //done
static uint8_t*  div_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  mod_rvrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  mod_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  pow_rvrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  pow_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  neg_rv     (uint8_t*, uint8_t*, void*);
static uint8_t* sqrt_rv     (uint8_t*, uint8_t*, void*);
static uint8_t*  not_rv     (uint8_t*, uint8_t*, void*); //done
static uint8_t*  and_rvrv   (uint8_t*, uint8_t*, void*); //done
static uint8_t*  and_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*   or_rvrv   (uint8_t*, uint8_t*, void*); //done
static uint8_t*   or_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  xor_rvrv   (uint8_t*, uint8_t*, void*); //done
static uint8_t*  xor_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*   lg_rv     (uint8_t*, uint8_t*, void*);
static uint8_t*  lsh_rvrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  lsh_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  rsh_rvrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  rsh_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  ars_rvrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  ars_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  jmp_rr     (uint8_t*, uint8_t*, void*); //done
static uint8_t*  jmp_ir     (uint8_t*, uint8_t*, void*);
static uint8_t*   jz_rvrr   (uint8_t*, uint8_t*, void*); //done
static uint8_t*   jz_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t*  jnz_rvrr   (uint8_t*, uint8_t*, void*); //done
static uint8_t*  jnz_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t*   jn_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t*   jn_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t*  jnn_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t*  jnn_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t* jmpr_rr     (uint8_t*, uint8_t*, void*);
static uint8_t* jmpr_ir     (uint8_t*, uint8_t*, void*);
static uint8_t*  jzr_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t*  jzr_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t* jnzr_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t* jnzr_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t*  jnr_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t*  jnr_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t* jnnr_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t* jnnr_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t*  prt_rv     (uint8_t*, uint8_t*, void*); //done
static uint8_t*  prt_ir     (uint8_t*, uint8_t*, void*);
static uint8_t*  prt_rr     (uint8_t*, uint8_t*, void*);
//  BASIC TYPES  //////////////////////////////////////////////////////////////
static const uint8_t UCHAR  = 0;
static const uint8_t USHORT = 1;
static const uint8_t UINT   = 2;
static const uint8_t FLOAT  = 3;
//  SIZES OF BASIC TYPES
static const uint32_t sizes [4] = {1, 2, 4, 4};
//  CORRESPONDS TO 'dual' (below)  ////////////////////////////////////////////
static const uint8_t UCHARXUCHAR   = 0 ;
static const uint8_t UCHARXUSHORT  = 1 ;
static const uint8_t UCHARXUINT    = 2 ;
static const uint8_t UCHARXFLOAT   = 3 ;

static const uint8_t USHORTXUCHAR  = 4 ;
static const uint8_t USHORTXUSHORT = 5 ;
static const uint8_t USHORTXUINT   = 6 ;
static const uint8_t USHORTXFLOAT  = 7 ;

static const uint8_t UINTXUCHAR    = 8 ;
static const uint8_t UINTXUSHORT   = 9 ;
static const uint8_t UINTXUINT     = 10;
static const uint8_t UINTXFLOAT    = 11;

static const uint8_t FLOATXUCHAR   = 12;
static const uint8_t FLOATXUSHORT  = 13;
static const uint8_t FLOATXUINT    = 14;
static const uint8_t FLOATXFLOAT   = 15;
///////////////////////////////////////////////////////////////////////////////
static const uint8_t  uint8_ts  [4] = {0 , 1 , 2 , 3 };
static const uint8_t  uint16_ts [4] = {4 , 5 , 6 , 7 };
static const uint8_t  uint32_ts   [4] = {8 , 9 , 10, 11};
static const uint8_t  floats  [4] = {12, 13, 14, 15};
static const uint8_t* dual    [4] = {uint8_ts, uint16_ts, uint32_ts, floats};
///////////////////////////////////////////////////////////////////////////////
static inline void copystuff(uint8_t* src, uint8_t* dst, uint8_t type)
{
    switch(type)
    {
        case UCHAR:
            *dst = *src;
            break;
        case USHORT:
            *(uint16_t*)dst = *(uint16_t*)src;
            break;
        case UINT:
            *(uint32_t*)dst = *(uint32_t*)src;
            break;
        case FLOAT:
            *(float*)dst = *(float*)src;
            break;
        default:
            break;
    }
}
static inline void copystuff(uint8_t* src, uint8_t* dst, uint8_t type1, uint8_t type2)
{
    if(type1 > type2) type1 = type2;
    copystuff(src, dst, type1);
}
//7:bits, 3:flgs, 3:oflo
static const uint32_t regsize = 128;

EmuCore::EmuCore()
{
    mem = new uint8_t[4096];
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
    
    regs = new uint8_t[regsize];
    regm = new uint8_t*[0x100];
    regt = new uint8_t[0x100];
    uint8_t* c = regs;
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
static uint8_t* nop(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    i++;
    if(i == e)
    {
        EmuCore* core = (EmuCore*)c;
        return mem;
    }
    return i;
}
//constant-to-register
static uint8_t* set_ivrv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    uint32_t diff = e - i;
    if(diff < 3) return mem;
    uint8_t* reg = core->getRegm()[i[1]];
    uint8_t type = core->getRegt()[i[1]];
    uint32_t sz = sizes[type];
    uint32_t req = sz + 2;
    if(diff < req) return mem;
    copystuff(i + 2, reg, type, type);
    return i + req;
}
static uint8_t*  set_ivrr   (uint8_t*, uint8_t*, void*);
static uint8_t*  set_ivir   (uint8_t*, uint8_t*, void*);
//register-to-register: src, tgt
static uint8_t* mov_rvrv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t** regm = core->getRegm();
    uint8_t* src = regm[i[1]];
    uint8_t* dst = regm[i[2]];
    uint8_t* regt = core->getRegt();
    uint8_t srct = regt[i[1]];
    uint8_t dstt = regt[i[2]];
    copystuff(src, dst, srct, dstt);
    return i + 3;
}
static uint8_t*  get_irrv   (uint8_t*, uint8_t*, void*);
//memory-to-register
static uint8_t* get_rrrv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t i1 = i[1];
    uint8_t i2 = i[2];
    uint8_t** regm = core->getRegm();
    uint8_t* r1 = regm[i1];
    uint8_t* r2 = regm[i2];
    uint8_t* regt = core->getRegt();
    uint8_t t1 = regt[i1];
    uint8_t t2 = regt[i2];
    if(t1 != UINT) return i + 3;
    uint8_t* tgt = mem + *(uint32_t*)r1;
    copystuff(tgt, r2, t2, t2);
    return i + 3;
}
static uint8_t*  put_rvir   (uint8_t*, uint8_t*, void*);
//register-to-memory: value, target
static uint8_t* put_rvrr(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t i1 = i[1];
    uint8_t i2 = i[2];
    uint8_t** regm = core->getRegm();
    uint8_t* r1 = regm[i1];
    uint8_t* r2 = regm[i2];
    uint8_t* regt = core->getRegt();
    uint8_t t1 = regt[i1];
    uint8_t t2 = regt[i2];
    if(t2 != UINT) return i + 3;
    uint8_t* tgt = mem + *(uint32_t*)r2;
    copystuff(r1, tgt, t1, t1);
    return i + 3;
}
static uint8_t* push_rrrv   (uint8_t*, uint8_t*, void*);
static uint8_t* push_irrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  pop_rrrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  pop_irrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  lea_rrivrv (uint8_t*, uint8_t*, void*);
static uint8_t*  lea_rrrvrv (uint8_t*, uint8_t*, void*);
static uint8_t*  lea_irivrv (uint8_t*, uint8_t*, void*);
//add reg1 to reg2, store in reg2. dst determines type of operation
static uint8_t* add_rvrv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t** regm = core->getRegm();
    uint8_t* r1 = regm[i[1]];
    uint8_t* r2 = regm[i[2]];
    uint8_t* regt = core->getRegt();
    uint8_t t1 = regt[i[1]];
    uint8_t t2 = regt[i[2]];
    uint8_t t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 + *r2;
            break;
        case UCHARXUSHORT:
            *(uint16_t*)r2 = *r1 + *(uint16_t*)r2;
            break;
        case UCHARXUINT:
            *(uint32_t*)r2 = *r1 + *(uint32_t*)r2;
            break;
        case UCHARXFLOAT:
            *(float*)r2 = *r1 + *(float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(uint16_t*)r1 + *r2;
            break;
        case USHORTXUSHORT:
            *(uint16_t*)r2 = *(uint16_t*)r1 + *(uint16_t*)r2;
            break;
        case USHORTXUINT:
            *(uint32_t*)r2 = *(uint16_t*)r1 + *(uint32_t*)r2;
            break;
        case USHORTXFLOAT:
            *(float*)r2 = *(uint16_t*)r1 + *(float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(uint16_t*)r1 + *r2;
            break;
        case UINTXUSHORT:
            *(uint16_t*)r2 = *(uint32_t*)r1 + *(uint16_t*)r2;
            break;
        case UINTXUINT:
            *(uint32_t*)r2 = *(uint32_t*)r1 + *(uint32_t*)r2;
            break;
        case UINTXFLOAT:
            *(float*)r2 = *(uint32_t*)r1 + *(float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(float*)r1 + *r2;
            break;
        case FLOATXUSHORT:
            *(uint16_t*)r2 = *(float*)r1 + *(uint16_t*)r2;
            break;
        case FLOATXUINT:
            *(uint32_t*)r2 = *(float*)r1 + *(uint32_t*)r2;
            break;
        case FLOATXFLOAT:
            *(float*)r2 = *(float*)r1 + *(float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uint8_t*  add_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t* sub_rvrv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t** regm = core->getRegm();
    uint8_t* r1 = regm[i[1]];
    uint8_t* r2 = regm[i[2]];
    uint8_t* regt = core->getRegt();
    uint8_t t1 = regt[i[1]];
    uint8_t t2 = regt[i[2]];
    uint8_t t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 - *r2;
            break;
        case UCHARXUSHORT:
            *(uint16_t*)r2 = *r1 - *(uint16_t*)r2;
            break;
        case UCHARXUINT:
            *(uint32_t*)r2 = *r1 - *(uint32_t*)r2;
            break;
        case UCHARXFLOAT:
            *(float*)r2 = *r1 - *(float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(uint16_t*)r1 - *r2;
            break;
        case USHORTXUSHORT:
            *(uint16_t*)r2 = *(uint16_t*)r1 - *(uint16_t*)r2;
            break;
        case USHORTXUINT:
            *(uint32_t*)r2 = *(uint16_t*)r1 - *(uint32_t*)r2;
            break;
        case USHORTXFLOAT:
            *(float*)r2 = *(uint16_t*)r1 - *(float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(uint16_t*)r1 - *r2;
            break;
        case UINTXUSHORT:
            *(uint16_t*)r2 = *(uint32_t*)r1 - *(uint16_t*)r2;
            break;
        case UINTXUINT:
            *(uint32_t*)r2 = *(uint32_t*)r1 - *(uint32_t*)r2;
            break;
        case UINTXFLOAT:
            *(float*)r2 = *(uint32_t*)r1 - *(float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(float*)r1 - *r2;
            break;
        case FLOATXUSHORT:
            *(uint16_t*)r2 = *(float*)r1 - *(uint16_t*)r2;
            break;
        case FLOATXUINT:
            *(uint32_t*)r2 = *(float*)r1 - *(uint32_t*)r2;
            break;
        case FLOATXFLOAT:
            *(float*)r2 = *(float*)r1 - *(float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uint8_t*  sub_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t* inc_rv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 2) return mem;
    uint8_t* reg = core->getRegm()[i[1]];
    uint8_t type = core->getRegt()[i[1]];
    switch(type)
    {
        case UCHAR:
            ++*reg;
            break;
        case USHORT:
            ++*(uint16_t*)reg;
            break;
        case UINT:
            ++*(uint32_t*)reg;
            break;
        case FLOAT:
            *(float*)reg = *(float*)reg + 1.f;
            break;
            
        default:
            break;
    }
    return i + 2;
}
static uint8_t* dec_rv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 2) return mem;
    uint8_t* reg = core->getRegm()[i[1]];
    uint8_t type = core->getRegt()[i[1]];
    switch(type)
    {
        case UCHAR:
            --*reg;
            break;
        case USHORT:
            --*(uint16_t*)reg;
            break;
        case UINT:
            --*(uint32_t*)reg;
            break;
        case FLOAT:
            *(float*)reg = *(float*)reg - 1.f;
            break;
            
        default:
            break;
    }
    return i + 2;
}
static uint8_t* mul_rvrv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t** regm = core->getRegm();
    uint8_t* r1 = regm[i[1]];
    uint8_t* r2 = regm[i[2]];
    uint8_t* regt = core->getRegt();
    uint8_t t1 = regt[i[1]];
    uint8_t t2 = regt[i[2]];
    uint8_t t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 * *r2;
            break;
        case UCHARXUSHORT:
            *(uint16_t*)r2 = *r1 * *(uint16_t*)r2;
            break;
        case UCHARXUINT:
            *(uint32_t*)r2 = *r1 * *(uint32_t*)r2;
            break;
        case UCHARXFLOAT:
            *(float*)r2 = *r1 * *(float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(uint16_t*)r1 * *r2;
            break;
        case USHORTXUSHORT:
            *(uint16_t*)r2 = *(uint16_t*)r1 * *(uint16_t*)r2;
            break;
        case USHORTXUINT:
            *(uint32_t*)r2 = *(uint16_t*)r1 * *(uint32_t*)r2;
            break;
        case USHORTXFLOAT:
            *(float*)r2 = *(uint16_t*)r1 * *(float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(uint16_t*)r1 * *r2;
            break;
        case UINTXUSHORT:
            *(uint16_t*)r2 = *(uint32_t*)r1 * *(uint16_t*)r2;
            break;
        case UINTXUINT:
            *(uint32_t*)r2 = *(uint32_t*)r1 * *(uint32_t*)r2;
            break;
        case UINTXFLOAT:
            *(float*)r2 = *(uint32_t*)r1 * *(float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(float*)r1 * *r2;
            break;
        case FLOATXUSHORT:
            *(uint16_t*)r2 = *(float*)r1 * *(uint16_t*)r2;
            break;
        case FLOATXUINT:
            *(uint32_t*)r2 = *(float*)r1 * *(uint32_t*)r2;
            break;
        case FLOATXFLOAT:
            *(float*)r2 = *(float*)r1 * *(float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uint8_t*  mul_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t* div_rvrv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t** regm = core->getRegm();
    uint8_t* r1 = regm[i[1]];
    uint8_t* r2 = regm[i[2]];
    uint8_t* regt = core->getRegt();
    uint8_t t1 = regt[i[1]];
    uint8_t t2 = regt[i[2]];
    uint8_t t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 / *r2;
            break;
        case UCHARXUSHORT:
            *(uint16_t*)r2 = *r1 / *(uint16_t*)r2;
            break;
        case UCHARXUINT:
            *(uint32_t*)r2 = *r1 / *(uint32_t*)r2;
            break;
        case UCHARXFLOAT:
            *(float*)r2 = *r1 / *(float*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(uint16_t*)r1 / *r2;
            break;
        case USHORTXUSHORT:
            *(uint16_t*)r2 = *(uint16_t*)r1 / *(uint16_t*)r2;
            break;
        case USHORTXUINT:
            *(uint32_t*)r2 = *(uint16_t*)r1 / *(uint32_t*)r2;
            break;
        case USHORTXFLOAT:
            *(float*)r2 = *(uint16_t*)r1 / *(float*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(uint16_t*)r1 / *r2;
            break;
        case UINTXUSHORT:
            *(uint16_t*)r2 = *(uint32_t*)r1 / *(uint16_t*)r2;
            break;
        case UINTXUINT:
            *(uint32_t*)r2 = *(uint32_t*)r1 / *(uint32_t*)r2;
            break;
        case UINTXFLOAT:
            *(float*)r2 = *(uint32_t*)r1 / *(float*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(float*)r1 / *r2;
            break;
        case FLOATXUSHORT:
            *(uint16_t*)r2 = *(float*)r1 / *(uint16_t*)r2;
            break;
        case FLOATXUINT:
            *(uint32_t*)r2 = *(float*)r1 / *(uint32_t*)r2;
            break;
        case FLOATXFLOAT:
            *(float*)r2 = *(float*)r1 / *(float*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uint8_t*  div_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  mod_rvrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  mod_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  pow_rvrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  pow_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t* not_rv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t* reg = core->getRegm()[i[1]];
    uint8_t type = core->getRegt()[i[1]];
    switch(type)
    {
        case UCHAR:
            *(uint8_t*)reg = ~*(uint8_t*)reg;
            break;
        case USHORT:
            *(uint16_t*)reg = ~*(uint16_t*)reg;
            break;
        case UINT:
        case FLOAT:
            *(uint32_t*)reg = ~*(uint32_t*)reg;
            break;
    }
    return i + 3;
}
static uint8_t* and_rvrv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t** regm = core->getRegm();
    uint8_t* r1 = regm[i[1]];
    uint8_t* r2 = regm[i[2]];
    uint8_t* regt = core->getRegt();
    uint8_t t1 = regt[i[1]];
    uint8_t t2 = regt[i[2]];
    uint8_t t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 & *r2;
            break;
        case UCHARXUSHORT:
            *(uint16_t*)r2 = *r1 & *(uint16_t*)r2;
            break;
        case UCHARXUINT:
        case UCHARXFLOAT:
            *(uint32_t*)r2 = *r1 & *(uint32_t*)r2;
            break;

        case USHORTXUCHAR:
            *r2 = *(uint16_t*)r1 & *r2;
            break;
        case USHORTXUSHORT:
            *(uint16_t*)r2 = *(uint16_t*)r1 & *(uint16_t*)r2;
            break;
        case USHORTXUINT:
        case USHORTXFLOAT:
            *(uint32_t*)r2 = *(uint16_t*)r1 & *(uint32_t*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(uint16_t*)r1 & *r2;
            break;
        case UINTXUSHORT:
            *(uint16_t*)r2 = *(uint32_t*)r1 & *(uint16_t*)r2;
            break;
        case UINTXUINT:
        case UINTXFLOAT:
            *(uint32_t*)r2 = *(uint32_t*)r1 & *(uint32_t*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(uint32_t*)r1 & *r2;
            break;
        case FLOATXUSHORT:
            *(uint16_t*)r2 = *(uint32_t*)r1 & *(uint16_t*)r2;
            break;
        case FLOATXUINT:
        case FLOATXFLOAT:
            *(uint32_t*)r2 = *(uint32_t*)r1 & *(uint32_t*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uint8_t*  and_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t* or_rvrv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t** regm = core->getRegm();
    uint8_t* r1 = regm[i[1]];
    uint8_t* r2 = regm[i[2]];
    uint8_t* regt = core->getRegt();
    uint8_t t1 = regt[i[1]];
    uint8_t t2 = regt[i[2]];
    uint8_t t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 | *r2;
            break;
        case UCHARXUSHORT:
            *(uint16_t*)r2 = *r1 | *(uint16_t*)r2;
            break;
        case UCHARXUINT:
        case UCHARXFLOAT:
            *(uint32_t*)r2 = *r1 | *(uint32_t*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(uint16_t*)r1 | *r2;
            break;
        case USHORTXUSHORT:
            *(uint16_t*)r2 = *(uint16_t*)r1 | *(uint16_t*)r2;
            break;
        case USHORTXUINT:
        case USHORTXFLOAT:
            *(uint32_t*)r2 = *(uint16_t*)r1 | *(uint32_t*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(uint16_t*)r1 | *r2;
            break;
        case UINTXUSHORT:
            *(uint16_t*)r2 = *(uint32_t*)r1 | *(uint16_t*)r2;
            break;
        case UINTXUINT:
        case UINTXFLOAT:
            *(uint32_t*)r2 = *(uint32_t*)r1 | *(uint32_t*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(uint32_t*)r1 | *r2;
            break;
        case FLOATXUSHORT:
            *(uint16_t*)r2 = *(uint32_t*)r1 | *(uint16_t*)r2;
            break;
        case FLOATXUINT:
        case FLOATXFLOAT:
            *(uint32_t*)r2 = *(uint32_t*)r1 | *(uint32_t*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uint8_t*   or_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t* xor_rvrv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t** regm = core->getRegm();
    uint8_t* r1 = regm[i[1]];
    uint8_t* r2 = regm[i[2]];
    uint8_t* regt = core->getRegt();
    uint8_t t1 = regt[i[1]];
    uint8_t t2 = regt[i[2]];
    uint8_t t = dual[t1][t2];
    switch(t)
    {
        case UCHARXUCHAR:
            *r2 = *r1 ^ *r2;
            break;
        case UCHARXUSHORT:
            *(uint16_t*)r2 = *r1 ^ *(uint16_t*)r2;
            break;
        case UCHARXUINT:
        case UCHARXFLOAT:
            *(uint32_t*)r2 = *r1 ^ *(uint32_t*)r2;
            break;
            
        case USHORTXUCHAR:
            *r2 = *(uint16_t*)r1 ^ *r2;
            break;
        case USHORTXUSHORT:
            *(uint16_t*)r2 = *(uint16_t*)r1 ^ *(uint16_t*)r2;
            break;
        case USHORTXUINT:
        case USHORTXFLOAT:
            *(uint32_t*)r2 = *(uint16_t*)r1 ^ *(uint32_t*)r2;
            break;
            
        case UINTXUCHAR:
            *r2 = *(uint16_t*)r1 ^ *r2;
            break;
        case UINTXUSHORT:
            *(uint16_t*)r2 = *(uint32_t*)r1 ^ *(uint16_t*)r2;
            break;
        case UINTXUINT:
        case UINTXFLOAT:
            *(uint32_t*)r2 = *(uint32_t*)r1 ^ *(uint32_t*)r2;
            break;
            
        case FLOATXUCHAR:
            *r2 = *(uint32_t*)r1 ^ *r2;
            break;
        case FLOATXUSHORT:
            *(uint16_t*)r2 = *(uint32_t*)r1 ^ *(uint16_t*)r2;
            break;
        case FLOATXUINT:
        case FLOATXFLOAT:
            *(uint32_t*)r2 = *(uint32_t*)r1 ^ *(uint32_t*)r2;
            break;
            
        default:
            break;
    }
    return i + 3;
}
static uint8_t*  xor_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*   lg_rv     (uint8_t*, uint8_t*, void*);
static uint8_t*  lsh_rvrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  lsh_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  rsh_rvrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  rsh_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  ars_rvrv   (uint8_t*, uint8_t*, void*);
static uint8_t*  ars_ivrv   (uint8_t*, uint8_t*, void*);
static uint8_t* jmp_rr(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 2) return mem;
    uint8_t* reg = core->getRegm()[i[1]];
    if(core->getRegt()[i[1]] != UINT) return i + 1;
    return mem + *(uint32_t*)reg;
}
static uint8_t*  jmp_ir     (uint8_t*, uint8_t*, void*);
static uint8_t* jz_rvrr(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t** regm = core->getRegm();
    uint8_t* regt = core->getRegt();
    uint8_t i1 = i[1];
    uint8_t i2 = i[2];
    if(regt[i2] != UINT) return i + 3;
    uint8_t* r1 = regm[i1];
    uint8_t* r2 = regm[i2];
    uint8_t t1 = regt[i1];
    bool doit;
    switch(t1)
    {
        case UCHAR:
            doit = !*(uint8_t*)r1;
            break;
        case USHORT:
            doit = !*(uint16_t*)r1;
            break;
        case UINT:
            doit = !*(uint32_t*)r1;
            break;
        case FLOAT:
            doit = !*(float*)r1;
            break;
        default:
            doit = false;
            break;
    }
    if(!doit) return i + 3;
    return mem + *(uint32_t*)r2;
}
static uint8_t*  jz_rvir     (uint8_t*, uint8_t*, void*);
static uint8_t* jnz_rvrr(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 3) return mem;
    uint8_t** regm = core->getRegm();
    uint8_t* regt = core->getRegt();
    uint8_t i1 = i[1];
    uint8_t i2 = i[2];
    if(regt[i2] != UINT) return i + 3;
    uint8_t* r1 = regm[i1];
    uint8_t* r2 = regm[i2];
    uint8_t t1 = regt[i1];
    bool doit;
    switch(t1)
    {
        case UCHAR:
            doit = *(uint8_t*)r1;
            break;
        case USHORT:
            doit = *(uint16_t*)r1;
            break;
        case UINT:
            doit = *(uint32_t*)r1;
            break;
        case FLOAT:
            doit = *(float*)r1;
            break;
        default:
            doit = false;
            break;
    }
    if(!doit) return i + 3;
    return mem + *(uint32_t*)r2;
}
static uint8_t*  jnz_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t*   jn_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t*   jn_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t*  jnn_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t*  jnn_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t* jmpr_rr     (uint8_t*, uint8_t*, void*);
static uint8_t* jmpr_ir     (uint8_t*, uint8_t*, void*);
static uint8_t*  jzr_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t*  jzr_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t* jnzr_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t* jnzr_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t*  jnr_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t*  jnr_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t* jnnr_rvrr   (uint8_t*, uint8_t*, void*);
static uint8_t* jnnr_rvir   (uint8_t*, uint8_t*, void*);
static uint8_t* prt_rv(uint8_t* i, uint8_t* e, void* c)
{
    EmuCore* core = (EmuCore*)c;
    uint8_t* mem = core->getMem();
    if(e - i < 2) return mem;
    uint8_t i1 = i[1];
    uint8_t* reg = core->getRegm()[i[1]];
    uint8_t type = core->getRegt()[i[1]];
    switch(type)
    {
        case UCHAR:
            printf("reg[%x] = %2x\n", i1, *reg);
            break;
        case USHORT:
            printf("reg[%x] = %4x\n", i1, *(uint16_t*)reg);
            break;
        case UINT:
            printf("reg[%x] = %8x\n", i1, *(uint32_t*)reg);
            break;
        case FLOAT:
            printf("reg[%x] = %f\n", i1, *(float*)reg);
            break;
    }
    return i + 2;
}
static uint8_t*  prt_ir     (uint8_t*, uint8_t*, void*);
static uint8_t*  prt_rr     (uint8_t*, uint8_t*, void*);
