#include <emu/memory.h>

#define EMUM_BCHECK(mem, addr) if(!emum_bcheck(mem, addr)) return false;

emu_memory* emum_create (uint32_t size)
{
  emu_memory* mem = malloc(sizeof(emu_memory));
  mem->size = size;
  mem->data = malloc(size);
  return mem;
}
void emum_free(emu_memory* mem)
{
  free(mem->data);
  mem->size = 0;
  free(mem);
}
bool emum_bcheck(emu_memory* mem, emu_offset addr)
{
  return (addr >= mem->size) ? false : true;
}
static uint8_t* getbaseptr(emu_memory* mem, emu_offset offset)
{
  return ((uint8_t*)mem->data) + offset;
}
bool emum_read8(uint8_t* out, emu_memory* mem, emu_offset addr)
{
  EMUM_BCHECK(mem, addr);
  *out = *getbaseptr(mem, addr);
}
bool emum_write8(uint8_t val, emu_memory* mem, emu_offset addr)
{
  EMUM_BCHECK(mem, addr);
  *getbaseptr(mem, addr) = val;
}
bool emum_read16(uint16_t* out, emu_memory* mem, emu_offset addr)
{
  EMUM_BCHECK(mem, addr);
  *out = *((uint16_t*)getbaseptr(mem, addr));
}
bool emum_write16(uint16_t val, emu_memory* mem, emu_offset addr)
{
  EMUM_BCHECK(mem, addr);
  *((uint16_t*)getbaseptr(mem, addr)) = val;
}
bool emum_read32(uint32_t* out, emu_memory* mem, emu_offset addr)
{
  EMUM_BCHECK(mem, addr);
  *out = *((uint32_t*)getbaseptr(mem, addr));
}
bool emum_write32(uint32_t val, emu_memory* mem, emu_offset addr)
{
  EMUM_BCHECK(mem, addr);
  *((uint32_t*)getbaseptr(mem, addr)) = val;
}
bool emum_readf(float* out, emu_memory* mem, emu_offset addr)
{
  EMUM_BCHECK(mem, addr);
  *out = *((float*)getbaseptr(mem, addr));
}
bool emum_writef(float val, emu_memory* mem, emu_offset addr)
{
  EMUM_BCHECK(mem, addr);
  *((float*)getbaseptr(mem, addr)) = val;
}
