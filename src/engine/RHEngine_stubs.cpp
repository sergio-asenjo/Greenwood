#include "SBNullstr.h"
#include "RHEngine.h"
#include "RHScript.h"
#include "RHEngineSpriteCalls.h"
#include "RHUnk0054eab0.h"
#include <stddef.h>

DECOMP_SIZE_ASSERT(RHSpriteListRoot, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk00564020, 0x18)
DECOMP_SIZE_ASSERT(SBResourceScalarVector, 0x10)
DECOMP_SIZE_ASSERT(SBResourceSurfaceArray, 0x20)
DECOMP_SIZE_ASSERT(RHUnk0054eab0, 0x1a0)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_1c) == 0x1c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_40) == 0x40)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_64) == 0x64)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_88) == 0x88)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_ac) == 0xac)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_d0) == 0xd0)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_f4) == 0xf4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_118) == 0x118)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_140) == 0x140)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_158) == 0x158)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_178) == 0x178)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0054eab0, m_19c) == 0x19c)


void RHEngine::FUN_004d3d00(void *, void *, unsigned, unsigned, unsigned, unsigned) {}
void RHEngine::FUN_004d3e90(void *, void *, unsigned, unsigned, unsigned, unsigned) {}

class RHEngineSoundCalls
{
public:
    void FUN_005a5060(void *source, void *first, void *second, unsigned third, unsigned volume);
};

void RHEngineSoundCalls::FUN_005a5060(void *, void *, void *, unsigned, unsigned) {}

void FUN_00570850(void *) {}
RHUnk004a1bc0::RHUnk004a1bc0(bool) {}

#include "RHSectorCore.h"

// FUNCTION: GAME 0x0057ee40
RHUnk0057ee40::RHUnk0057ee40()
{
    ((RHSector *)this)->RHSector::RHSector();
    *(unsigned *)((char *)this + 0x30) |= 0x90;
    *(unsigned *)this = 0x679c7c;
}

