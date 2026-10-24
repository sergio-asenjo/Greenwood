#include "SBNullstr.h"
#include "RHElementActorHuman.h"

void RHEngine::FUN_004e39b0(void *, bool) {}
#include "RHWeapon.h"

class RHProfileManager;
RHProfileManager *RHUnk00436500GetProfileManager();

void RHElementActorHuman::FUN_0046e2e0(void *) {}
void RHElementActorHuman::FUN_00483c90(RHActorTranslationSequenceCalls *) {}
void RHElementActor::FUN_00468f40(void *) {}
bool RHElementActor::FUN_00464230() { return false; }
void RHElementActorHuman::FUN_0047ef70() {}
void RHElementActor::FUN_0046bd40(RHSequenceElement *) {}
bool RHElementActor::FUN_0046b760(unsigned, void *) { return false; }

// FUNCTION: GAME 0x005c1b20
RHUnkHumanPlacementA::RHUnkHumanPlacementA(int value)
{
    ((RHWeapon *)this)->RHWeapon::RHWeapon();
    void **array = *(void ***)((char *)(void *)RHUnk00436500GetProfileManager() + 0x34);
    void *element = array[value];
    m_profile = element;
    m_vptr = 0x679e48;
}

// FUNCTION: GAME 0x00450040
RHUnkHumanPlacementB::RHUnkHumanPlacementB(int value)
{
    ((RHWeapon *)this)->RHWeapon::RHWeapon();
    void **array = *(void ***)((char *)(void *)RHUnk00436500GetProfileManager() + 0x44);
    void *element = array[value];
    m_profile = element;
    m_vptr = 0x67765c;
}
// FUNCTION: GAME 0x0051afe0
bool RHUnkHumanPositionRange::FUN_0051afe0(RHUnk00571160Position position)
{
    if (position.area == m_10 && FUN_0040ec60(*(const RHMalignityPosition *)&position, m_20).Unk005fc6d0(1.0f) <= 400.0f)
        return true;
    if (position.area == m_0c && FUN_0040ec60(*(const RHMalignityPosition *)&position, m_18).Unk005fc6d0(1.0f) <= 400.0f)
        return true;
    return false;
}

int RHHumanActorCalls::FUN_0047b8a0(const RHUnk00613e90 &, int *, bool) { return 0; }
unsigned short RHHumanWeaponCalls::FUN_005c1b70(void *, void *, unsigned short) { return 0; }
SBGeoPoint2D RHHumanActorCalls::FUN_004237d0() { return *(SBGeoPoint2D *)this; }
RHHumanFloatIterator RHHumanFloatList::FUN_00424410(RHHumanFloatIterator position, const float &) { return position; }
RHHumanFloatIterator RHHumanFloatList::FUN_0044e8b0(RHHumanFloatIterator, RHHumanFloatIterator last) { return last; }
RHHumanFloatIterator RHHumanFloatList::FUN_0046eb80() { return RHHumanFloatIterator(m_head->next); }
void RHHumanFloatList::At(int) {}

class RHNPCBaseCalls
{
public:
    bool FUN_004799e0(SBFile &file);
};

bool RHNPCBaseCalls::FUN_004799e0(SBFile &file)
{
    return ((RHElementActorHuman *)this)->Serialize(file);
}
