#ifndef RHUNK005DB7E0_H
#define RHUNK005DB7E0_H

#include "RHGameWidgetLifetime.h"
#include "RHPortraitRootList.h"
#include <vector>

class RHMission;

// SIZE 0x278
struct RHPortraitQuickEntry
{
    // FUNCTION: GAME 0x005dc5d0
    ~RHPortraitQuickEntry() {}
    RHPortraitQuickEntry &operator=(const RHPortraitQuickEntry &other);
    int m_00; // 0x00
    int m_04; // 0x04
    RHGameLifetime0044fe90 m_08; // 0x08
    RHGameLifetime0044fe90 m_d8; // 0xd8
    RHGameLifetime005161a0 m_1a8; // 0x1a8
};

// SIZE 0xc0
// VTABLE: GAME 0x00678f30
class RHUnk005db7e0 : public RHPortraitRootList
{
public:
    ~RHUnk005db7e0();
    void FUN_005dc690(const SBGeoBoundingBox2D &bounds);
    void *FUN_0050ef90(unsigned flags);
    bool FUN_005db920(RHMission *mission);
    std::vector<RHPortraitQuickEntry> m_entries; // 0xb0
};

#endif
