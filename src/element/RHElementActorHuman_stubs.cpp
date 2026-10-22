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

class RHUnk004b1270
{
public:
    void FUN_004b1270();
};

void RHUnk004b1270::FUN_004b1270() {}
// Parked: vptr-literal placement matches, but VC6 reuses eax for the table
// element where the target keeps it in edx (`mov edx,[eax+ecx*4]`). 4 shapes
// tried (inline element, named int/void* local, base-ctor placement).
// STUB: GAME 0x005c1b20
void *RHUnkHumanPlacementA::FUN_005c1b20(int value)
{
    ((RHWeapon *)this)->RHWeapon::RHWeapon();
    void **array = *(void ***)((char *)(void *)RHUnk00436500GetProfileManager() + 0x34);
    void *element = array[value];
    *(unsigned *)this = 0x679e48;
    *(void **)((char *)this + 4) = element;
    return this;
}

// Parked: same eax-vs-edx table-element residual as 0x005c1b20.
// STUB: GAME 0x00450040
void *RHUnkHumanPlacementB::FUN_00450040(int value)
{
    ((RHWeapon *)this)->RHWeapon::RHWeapon();
    void **array = *(void ***)((char *)(void *)RHUnk00436500GetProfileManager() + 0x44);
    void *element = array[value];
    *(unsigned *)this = 0x67765c;
    *(void **)((char *)this + 4) = element;
    return this;
}
void RHUnkHumanPositionProvider::FUN_00560420(void *) {}
bool RHUnkHumanPositionRange::FUN_0051afe0() { return false; }

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
