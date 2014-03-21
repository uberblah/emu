#ifndef EMU_EXE_HPP
#define EMU_EXE_HPP

#include <cstdio>
#include "util.hpp"
//see definition of Instruction below for information on this include
//#include <functional>

namespace emu
{

//three parameters: instruction pointer, end-of-ip-range, userdata
typedef emu_uchar* (*Instruction)(emu_uchar*,emu_uchar*,void*);
//if you need more flexibility, replace the line above w/ this one...
//typedef std::function<emu_uchar*(emu_uchar*, emu_uchar*, void*)> Instruction;

class InsTable
{
public:    
    InsTable()
    {
        it = new Instruction[256];
        for(int i = 0; i < 256; i++) it[i] = Instruction();
    }

    ~InsTable()
    {
        delete[] it;
    }
    
    inline Instruction& operator[](emu_uchar opcode)
    {
        return it[opcode];
    }

    //i is the address of the instruction
    //e is the address of the end of the buffer
    //instructions will not pass beyond the end of the buffer
    //return value is the new instruction pointer
    inline emu_uchar* exec(emu_uchar* i, emu_uchar* e, void* u)
    {
        return it[*i](i, e, u);
    }
    
private:
    Instruction* it;
};

}

#endif
