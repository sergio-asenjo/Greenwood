#ifndef SBSIMPLEVIRTUALMACHINE_H
#define SBSIMPLEVIRTUALMACHINE_H

#include "SCSerialize.h"
#include <string>
#include "VMCore.h"

class SBSimpleUnkCodeManager : public SCSerialize
{
public:
    int FUN_0063a450(const char *);
};

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

void SBSimpleUnk005f9510(void *, const char *, ...);

#endif
