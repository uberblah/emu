#ifndef EMU_UTIL_HPP
#define EMU_UTIL_HPP

#include <cstdlib>

namespace emu
{

    typedef char           emu_char;
    typedef short          emu_short;
    typedef int            emu_int;
    typedef float          emu_float;

    typedef unsigned char  emu_uchar;
    typedef unsigned short emu_ushort;
    typedef unsigned int   emu_uint;

    typedef size_t         emu_ptrdiff;
    
    const emu_uchar UCHAR  = 0x0;
    const emu_uchar USHORT = 0x1;
    const emu_uchar UINT   = 0x2;
    const emu_uchar FLOAT  = 0x3;
    
    const extern emu_uint sizes[4];
    
    const emu_uchar UCHARXUCHAR   = 0x0;
    const emu_uchar UCHARXUSHORT  = 0x1;
    const emu_uchar UCHARXUINT    = 0x2;
    const emu_uchar UCHARXFLOAT   = 0x3;

    const emu_uchar USHORTXUCHAR  = 0x4;
    const emu_uchar USHORTXUSHORT = 0x5;
    const emu_uchar USHORTXUINT   = 0x6;
    const emu_uchar USHORTXFLOAT  = 0x7;

    const emu_uchar UINTXUCHAR    = 0x8;
    const emu_uchar UINTXUSHORT   = 0x9;
    const emu_uchar UINTXUINT     = 0xA;
    const emu_uchar UINTXFLOAT    = 0xB;

    const emu_uchar FLOATXUCHAR   = 0xC;
    const emu_uchar FLOATXUSHORT  = 0xD;
    const emu_uchar FLOATXUINT    = 0xE;
    const emu_uchar FLOATXFLOAT   = 0xF;
    
    const extern emu_uchar* dual[4];
    
}

#endif
