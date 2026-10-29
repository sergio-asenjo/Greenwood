#include "RHHikingGuideStorage.h"
struct RHUnkPathRegistry;
extern RHUnkPathRegistry *g_unk0x6c0b9c;

DECOMP_SIZE_ASSERT(RHHikingGuide, 0x24)
DECOMP_SIZE_ASSERT(RHHikingGroupArray, 0x20)
DECOMP_SIZE_ASSERT(RHUnk0051d2c0, 0x20)

// FUNCTION: GAME 0x0051c8f0
RHHikingGuide::RHHikingGuide()
{
    g_unk0x6c0b9c = (RHUnkPathRegistry *)this;
}

// SYNTHETIC: GAME 0x0051c920
// RHHikingGuide::`scalar deleting destructor'

// STUB: GAME 0x0051c940
RHHikingGuide::~RHHikingGuide()
{
    m_04.Destroy();
}
