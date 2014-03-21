#ifndef EMU_MEM_HPP
#define EMU_MEM_HPP

#include "util.hpp"

namespace emu
{

    emu_uchar*  set_ivrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  set_ivrr   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  set_ivir   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  mov_rvrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  get_irrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  get_rrrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  put_rvir   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  put_rvrr   (emu_uchar*,emu_uchar*,void*);
    emu_uchar* push_rrrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar* push_irrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  pop_rrrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  pop_irrv   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  lea_rrivrv (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  lea_rrrvrv (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  lea_irivrv (emu_uchar*,emu_uchar*,void*);

}

#endif

