#include "RHUnk0060c2xx.h"

class RHUnk0060bd40 : public SBGeoPolyLine2DList
{
public:
    RHUnk0060bd40();
    RHUnk0060bd40(const RHUnk0060bd40 &other);
    RHUnk0060bd40(const RHUnkSectorPoints &other);
    void FUN_0060bc80(const RHUnk0060bd40 &other);
    void FUN_0060bce0(const RHUnkSectorPoints &other);
    short m_28;
    short m_2a;
    char m_2c;
    char m_2d;
};

// FUNCTION: GAME 0x0060bc80
void RHUnk0060bd40::FUN_0060bc80(const RHUnk0060bd40 &other)
{
    unsigned long count = ((const RHUnk0060c2xx *)&other)->FUN_0060c250();
    ((RHUnk0060c2xx *)this)->FUN_0060c280();
    for (unsigned long index = 0; index < count; ++index)
        ((RHUnk0060c2xx *)this)->FUN_0060c260(((const RHUnk0060c2xx *)&other)->FUN_0060c2b0(index));
    m_28 = other.m_28;
    m_2a = other.m_2a;
    m_2c = other.m_2c;
    m_2d = other.m_2d;
}

// FUNCTION: GAME 0x0060bce0
void RHUnk0060bd40::FUN_0060bce0(const RHUnkSectorPoints &other)
{
    unsigned long count = ((RHUnkSectorPoints *)&other)->Unk0060ce80();
    ((RHUnk0060c2xx *)this)->FUN_0060c280();
    for (unsigned long index = 0; index < count; ++index)
        ((RHUnk0060c2xx *)this)->FUN_0060c260(((RHUnkSectorPoints *)&other)->Unk0060cef0(index));
    m_28 = other.m_24;
    m_2a = other.m_26;
    m_2c = other.m_28;
    m_2d = other.m_29;
}

// FUNCTION: GAME 0x0060bd40
RHUnk0060bd40::RHUnk0060bd40() : SBGeoPolyLine2DList()
{
    m_28 = 3;
    m_2a = 7;
    m_2c = 1;
    m_2d = 1;
}

// FUNCTION: GAME 0x0060bd60
RHUnk0060bd40::RHUnk0060bd40(const RHUnk0060bd40 &other) : SBGeoPolyLine2DList()
{
    FUN_0060bc80(other);
}

// FUNCTION: GAME 0x0060bdb0
RHUnk0060bd40::RHUnk0060bd40(const RHUnkSectorPoints &other) : SBGeoPolyLine2DList()
{
    FUN_0060bce0(other);
}
