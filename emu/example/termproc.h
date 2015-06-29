#ifndef EMU_EXAMPLE_TERMPROC_H
#define EMU_EXAMPLE_TERMPROC_H

#include <emu/processor.h>

//ARGUMENT ORDER: DESTINATION ALWAYS LAST

#define EMUX_TP_INOP   0x00 //nop, no args
#define EMUX_TP_ISET   0x01 //set register to in-line value
#define EMUX_TP_IWRITE 0x02 //set value in memory
#define EMUX_TP_IREAD  0x03 //get value from memory
#define EMUX_TP_IMOV   0x04 //move register to register

#define EMUX_TP_IADD   0x05 //add reg2 + reg1
#define EMUX_TP_ISUB   0x06 //sub reg2 - reg1
#define EMUX_TP_IMUL   0x07 //multiply reg2 * reg1
#define EMUX_TP_IDIV   0x08 //divide reg2 / reg1
#define EMUX_TP_IMOD   0x09 //take modulo reg2 % reg1

#define EMUX_TP_INOT   0x0A //take not of two registers
#define EMUX_TP_IOR    0x0B //take or of two registers
#define EMUX_TP_IAND   0x0C //take and of two registers
#define EMUX_TP_IXOR   0x0D //take xor of two registers
#define EMUX_TP_INOT   0x0E //take not of register

#define EMUX_TP_IJP    0x0F //jump to in-line address
#define EMUX_TP_IJZ    0x10 //jump if "zero"
#define EMUX_TP_IJNZ   0x11 //jump if "not zero"
#define EMUX_TP_IJL    0x12 //jump if "sign"
#define EMUX_TP_IJLE   0x13 //jump if "sign" or "zero"
#define EMUX_TP_IJG    0x14 //jump if "not sign" and "not zero"
#define EMUX_TP_IJGE   0x15 //jump if "not sign"

#define EMUX_TP_IJS    0x16 //jump to address in register
#define EMUX_TP_IJZS   0x17 //jump if "zero"
#define EMUX_TP_IJNZS  0x18 //jump if "not zero"
#define EMUX_TP_IJLS   0x19 //jump if "sign"
#define EMUX_TP_IJLES  0x1A //jump if "sign" or "zero"
#define EMUX_TP_IJGS   0x1B //jump if "not sign" and "not zero"
#define EMUX_TP_IJGES  0x1C //jump if "not sign"

#define EMUX_TP_IPRT   0x1D //print value in register
#define EMUX_TP_IINP   0x1E //get input, place in register

#define EMUX_TP_IIRQ   0xF0 //send interrupt to board
#define EMUX_TP_IBDC   0xF1 //broadcast interrupt in board
#define EMUX_TP_IIST   0xF2 //set interrupt callback address
#define EMUX_TP_IIGT   0xF3 //get interrupt callback address

emu_processor* emux_tp_create();
void emux_tp_free(emu_processor* proc);
void emux_tp_step(emu_processor* proc);

#endif
