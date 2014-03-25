#include "core.hpp"
#include "mem.hpp"
#include "jump.hpp"
#include "math.hpp"
#include "bits.hpp"
#include "sys.hpp"
#include "debug.hpp"
using namespace emu;

EmuCore::EmuCore()
{
    mem = new emu_uchar[EMU_CORE_MEM];
    end = mem + EMU_CORE_MEM;
    memsz = EMU_CORE_MEM;
    ip = mem;
    regs = new emu_uchar[EMU_CORE_NREGS];
    regm = new emu_uchar*[EMU_CORE_NREGS];
    regt = new emu_uchar[EMU_CORE_NREGS];
    emu_uchar* c = regs;
    for(emu_uint i = 0; i < EMU_CORE_NREGS; i += 8)
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
    itable = new InsTable();
    for(emu_uint i = 0x0; i < 0x100; i++)
    {
        (*itable)[i] = nop;
    }
    (*itable)[0x01] =  set_ivrv   ;
    //(*itable)[0x02] =  set_ivir   ;
    //(*itable)[0x03] =  set_ivrr   ;
    (*itable)[0x04] =  mov_rvrv   ;
    //(*itable)[0x05] =  get_irrv   ;
    (*itable)[0x06] =  get_rrrv   ;
    //(*itable)[0x07] =  put_rvir   ;
    (*itable)[0x08] =  put_rvrr   ;
    //(*itable)[0x09] = push_rrrv   ;
    //(*itable)[0x0A] = push_irrv   ;
    //(*itable)[0x0B] =  pop_rrrv   ;
    //(*itable)[0x0C] =  pop_irrv   ;
    //(*itable)[0x0D] =  lea_rrivrv ;
    //(*itable)[0x0E] =  lea_rrrvrv ;
    //(*itable)[0x0F] =  lea_irivrv ;
    //(*itable)[0x10] =  add_ivrv   ;
    (*itable)[0x11] =  add_rvrv   ;
    //(*itable)[0x12] =  sub_ivrv   ;
    (*itable)[0x13] =  sub_rvrv   ;
    (*itable)[0x14] =  inc_rv     ;
    (*itable)[0x15] =  dec_rv     ;
    //(*itable)[0x16] =  mul_ivrv   ;
    (*itable)[0x17] =  mul_rvrv   ;
    //(*itable)[0x18] =  neg_rv     ;
    //(*itable)[0x19] =  div_ivrv   ;
    (*itable)[0x1A] =  div_rvrv   ;
    //(*itable)[0x1B] =  mod_ivrv   ;
    //(*itable)[0x1C] =  mod_rvrv   ;
    //(*itable)[0x1D] =  pow_ivrv   ;
    //(*itable)[0x1E] =  pow_rvrv   ;
    //(*itable)[0x1F] = sqrt_rv     ;
    (*itable)[0x20] =  not_rv     ;
    //(*itable)[0x21] =  and_ivrv   ;
    (*itable)[0x22] =  and_rvrv   ;
    //(*itable)[0x23] =   or_ivrv   ;
    (*itable)[0x24] =   or_rvrv   ;
    //(*itable)[0x25] =  xor_ivrv   ;
    (*itable)[0x26] =  xor_rvrv   ;
    //(*itable)[0x27] =   lg_rv     ;
    //(*itable)[0x28] =  lsh_ivrv   ;
    //(*itable)[0x29] =  lsh_rvrv   ;
    //(*itable)[0x2A] =  rsh_ivrv   ;
    //(*itable)[0x2B] =  rsh_rvrv   ;
    //(*itable)[0x2C] =  ars_ivrv   ;
    //(*itable)[0x2D] =  ars_rvrv   ;
    (*itable)[0x2E] =  jmp_rr     ;
    (*itable)[0x2F] =   jz_rvrr   ;
    (*itable)[0x30] =  jnz_rvrr   ;
    (*itable)[0x31] =  prt_rv     ;
}

EmuCore::~EmuCore()
{
    delete itable;
    delete[] regs;
    delete[] regm;
    delete[] regt;
    delete[] mem;
}


