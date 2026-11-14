#ifndef SBSIMPLEVIRTUALMACHINECORE_H
#define SBSIMPLEVIRTUALMACHINECORE_H

#include "VMCore.h"
#include <string>

// VTABLE: GAME 0x0067bbc8
class SBSimpleVirtualMachine : public VMCore
{
public:
    static bool Initialize(std::string &);
    static bool Destroy();
    SBSimpleVirtualMachine();
    ~SBSimpleVirtualMachine();
    std::string m_name;
    bool m_bound;
};

#endif
