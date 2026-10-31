#ifndef RHUNK005DB7E0_H
#define RHUNK005DB7E0_H

#include "RHGameWidgetLifetime.h"
#include "RHPortraitRootList.h"
#include <vector>

// SIZE 0xd0
struct RHUnk005db7e0Slot
{
    RHGameLifetime00515f00 m_widget; // 0x00
    undefined m_cc[4]; // 0xcc
};

// SIZE 0x278
struct RHUnk005db7e0Entry
{
    int m_00; // 0x00
    int m_04; // 0x04
    RHUnk005db7e0Slot m_08; // 0x08
    RHUnk005db7e0Slot m_d8; // 0xd8
    RHGameLifetime00515b40 m_1a8; // 0x1a8
};

// SIZE 0xc0
// VTABLE: GAME 0x00678f30
class RHUnk005db7e0 : public RHPortraitRootList
{
public:
    ~RHUnk005db7e0();
    void FUN_005dc690(const SBGeoBoundingBox2D &bounds);
    void *FUN_0050ef90(unsigned flags);
    std::vector<RHUnk005db7e0Entry> m_entries; // 0xb0
};

#endif
