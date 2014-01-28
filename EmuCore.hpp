#ifndef EMUCORE_HPP
#define EMUCORE_HPP

#include <functional>
#include "InsTable.hpp"
#include "utypes.hpp"
using namespace ugl;

namespace emu
{

class EmuCore
{
public:
    EmuCore();
    ~EmuCore();
    
    inline void setIP(uchar* ip){if(mem <= ip && end > ip) this->ip = ip;}
    inline void step(){ip = itable.exec(ip, end, (void*)this);}
    inline uchar* getMem(){return mem;}
    inline uchar* getIP(){return ip;}
    inline uchar* getEnd(){return end;}
    inline uchar* getRegs(){return regs;}
    inline uchar** getRegm(){return regm;}
    inline uchar* getRegt(){return regt;}
    
private:
    InsTable itable;
    uchar* mem;
    uchar* ip;
    uchar* end;
    uchar* regs;
    uchar** regm;
    uchar* regt;
};

}

#endif

