#ifndef SBSIMPLEVIRTUALMACHINE_H
#define SBSIMPLEVIRTUALMACHINE_H

#include "SCSerialize.h"
#include <string>

class SBSimpleUnkCodeManager : public SCSerialize
{
public:
    int FUN_0063a450(const char *);
};

class SBSimpleVirtualMachine
{
public:
    static bool Initialize(std::string &);
    static bool Destroy();
};

void SBSimpleUnk005f9510(void *, const char *, ...);

#endif
