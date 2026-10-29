#include "SBNullstr.h"
#include "RHElementActorHuman.h"

void RHEngine::FUN_004e39b0(void *, bool) {}
#include "RHWeapon.h"

class RHProfileManager;
RHProfileManager *RHUnk00436500GetProfileManager();

void RHElementActorHuman::FUN_0046e2e0(void *) {}
void RHElementActor::FUN_00468f40(void *) {}
bool RHElementActor::FUN_00464230() { return false; }
void RHElementActorHuman::FUN_0047ef70() {}
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
SBGeoPoint2D RHHumanActorCalls::FUN_004237d0() { return *(SBGeoPoint2D *)this; }

// TEMPLATE: GAME 0x00424410 FOLDED
// ?FUN_00424410@RHHumanFloatList@@QAE?AURHHumanFloatIterator@@U2@ABM@Z
RHHumanFloatIterator RHHumanFloatList::FUN_00424410(RHHumanFloatIterator position, const float &value)
{
    RHHumanFloatNode *next = position.node;
    RHHumanFloatNode *previous = next->previous;
    RHHumanFloatNode *node = (RHHumanFloatNode *)operator new(sizeof(RHHumanFloatNode));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    new (&node->value) float(value);
    ++m_count;
    return RHHumanFloatIterator(node);
}

RHHumanFloatIterator RHHumanFloatList::FUN_0044e8b0(RHHumanFloatIterator, RHHumanFloatIterator last) { return last; }
RHHumanFloatIterator RHHumanFloatList::FUN_0046eb80() { return RHHumanFloatIterator(m_head->next); }

class RHNPCBaseCalls
{
public:
    bool FUN_004799e0(SBFile &file);
};

bool RHNPCBaseCalls::FUN_004799e0(SBFile &file)
{
    return ((RHElementActorHuman *)this)->Serialize(file);
}
