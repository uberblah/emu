#include <cstdio>
#include <cstdlib>
#include "core.hpp"
#include "mem.hpp"
using namespace emu;
using namespace std;
int main(int argc, char** argv)
{
    printf("Initializing Virtual Processor...\n");
    EmuCore* core = new EmuCore();
    
    printf("Loading Test Program (test.bin)...\n");
    FILE* file = fopen("test.bin", "rb");
    if(!file)
    {
        fprintf(stderr, "ERROR: failed to open test program (test.bin)\n");
        return 1;
    }
    
    emu_uint size = fread(core->mem, 1, 255, file);
    printf("Size of Test Program: %d\n", size);
    
    printf("Running Test Program...\n");
    do
    {core->step();}
    while(core->ip != core->mem);
    
    return 0;
}

