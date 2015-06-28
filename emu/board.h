#ifndef EMU_BOARD_H
#define EMU_BOARD_H

#include <stdint.h>

typedef struct emu_device emu_device;
typedef emu_device* emu_board[0x100];
typedef void(*emu_irq_cb)(emu_device* dev, uint32_t code);
typedef void(*emu_ev_cb)(emu_device* dev);
struct emu_device
{
  emu_board* board;
  uint32_t memsize;
  void* mem;
  emu_irq_cb irq_cb;
  emu_ev_cb cc_cb;
  emu_ev_cb dc_cb;
  void* data;
  uint8_t id;
};

emu_board* emub_create();
void emub_free(emu_board* board);
void emub_connect(emu_board* board, emu_device* device, uint8_t id);
void emub_disconnect(emu_board* board, uint8_t id);
void emub_send(emu_board* board, uint8_t id, uint32_t code);
void emub_broadcast(emu_board* board, uint32_t code);

#endif
