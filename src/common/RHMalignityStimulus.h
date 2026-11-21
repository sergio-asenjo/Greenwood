#ifndef RHMALIGNITYSTIMULUS_H
#define RHMALIGNITYSTIMULUS_H

#include "Decomp.h"
#include "RHMalignityPosition.h"

struct RHMalignityAlertPayload;
class RHElementActor;

// SIZE 0x2c
struct RHMalignityStimulus
{
    enum Payload { Position };
    RHMalignityStimulus() : m_type(0), m_24(0), m_28(0) {}
    explicit RHMalignityStimulus(Payload) : m_24(0), m_28(0) {}
    RHMalignityStimulus(unsigned value, const RHMalignityAlertPayload &payload);
    ~RHMalignityStimulus() {}
    union
    {
        undefined m_00[0x1c];
        RHElementActor *m_actor;
        RHMalignityPosition m_position;
    };
    unsigned m_type;
    unsigned m_20;
    void *m_24;
    char m_28;
};

#endif
