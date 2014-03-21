#ifndef EMU_JUMP_HPP
#define EMU_JUMP_HPP

#include "util.hpp"

namespace emu
{

    emu_uchar*  nop        (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  jmp_rr     (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  jmp_ir     (emu_uchar*,emu_uchar*,void*);
    emu_uchar*   jz_rvrr   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*   jz_rvir   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  jnz_rvrr   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  jnz_rvir   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*   jn_rvrr   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*   jn_rvir   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  jnn_rvrr   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  jnn_rvir   (emu_uchar*,emu_uchar*,void*);
    emu_uchar* jmpr_rr     (emu_uchar*,emu_uchar*,void*);
    emu_uchar* jmpr_ir     (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  jzr_rvrr   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  jzr_rvir   (emu_uchar*,emu_uchar*,void*);
    emu_uchar* jnzr_rvrr   (emu_uchar*,emu_uchar*,void*);
    emu_uchar* jnzr_rvir   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  jnr_rvrr   (emu_uchar*,emu_uchar*,void*);
    emu_uchar*  jnr_rvir   (emu_uchar*,emu_uchar*,void*);
    emu_uchar* jnnr_rvrr   (emu_uchar*,emu_uchar*,void*);
    emu_uchar* jnnr_rvir   (emu_uchar*,emu_uchar*,void*);

}

#endif
