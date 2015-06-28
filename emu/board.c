#include <stdlib.h>
#include <emu/board.h>

emu_board* emub_create()
{
  emu_board* board = (emu_board*)malloc(sizeof(emu_board));
  int i = 0;
  for(; i < 256; i++) (*board)[i] = NULL;
  return board;
}

void emub_free(emu_board* board)
{
  unsigned int i = 0;
  for(; i < 256; i++)
  {
    emu_device* dev = (*board)[i];
    if(dev) emub_disconnect(board, i);
  }
  free(board);
}

void emub_connect(emu_board* board, emu_device* device, uint8_t id)
{
  if((*board)[id]) emub_disconnect(board, id);
  device->board = board;
  device->id = id;
  (*board)[id] = device;
  if(device->cc_cb) device->cc_cb(device);
}

void emub_disconnect(emu_board* board, uint8_t id)
{
  emu_device* device = (*board)[id];
  if(!device) return;  
  if(device->dc_cb) device->dc_cb(device);
  (*board)[id] = NULL;
}

void emub_send(emu_board* board, uint8_t id, uint32_t code)
{
  emu_device* device = (*board)[id];
  if(!device) return;
  if(device->irq_cb) device->irq_cb(device, code);
}

void emub_broadcast(emu_board* board, uint32_t code)
{
  int id = 0;
  for(; id < 0x100; id++) emub_send(board, id, code);
}
