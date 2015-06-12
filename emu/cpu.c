#include <emu/cpu.h>

void emuc_tick(emu_cpu* cpu)
{
  emu_memory* mem = cpu->host->mem;
  if(cpu->ip >= mem->size) return;
  cpu->it[((uint8_t*)mem->data)[cpu->ip]](cpu);
}
