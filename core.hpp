#ifndef EMU_CORE_HPP
#define EMU_CORE_HPP

#include "util.hpp"
#include "exec.hpp"

#ifndef EMU_CORE_MEM
#define EMU_CORE_MEM 0x4000
#endif

#ifndef EMU_CORE_NREGS
#define EMU_CORE_NREGS 0x100
#endif

namespace emu
{    
//a simple, flexible processor implementation using our "exec" classes
//be careful: all its guts are hanging out for the world to touch and see!
    struct EmuCore
    {
        EmuCore();
        ~EmuCore();
    
        InsTable*   itable;
        emu_uchar*  mem;
        emu_uint    memsz;
        emu_uchar*  ip;
        emu_uchar*  end; //end of execution memory
        emu_uchar*  regs;
        emu_uchar** regm;	emu_uchar*  regt;
        inline void step()
        {
            ip = itable->exec(ip, end, this);
            if(end <= ip || mem > ip) ip = mem;
        }
    };
}

#endif

