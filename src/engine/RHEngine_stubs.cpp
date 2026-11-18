#include "SBNullstr.h"
#include "RHEngine.h"
#include "RHScript.h"
#include "RHEngineSpriteCalls.h"
#include "RHUnk0054eab0.h"
#include "SBFilePosition.h"
#include "RHFastFindGridCore.h"
#include "RHUnkMaskObstacleTable.h"
#include "RHUnkTargetSpriteCalls.h"
#include "RHSpriteLastFrameCalls.h"
#include "RHElementFX.h"
#include "RHElementGrid.h"
#include "RHUnk004b1520List.h"
#include <stddef.h>

struct RHUnk004b1520VoidList : public std::list<void *>
{
    void *m_cursor;
    bool m_dirty;
    int m_index;
};

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


class RHEngineSoundCalls
{
public:
    void FUN_005a5060(void *source, void *first, void *second, unsigned third, unsigned volume);
};

void RHEngineSoundCalls::FUN_005a5060(void *, void *, void *, unsigned, unsigned) {}

RHUnk004a1bc0::RHUnk004a1bc0(bool) {}

#include "RHSectorCore.h"
#include "RHSector.h"

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

#include "VMCore.h"

extern char g_unk0x6c0691;
void RHSerializeName(SBFile &file, const char *name);

// FUNCTION: GAME 0x00551da0
bool RHWaypoint::FUN_00551da0(SBFile &file)
{
    // STRING: GAME 0x006b15a4
    RHSerializeName(file, "RHWayPoint");
    if (g_unk0x6c0691 == 1 && *(unsigned char *)((char *)this + 0x6e) == 1)
        return ((VMCore *)this)->SerializeMemberVariable(file);
    return true;
}
void RHUnk004e51e0::FUN_00454bb0() {}

struct RHbeamMe;

#include "RHEngineSerializationCalls.h"

