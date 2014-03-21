#ifndef EMU_MATH_HPP
#define EMU_MATH_HPP

#include "util.hpp"

namespace emu
{

    emu_uchar*  add_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  add_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  sub_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  sub_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  inc_rv     (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  dec_rv     (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  mul_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  mul_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  div_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  div_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  mod_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  mod_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  pow_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  pow_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  neg_rv     (emu_uchar*,emu_uchar*,void*);
    emu_uchar* sqrt_rv     (emu_uchar*,emu_uchar*,void*);

}

#endif
