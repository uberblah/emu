#include <stdlib.h>
#include <emu/board.h>

emu_board* emub_create()
{
  //allocate the board
  emu_board* board = (emu_board*)malloc(sizeof(emu_board));
  //set each plug to empty (NULL)
  int i = 0;
  for(; i < 256; i++) (*board)[i] = NULL;
  //return it...
  return board;
}

void emub_free(emu_board* board)
{
  //for each occupied plug, disconnect the device
  unsigned int i = 0;
  for(; i < 256; i++)
  {
    emu_device* dev = (*board)[i];
    if(dev) emub_disconnect(board, i);
  }
  //free the board itself
  free(board);
}

void emub_connect(emu_board* board, emu_device* device, uint8_t id)
{
  //clear the plug of any other devices
  if((*board)[id]) emub_disconnect(board, id);
  //set the new device's fields
  device->board = board;
  device->id = id;
  //plug the device in
  (*board)[id] = device;
  //notify the device
  if(device->cc_cb) device->cc_cb(device);
}

void emub_disconnect(emu_board* board, uint8_t id)
{
  emu_device* device = (*board)[id];
  if(!device) return; //if there's no device, stop here
  //notify the device that we are unplugging it
  if(device->dc_cb) device->dc_cb(device);
  //unplug the device
  (*board)[id] = NULL;
}

void emub_send(emu_board* board, uint8_t id, uint32_t code)
{
  emu_device* device = (*board)[id];
  if(!device) return; //if no device is plugged in, don't bother
  //call the device's interrupt callback
  if(device->irq_cb) device->irq_cb(device, code);
}

void emub_broadcast(emu_board* board, uint32_t code)
{
  //just iterate over all plugs, sending the message to each
  int id = 0;
  for(; id < 0x100; id++) emub_send(board, id, code);
}
