#ifndef EMU_CPU_H
#define EMU_CPU_H

#include <emu/memory.h>
#include <emu/device.h>
#include <stdint.h>

typedef struct emu_cpu emu_cpu;

typedef void(*emu_instruction)(emu_cpu* cpu);
typedef uint8_t emu_insid;

struct emu_cpu
{
  emu_device* dev;
  emu_offset ip;
  emu_instruction it[UINT8_MAX + 1];
};

void emuc_tick(emu_cpu* cpu);

#endif
