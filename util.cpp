#include "util.hpp"

namespace emu
{
//  SIZES OF BASIC TYPES
const emu_uint sizes[4] = {1, 2, 4, 4};
//  TABLE FOR INDEXING OF DUAL TYPE ENUMS
static emu_uchar  _chars   [4] = {0x0, 0x1, 0x2, 0x3};
static emu_uchar  _shorts  [4] = {0x4, 0x5, 0x6, 0x7};
static emu_uchar  _ints    [4] = {0x8, 0x9, 0xA, 0xB};
static emu_uchar  _floats  [4] = {0xC, 0xD, 0xE, 0xF};
const  emu_uchar* dual     [4] = {_chars, _shorts, _ints, _floats};

}

