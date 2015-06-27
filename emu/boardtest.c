#include <stdlib.h>
#include <stdio.h>

#include <emu/board.h>

void pinger_irq_cb(emu_device* pinger, uint32_t code)
{
  printf("PING: slot=%d, msg=%d\n", pinger->id, code);
}

void pinger_cc_cb(emu_device* pinger)
{
  printf("CONNECT: slot=%d\n", pinger->id);
}

void pinger_dc_cb(emu_device* pinger)
{
  printf("DISCONNECT: slot=%d\n", pinger->id);
}

emu_device* create_pinger()
{
  emu_device* pinger = (emu_device*)malloc(sizeof(emu_device));
  pinger->mem = malloc(128);
  if(!pinger->mem)
  {
    free(pinger);
    return NULL;
  }
  pinger->memsize = 128;
  pinger->irq_cb = pinger_irq_cb;
  pinger->cc_cb = pinger_cc_cb;
  pinger->dc_cb = pinger_dc_cb;
  pinger->data = NULL;
  return pinger;
}

void my_connect(emu_board* board, emu_device* pinger, uint8_t id)
{
  printf("CONNECTING PINGER AT PLUG %d\n", id);
  emub_connect(board, pinger, id);
}

void my_disconnect(emu_board* board, uint8_t id)
{
  printf("DISCONNECTING PINGER AT PLUG %d\n", id);
  emub_disconnect(board, id);
}

void my_broadcast(emu_board* board, uint32_t msg)
{
  printf("BROADCASTING CODE %d\n", msg);
  emub_broadcast(board, msg);
}

void my_send(emu_board* board, uint8_t id, uint32_t msg)
{
  printf("SENDING %d TO PLUG %d\n", msg, id);
  emub_send(board, id, msg);
}

void free_pinger(emu_device* pinger)
{
  free(pinger->mem);
  free(pinger);
}

int main(int argc, char** argv)
{
  emu_board* b = (emu_board*)malloc(sizeof(emu_board));
  int i = 0;
  for(; i < 256; i++) (*b)[i] = NULL;
  emu_device* d1 = create_pinger();
  emu_device* d2 = create_pinger();
  int i1 = 0;
  int i2 = 1;
  
  my_connect(b, d1, i1);
  my_connect(b, d2, i2);

  for(i = 0; i < 100; i += 10) my_broadcast(b, i);

  for(i = 0; i < 0x100; i++) my_send(b, i, 0x100 - i);

  my_disconnect(b, i1);
  my_disconnect(b, i2);
  
  free_pinger(d2);
  free_pinger(d1);
  free(b);
  
  exit(EXIT_SUCCESS);
}
