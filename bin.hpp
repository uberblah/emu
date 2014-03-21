#ifndef EMU_BIN_HPP
#define EMU_BIN_HPP

#include "util.hpp"

namespace emu
{

    //returns the number of bytes represented by a hex string
    emu_uint hexlen(emu_uchar* hex);
    //returns the hex equivalent of one byte, capitalized
    emu_uchar* bin2hex(emu_uchar bin);
    //returns byte for given hex, skipping useless chars
    //if newaddr != NULL, places next hex start address in newaddr
    emu_uchar hex2bin(emu_uchar* hex, emu_uchar** newaddr);

}

#endif
