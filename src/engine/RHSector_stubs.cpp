#include "SBNullstr.h"
#include "RHSector.h"

RHSectorActorIter RHSectorActorList::insert(RHSectorActorIter pos, RHElementActor *const &) { return pos; }
RHSectorActorIter RHSectorActorList::erase(RHSectorActorIter pos) { return pos; }
void RHSectorActorList::Unk005c8e40(int) {}

RHUnk00522540::~RHUnk00522540() {}

class RHMobileUnk00611360
{
public:
    void FUN_00610f50(const SBGeoPoint2D &point, unsigned long index);
};


// FUNCTION: GAME 0x0060ce90
void RHUnkSectorPoints::FUN_0060ce90(const SBGeoPoint2D &point, unsigned int index)
{
    m_28 = 0;
    m_29 = 0;
    ((RHMobileUnk00611360 *)this)->FUN_00610f50(point, index);
}
void RHUnkSectorPoints::FUN_0060c2e0() {}

int RHUnk005f5440::Unk() { return 0; }
RHSector::RHSector() {}
void RHSector::UnkV0() {}
RHUnk0057d440::~RHUnk0057d440() {}
void RHUnk0057d440::UnkV0() {}
void RHUnk0057d440::UnkV4(SBFile &, bool) {}
void RHUnk0057d440::UnkV8() {}
void RHUnk0057d440::UnkVc() {}
void RHUnk0051aa00::Unk0051b2a0(SBFile &, bool) {}
