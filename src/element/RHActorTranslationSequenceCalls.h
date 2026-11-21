#ifndef RH_ACTOR_TRANSLATION_SEQUENCE_CALLS_H
#define RH_ACTOR_TRANSLATION_SEQUENCE_CALLS_H

#include "SBList.h"

class RHOrder;

class RHActorTranslationSequenceCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c(int value, bool mode) = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24(int value) = 0;
    void FUN_00585970(RHOrder *order);

    undefined m_04[0xc];
    int m_10;
    undefined m_14[4];
    SBList<RHOrder *> m_orders;
    undefined m_3c[0x1c];
    int m_58;
};

#endif
