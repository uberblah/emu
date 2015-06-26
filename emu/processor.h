#ifndef EMU_PROCESSOR_H
#define EMU_PROCESSOR_H

#include <stdint.h>

#include <emu/board.h>

#define EMU_REGTYPE_INT8  0
#define EMU_REGTYPE_INT16 1
#define EMU_REGTYPE_INT32 2
#define EMU_REGTYPE_FLOAT  3
#define EMU_REG_A 0x00
#define EMU_REG_B 0x08
#define EMU_REG_C 0x10
#define EMU_REG_D 0x18
#define EMU_REG_E 0x20
#define EMU_REG_F 0x28
#define EMU_REG_G 0x30
#define EMU_REG_H 0x38
#define EMU_REG_I 0x40
#define EMU_REG_J 0x48
#define EMU_REG_K 0x50
#define EMU_REG_L 0x58
#define EMU_REG_M 0x60
#define EMU_REG_N 0x68
#define EMU_REG_O 0x70
#define EMU_REG_P 0x78
#define EMU_REG_Q 0x80
#define EMU_REG_R 0x88
#define EMU_REG_S 0x90
#define EMU_REG_T 0x98
#define EMU_REG_U 0xA0
#define EMU_REG_V 0xA8
#define EMU_REG_W 0xB0
#define EMU_REG_X 0xB8
#define EMU_REG_Y 0xC0
#define EMU_REG_Z 0xC8
#define EMU_REGPART_I  0x00
#define EMU_REGPART_F  0x01
#define EMU_REGPART_A  0x02
#define EMU_REGPART_B  0x03
#define EMU_REGPART_AA 0x04
#define EMU_REGPART_AB 0x05
#define EMU_REGPART_BA 0x06
#define EMU_REGPART_BB 0x07

typedef struct emu_processor emu_processor;
typedef void(*emu_instruction)(emu_processor* p);

struct emu_processor
{
  emu_instruction iset[256]; //the instruction set
  uint8_t regs [128]; //register memory
  uint32_t ip; //a byte-index into local memory
  emu_device* device; //access to board, memory
  emu_irq_cb irq_cb;
  emu_ev_cb cc_cb;
  emu_ev_cb dc_cb;
};

emu_processor* emup_create(emu_instruction* iset, uint32_t memsize);
void emup_free(emu_processor* proc);
void emup_step(emu_processor* proc);
int emup_regtype(emu_processor* proc, uint8_t regid);
void emup_regset(emu_processor* proc, uint8_t regid, void* val);
void emup_regget(emu_processor* proc, uint8_t regid, void* out);

#endif
