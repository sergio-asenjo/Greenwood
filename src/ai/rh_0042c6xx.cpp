// Anonymous cluster at 0x0042c6xx / 0x0042c8xx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

struct RHUnk0042c6e0Value
{
    int m_00;
    int m_04;
    int m_08;
    int m_0c;
};

class RHUnk0042c6e0
{
public:
    RHUnk0042c6e0Value FUN_0042c6e0();
    int m_0;
    int m_4;
    int m_8;
    unsigned short m_c;
    unsigned short m_e;
    int m_10;
};

// Parked: by-value struct return shape reaches 13.33%; the target keeps m_4/m_8/
// m_c in stack slots while VC6 allocates ebx/edi and no frame. Explicit-pointer
// and named-local shapes also failed (20.00%/22.22%).
// STUB: GAME 0x0042c6e0
RHUnk0042c6e0Value RHUnk0042c6e0::FUN_0042c6e0()
{
    RHUnk0042c6e0Value result;
    result.m_00 = m_4;
    result.m_04 = m_8;
    result.m_08 = m_10;
    result.m_0c = m_c;
    return result;
}

struct RHUnk0042c830Value
{
    float m_00;
    float m_04;
    int m_08;
    int m_0c;
};

struct RHUnk0042c830Source
{
    char m_00[0x64];
    short m_64;
    short m_66;
    int m_68;
    unsigned short m_6c;
};

// Parked: by-value __stdcall return gets the frame (sub esp,0x10; push esi) but
// allocates an extra push edi and spills to [esp+0x20] where the target uses the
// arg2 slot [esp+0x1c]. Explicit-pointer shapes scored 0.00-13.33%.
// STUB: GAME 0x0042c830
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