void RHEngineSerializationCalls::FUN_0048fa30() {}

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
// STUB: GAME 0x0054eea0
int RHUnk0054eab0::FUN_0054eea0(SBFile &file, void *grid)
{
    int start = ((ToolboxPositionFile *)&file)->FUN_005f5440();
    RHMobileBase004a8130 *element = new RHMobileBase004a8130(1);
    *(void **)((char *)this + 0x18) = element;
    *(void **)((char *)element + 0xac) = this;
    element->Unk38(file);
    file.Access((char *)this + 2, 1);
    *(char *)((char *)this + 3) = 1;
    file.Access((char *)this + 0x10, 4);
    if (*(int *)((char *)this + 0x10) != 0)
    {
        file.Access((char *)this + 0x16, 2);
        *(char *)((char *)this + 0xd) = 1;
        file.Access((char *)this + 0x14, 2);
        *(unsigned *)((char *)this + 0x10) = (*(unsigned *)((char *)this + 0x10) - 1) >> 1;
    }
    else
    {
        *(char *)((char *)this + 0xd) = 0;
    }
    file.Access((char *)this + 8, 1);
    file.Access((char *)this + 9, 1);
    file.Access((char *)this + 0xa, 1);
    if (*(char *)((char *)this + 8) != 0)
    {
        (*(RHUnkTargetSprite **)((char *)element + 0x50))->FUN_005b76e0(0x94, 0);
        ((RHUnk005bd5b0 *)*(void **)((char *)element + 0x50))->Unk(false);
    }
    else
    {
        *(char *)((char *)element + 0x12) = 0;
    }
    short first;
    short second;
    file.Access(&first, 2);
    file.Access(&second, 2);
    m_140.m_x = (float)first;
    m_140.m_y = (float)second;
    file.Access((char *)this + 0x13e, 2);
    file.Access((char *)this + 0x13c, 2);
    file.Access((char *)this + 1, 1);
    *(char *)((char *)this + 1) = *(char *)((char *)this + 1) == 0;
    file.Access((char *)this + 7, 1);
    if (*(char *)((char *)this + 7) != 0)
        ((RHElementFX *)element)->InitializeBackgroundRestoration();

    unsigned short count;
    unsigned short layer;
    unsigned short index;
    unsigned short i;
    void *value;
    RHUnk004b1520List *list;
    RHUnk004b1520VoidList *appendList;
    RHUnk0057d3f0 *sector;

    file.Access(&count, 2);
    list = (RHUnk004b1520List *)&m_1c;
    for (i = 0; i < count; ++i)
    {
        file.Access(&layer, 2);
        file.Access(&index, 2);
        value = (*(void ***)((char *)&((RHFastFindGrid *)grid)->m_3ea4[layer] + 0x84))[index];
        *(char *)value = 1;
        list->FUN_00424410(list->end(), value);
        list->m_10 = 1;
    }

    file.Access(&count, 2);
    list = (RHUnk004b1520List *)&m_64;
    for (i = 0; i < count; ++i)
    {
        file.Access(&index, 2);
        value = ((RHFastFindGrid *)grid)->m_3ea4[0].m_obstacles.m_first[index];
        *(char *)((char *)value + 8) = 1;
        list->FUN_00424410(list->end(), value);
        list->m_10 = 1;
    }

    sector = new RHUnk0057d3f0;
    sector->m_30 = 0x44;
    sector->Unk0057cd60(file, false);
    if (((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060ce80() > 0)
    {
        m_150 = sector;
        sector->m_34 = 1;
        sector->m_58 = this;
        value = sector;
        list = (RHUnk004b1520List *)&m_ac;
        list->FUN_00424410(list->end(), value);
        list->m_10 = 1;
    }
    else
    {
        m_150 = 0;
        delete sector;
    }

    sector = new RHUnk0057d3f0;
    sector->m_30 = 0x42;
    sector->Unk0057cd60(file, false);
    if (((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060ce80() > 0)
    {
        sector->m_34 = 1;
        sector->m_58 = this;
        value = sector;
        list = (RHUnk004b1520List *)&m_ac;
        list->FUN_00424410(list->end(), value);
        list->m_10 = 1;
    }
    else
    {
        delete sector;
    }

    file.Access(&count, 2);
    list = (RHUnk004b1520List *)&m_40;
    for (i = 0; i < count; ++i)
    {
        file.Access(&layer, 2);
        file.Access(&index, 2);
        value = (*(void ***)((char *)&((RHFastFindGrid *)grid)->m_3ea4[layer] + 0x84))[index];
        *(char *)value = 0;
        list->FUN_00424410(list->end(), value);
        list->m_10 = 1;
    }

    file.Access(&count, 2);
    appendList = (RHUnk004b1520VoidList *)&m_88;
    for (i = 0; i < count; ++i)
    {
        file.Access(&index, 2);
        value = ((RHFastFindGrid *)grid)->m_3ea4[0].m_obstacles.m_first[index];
        *(char *)((char *)value + 8) = 0;
        appendList->insert(appendList->end(), value);
        appendList->m_dirty = 1;
    }

    sector = new RHUnk0057d3f0;
    sector->m_30 = 0x44;
    sector->Unk0057cd60(file, false);
    if (((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060ce80() > 0)
    {
        m_154 = sector;
        sector->m_34 = 0;
        sector->m_58 = this;
        value = sector;
        appendList = (RHUnk004b1520VoidList *)&m_d0;
        appendList->insert(appendList->end(), value);
        appendList->m_dirty = 1;
    }
    else
    {
        m_154 = 0;
        delete sector;
    }

    sector = new RHUnk0057d3f0;
    sector->m_30 = 0x42;
    sector->Unk0057cd60(file, false);
    if (((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060ce80() > 0)
    {
        sector->m_34 = 0;
        sector->m_58 = this;
        value = sector;
        appendList = (RHUnk004b1520VoidList *)&m_d0;
        appendList->insert(appendList->end(), value);
        appendList->m_dirty = 1;
    }
    else
    {
        delete sector;
    }

    sector = new RHUnk0057d3f0;
    m_148 = sector;
    sector->m_30 = 0x184;
    sector->Unk0057cd60(file, false);
    if (((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060ce80() > 0)
    {
        sector->m_34 = 1;
        sector->m_58 = this;
    }
    else
    {
        delete sector;
        m_148 = 0;
    }

    sector = new RHUnk0057d3f0;
    m_14c = sector;
    sector->m_30 = 0x84;
    sector->Unk0057cd60(file, false);
    if (((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060ce80() > 0)
    {
        sector->m_34 = 1;
        sector->m_58 = this;
    }
    else
    {
        delete sector;
        m_14c = 0;
    }

    file.Access((char *)this + 4, 1);
    file.Access((char *)this + 5, 1);
    RHFastFindPointerArray *gates = &g_unk0x6c0a9c->m_gates;
    file.Access(&count, 2);
    for (i = 0; i < count; ++i)
    {
        file.Access(&index, 2);
        value = gates->m_first[index];
        if (*(char *)((char *)this + 4) != 0)
        {
            *(void **)((char *)value + 0xb0) = this;
        }
        else
        {
            m_158.m_values.push_back((unsigned long)value);
            m_158.m_changed = 1;
        }
    }
    file.Access(&count, 2);
    return ((ToolboxPositionFile *)&file)->FUN_005f5440() - start;
}
void RHEngineGridCalls::FUN_004efd10(void *, unsigned short, bool) {}

// FUNCTION: GAME 0x004e9760
short RHEngineGridCalls::FUN_004e9760(const SBGeoPoint2D &point, const SBGeoPoint2D &origin, void *&sector, unsigned short &layer)
{
    for (short i = *(short *)((char *)this + 0x3e9c) - 1; i >= 0; --i)
    {
        short result = ((RHElementGrid *)this)->FUN_004e8fc0(point, origin, i, sector);
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
        short result = ((RHElementGrid *)this)->FUN_004e8fc0(point, origin, i, sector);
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

struct RHBonusProjection;

class RHEngineReinforcementCalls
{
public:
    void *FUN_00452130(void *profile);
    void FUN_004936a0(int value);
    void FUN_00491fd0(const RHbeamMe &beamMe);
    unsigned FUN_004e4460(RHBonusProjection *const &value, bool insert);
    bool FUN_004f6c20(const SBGeoPoint2D &origin, SBGeoPoint2D &destination,
        unsigned short layer, const SBGeoPoint2D &extent);
};

bool RHEngineReinforcementCalls::FUN_004f6c20(const SBGeoPoint2D &, SBGeoPoint2D &, unsigned short, const SBGeoPoint2D &) { return false; }

class RHUnk0048f280
{
public:
    RHUnk0048f280(void *description);
    char m_data[0x60c];
};




#include "RHEngineBackgroundCalls.h"


RHUnk0046ffe0::RHUnk0046ffe0(bool) {}
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
