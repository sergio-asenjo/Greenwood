#include "SBNullstr.h"
#include "RHElementActorHuman.h"

void RHHumanActorCalls::FUN_00479320(RHUnk00613e90 &) {}
int RHHumanActorCalls::FUN_0047b8a0(const RHUnk00613e90 &, int *, bool) { return 0; }
void RHHumanActorCalls::FUN_0047d270(void *) {}
void RHHumanActorCalls::FUN_0049d780() {}
void RHHumanActorCalls::FUN_0047d4c0() {}
unsigned short RHHumanWeaponCalls::FUN_005c1d70(int) { return 0; }
unsigned short RHHumanWeaponCalls::FUN_005c1b70(void *, void *, unsigned short) { return 0; }
unsigned short RHHumanWeaponCalls::FUN_005c1db0(int) { return 0; }
SBGeoPoint2D SBGeoPoint2D::FUN_005fc200(const SBGeoPoint2D &other) const { return other; }
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
