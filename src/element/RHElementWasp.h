#ifndef RHELEMENTWASP_H
#define RHELEMENTWASP_H

#include "RHElementProjectile.h"

class RHElementWasp : public RHElementObject
{
public:
    virtual bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    char m_100[0x5c];
    void *m_15c;
    void *m_160;
    int m_164;
    char m_168;
    char m_169[3];
    RHUnk005df510 m_16c;
};

#endif
