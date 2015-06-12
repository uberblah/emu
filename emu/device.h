#ifndef EMU_DEVICE_H
#define EMU_DEVICE_H

#include <emu/memory.h>
#include <stdint.h>

typedef uint32_t emu_msg;
typedef void(*emu_irq_cb)(void* state, emu_msg msg);
typedef void(*emu_ev_cb)(void* state);

typedef struct emu_device emu_device;
struct emu_device
{
  void* state;
  emu_irq_cb irq_cb;
  emu_ev_cb cc_cb;
  emu_ev_cb dc_cb;
  emu_memory* mem;
};

#endif
