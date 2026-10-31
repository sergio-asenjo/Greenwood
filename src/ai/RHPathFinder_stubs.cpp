#include "SBNullstr.h"
#include "RHPathFinder.h"
#include "SBGeoSegment2D.h"
#include "SBGeoSegmentVector.h"
#include "RHGameInputTranslator.h"

RHPathRequestList::~RHPathRequestList()
{
    ((std::list<void *> *)this)->clear();
    ((std::list<void *> *)this)->~list();
}

// FUNCTION: GAME 0x004e6ba0
void SBGeoSegmentVector::DestroyElements(SBGeoSegment2D *first, SBGeoSegment2D *last)
{
    for (; first != last; ++first)
        ((RHGameInputSegment *)first)->FUN_004611c0();
}

// TEMPLATE: GAME 0x0055b9f0
// ?Copy@SBGeoSegmentVector@@SAPAVSBGeoSegment2D@@PAV2@00@Z

// FUNCTION: GAME 0x0055b970
SBGeoSegment2D *SBGeoSegmentVector::Erase(SBGeoSegment2D *first, SBGeoSegment2D *last)
{
    SBGeoSegment2D *end = m_last;
    SBGeoSegment2D *next = first;
    for (; last != end; ++last, ++next)
        *next = *last;
    end = m_last;
    for (SBGeoSegment2D *entry = next; entry != end; ++entry)
        ((RHGameInputSegment *)entry)->FUN_004611c0();
    m_last = next;
    return first;
}

void RHPathFinder::FUN_005596d0(const SBGeoBoundingBox2D &, float, unsigned short) {}
void RHPathFinder::FUN_00559e00(const SBGeoBoundingBox2D &, float, unsigned short) {}

// Parked: vector assignment forwards constructor EAX instead of materializing its address.
// STUB: GAME 0x00608f40
SBGeoPoint2D SBGeoBoundingBox2D::FUN_00608f40() const
{
    SBGeoVector2D center;
    center = SBGeoVector2D((const SBGeoVector2D &)SBGeoVector2D((const SBGeoVector2D &)first).Unk005fc190(
        SBGeoVector2D((const SBGeoVector2D &)last)));
    ((RHUnk005fc3b0 *)&center)->FUN_005fc5b0(2.0f);
    return SBGeoPoint2D(center);
}
void RHPathFinder::FUN_00555a10(unsigned short, unsigned short, unsigned, RHPathWorkList &) {}
RHUnkIter RHPathRequestList::FUN_0046eb80() { return RHUnkIter(head->next); }

bool FUN_00558210(const SBGeoPoint2D &) { return false; }
bool FUN_00556990(SBGeoPoint2D, SBGeoPoint2D) { return false; }
void FUN_00553e60(const SBGeoPoint2D &, const SBGeoPoint2D &) {}
RHPathSearchNode *FUN_00556490(const SBGeoPoint2D &) { return 0; }
unsigned char FUN_00554b80(RHPathSearchNode *, unsigned char, RHPathPointList &) { return 0; }
