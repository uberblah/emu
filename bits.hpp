#ifndef EMU_BITS_HPP
#define EMU_BITS_HPP

#include "util.hpp"

namespace emu
{

    emu_uchar*  not_rv     (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  and_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  and_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*   or_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*   or_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  xor_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  xor_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*   lg_rv     (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  lsh_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  lsh_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  rsh_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  rsh_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  ars_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  ars_ivrv   (emu_uchar*,emu_uchar*,void*);

}

#endif