// FUNCTION: GAME 0x0057ee60
void *RHUnk0057ee40::FUN_0057ee60(unsigned flags)
{
    this->~RHUnk0057ee40();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0057ee80
RHUnk0057ee40::~RHUnk0057ee40()
{
    *(unsigned *)this = 0x679c7c;
    ((RHSector *)this)->RHSector::~RHSector();
}

// FUNCTION: GAME 0x0051d2c0
RHUnk0051d2c0::~RHUnk0051d2c0()
{
    int count = size();
    for (int index = 0; index < count; ++index)
    {
        RHUnk00551da0 *entry = (*this)[index];
        if (entry)
            ((RHUnk0051d370Entry *)((char *)entry + 0x5c))->V00(1);
    }
    clear();
}
int RHHikingGuide::FUN_0051cac0(SBFile &) { return 0; }
class RHScrollScript
{
public:
    bool FUN_006348f0(SBFile &file);
};

extern char g_unk0x6c0691;
void RHSerializeName(SBFile &file, const char *name);

// FUNCTION: GAME 0x00551da0
bool RHUnk00551da0::FUN_00551da0(SBFile &file)
{
    // STRING: GAME 0x006b15a4
    RHSerializeName(file, "RHWayPoint");
    if (g_unk0x6c0691 == 1 && *(unsigned char *)((char *)this + 0x6e) == 1)
        return ((RHScrollScript *)this)->FUN_006348f0(file);
    return true;
}
void RHUnk004e51e0::FUN_00454bb0() {}

struct RHbeamMe;

#include "RHEngineSerializationCalls.h"

void RHEngineSerializationCalls::FUN_0048fa30() {}
void RHEngineSerializationCalls::FUN_004d88e0(void *, int, int) {}

class RHEngineMissionCalls
{
public:
    void FUN_004c1ab0(SBFile &file, RHMission *mission, std::string &background, unsigned *version);
    void FUN_004c3680(SBFile &file);
    void FUN_004c3630(SBFile &file);
    void FUN_004c3930(SBFile &file, int protoLevel);
    void FUN_004c1ee0(SBFile &file);
    void FUN_004c20a0(SBFile &file);
    void FUN_004c2830(SBFile &file);
};

// TEMPLATE: GAME 0x004e5270 FOLDED
// ??0RHSpriteListRoot@@QAE@ABD@Z
RHSpriteListRoot::RHSpriteListRoot(const char &allocator)
{
    *(char *)&m_allocator = allocator;
    RHSpriteListNode *node = (RHSpriteListNode *)operator new(0xc);
    node->next = node;
    node->previous = node;
    head = node;
    count = 0;
}

// FUNCTION: GAME 0x0054eab0
RHUnk0054eab0::RHUnk0054eab0()
    : m_f4(*(const char *)&std::allocator<int>()),
      m_118(*(const char *)&std::allocator<unsigned long>()),
      m_158(std::allocator<unsigned long>())
{
    m_00[2] = 0;
    m_00[0] = 0;
    m_00[1] = 0;
    m_00[0xb] = 0;
    m_19c = false;
    m_00[6] = 1;
    m_00[0xc] = 0;
    *(int *)(m_00 + 0x18) = 0;
}

// TEMPLATE: GAME 0x0059fba0 FOLDED
// ??0SBResourceScalarVector@@QAE@ABV?$allocator@K@std@@@Z
SBResourceScalarVector::SBResourceScalarVector(const std::allocator<unsigned long> &allocator)
    : std::vector<unsigned long>(allocator)
{
}
void RHUnk0054eab0::FUN_0054eea0(SBFile &, void *) {}
void RHEngineGridCalls::FUN_004efd10(void *, unsigned short, bool) {}
short RHEngineGridCalls::FUN_004e8fc0(const SBGeoPoint2D &, const SBGeoPoint2D &, short, void *&) { return -1; }

// FUNCTION: GAME 0x004e9760
short RHEngineGridCalls::FUN_004e9760(const SBGeoPoint2D &point, const SBGeoPoint2D &origin, void *&sector, unsigned short &layer)
{
    for (short i = *(short *)((char *)this + 0x3e9c) - 1; i >= 0; --i)
    {
        short result = FUN_004e8fc0(point, origin, i, sector);
        if (result != -2)
        {
            if (result > 0 && (unsigned char)(*(unsigned *)((char *)sector + 0x30) >> 10) & 1)
            {
                sector = *(void **)((char *)sector + 0x58);
                if ((unsigned char)(*(unsigned *)((char *)sector + 0x30) >> 9) & 1)
                {
                    layer = *(unsigned short *)((char *)sector + 0x36);
                    return *(short *)((char *)sector + 0x38);
                }
            }
            layer = i;
            return result;
        }
    }
    layer = 0xffff;
    return -1;
}

// FUNCTION: GAME 0x004e9920
short RHEngineGridCalls::FUN_004e9920(const SBGeoPoint2D &point, const SBGeoPoint2D &origin, void *&sector, unsigned short &layer)
{
    bool first = true;
    short found;
    for (short i = *(short *)((char *)this + 0x3e9c) - 1; i >= 0; --i)
    {
        short result = FUN_004e8fc0(point, origin, i, sector);
        if (first)
        {
            if (result != -2)
            {
                found = result;
                first = false;
                layer = i;
            }
        }
        else if (result != -2)
        {
            if (result > 0 && (unsigned char)(*(unsigned *)((char *)sector + 0x30) >> 10) & 1)
            {
                sector = *(void **)((char *)sector + 0x58);
                if ((unsigned char)(*(unsigned *)((char *)sector + 0x30) >> 9) & 1)
                {
                    layer = *(unsigned short *)((char *)sector + 0x36);
                    return *(short *)((char *)sector + 0x38);
                }
            }
            layer = i;
            return result;
        }
    }
    if (!first)
        return found;
    return -2;
}

class RHEngineReinforcementCalls
{
public:
    void *FUN_00452130(void *profile);
    void FUN_004936a0(int value);
    void FUN_00491fd0(const RHbeamMe &beamMe);
    void FUN_004d8460(void *actor, int first, int second);
    unsigned FUN_004e4460(void **value, int insert);
    bool FUN_004f6c20(const SBGeoPoint2D &origin, SBGeoPoint2D &destination,
        unsigned short layer, const SBGeoPoint2D &extent);
};

void RHEngineReinforcementCalls::FUN_004d8460(void *, int, int) {}
bool RHEngineReinforcementCalls::FUN_004f6c20(const SBGeoPoint2D &, SBGeoPoint2D &, unsigned short, const SBGeoPoint2D &) { return false; }

class RHUnk0048f280
{
public:
    RHUnk0048f280(void *description);
    char m_data[0x60c];
};




#include "RHEngineBackgroundCalls.h"

class RHEngineBeamCalls
{
public:
    void FUN_004e4120(RHbeamMe *position, unsigned count, const RHbeamMe &value);
};


RHUnk0046ffe0::RHUnk0046ffe0(bool) {}
RHUnk004ab090::RHUnk004ab090() {}
RHUnk004b9b70::RHUnk004b9b70() {}
RHUnk004bac30::RHUnk004bac30() {}

void RHEngineMissionElementCalls::Unk00() {}
void RHEngineMissionElementCalls::Unk04() {}
void RHEngineMissionElementCalls::Unk08() {}
void RHEngineMissionElementCalls::Unk0c() {}
void RHEngineMissionElementCalls::Unk10() {}
void RHEngineMissionElementCalls::Unk14() {}
void RHEngineMissionElementCalls::Unk18() {}
void RHEngineMissionElementCalls::Unk1c() {}
void RHEngineMissionElementCalls::Unk20() {}
void RHEngineMissionElementCalls::Unk24() {}
void RHEngineMissionElementCalls::Unk28() {}
void RHEngineMissionElementCalls::Unk2c() {}
void RHEngineMissionElementCalls::Unk30() {}
void RHEngineMissionElementCalls::Unk34() {}
void RHEngineMissionElementCalls::Unk38(SBFile &) {}
void RHEngineMissionElementCalls::Unk3c(SBFile &) {}

#include "RHEngineWidenedCalls.h"

void RHEngineWidenedCalls::FUN_004eb120(SBFile &, void *) {}
void RHEngineWidenedCalls::FUN_00558670(SBFile &) {}
void RHEngineWidenedCalls::FUN_005e5160(unsigned) {}
class RHEngineActorUpdateCalls
{
public:
    void FUN_004af2a0();
};

void RHEngineActorUpdateCalls::FUN_004af2a0() {}

void RHEngineReset51bd90::FUN_0051bd90() {}
void RHEngineReset581c70::FUN_00581c70() {}
void RHEngineReset5c2570::FUN_005c2570() {}

void *RHUnk0051e790::FUN_0051e790(RHElementActorPC *, void *, const SBGeoPoint2D &, int) { return 0; }
