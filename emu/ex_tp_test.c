#include <stdlib.h>
#include <stdio.h>
#include <emu/example/termproc.h>

int main(int argc, char** argv)
{
    emu_processor* tp = emux_tp_create(1024);
    emu_board* b = emub_create();
    emu_connect(b, 
}
