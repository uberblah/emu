#include <cstdio>
#include <cstdlib>
#include "EmuCore.hpp"
using namespace emu;
using namespace std;
using namespace ugl;

int main(int argc, char** argv)
{
    printf("Initializing Virtual Processor...\n");
    EmuCore core = EmuCore();
    uchar* mem = core.getMem();
    
    printf("Loading Test Program (test.bin)...\n");
    FILE* file = fopen("test.bin", "rb");
    if(!file)
    {
        fprintf(stderr, "ERROR: failed to open test program (test.bin)\n");
        return 1;
    }
    
    uint size = fread(mem, 1, 255, file);
    printf("Size of Test Program: %d\n", size);
    
    printf("Running Test Program...\n");
    core.setIP(core.getMem());
    do
    {
        core.step();
    }
    while(core.getIP() != core.getMem());
    
    return 0;
}

