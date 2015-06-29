#include <emu/example/termproc.h>

//just a quick self-reminder about the rules of the set...
//  destination last, reg2 before reg1 in div, sub, mod

static void inop(emu_processor* proc)
{
  
}

static void iset(emu_processor* proc)
{

}

static void iwrite(emu_processor* proc)
{

}

static void iread(emu_processor* proc)
{

}

static void imov(emu_processor* proc)
{

}

static void iadd(emu_processor* proc)
{

}

static void isub(emu_processor* proc)
{

}

static void imul(emu_processor* proc)
{

}

static void idiv(emu_processor* proc)
{

}

static void inot(emu_processor* proc)
{

}

static void ior(emu_processor* proc)
{

}

static void iand(emu_processor* proc)
{

}

static void ixor(emu_processor* proc)
{

}

static void ijmp(emu_processor* proc)
{

}

static void ijz(emu_processor* proc)
{

}

static void ijnz(emu_processor* proc)
{

}

static void ijl(emu_processor* proc)
{

}

static void ijle(emu_processor* proc)
{

}

static void ijg(emu_processor* proc)
{

}

static void ijge(emu_processor* proc)
{

}

static void ijs(emu_processor* proc)
{

}

static void ijzs(emu_processor* proc)
{

}

static void ijnzs(emu_processor* proc)
{

}

static void ijls(emu_processor* proc)
{

}

static void ijles(emu_processor* proc)
{

}

static void ijgs(emu_processor* proc)
{

}

static void ijges(emu_processor* proc)
{

}

static void iprt(emu_processor* proc)
{

}

static void iinp(emu_processor* proc)
{

}

static void iirq(emu_processor* proc)
{

}

static void ibdc(emu_processor* proc)
{

}

static void iist(emu_processor* proc)
{

}

static void iigt(emu_processor* proc)
{

}

/*
const emu_instruction inset[256] =
{
  inop , iset, iwrite, iread, imov, iadd, isub , imul, //0 - 7
  idiv , inot, ior   , iand , ixor, ijmp, ijz  , ijnz, //8 - 15
  ijl  , ijle, ijg   , ijge , ijs , ijzs, ijnzs, ijls, //16 - 23
  ijles, ijg , ijges , iprt , iinp, 0   , 0    , 0   , //24 - 31
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //32 - 47
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //48 - 63
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //64 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //80 - 95
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, //96 - 111
  iirq, ibdc , iist  , iigt , 0   , 0   , 0    , 0   , //112 - 119
  0, 0, 0, 0, 0, 0, 0, 0 //120 - 127
};
*/

emu_processor* emux_tp_create(uint32_t memsize)
{
  emu_instruction inset[256];
  inset[EMUX_TP_INOP]   = inop;
  inset[EMUX_TP_ISET]   = iset;
  inset[EMUX_TP_IWRITE] = iwrite;
  inset[EMUX_TP_IREAD]  = iread;
  inset[EMUX_TP_IMOV]   = imov;
  inset[EMUX_TP_IADD]   = iadd;
  inset[EMUX_TP_ISUB]   = isub;
  inset[EMUX_TP_IMUL]   = imul;
  inset[EMUX_TP_IDIV]   = idiv;
  inset[EMUX_TP_INOT]   = inot;
  inset[EMUX_TP_IOR]    = ior;
  inset[EMUX_TP_IAND]   = iand;
  inset[EMUX_TP_IXOR]   = ixor;
  inset[EMUX_TP_IJMP]   = ijmp;
  inset[EMUX_TP_IJZ]    = ijz;
  inset[EMUX_TP_IJNZ]   = ijnz;
  inset[EMUX_TP_IJL]    = ijl;
  inset[EMUX_TP_IJLE]   = ijle;
  inset[EMUX_TP_IJG]    = ijg;
  inset[EMUX_TP_IJGE]   = ijge;
  inset[EMUX_TP_IJS]    = ijs;
  inset[EMUX_TP_IJZS]   = ijzs;
  inset[EMUX_TP_IJNZS]  = ijnzs;
  inset[EMUX_TP_IJLS]   = ijls;
  inset[EMUX_TP_IJLES]  = ijles;
  inset[EMUX_TP_IJGS]   = ijgs;
  inset[EMUX_TP_IJGES]  = ijges;
  inset[EMUX_TP_IPRT]   = iprt;
  inset[EMUX_TP_IINP]   = iinp;
  inset[EMUX_TP_IIRQ]   = iirq;
  inset[EMUX_TP_IBDC]   = ibdc;
  inset[EMUX_TP_IIST]   = iist;
  inset[EMUX_TP_IIGT]   = iigt;

  return emup_create(inset, memsize);
}

