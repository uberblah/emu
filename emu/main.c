#include <stdlib.h>
#include <stdio.h>
#include <emu/board.h>
#include <emu/processor.h>
#include <emu/example/termproc.h>

#define TEST_MEMSIZE 1024

int main(int argc, char** argv)
{
    char buf[TEST_MEMSIZE];
    emu_board* board = emub_create();
    emu_processor* proc = emux_tp_create(TEST_MEMSIZE);
    emu_device* dev = proc->device;
    emub_connect(board, dev, 0);

    //TEST THE NOP, SET AND PRINT INSTRUCTIONS
    printf("you should see \"deadbeef\" and its parts\n");
    char regid = EMU_REG_A;
    int value = 0xdeadbeef;
    //NOP
    buf[0x00] = EMUX_TP_INOP;
    //SET THE VALUE OF A REGISTER
    buf[0x01] = EMUX_TP_ISET;
    buf[0x02] = regid;
    buf[0x03] = ((char*)&value)[0];
    buf[0x04] = ((char*)&value)[1];
    buf[0x05] = ((char*)&value)[2];
    buf[0x06] = ((char*)&value)[3];
    //READ THE DIFFERENT PARTS OF THE REGISTER
    buf[0x07] = EMUX_TP_INOP; //more random nops
    buf[0x08] = EMUX_TP_INOP;
    buf[0x09] = EMUX_TP_IPRT;
    buf[0x0a] = regid | EMU_REGPART_I;
    buf[0x0b] = EMUX_TP_IPRT;
    buf[0x0c] = regid | EMU_REGPART_A;
    buf[0x0d] = EMUX_TP_IPRT;
    buf[0x0e] = regid | EMU_REGPART_B;
    buf[0x0f] = EMUX_TP_INOP;
    buf[0x10] = EMUX_TP_IPRT;
    buf[0x11] = regid | EMU_REGPART_AA;
    buf[0x12] = EMUX_TP_IPRT;
    buf[0x13] = regid | EMU_REGPART_AB;
    buf[0x14] = EMUX_TP_IPRT;
    buf[0x15] = regid | EMU_REGPART_BA;
    buf[0x16] = EMUX_TP_IPRT;
    buf[0x17] = regid | EMU_REGPART_BB;
    //WRITE THE TEST TO MEMORY
    emub_write(board, 0, TEST_MEMSIZE, (void*)buf);

    proc->ip = 0;
    while(proc->ip < 0x017)
	emup_step(proc);
    
    exit(EXIT_SUCCESS);
}
