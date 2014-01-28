#ifndef INSTABLE_HPP
#define INSTABLE_HPP

#include "utypes.hpp"
using namespace ugl;

namespace emu
{

//three parameters: instruction pointer, end-of-ip-range, userdata
typedef uchar* (*Instruction)(uchar*, uchar*, void*);
//if you need more flexibility, replace the line above w/ this one...
//typedef std::function<uchar*(uchar*, uchar*, void*)> Instruction;

class InsTable
{
public:
    InsTable();
    ~InsTable();
    
    inline Instruction& operator[](uchar opcode)
    {
        return itable[opcode];
    }

    //i is the address of the instruction
    //e is the address of the end of the buffer
    //instructions will not pass beyond the end of the buffer
    //return value is the new instruction pointer
    inline uchar* exec(uchar* i, uchar* e, void* u)
    {
        return itable[*i](i, e, u);
    }
    
private:
    Instruction* itable;
};

}

#endif

