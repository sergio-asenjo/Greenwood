#include "SBNullstr.h"
#include "RHSector.h"

RHUnk0057d490::RHUnk0057d490() {}

// SYNTHETIC: GAME 0x0057d590
// RHUnk0057d490::`scalar deleting destructor'
RHUnk0057d490::~RHUnk0057d490() {}

void RHSector::DisplayAlpha(unsigned long, unsigned long, bool) {}

RHSectorActorIter RHSectorActorList::insert(RHSectorActorIter pos, RHElementActor *const &) { return pos; }
RHSectorActorIter RHSectorActorList::erase(RHSectorActorIter pos) { return pos; }
void RHSectorActorList::Unk005c8e40(int) {}

// SYNTHETIC: GAME 0x00522560
// RHUnk00522540::`scalar deleting destructor'


// FUNCTION: GAME 0x0060ce90
void RHUnkSectorPoints::FUN_0060ce90(const SBGeoPoint2D &point, unsigned int index)
{
    m_28 = 0;
    m_29 = 0;
    ((RHMobileUnk00611360 *)this)->FUN_00610f50(point, index);
}
void RHUnkSectorPoints::FUN_0060c2e0() {}

int RHUnk005f5440::Unk() { return 0; }
void RHSector::UnkV0() {}
// SYNTHETIC: GAME 0x0057d3c0
// RHUnk0057d3a0::`scalar deleting destructor'
// FUNCTION: GAME 0x0057d3e0
RHUnk0057d3a0::~RHUnk0057d3a0() {}
// SYNTHETIC: GAME 0x0057d410
// RHUnk0057d3f0::`scalar deleting destructor'
// FUNCTION: GAME 0x0057d430
RHUnk0057d3f0::~RHUnk0057d3f0() {}
// SYNTHETIC: GAME 0x0057eda0
// RHUnk0057ed80::`scalar deleting destructor'
// FUNCTION: GAME 0x0057edc0
RHUnk0057ed80::~RHUnk0057ed80() {}
// SYNTHETIC: GAME 0x0057d460
// RHUnk0057d440::`scalar deleting destructor'
// FUNCTION: GAME 0x0057d480
RHUnk0057d440::~RHUnk0057d440() {}
// FUNCTION: GAME 0x0057dcc0
void *RHUnk0057dc80::FUN_0057dcc0(unsigned flags)
{
    this->~RHUnk0057dc80();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0057dce0
RHUnk0057dc80::~RHUnk0057dc80()
{
    *(unsigned *)this = 0x679c44;
    ((RHUnk0057d490 *)this)->RHUnk0057d490::~RHUnk0057d490();
}
void RHUnk0057d440::UnkV0() {}
void RHUnk0057d440::UnkV4(SBFile &, bool) {}
void RHUnk0057d440::UnkV8() {}
void RHUnk0057d440::UnkVc() {}
void RHUnk0051aa00::Unk0051b2a0(SBFile &, RHSectorBuilding *) {}
