#ifndef EMU_BIN_HPP
#define EMU_BIN_HPP

#include "util.hpp"

#ifndef EMU_HEX_CAPS
#define EMU_HEX_CAPS false
#endif

namespace emu
{

    inline emu_uint hexlen(emu_uchar* hex);

    inline void byte2hex
        (emu_uchar byte, emu_char* out, bool caps = EMU_HEX_CAPS);

    inline bool hex2byte(emu_char* hex, emu_uchar* out, emu_char** newaddr);

    emu_uint bin2hex
        (emu_uchar* bin, emu_uint isz, emu_char* out, emu_uint osz, 
                                                    bool caps = EMU_HEX_CAPS);

    emu_uint hex2bin(emu_char* hex, emu_uchar* out, emu_uint osz);
    
}

#endif
