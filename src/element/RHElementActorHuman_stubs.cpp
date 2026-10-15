#include "SBNullstr.h"
#include "RHElementActorHuman.h"

void RHElementActorHuman::FUN_0046e2e0(void *) {}
void RHElementActor::FUN_00468f40(void *) {}
void RHElementActor::FUN_0046bd40(RHSequenceElement *) {}
bool RHElementActor::FUN_0046b760(unsigned, void *) { return false; }
bool RHElementActor::FUN_0046b2b0(unsigned, RHActorTranslationSequenceCalls *) { return false; }

class RHUnk004b1270
{
public:
    void FUN_004b1270();
};

void RHUnk004b1270::FUN_004b1270() {}
float RHUnk005bdcb0::FUN_005bdcb0() { return 0; }
void *RHUnkHumanPlacementA::FUN_005c1b20(int) { return this; }
void *RHUnkHumanPlacementB::FUN_00450040(int) { return this; }
void RHUnkHumanPositionProvider::FUN_00560420(void *) {}
bool RHUnkHumanPositionRange::FUN_0051afe0() { return false; }

int RHHumanActorCalls::FUN_0047b8a0(const RHUnk00613e90 &, int *, bool) { return 0; }
void RHHumanActorCalls::FUN_0049d780() {}
unsigned short RHHumanWeaponCalls::FUN_005c1d70(int) { return 0; }
unsigned short RHHumanWeaponCalls::FUN_005c1b70(void *, void *, unsigned short) { return 0; }
unsigned short RHHumanWeaponCalls::FUN_005c1db0(int) { return 0; }
SBGeoPoint2D RHHumanActorCalls::FUN_004237d0() { return *(SBGeoPoint2D *)this; }
float RHUnk0042fde0::FUN_0060ba80(const SBGeoPoint2D &) const { return 0; }
RHHumanFloatIterator RHHumanFloatList::FUN_00424410(RHHumanFloatIterator position, const float &) { return position; }
RHHumanFloatIterator RHHumanFloatList::FUN_0044e8b0(RHHumanFloatIterator, RHHumanFloatIterator last) { return last; }
RHHumanFloatIterator RHHumanFloatList::FUN_0046eb80() { return RHHumanFloatIterator(m_head->next); }
void RHHumanFloatList::At(int) {}

RHHumanMapNode *RHHumanMap::FUN_00588060(const int &key)
{
    return m_head;
}

class RHNPCBaseCalls
{
public:
    bool FUN_004799e0(SBFile &file);
};

bool RHNPCBaseCalls::FUN_004799e0(SBFile &file)
{
    return ((RHElementActorHuman *)this)->Serialize(file);
}
