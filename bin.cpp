#include "bin.hpp"

namespace emu
{

static emu_uchar h2btable[] = { 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 16, 16, 16, 16, 16, 16, 16, 10, 11, 12, 13, 14, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 10, 11, 12, 13, 14, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};

static emu_char b2htablel[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

static emu_char b2htablec[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

inline emu_uint hexlen(emu_uchar* hex)
{
    emu_uint count = 0;
    for(emu_uint i = 0; hex[i] != 0; i++) if(h2btable[hex[i]] != 16) count++;
    return count << 1;
}

inline void byte2hex
    (emu_uchar byte, emu_char* out, bool caps)
{
    emu_char* table = caps ? b2htablec : b2htablel;
    out[0] = table[(byte >> 4) & 0x0F];
    out[1] = table[byte & 0x0F];
}

inline bool hex2byte(emu_char* hex, emu_uchar* out, emu_char** newaddr)
{
    emu_char r = 0;
    emu_char v = hex[0];
    emu_char* i = hex;
    
    for(; h2btable[v] == 16 && v != 0; i++) v = *i;
    if(v == 0) return false;
    r |= h2btable[v] << 4;
    
    i++;
    
    for(; h2btable[v] == 16 && v != 0; i++) v = *i;
    if(v == 0) return false;
    r |= h2btable[v];
    
    *out = r;
    if(newaddr) *newaddr = i;
    return true;
}

inline emu_uint bin2hex
    (emu_uchar* bin, emu_uint isz, emu_char* out, emu_uint osz, bool caps)
{
    emu_uint i = 0;
    emu_uint j = 0;
    while(i < isz && j + 1 < osz)
    {
        byte2hex(bin[i], out + j, caps);
        i++;
        j += 2;
    }
    return i;
}

inline emu_uint hex2bin(emu_char* hex, emu_uchar* out, emu_uint osz)
{
    emu_uchar* oend = out + osz;
    emu_char* i = hex;
    emu_uchar* o = out;
    emu_char v = *i;
    emu_uint count = 0;
    while(v != 0 && o < oend)
        if(hex2byte(i, o, &i)) count++;
    return count;
}

}


