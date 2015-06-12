#ifndef EMU_MEMORY_H
#define EMU_MEMORY_H

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t emu_offset;

typedef struct emu_memory emu_memory;
struct emu_memory
{
  uint32_t size;
  void* data;
};

emu_memory* emum_create (uint32_t size);
void emum_free(emu_memory* mem);
bool emum_read8(uint8_t* out, emu_memory* mem, emu_offset addr);
bool emum_write8(uint8_t val, emu_memory* mem, emu_offset addr);
bool emum_read16(uint16_t* out, emu_memory* mem, emu_offset addr);
bool emum_write16(uint16_t val, emu_memory* mem, emu_offset addr);
bool emum_read32(uint32_t* out, emu_memory* mem, emu_offset addr);
bool emum_write32(uint32_t val, emu_memory* mem, emu_offset addr);
bool emum_readf(float* out, emu_memory* mem, emu_offset addr);
bool emum_writef(float val, emu_memory* mem, emu_offset addr);

#endif
