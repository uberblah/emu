#ifndef EMU_CORE_HPP
#define EMU_CORE_HPP

#include "util.hpp"
#include "exec.hpp"

namespace emu
{    
//a simple, flexible processor implementation using our "exec" library
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

