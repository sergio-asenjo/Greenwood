#include "RHSector.h"

int RHSectorActorList::Unk004b8f80(RHElementActor *const &, bool) { return -1; }
RHSectorActorIter RHSectorActorList::insert(RHSectorActorIter pos, RHElementActor *const &) { return pos; }
RHSectorActorIter RHSectorActorList::erase(RHSectorActorIter pos) { return pos; }
void RHSectorActorList::Unk005c8e40(int) {}
RHSectorActorIter RHSectorActorIter::operator++(int) { return *this; }
void RHUnkSectorScriptRef::Unk004089f0(RHElementActor *) {}
void RHUnkSectorScriptRef::Unk00408af0(RHElementActor *) {}

void RHSector::Unk0057cd60(SBFile &, bool) {}
RHUnk00522540::RHUnk00522540() {}
RHUnk00522540::~RHUnk00522540() {}
void RHUnk00522540::Unk005225a0(SBFile &) {}
void RHSectorArray<RHUnk00522540 *>::Erase(RHUnk00522540 **, RHUnk00522540 **) {}

unsigned int RHUnkSectorPoints::Unk0060ce80() { return 0; }
SBGeoPoint2D &RHUnkSectorPoints::Unk0060cef0(unsigned int) { return *(SBGeoPoint2D *)0; }
void RHUnkSectorPoints::Unk0060ced0(const SBGeoPoint2D &, unsigned int) {}
bool RHUnkSectorScript::Unk00639a30(const std::string &) { return true; }
void RHUnkSectorScriptRef::Unk00408900() {}

int RHUnk005f5440::Unk() { return 0; }
RHUnk0057d440::RHUnk0057d440() {}
RHUnk0057d440::~RHUnk0057d440() {}
void RHUnk0057d440::UnkV0() {}
void RHUnk0057d440::UnkV4(SBFile &, bool) {}
RHUnk0051aa00::RHUnk0051aa00() {}
RHUnk0051aa00::~RHUnk0051aa00() {}
void RHUnk0051aa00::Unk0051b2a0(SBFile &, bool) {}
