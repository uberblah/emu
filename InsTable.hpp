#ifndef INSTABLE_HPP
#define INSTABLE_HPP

#include <cstdint>

namespace emu
{

//three parameters: instruction pointer, end-of-ip-range, userdata
typedef uint8_t* (*Instruction)(uint8_t*, uint8_t*, void*);
//if you need more flexibility, replace the line above w/ this one...
//typedef std::function<uint8_t*(uint8_t*, uint8_t*, void*)> Instruction;

class InsTable
{
public:
    InsTable();
    ~InsTable();
    
    inline Instruction& operator[](uint8_t opcode)
    {
        return itable[opcode];
    }

    //i is the address of the instruction
    //e is the address of the end of the buffer
    //instructions will not pass beyond the end of the buffer
    //return value is the new instruction pointer
    inline uint8_t* exec(uint8_t* i, uint8_t* e, void* u)
    {
        return itable[*i](i, e, u);
    }
    
private:
    Instruction* itable;
};

}

#endif

