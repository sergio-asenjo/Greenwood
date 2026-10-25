#ifndef RHSEQUENCEELEMENTDAMAGE_H
#define RHSEQUENCEELEMENTDAMAGE_H

#include "RHSequenceElementSerialization.h"

class RHSequenceElementDamage : public RHSequenceElement
{
public:
    virtual bool Serialize(SBFile &file, bool pointers);
    bool FUN_005864e0();
    void Emit(SBFile &file, bool pointers);

    void *m_64;
    unsigned short m_68;
    unsigned short m_6a;
    bool m_6c;
    char m_6d[3];
    RHSword *m_70;
    int m_74;
    void *m_78;
};

#endif
