#include <stdlib.h>
#include <stdio.h>

#include <emu/example/termproc.h>

//value-containing register first
//in mov, target register is first
//first register receives values
//first register is reduced by second in arithmetic ops

static void inop(emu_processor* proc)
{
  proc->ip++; //jump over the nop byte
}

static emu_board* getboard(emu_processor* proc)
{
  emu_board* board = proc->device->board;
  if(!board)
    fprintf(stderr, "no board attached to this processor!\n");
  return board;
}

//set the value of a register with in-line data
static void iset(emu_processor* proc)
{
  //get the board pointer
  emu_board* board = getboard(proc);
  if(!board) return;
  //get the regid from the instruction stream
  uint8_t regid;
  if(emub_read(board, proc->ip + 1, 1, (void*)(&regid)) < 1) return;
  //figure out the size of the register
  uint32_t value = 0;
  uint32_t size = emup_regsize(regid);
  //get the bytes from the instruction stream
  if(emub_read(board, proc->ip + 2, size, (void*)(&value)) < size) return;
  //place the bytes in the register
  emup_regset(proc, regid, (void*)(&value));
  //increment the instruction pointer
  proc->ip += 2 + size;
}

//write register data to inline address
static void iwt(emu_processor* proc)
{
  //get the board pointer
  emu_board* board = getboard(proc);
  if(!board) return;
  //get the source regid from the instruction stream
  uint8_t srcregid;
  if(emub_read(board, proc->ip + 1, 1, (void*)(&srcregid)) < 1) return;
  //figure out the size of the register
  uint32_t value = 0;
  uint32_t size = emup_regsize(srcregid);
  //get the data from the register
  emup_regget(proc, srcregid, (void*)(&value));
  //get the target address
  uint32_t tgtaddr;
  if(emub_read(board, proc->ip + 2, 4, (void*)(&tgtaddr)) < 4) return;
  //write the data
  emub_write(board, tgtaddr, size, (void*)(&value));
  proc->ip += 6;
}

//read data from inline address to register
static void ird(emu_processor* proc)
{
  //get the board pointer
  emu_board* board = getboard(proc);
  if(!board) return;
  //get the target regid from the instruction stream
  uint8_t tgtregid;
  if(emub_read(board, proc->ip + 1, 1, (void*)(&tgtregid)) < 1) return;
  //figure out the size of the register
  uint32_t value = 0;
  uint32_t size = emup_regsize(tgtregid);
  //get the source address
  uint32_t srcaddr;
  if(emub_read(board, proc->ip + 2, 4, (void*)(&srcaddr)) < 4) return;
  //read the data from memory
  if(emub_read(board, srcaddr, size, (void*)(&value)) < size)
  {
    proc->ip += 6;
    return;
  }
  //write the data to the register
  emup_regset(proc, tgtregid, (void*)(&value));
  //increment the instruction pointer
  proc->ip += 6;
}

//write register data to address in another register
static void iwtr(emu_processor* proc)
{
  //get the board pointer
  emu_board* board = getboard(proc);
  if(!board) return;
  //get the source regid
  uint8_t srcregid;
  if(emub_read(board, proc->ip + 1, 1, (void*)(&srcregid)) < 1) return;
  //figure out the size of the value
  uint32_t value = 0;
  uint32_t size = emup_regsize(srcregid);
  //get the value we want to write at the target address
  emup_regget(proc, srcregid, (void*)(&value));
  //get the target address register
  uint8_t tgtregid;
  if(emub_read(board, proc->ip + 2, 1, (void*)(&tgtregid)) < 1) return;
  //get the target address from the target address register
  uint32_t tgtaddr = 0;
  emup_regget(proc, tgtregid, (void*)(&tgtaddr));
  //write the data to the target address
  emub_write(board, tgtaddr, size, (void*)(&value));
  //increment the instruction pointer
  proc->ip += 3;
}

//retrieve value from register address, place in register
static void irdr(emu_processor* proc)
{
  //get the board pointer
  emu_board* board = getboard(proc);
  if(!board) return;
  //get the source address regid
  uint8_t srcregid;
  if(emub_read(board, proc->ip + 2, 1, (void*)(&srcregid)) < 1) return;
  //get the target regid
  uint8_t tgtregid;
  if(emub_read(board, proc->ip + 1, 1, (void*)(&tgtregid)) < 1) return;
  //get the size of the value
  uint32_t value;
  uint32_t size = emup_regsize(tgtregid);
  //get the address from the source address register
  uint32_t srcaddr = 0;
  emup_regget(proc, srcregid, (void*)(&srcaddr));
  //copy the data from that address
  if(emub_read(board, srcaddr, size, (void*)(&value)) < size)
  {
    proc->ip += 3;
    return;
  }
  //place the data in the target register
  emup_regset(proc, tgtregid, (void*)(&value));
  //increment the instruction pointer
  proc->ip += 3;
}

//move value from one register to another
static void imov(emu_processor* proc)
{
  //get the board pointer
  emu_board* board = getboard(proc);
  if(!board) return;
  //get the source register from memory
  uint8_t srcregid;
  if(emub_read(board, proc->ip + 2, 1, (void*)(&srcregid)) < 1) return;
  //get the target register from memory
  uint8_t tgtregid;
  if(emub_read(board, proc->ip + 1, 1, (void*)(&tgtregid)) < 1) return;
  //move the data
  uint32_t value = 0;
  emup_regget(proc, srcregid, (void*)(&value));
  emup_regset(proc, tgtregid, (void*)(&value));
  //increment the instruction pointer
  proc->ip += 3;
}

//convert the value from one register to the type of the other,
//and return the converted value
static uint32_t convert(emu_processor* proc, uint8_t tgtregid, uint8_t srcregid)
{
  
}

//add value from one register to value in another
static void iadd(emu_processor* proc)
{
  //get the board pointer
  emu_board* board = getboard(proc);
  if(!board) return;
  //get the source and target registers from memory
  uint8_t tgtregid;
  uint8_t srcregid;
  if(emub_read(board, proc->ip + 1, 1, (void*)(&tgtregid)) < 1) return;
  if(emub_read(board, proc->ip + 2, 1, (void*)(&srcregid)) < 1) return;
  //get the types of these registers
  int tgttype = emup_regtype(tgtregid);
  int srctype = emup_regtype(srcregid);
  uint32_t tgtval;
  uint32_t srcval;
  emup_regget(proc, tgtregid, (void*)(&tgtval));
  emup_regget(proc, srcregid, (void*)(&srcval));
  if(tgttype != EMU_REGTYPE_FLOAT)
  {
    if(srctype == EMU_REGTYPE_FLOAT)
    {
      int32_t inted = (int32_t)(*(float*)(&srcval));
    }
  }
  else
  {

  }
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
  //get the board pointer
  emu_board* board = getboard(proc);
  if(!board) return;
  //get the regid from the instruction stream
  uint8_t regid;
  if(emub_read(board, proc->ip + 1, 1, (void*)(&regid)) < 1) return;
  //figure out the size of the register
  uint32_t size = emup_regsize(regid);
  int val = 0;
  emup_regget(proc, regid, &val);
  printf("reg %x(%u): %x\n", regid, size, val);

  proc->ip += 2;
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
  inset[EMUX_TP_IWT]    = iwt;
  inset[EMUX_TP_IRD]    = ird;
  inset[EMUX_TP_IWTR]   = iwtr;
  inset[EMUX_TP_IRDR]   = irdr;
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

