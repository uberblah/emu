#ifndef EMU_BOARD_H
#define EMU_BOARD_H

#include <emu/device.h>
#include <stdint.h>
#include <stdbool.h>

typedef emu_device* emu_board[UINT8_MAX + 1];

typedef uint8_t emu_plugid;

void emub_send(emu_board* board, emu_plugid id, emu_msg msg);
void emub_broadcast(emu_board* board, emu_msg msg);
bool emub_ping(emu_board* board, emu_plugid id);
uint32_t emub_memsize(emu_board* board, emu_plugid id);
void emub_disconnect(emu_board* board, emu_plugid id);
void emub_connect(emu_board* board, emu_plugid id, emu_device* dev);

bool emub_read8(uint8_t* out, emu_board* board, emu_offset addr);
bool emub_write8(uint8_t val, emu_board* board, emu_offset addr);
bool emub_read16(uint16_t* out, emu_board* board, emu_offset addr);
bool emub_write16(uint16_t val, emu_board* board, emu_offset addr);
bool emub_read32(uint32_t* out, emu_board* board, emu_offset addr);
bool emub_write32(uint32_t val, emu_board* board, emu_offset addr);
bool emub_readf(float* out, emu_board* board, emu_offset addr);
bool emub_writef(float val, emu_board* board, emu_offset addr);

#endif
