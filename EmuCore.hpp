#ifndef EMUCORE_HPP
#define EMUCORE_HPP

#include <functional>
#include "InsTable.hpp"
#include <cstdint>

namespace emu
{

class EmuCore
{
public:
    EmuCore();
    ~EmuCore();
    
    inline void setIP(uint8_t* ip){if(mem <= ip && end > ip) this->ip = ip;}
    inline void step(){ip = itable.exec(ip, end, (void*)this);}
    inline uint8_t* getMem(){return mem;}
    inline uint8_t* getIP(){return ip;}
    inline uint8_t* getEnd(){return end;}
    inline uint8_t* getRegs(){return regs;}
    inline uint8_t** getRegm(){return regm;}
    inline uint8_t* getRegt(){return regt;}
    
private:
    InsTable itable;
    uint8_t* mem;
    uint8_t* ip;
    uint8_t* end;
    uint8_t* regs;
    uint8_t** regm;
    uint8_t* regt;
};

}

#endif

