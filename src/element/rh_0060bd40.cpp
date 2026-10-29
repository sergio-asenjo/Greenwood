#include "RHUnk0060c2xx.h"
#include "RHUnk0060bd40.h"

DECOMP_SIZE_ASSERT(RHUnk0060bd40, 0x30)

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

// SYNTHETIC: GAME 0x0044c780
// RHUnk0060bd40::~RHUnk0060bd40

// TEMPLATE: GAME 0x0048f170 FOLDED
// ?_Next@_Acc@?$list@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@SAAAPAU_Node@23@PAU423@@Z

// TEMPLATE: GAME 0x0046eb80 FOLDED
// ?begin@?$list@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@QAE?AViterator@12@XZ

// TEMPLATE: GAME 0x0044e850 FOLDED
// ?erase@?$list@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@QAE?AViterator@12@V312@0@Z

void EmitPolygonListDestroy(RHUnk0060bd40 *value)
{
    value->~RHUnk0060bd40();
}
