// Anonymous cluster at 0x0042c6xx / 0x0042c8xx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

#include "Decomp.h"

struct RHUnk0042c6e0Value
{
    float m_00;
    float m_04;
    int m_08;
    unsigned short m_0c;
};

DECOMP_SIZE_ASSERT(RHUnk0042c6e0Value, 0x10)

class RHUnk0042c6e0
{
public:
    RHUnk0042c6e0Value FUN_0042c6e0();
    int m_0;
    float m_4;
    float m_8;
    unsigned short m_c;
    unsigned short m_e;
    int m_10;
};

// FUNCTION: GAME 0x0042c6e0
RHUnk0042c6e0Value RHUnk0042c6e0::FUN_0042c6e0()
{
    RHUnk0042c6e0Value result;
    result.m_00 = m_4;
    result.m_04 = m_8;
    result.m_08 = m_10;
    result.m_0c = m_c;
    return result;
}

#include "RHMalignityPosition.h"

struct RHMalignityActorDescription
{
    char m_00[0x18];
    float m_18;
};

struct RHMalignityActor
{
    char m_00[0x50];
    RHMalignityActorDescription *m_50;
    float GetValue18() const { return m_50->m_18; }
};

#include "RHArtificialIntelligenceCore.h"

class RHMalignityReactionCalls
{
public:
    void FUN_00412d60(RHMalignityPosition position, short heading, int mode);
    void FUN_0042c7d0(RHMalignityActor *actor, int mode);
};

// FUNCTION: GAME 0x0042c7d0
void RHMalignityReactionCalls::FUN_0042c7d0(RHMalignityActor *actor, int mode)
{
    FUN_00412d60(((RHArtificialIntelligence *)this)->FUN_004165e0(actor, true),
        (int)actor->GetValue18(), mode);
}

struct RHUnk0042c830Value
{
    float m_00;
    float m_04;
    int m_08;
    unsigned short m_0c;
};

DECOMP_SIZE_ASSERT(RHUnk0042c830Value, 0x10)

struct RHUnk0042c830Source
{
    char m_00[0x64];
    short m_64;
    short m_66;
    int m_68;
    unsigned short m_6c;
};

// FUNCTION: GAME 0x0042c830
RHUnk0042c830Value __stdcall FUN_0042c830(const RHUnk0042c830Source *source)
{
    RHUnk0042c830Value result;
    result.m_00 = (float)source->m_64;
    result.m_04 = (float)source->m_66;
    result.m_08 = source->m_68;
    result.m_0c = source->m_6c;
    return result;
}

class RHUnk0042c890Stimulus
{
public:
    RHUnk0042c890Stimulus() : m_24(0), m_28(0) {}
    ~RHUnk0042c890Stimulus() {}
    char m_00[0x1c];
    unsigned m_type; // 0x1c
    unsigned m_20; // 0x20
    void *m_24; // 0x24
    char m_28; // 0x28
};

class RHUnk0042c890Dispatch
{
public:
    virtual void v00() = 0;
    virtual void v01() = 0;
    virtual void v02() = 0;
    virtual void v03() = 0;
    virtual void v04() = 0;
    virtual void v05() = 0;
    virtual void v06() = 0;
    virtual void v07() = 0;
    virtual void v08() = 0;
    virtual void v09(RHUnk0042c890Stimulus &value) = 0;
};

class RHMalignityAlertCalls
{
public:
    void FUN_0042c890(int type, void *actor);
};

// FUNCTION: GAME 0x0042c890
void RHMalignityAlertCalls::FUN_0042c890(int state, void *value)
{
    RHUnk0042c890Stimulus stimulus;
    stimulus.m_20 = state;
    *(void **)stimulus.m_00 = value;
    stimulus.m_type = 3;
    ((RHUnk0042c890Dispatch *)this)->v09(stimulus);
}

struct RHUnk0042c8f0Payload
{
    int m_0[6];
};

class RHUnk0042c8f0
{
public:
    void FUN_0042c8f0(int state, const RHUnk0042c8f0Payload *source);
};

// FUNCTION: GAME 0x0042c8f0
void RHUnk0042c8f0::FUN_0042c8f0(int state, const RHUnk0042c8f0Payload *source)
{
    RHUnk0042c890Stimulus stimulus;
    stimulus.m_20 = state;
    *(RHUnk0042c8f0Payload *)stimulus.m_00 = *source;
    stimulus.m_type = 4;
    ((RHUnk0042c890Dispatch *)this)->v09(stimulus);
}
