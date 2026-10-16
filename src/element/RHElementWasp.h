#ifndef RHELEMENTWASP_H
#define RHELEMENTWASP_H

#include "RHElementProjectile.h"
#include "RHProjectileLifetime.h"

class RHElementWaspNest;

class RHUnk004bc4d0 : public RHProjectileLifetime
{
public:
    RHUnk004bc4d0();
    RHUnk004bc4d0(const RHElementWaspNest *nest);
    const RHElementWaspNest *m_15c;
    void *m_160;
    int m_164;
    unsigned char m_168;
    unsigned char m_169[3];
    RHProjectilePointLifetime m_16c;
};

class RHElementWasp : public RHElementObject
{
public:
    struct VictimCandidature
    {
        unsigned int m_00;
        void *m_04;
    };
    struct VictimCandidatureOrdering
    {
        int operator()(const VictimCandidature &first, const VictimCandidature &second) const;
    };
    virtual bool Serialize(SBFile &file);
    void FUN_004bd0f0(void *element);
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
