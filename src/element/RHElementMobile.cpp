#include "SBNullstr.h"
#include "RHElementMobile.h"
#include "RHUnk0051f0f0.h"
#include <stdlib.h>

extern "C" double __cdecl fabs(double);

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(RHMobilePath, 0x08)
DECOMP_SIZE_ASSERT(RHMobileNode005504d0, 0x1c)
DECOMP_SIZE_ASSERT(RHMobileUnk005504d0, 0x20)
DECOMP_SIZE_ASSERT(RHMobileSoundNode, 0x24)
DECOMP_SIZE_ASSERT(RHSound, 0x294)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHMobileBase004a8130, 0xfc)
DECOMP_SIZE_ASSERT(RHUnk004aac40, 0x104)
DECOMP_SIZE_ASSERT(RHElementMobile, 0x260)
DECOMP_SIZE_ASSERT(RHUnk004af060, 0x260)

RHMobileElementBase::RHMobileElementBase(int, int) {}
RHMobileElementBase::~RHMobileElementBase() {}

// GLOBAL: GAME 0x006c0960
bool g_mobileAssertDoubleBond = false;

// FUNCTION: GAME 0x0042fde0
SBGeoVector2D RHUnk0042fde0::FUN_0042fde0() const
{
    return m_8.Unk005fc110(m_0);
}

class RHUnk0048f0e0List
{
public:
    RHUnk0048f0e0List *m_next;
    RHUnk0048f0e0List *m_prev;
    char m_08[0x2c];
};

class RHUnk0048f0e0
{
public:
    RHUnk0048f0e0(const char *value);
    char m_0;
    char m_1[3];
    RHUnk0048f0e0List *m_4;
    int m_8;
};

// FUNCTION: GAME 0x0048f0e0
RHUnk0048f0e0::RHUnk0048f0e0(const char *value)
{
    m_0 = *value;
    RHUnk0048f0e0List *list = new RHUnk0048f0e0List;
    list->m_next = list;
    list->m_prev = list;
    m_4 = list;
    m_8 = 0;
}

// FUNCTION: GAME 0x0048f170
void *FUN_0048f170(void *value)
{
    return value;
}

// TEMPLATE: GAME 0x004aab50
// ??1?$vector@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@QAE@XZ

// FUNCTION: GAME 0x004aac40
RHUnk004aac40::RHUnk004aac40() : RHMobileBase004a8130(5)
{
    RHMobileField<unsigned>(this, 0xa8) = 1;
    RHMobileField<unsigned char>(this, 0x12) = 1;
    RHMobileField<unsigned short>(this, 0x10) = 0x1002;
    m_fc = 1.0f;
    m_100 = 0;
}

// Parked: command-state stack coloring and geometry scheduling require comparison.
// STUB: GAME 0x004abfe0
void RHElementMobile::FUN_004abfe0()
{
    bool fallback;
    if (m_190)
    {
        if (m_194)
        {
            do
            {
                if (!ExecuteMacroCommand())
                    break;
            } while (m_194);
            if (m_194 && !fallback)
                return;
        }
    }
    else
    {
        RHMobileElement *waypoint = RHMobileField<RHMobileElement *>(this, 0x18c);
        if (RHMobileField<unsigned short>(waypoint, 0x70))
        {
            if (RHMobileField<bool>(waypoint, 0x6e))
            {
                if (g_unk0x6c0691)
                    ((RHUnkWaypointRef *)((char *)waypoint + 0x60))->Unk00408750(this);
            }
            else
            {
                unsigned char *start = RHMobileField<unsigned char *>(waypoint, 0x74);
                m_190 = start;
                unsigned short alternatives = *(unsigned short *)m_190;
                m_190 += 2;
                unsigned char condition = *m_190++;
                bool selected = m_188->FUN_00550660(condition);
                if (!selected)
                {
                    m_190 += 2;
                    if (alternatives == 2)
                    {
                        condition = *m_190++;
                        selected = m_188->FUN_00550660(condition);
                    }
                }
                fallback = true;
                if (selected)
                {
                    m_190 = start + *(unsigned short *)m_190;
                    alternatives = *(unsigned short *)m_190;
                    m_190 += 2;
                    fallback = false;
                    unsigned char random = (unsigned char)(rand() % 100 + 1);
                    for (;;)
                    {
                        --alternatives;
                        unsigned char probability = *m_190;
                        if (random <= probability)
                        {
                            ++m_190;
                            m_190 = start + *(unsigned short *)m_190;
                            break;
                        }
                        if (!alternatives)
                        {
                            fallback = true;
                            break;
                        }
                        random -= probability;
                        m_190 += 3;
                    }
                }
                m_194 = *(unsigned short *)m_190;
                m_190 += 2;
                if (!fallback && m_194)
                {
                    do
                    {
                        if (!ExecuteMacroCommand())
                            break;
                    } while (m_194);
                    if (m_194)
                        return;
                }
            }
        }
    }
    RHUnk005fc3b0 direction;
    SBGeoPoint2D destination;
    m_188->FUN_005505c0();
    RHMobileElement *waypoint = m_188->m_4->m_4[RHMobileField<unsigned char>(m_188, 0)];
    destination.m_x = waypoint->m_64;
    destination.m_y = waypoint->m_66;
    RHMobilePosition *position = (RHMobilePosition *)((char *)m_50 + 4);
    RHMobileField<SBGeoPoint2D>(position, 0x44) = destination;
    RHMobileField<unsigned>(position, 8) = 0;
    direction.FUN_005fc430(destination.Unk005fc110(m_50->m_24));
    direction.FUN_005fc7c0(1.0f);
    RHMobileField<unsigned>(position, 8) = 1;
    RHMobileField<RHUnk005fc3b0>(position, 0x6c).FUN_005fc430(direction);
    position->FUN_0055fc20(false);
    if (RHMobileField<bool>(this, 0x1f0))
        ((RHUnk004af060 *)this)->Unk(direction.FUN_005fcc50(0.57357645f));
    unsigned short count = Size();
    for (unsigned short i = 0; i < count; ++i)
    {
        RHMobilePosition *part = (RHMobilePosition *)((char *)m_b0[i]->m_50 + 4);
        RHMobileField<unsigned>(part, 8) = 1;
        RHMobileField<RHUnk005fc3b0>(part, 0x6c).FUN_005fc430(direction);
        part->FUN_0055fc20(false);
    }
    RHMobileField<void *>(this, 0x18c) = 0;
    m_190 = 0;
}

// Parked: x87 ordering and register/store scheduling remain non-exact.
// STUB: GAME 0x004ac350
bool RHElementMobile::ExecuteMacroCommand()
{
    unsigned char command = *m_190++;
    switch (command)
    {
    case 128:
    {
        m_1ec = *(unsigned short *)m_190;
        m_190 += 2;
        unsigned short count = Size();
        for (unsigned short i = 0; i < count; ++i)
        {
            RHMobileElement *element = i[m_b0];
            element->m_50->FUN_005b76e0(m_1ec, 0);
            ((RHUnk005bd5b0 *)element->m_50)->Unk(false);
        }
        m_194 -= 3;
        return true;
    }
    case 129:
    {
        float speed = *(float *)m_190;
        m_19c = speed;
        m_194 -= 5;
        m_190 += 4;
        ((RHUnk004af1d0 *)this)->Unk(speed != 0.0f);
        return true;
    }
    case 130:
    {
        SBGeoPoint2D position;
        SBGeoPoint2D destination;
        m_1a0 = *(float *)m_190;
        if (m_1a0 == 0.0f)
            m_1a0 = 0.1f;
        m_190 += 4;
        unsigned short waypoint = *(unsigned short *)m_190;
        m_190 += 2;
        if (waypoint >= m_188->Size())
            SBAssert(1,
                // STRING: GAME 0x006aeb08
                "P:\\Robin Hood\\RHelementmobile.cpp", 741,
                // STRING: GAME 0x006aebb8
                "VERBOTEN : Mobile element waypoint command referencing non-existing waypoint (%d) !", waypoint);
        RHMobileElement *element = m_188->m_4->m_4[waypoint];
        destination.m_x = element->m_64;
        destination.m_y = element->m_66;
        position = m_50->m_24;
        float distance = ((RHUnk005fc3b0 *)&destination.Unk005fc110(position))->Unk005fc6a0(1.0f);
        m_194 -= 7;
        m_1a4 = (m_19c + m_1a0) * (m_1a0 - m_19c) * 0.5f / distance;
        return true;
    }
    case 131:
    {
        m_198 = *(unsigned short *)m_190;
        m_190 += 2;
        unsigned short count = Size();
        for (unsigned short i = 0; i < count; ++i)
            i[m_b0]->m_fc = 1000000.0f;
        m_194 -= 3;
        return false;
    }
    case 132:
        SBAssert(0, "P:\\Robin Hood\\RHelementmobile.cpp", 780,
            // STRING: GAME 0x006aeb64
            "WARNUNG : \"Flip extremities\" command of moving elements was declared deprecated !");
        return true;
    case 133:
    {
        unsigned value = *(unsigned short *)m_190;
        m_190 += 2;
        FUN_004af0f0(value);
        m_194 -= 3;
        return true;
    }
    case 134:
    {
        unsigned short value = *(unsigned short *)m_190;
        m_190 += 2;
        ((RHUnk004af060 *)this)->Unk(value);
        m_194 -= 3;
        return true;
    }
    default:
        SBAssert(0, "P:\\Robin Hood\\RHelementmobile.cpp", 835,
            // STRING: GAME 0x006aeb2c
            "VERBOTEN : Unknown mobile element waypoint command !");
        return false;
    }
}

#define SBGEO_BOUNDINGBOX2D_VIEW
#include "RHActorSequenceStorage.h"

// Parked: the compiler-generated static cleanup callback has no unique bindable symbol.
// STUB: GAME 0x004ac750
RHUnk0045aaf0 *RHElementMobile::FUN_004ac750(void *actor)
{
    static RHUnk0045aaf0 changeMouse;
    if (actor != 0 && RHMobileField<void *>(this, 0x1fc) != actor)
    {
        changeMouse.FUN_0045abc0(0x11, 0, 0);
        return &changeMouse;
    }
    return 0;
}

void EmitRHMobileMouseFocus(RHElementMobile *element)
{
    element->FUN_004ac750(0);
}

// Parked: holder/count register roles and argument/index scheduling differ.
// STUB: GAME 0x004ac7c0
bool RHElementMobile::FUN_004ac7c0(void *value, void *unused, int type)
{
    if (type == 9 && RHMobileField<bool>(this, 0x12) && RHMobileField<bool>(this, 0x1f1) && RHMobileField<bool>(this, 0xa8))
    {
        unsigned short count = Size();
        for (unsigned short i = 0; i < count; ++i)
            if (((RHMobilePartCalls *)m_b0[i])->FUN_004aafc0(value))
                return true;
    }
    return false;
}

// Parked: mission-loader EH layout, container lowering and helper bindings require comparison.
// STUB: GAME 0x004ad5f0
void RHElementMobile::InitializeFromMissionStream(SBFile &file)
{
    SBGeoPoint2D translation;
    SBGeoPoint2D original;
    SBGeoBoundingBox2D bounds;
    RHMobilePointerList lines;
    RHMobilePointerList vertices;
    unsigned short count;
    unsigned short i;
    FUN_005e1d50(file, 0x464c494d, 2);
    file.Access(&count, 2);
    RHMobilePointerArray &parts = RHMobileField<RHMobilePointerArray>(this, 0xac);
    for (i = 0; i < count; ++i)
    {
        RHUnk004aac40 *part = new RHUnk004aac40;
        part->v14(file);
        part->m_100 = this;
        parts.Append(part);
    }
    FUN_005e20c0(file);
    FUN_005e1d50(file, 0x574f4157, 3);
    RHMobilePointerArray materials;
    file.Access(&count, 2);
    RHMobilePointerArray &areas = RHMobileField<RHMobilePointerArray>(this, 0xcc);
    for (i = 0; i < count; ++i)
    {
        RHMobileAreaLoad *area = new RHMobileAreaLoad;
        area->FUN_005a3810(file, materials);
        areas.Append(area);
        bounds.FUN_00607e90(RHMobileField<SBGeoBoundingBox2D>(area, 0x24));
    }
    FUN_005e20c0(file);
    RHMobileField<unsigned>(this, 0x11c) = 0x42;
    RHMobilePolygon &polygon = RHMobileField<RHMobilePolygon>(this, 0xec);
    polygon.FUN_00464530(file, false);
    RHMobileGrid *grid = RHMobileField<RHMobileGrid *>(this, 0x64);
    grid->FUN_004e9d90(lines, polygon);
    count = (unsigned short)lines.m_8;
    RHMobilePointerArray &edges = RHMobileField<RHMobilePointerArray>(this, 0x164);
    for (i = 0; i < count; ++i)
    {
        lines.FUN_005c8e40(i);
        ((RHMobileUnk0051fd90 *)lines.m_c->value)->FUN_0051fd90(0, 15.0f);
        lines.FUN_005c8e40(i);
        edges.Append(lines.m_c->value);
    }
    grid->FUN_004ea7b0(vertices, polygon);
    count = (unsigned short)vertices.m_8;
    RHMobilePointerArray &corners = RHMobileField<RHMobilePointerArray>(this, 0x144);
    for (i = 0; i < count; ++i)
    {
        vertices.FUN_005c8e40(i);
        ((RHMobileUnk00520c50 *)vertices.m_c->value)->FUN_00520c50(0, 15.0f);
        vertices.FUN_005c8e40(i);
        corners.Append(vertices.m_c->value);
    }
    short x;
    short y;
    file.Access(&x, 2);
    file.Access(&y, 2);
    file.Access(&RHMobileField<bool>(this, 0x1f1), 1);
    if (RHMobileField<bool>(this, 0x1f1))
    {
        file.Access(&x, 2);
        file.Access(&y, 2);
        RHMobileField<float>(this, 0x1f4) = x;
        RHMobileField<float>(this, 0x1f8) = y;
    }
    bool orient;
    file.Access(&orient, 1);
    RHMobileField<bool>(this, 0x1f0) = orient;
    if (orient)
    {
        RHMobileField<bool>(this, 0x1f1) = true;
        file.Access(&x, 2);
        file.Access(&y, 2);
        RHMobileField<float>(this, 0x1f4) = x;
        RHMobileField<float>(this, 0x1f8) = y;
    }
    else
        RHMobileField<bool>(this, 0x1a8) = true;
    unsigned short pathIndex;
    file.Access(&pathIndex, 2);
    void *storage = ::operator new(0x40);
    m_188 = (RHMobilePath *)new (storage) RHMobileUnk005504d0;
    ((RHArtificialIntelligencePathCursor *)m_188)->Unk00550f60(pathIndex);
    unsigned initial;
    unsigned unused;
    file.Access(&initial, 4);
    file.Access(&unused, 4);
    RHMobileField<unsigned short>(this, 0x184) = (unsigned short)initial;
    ((RHArtificialIntelligencePathCursor *)m_188)->Unk005505b0((unsigned short)initial);
    RHMobileElement *waypoint = m_188->m_4->m_4[RHMobileField<unsigned char>(m_188, 0)];
    RHMobileField<RHMobileElement *>(this, 0x18c) = waypoint;
    m_50->m_de = RHMobileField<unsigned short>(waypoint, 0x6c);
    RHMobileField<void *>(m_50, 0xe0) = RHMobileField<void *>(waypoint, 0x68);
    unsigned short areaIndex;
    file.Access(&areaIndex, 2);
    void *projection = areaIndex == 0xffff ? 0 : RHMobileField<void **>(grid, 0x4144)[areaIndex];
    if (projection)
    {
        if (!(RHMobileField<unsigned>(projection, 0) >> 2 & 1))
            SBAssert(1, "P:\\Robin Hood\\RHelementmobile.cpp", 0x4d4,
                "DA F\304LLT MIR NICHTS MEHR EIN ! Element mobile (%d,%d) not lying on projection area !", (int)(short)m_50->m_24.m_y, (int)(short)m_50->m_24.m_x);
        if (!RHMobileField<SBGeoBoundingBox2D>(projection, 0x38).FUN_00608400(m_50->m_24))
            SBAssert(1, "P:\\Robin Hood\\RHelementmobile.cpp", 0x4d8,
                "DA F\304LLT MIR NICHTS MEHR EIN ! Element mobile (%d,%d) map position not lying in projection area screen box !", (int)(short)m_50->m_24.m_y, (int)(short)m_50->m_24.m_x);
    }
    RHMobilePosition *position = (RHMobilePosition *)((char *)m_50 + 4);
    ((RHBonusInfoBase *)position)->FUN_0055fa20((RHBonusProjection *)projection);
    translation.m_x = waypoint->m_64;
    translation.m_y = waypoint->m_66;
    ((RHActorPositionCalls *)this)->FUN_00464530(translation);
    ((RHBonusInfoBase *)position)->FUN_0055f290();
    TranslateGeometry(SBGeoVector2D(translation));
    RHMobileField<SBGeoPoint2D>(this, 0x1ac).FUN_005fc1e0(SBGeoVector2D(translation));
    count = Size();
    RHMobileUnk004b06f0 &vectors = RHMobileField<RHMobileUnk004b06f0>(this, 0x1c8);
    for (i = 0; i < count; ++i)
    {
        RHMobileBase004a8130 *part = (RHMobileBase004a8130 *)m_b0[i];
        part->v17(true);
        SBGeoBoundingBox2D local(-50.0f, -50.0f, 50.0f, 50.0f);
        RHMobileField<RHMobileUnk00607da0>(part, 0x54).FUN_00607da0(*(RHMobileUnk00607da0 *)&local);
        RHUnkTargetSprite *sprite = m_b0[i]->m_50;
        original = sprite->m_24;
        SBGeoPoint2D destination = original.Unk005fc190(SBGeoVector2D(translation));
        sprite->m_24 = destination;
        void *base = ((RHUnkPathActorInfoBase *)((char *)sprite + 4))->Unk0055fa10(RHMobileField<int>(sprite, 0x8c));
        SBGeoBoundingBox2D shifted = ((SBGeoBoundingBox2D *)base)->FUN_006090d0(SBGeoVector2D(destination));
        RHMobileField<RHMobileUnk00607da0>(sprite, 0xc0).FUN_00607da0(*(RHMobileUnk00607da0 *)&shifted);
        RHMobileField<unsigned>(sprite, 8) = 2;
        RHMobilePosition *partPosition = (RHMobilePosition *)((char *)sprite + 4);
        ((RHBonusInfoBase *)partPosition)->FUN_0055fa20((RHBonusProjection *)m_50->m_ec);
        ((RHBonusInfoBase *)partPosition)->FUN_0055f290();
        ((RHBonusInfo *)sprite)->FUN_005bd560(0, true);
        sprite->m_de = RHMobileField<unsigned short>(waypoint, 0x6c);
        RHMobileField<void *>(sprite, 0xe0) = RHMobileField<void *>(waypoint, 0x68);
        vectors.FUN_004b01b0(vectors.m_8, 1, RHUnk005fc3b0(0, 0));
        RHMobileField<bool>(this, 0x1dc) = true;
    }
    FUN_004abfe0();
    if (RHMobileField<bool>(this, 0x1f1))
        RHMobileField<bool>(this, 0xa8) = true;
    count = Size();
    for (i = 0; i < count; ++i)
        RHMobileField<float>(m_b0[i], 0xfc) = m_19c == 0.0f ? 1000000.0f : 1.0f / m_19c;
    if (RHMobileField<bool>(this, 0x1f0))
        ((RHUnk004af060 *)this)->Unk(((RHUnk005fc3b0 *)&m_188->FUN_004ae380())->FUN_005fcc50(1.0f));
}

static inline const SBGeoVector2D &MobilePathDifference(SBGeoVector2D &result, float lastX, float lastY, RHMobileElement *first)
{
    result.m_x = lastX;
    result.m_y = lastY;
    result.m_x = lastX - first->m_64;
    result.m_y = lastY - first->m_66;
    return result;
}

// Parked: first-waypoint loads are CSE-hoisted before the result's coordinate stores.
// STUB: GAME 0x004ae380
SBGeoVector2D RHMobilePath::FUN_004ae380() const
{
    SBGeoVector2D result;
    unsigned int count = m_4 == 0 ? 0 : m_4->m_4 == 0 ? 0 : m_4->m_8 - m_4->m_4;
    RHMobileElement *last = m_4->m_4[(unsigned short)(count - 1)];
    float lastY = last->m_66;
    float lastX = last->m_64;
    RHMobileElement *first = m_4->m_4[0];
    return SBGeoVector2D(MobilePathDifference(result, lastX, lastY, first));
}

#define RH_MOBILE_ACCESS(value, bytes, line) \
    if (file.Access(&(value), bytes) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, "P:\\Robin Hood\\RHelementmobile.cpp", line, "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

// Parked: serializer EH states, temporary scheduling and named call operands require comparison.
// STUB: GAME 0x004ae470
bool RHElementMobile::Serialize(SBFile &file)
{
    SBGeoPoint2D origin;
    RHUnk005fc3b0 saved;
    RHUnk005fc3b0 displacement;
    RHUnk005fc3b0 value;
    // STRING: GAME 0x006aecd4
    RHSerializeName(file, "RHElementMobile");
    unsigned short parts = Size();
    for (unsigned short i = 0; i < parts; ++i)
        ((RHMobileBase004a8130 *)m_b0[i])->v16(file);
    RH_MOBILE_ACCESS(RHMobileField<unsigned char>(this, 0xa8), 1, 0x550);
    RHMobileUnk004b06f0 &vectors = RHMobileField<RHMobileUnk004b06f0>(this, 0x1c8);
    unsigned count;
    if (file.m_bLoading)
    {
        RH_MOBILE_ACCESS(count, 4, 0x555);
        vectors.FUN_004b06f0(vectors.m_4, vectors.m_8);
        RHMobileField<bool>(this, 0x1dc) = true;
        for (unsigned index = 0; index < count; ++index)
        {
            value.Serialize(file);
            vectors.FUN_004afd70(vectors.m_8, value);
            RHMobileField<bool>(this, 0x1dc) = true;
        }
    }
    else
    {
        count = vectors.Size();
        RH_MOBILE_ACCESS(count, 4, 0x563);
        for (unsigned index = 0; index < count; ++index)
        {
            value.FUN_005fc430(vectors.m_4[index]);
            value.Serialize(file);
        }
    }
    RH_MOBILE_ACCESS(m_1ec, 4, 0x56d);
    RHMobileField<SBGeoPoint2D>(this, 0x204).Serialize(file);
    g_pEngine->FUN_004c3af0(file, RHMobileField<void *>(this, 0x1fc));
    RH_MOBILE_ACCESS(RHMobileField<unsigned>(this, 0x210), 4, 0x570);
    RH_MOBILE_ACCESS(RHMobileField<unsigned>(this, 0x214), 4, 0x571);
    RHMobileElement *waypoint = m_188->m_4->m_4[RHMobileField<unsigned short>(this, 0x184)];
    origin.m_x = waypoint->m_64;
    origin.m_y = waypoint->m_66;
    saved.FUN_005fc430(m_50->m_24.Unk005fc110(origin));
    if (file.m_bLoading)
    {
        saved.Serialize(file);
        displacement.FUN_005fc430(origin.Unk005fc190(saved.FUN_005fc450()).Unk005fc110(m_50->m_24));
        TranslateGeometry(SBGeoVector2D(displacement));
    }
    else
        saved.Serialize(file);
    ((RHPath *)m_188)->SerializeStatus(file);
    bool active;
    int offset;
    if (file.m_bLoading)
    {
        file.Access(&active, 1);
        if (active)
        {
            RHMobileElement *current = m_188->m_4->m_4[RHMobileField<unsigned char>(m_188, 0)];
            RHMobileField<RHMobileElement *>(this, 0x18c) = current;
            file.Access(&offset, 4);
            m_190 = offset == -1 ? 0 : RHMobileField<unsigned char *>(current, 0x74) + offset;
            file.Access(&m_194, 2);
        }
        else
        {
            RHMobileField<void *>(this, 0x18c) = 0;
            m_190 = 0;
        }
    }
    else
    {
        RHMobileElement *current = RHMobileField<RHMobileElement *>(this, 0x18c);
        active = current != 0;
        file.Access(&active, 1);
        if (active)
        {
            offset = m_190 ? m_190 - RHMobileField<unsigned char *>(current, 0x74) : -1;
            file.Access(&offset, 4);
            file.Access(&m_194, 2);
        }
    }
    file.Access(&m_198, 4);
    file.Access(&m_19c, 4);
    file.Access(&m_1a0, 4);
    file.Access(&m_1a4, 4);
    file.Access(&m_1a8, 1);
    RHMobileField<SBGeoPoint2D>(this, 0x1ac).Serialize(file);
    RHMobileField<SBGeoPoint2D>(this, 0x1b4).Serialize(file);
    RHMobilePointerList &references = RHMobileField<RHMobilePointerList>(this, 0x24c);
    if (file.m_bLoading)
    {
        RHMobilePointerNode *node = references.m_4->next;
        while (node != references.m_4)
        {
            RHMobilePointerNode *next = node->next;
            node->previous->next = next;
            next->previous = node->previous;
            ::operator delete(node);
            --references.m_8;
            node = next;
        }
        references.m_10 = true;
        RH_MOBILE_ACCESS(count, 4, 0x5f4);
        for (unsigned index = 0; index < count; ++index)
        {
            void *reference;
            g_pEngine->FUN_004c3f50(file, reference);
            references.Append(reference);
        }
    }
    else
    {
        count = references.m_8;
        RH_MOBILE_ACCESS(count, 4, 0x5e5);
        for (unsigned index = 0; index < count; ++index)
        {
            references.FUN_005c8e40(index);
            void *reference = references.m_c->value;
            g_pEngine->FUN_004c3f50(file, reference);
        }
    }
    RHSound *sound = (RHSound *)g_unk0x006c1070;
    RHMobileUnk005b4fa0 *sources = RHMobileField<RHMobileUnk005b4fa0 *>(sound, 0x200);
    short sourceIndex;
    if (file.m_bLoading)
    {
        RH_MOBILE_ACCESS(sourceIndex, 2, 0x601);
        RHMobileField<RHSoundSource *>(this, 0x23c) = sourceIndex == -1 ? 0 : sources->m_8[sourceIndex];
        RH_MOBILE_ACCESS(sourceIndex, 2, 0x604);
        RHMobileField<RHSoundSource *>(this, 0x240) = sourceIndex == -1 ? 0 : sources->m_8[sourceIndex];
        RH_MOBILE_ACCESS(RHMobileField<bool>(this, 0x238), 1, 0x607);
        RH_MOBILE_ACCESS(sourceIndex, 2, 0x608);
        RHMobileField<RHSoundSource *>(this, 0x244) = sourceIndex == -1 ? 0 : sources->m_8[sourceIndex];
        bool previous = RHMobileField<bool>(this, 0x248);
        RH_MOBILE_ACCESS(RHMobileField<bool>(this, 0x248), 1, 0x60c);
        if (previous != RHMobileField<bool>(this, 0x248))
        {
            if (RHMobileField<bool>(this, 0x248))
                sound->FUN_005a87f0(RHMobileField<RHSoundSource *>(this, 0x244));
            else
                sound->FUN_005a8810(RHMobileField<void *>(this, 0x244));
        }
    }
    else
    {
        sourceIndex = sources->FUN_005b4fa0(RHMobileField<RHSoundSource *>(this, 0x23c));
        RH_MOBILE_ACCESS(sourceIndex, 2, 0x61c);
        sourceIndex = sources->FUN_005b4fa0(RHMobileField<RHSoundSource *>(this, 0x240));
        RH_MOBILE_ACCESS(sourceIndex, 2, 0x61f);
        RH_MOBILE_ACCESS(RHMobileField<bool>(this, 0x238), 1, 0x621);
        sourceIndex = sources->FUN_005b4fa0(RHMobileField<RHSoundSource *>(this, 0x244));
        RH_MOBILE_ACCESS(sourceIndex, 2, 0x624);
        RH_MOBILE_ACCESS(RHMobileField<bool>(this, 0x248), 1, 0x626);
    }
    return ((RHElement *)this)->RHElement::Serialize(file);
}

#undef RH_MOBILE_ACCESS

// Parked: position-subobject address arithmetic remains folded into the store.
// STUB: GAME 0x004af060
void RHUnk004af060::Unk(int direction)
{
    unsigned short count = Size();
    for (unsigned short i = 0; i < count; ++i)
    {
        RHMobileElement *element = i[m_b0];
        int value = direction & 15;
        RHUnkTargetSprite *sprite = element->m_50;
        *(unsigned short *)((char *)sprite + 0xd8) = (unsigned short)value;
        ((RHMobilePosition *)((char *)sprite + 4))->SetFieldD6(value);
        element->m_50->FUN_005b76e0(m_1ec, direction);
        ((RHUnk005bd5b0 *)element->m_50)->Unk(false);
    }
}

// FUNCTION: GAME 0x004af0f0
void RHElementMobile::FUN_004af0f0(int value)
{
    m_1ec = value;
    unsigned short count = Size();
    for (unsigned short i = 0; i < count; ++i)
    {
        RHMobileElement *element = m_b0[i];
        element->m_50->FUN_005b76e0(m_1ec, 0);
        element->m_50->FUN_005b76e0(m_1ec, 0);
        ((RHUnk005bd5b0 *)element->m_50)->Unk(false);
    }
}

// New probe: marker flip is effective-only (100.00%*) with the SIB operand order unresolved.
// STUB: GAME 0x004af170
void RHElementMobile::FUN_004af170(void *value)
{
    unsigned short count = Size();
    for (unsigned short i = 0; i < count; ++i)
        ((RHBonusInfoBase *)((char *)m_b0[i]->m_50 + 4))->FUN_0055fa20((RHBonusProjection *)value);
}

// FUNCTION: GAME 0x004af210
void RHElementMobile::FUN_004af210(RHMobileEvent *event)
{
    switch (event->m_10)
    {
    case 156:
        RHMobileField<bool>(this, 0xa8) = false;
        break;
    case 157:
        RHMobileField<bool>(this, 0xa8) = true;
        break;
    case 158:
        ((RHUnk004af1d0 *)this)->Unk(true);
        break;
    case 159:
        ((RHUnk004af1d0 *)this)->Unk(false);
        break;
    default:
        return;
    }
    event->v3(0, true);
}

// Parked: list cleanup, registers, and local scheduling remain non-exact.
// STUB: GAME 0x004af540
void RHElementMobile::CheckForLineCrossing()
{
    RHUnk0040f060 lines;
    if (!m_50->m_24.FUN_005fc0e0(m_50->m_40))
        return;
    ((RHMobileGrid *)*(void **)((char *)this + 0x64))->FUN_004ed370(&lines, m_50->m_de, RHMobileSegment(m_50->m_40, m_50->m_24), 12);
    unsigned short count = (unsigned short)lines.count;
    if (count)
    {
        for (unsigned short i = 0; i < count; ++i)
        {
            lines.GoTo(i);
            RHElevationLine *line = lines.cursor->data;
            unsigned flags = line->m_14;
            if ((flags >> 2) & 1)
            {
                SBGeoPoint2D first(line->m_4);
                SBGeoPoint2D second(line->m_c);
                for (unsigned short j = i + 1; j < count; ++j)
                {
                    lines.GoTo(j);
                    RHElevationLine *other = lines.cursor->data;
                    if (other->m_14 == flags &&
                        ((first == other->m_4 && second == other->m_c) ||
                         (second == other->m_4 && first == other->m_c)))
                    {
                        if (!g_mobileAssertDoubleBond)
                            g_mobileAssertDoubleBond = true;
                        SBAssert(0, "P:\\Robin Hood\\RHelementmobile.cpp", 1916,
                            // STRING: GAME 0x006ae298
                            "Double bond : (%f,%f) - (%f,%f) !\n", other->m_4.m_x, other->m_4.m_y, other->m_c.m_x, other->m_c.m_y);
                        lines.GoTo(j);
                        ((RHUnk0046eb30 *)&lines)->erase(RHScriptIter(lines.cursor));
                        --j;
                        --count;
                        lines.dirty = true;
                    }
                }
            }
        }
        for (unsigned short index = 0; index < count; ++index)
        {
            RHUnk005fc3b0 movement;
            lines.GoTo(index);
            SBGeoPoint2D &first = lines.cursor->data->m_4;
            movement.FUN_005fc430(m_50->m_40.Unk005fc110(first));
            if (((RHUnk005fc3b0 *)&((RHUnk0042fde0 *)&first)->FUN_0042fde0())->FUN_005fc680(movement, 1.0f) == 0.0f)
            {
                lines.GoTo(index);
                ((RHUnk0046eb30 *)&lines)->erase(RHScriptIter(lines.cursor));
                --index;
                --count;
                lines.dirty = true;
            }
        }
        if (count == 1)
        {
            ((RHElement *)this)->CrossElevationLine(lines.head->next->data);
            ((RHMobilePosition *)((char *)m_50 + 4))->FUN_0055fc20(false);
            FUN_004af170(m_50->m_ec);
        }
        else
        {
            void *area = m_50->m_ec;
            for (unsigned short index = 0; index < (int)count - 1; ++index)
            {
                for (unsigned short j = index; j < count; ++j)
                {
                    lines.GoTo(j);
                    RHElevationLine *line = lines.cursor->data;
                    if (line->m_28 == area)
                    {
                        area = line->m_24;
                        lines.GoTo(index);
                        RHElevationLine *&destination = lines.cursor->data;
                        lines.GoTo(j);
                        RHElevationLine *value = lines.cursor->data;
                        lines.cursor->data = destination;
                        lines.GoTo(index);
                        lines.cursor->data = value;
                        break;
                    }
                    if (line->m_24 == area)
                    {
                        area = line->m_28;
                        lines.GoTo(index);
                        RHElevationLine *&destination = lines.cursor->data;
                        lines.GoTo(j);
                        RHElevationLine *value = lines.cursor->data;
                        lines.cursor->data = destination;
                        lines.GoTo(index);
                        lines.cursor->data = value;
                        break;
                    }
                }
            }
        }
    }
}

// TEMPLATE: GAME 0x004afb80
// ??1?$vector@VSBGeoVector2D@@V?$allocator@VSBGeoVector2D@@@std@@@std@@QAE@XZ

// TEMPLATE: GAME 0x004afd50
// ?size@?$vector@VSBGeoVector2D@@V?$allocator@VSBGeoVector2D@@@std@@@std@@QBEIXZ

unsigned RHMobileUnk004b06f0::FUN_004afd50() const
{
    RHUnk005fc3b0 *first = *(RHUnk005fc3b0 *volatile *)&m_4;
    if (!first)
        return 0;
    return m_8 - first;
}

RHUnk005fc3b0 *RHMobileUnk004b06f0::FUN_004afd70(RHUnk005fc3b0 *position, const RHUnk005fc3b0 &value)
{
    int offset = position - m_4;
    if ((unsigned)(m_c - m_8) < 1)
    {
        unsigned grow = Size() > 1 ? Size() : 1;
        int capacity = Size() + grow;
        RHUnk005fc3b0 *storage = (RHUnk005fc3b0 *)::operator new((capacity < 0 ? 0 : capacity) * 8);
        RHUnk005fc3b0 *destination = storage;
        for (RHUnk005fc3b0 *current = m_4; current != position; ++current, ++destination)
            FUN_004b0620(destination, *current);
        FUN_004b0620(destination, value);
        FUN_004b04d0(position, m_8, destination + 1);
        FUN_004aff00(m_4, m_8);
        ::operator delete(m_4);
        m_c = storage + capacity;
        unsigned size = Size();
        m_4 = storage;
        m_8 = storage + size + 1;
    }
    else
    {
        if ((unsigned)(m_8 - position) < 1)
        {
            FUN_004b04d0(position, m_8, position + 1);
            FUN_004b0510(m_8, 1 - (m_8 - position), value);
            FUN_004b05b0(position, m_8, value);
        }
        else
        {
            FUN_004b04d0(m_8 - 1, m_8, m_8);
            FUN_004b05e0(position, m_8 - 1, m_8);
            FUN_004b05b0(position, position + 1, value);
        }
        ++m_8;
    }
    return m_4 + offset;
}

// Parked: vector fill-insertion frame and copy scheduling require comparison.
// deferred: unannotated to preserve shared container call operands (0x004b01b0).
void RHMobileUnk004b06f0::FUN_004b01b0(RHUnk005fc3b0 *position, unsigned count, const RHUnk005fc3b0 &value)
{
    if ((unsigned)(m_c - m_8) < count)
    {
        unsigned grow = Size() > count ? Size() : count;
        int capacity = Size() + grow;
        RHUnk005fc3b0 *storage = (RHUnk005fc3b0 *)::operator new((capacity < 0 ? 0 : capacity) * 8);
        RHUnk005fc3b0 *destination = storage;
        for (RHUnk005fc3b0 *current = m_4; current != position; ++current, ++destination)
            FUN_004b0620(destination, *current);
        RHUnk005fc3b0 *fill = destination;
        for (unsigned remaining = count; remaining; --remaining, ++fill)
            FUN_004b0620(fill, value);
        destination += count;
        for (RHUnk005fc3b0 *currentTail = position; currentTail != m_8; ++currentTail, ++destination)
            FUN_004b0620(destination, *currentTail);
        for (RHUnk005fc3b0 *currentOld = m_4; currentOld != m_8; ++currentOld)
            currentOld->~RHUnk005fc3b0();
        ::operator delete(m_4);
        m_c = storage + capacity;
        unsigned size = Size();
        m_4 = storage;
        m_8 = storage + size + count;
    }
    else if ((unsigned)(m_8 - position) < count)
    {
        RHUnk005fc3b0 *destination = position + count;
        for (RHUnk005fc3b0 *current = position; current != m_8; ++current, ++destination)
            FUN_004b0620(destination, *current);
        destination = m_8;
        for (unsigned remaining = count - (m_8 - position); remaining; --remaining, ++destination)
            FUN_004b0620(destination, value);
        for (RHUnk005fc3b0 *currentFill = position; currentFill != m_8; ++currentFill)
            currentFill->FUN_005fc430(value);
        m_8 += count;
    }
    else if (count)
    {
        RHUnk005fc3b0 *destination = m_8;
        for (RHUnk005fc3b0 *current = m_8 - count; current != m_8; ++current, ++destination)
            FUN_004b0620(destination, *current);
        RHUnk005fc3b0 *currentBack = m_8 - count;
        destination = m_8;
        while (currentBack != position)
        {
            --currentBack;
            --destination;
            destination->FUN_005fc430(*currentBack);
        }
        for (RHUnk005fc3b0 *currentFill = position; currentFill != position + count; ++currentFill)
            currentFill->FUN_005fc430(value);
        m_8 += count;
    }
}

// TEMPLATE: GAME 0x004b06f0
// ?erase@?$vector@VSBGeoVector2D@@V?$allocator@VSBGeoVector2D@@@std@@@std@@QAEPAVSBGeoVector2D@@PAV3@0@Z

RHUnk005fc3b0 *RHMobileUnk004b06f0::FUN_004b06f0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last)
{
    RHUnk005fc3b0 *destination = first;
    RHUnk005fc3b0 *end = m_8;
    for (; last != end; ++last, ++destination)
        destination->FUN_005fc430(*last);
    end = m_8;
    for (RHUnk005fc3b0 *current = destination; current != end; ++current)
        current->~RHUnk005fc3b0();
    m_8 = destination;
    return first;
}

// Parked: point-assignment argument registers and receiver setup remain reordered.
// STUB: GAME 0x004e9d90
void RHMobileGrid::FUN_004e9d90(RHMobilePointerList &output, RHMobilePolygon &polygon)
{
    SBGeoPoint2D previous;
    SBGeoPoint2D current;
    RHMobilePolygonPoints &points = RHMobileField<RHMobilePolygonPoints>(&polygon, 4);
    unsigned short count = points.FUN_0060ce80();
    previous = points.FUN_0060cef0(count - 1);
    if (count > 0)
    {
        unsigned index = 0;
        unsigned remaining = count;
        do
        {
            current = points.FUN_0060cef0(index);
            RHMobileUnk0051fd10 *line = new RHMobileUnk0051fd10(0, 5.0f);
            bool inside = (RHMobileField<unsigned char>(&polygon, 0x30) & 1) != 0;
            unsigned &flags = RHMobileField<unsigned>(line, 0x14);
            if (inside)
                flags |= 1;
            else
                flags &= ~1;
            RHMobileField<volatile unsigned char>(line, 0x18) = RHMobileField<unsigned char>(&polygon, 0x34);
            SBGeoPoint2D *ends = (SBGeoPoint2D *)((char *)line + 4);
            ends[0] = previous;
            ends[1] = current;
            line->FUN_0051fdc0();
            output.Append(line);
            previous = current;
            ++index;
        } while (--remaining);
    }
}

// Parked: repeated vertex EH states and list insertion lowering require comparison.
// STUB: GAME 0x004ea7b0
void RHMobileGrid::FUN_004ea7b0(RHMobilePointerList &output, RHMobilePolygon &polygon)
{
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    SBGeoPoint2D next;
    RHUnk005fc3b0 incoming;
    RHUnk005fc3b0 outgoing;
    RHMobilePolygonPoints &points = RHMobileField<RHMobilePolygonPoints>(&polygon, 4);
    unsigned short count = points.FUN_0060ce80();
    first = points.FUN_0060cef0(0);
    second = points.FUN_0060cef0(1);
    incoming.FUN_005fc430(second.Unk005fc110(first));
    bool reverse = (RHMobileField<unsigned char>(&polygon, 0x30) & 1) != 0;
    for (unsigned index = 2; index < (unsigned)count + 2; ++index)
    {
        next = points.FUN_0060cef0(index < count ? index : index - count);
        outgoing.FUN_005fc430(next.Unk005fc110(second));
        float cross = outgoing.FUN_005fc680(incoming, 1.0f);
        if (reverse ? cross < 0.0f : cross > 0.0f)
        {
            RHUnk00520ae0 *vertex = new RHUnk00520ae0(second, 0, 5.0f);
            vertex->FUN_00520c80(incoming.FUN_005fc8f0(0, 1.0f), outgoing.FUN_005fc8f0(0, 1.0f));
            output.Append(vertex);
        }
        first = second;
        second = next;
        incoming.FUN_005fc430(outgoing);
    }
}

class RHUnk0051fc10
{
public:
    RHUnk0051fc10();
    ~RHUnk0051fc10();
    void *FUN_0051fc40(unsigned flags);
    char m_00[0x14];
    int m_14;
    char m_18[8];
    char m_20;
    char m_21[3];
    int m_24;
    int m_28;
    int m_2c;
    int m_30;
};

// FUNCTION: GAME 0x0051fc10
RHUnk0051fc10::RHUnk0051fc10()
{
    ((RHUnk0051f0f0 *)this)->RHUnk0051f0f0::RHUnk0051f0f0();
    *(unsigned *)this = 0x6790f0;
    m_20 = 0;
    m_28 = 0;
    m_30 = 0;
    m_14 = 0x10;
    m_24 = 1;
}

// FUNCTION: GAME 0x0051fc40
void *RHUnk0051fc10::FUN_0051fc40(unsigned flags)
{
    this->~RHUnk0051fc10();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0051fc60
RHUnk0051fc10::~RHUnk0051fc10()
{
    *(unsigned *)this = 0x6790f0;
    if (m_20)
        operator delete((void *)m_28);
    ((RHUnk0051f0f0 *)this)->RHUnk0051f0f0::~RHUnk0051f0f0();
}

// SYNTHETIC: GAME 0x0051fc90
// RHMobileUnk0051fd10::`scalar deleting destructor'

// FUNCTION: GAME 0x0051fcb0
RHMobileUnk0051fd10::~RHMobileUnk0051fd10()
{
}

// FUNCTION: GAME 0x0051fd10
RHMobileUnk0051fd10::RHMobileUnk0051fd10(float first, float second)
{
    m_14 |= 0x80;
    ((RHMobileUnk0051fd90 *)this)->FUN_0051fd90(first, second);
}

// FUNCTION: GAME 0x0051fd90
void RHMobileUnk0051fd90::FUN_0051fd90(float first, float second)
{
    m_24 = first + second;
    m_28 = first;
    m_2c = 1.0f / (m_24 - first);
    m_30 = -(m_2c * first);
}

// FUNCTION: GAME 0x0051fdc0
void RHMobileUnk0051fd10::FUN_0051fdc0()
{
    m_3c.FUN_005fc430(((RHUnk0042fde0 *)((char *)this + 4))->FUN_0042fde0());
    m_3c.FUN_005fc7c0(1.0f);
    if (m_14 & 1)
        m_34.FUN_005fc430(m_3c.FUN_005fc8f0(true, 1.0f));
    else
        m_34.FUN_005fc430(m_3c.FUN_005fc8f0(false, 1.0f));
}

// FUNCTION: GAME 0x0051fea0
bool RHMobileUnk0051fd10::FUN_0051fea0(const SBGeoPoint2D &point, float &distance)
{
    distance = point.Unk005fc110(*(SBGeoPoint2D *)((char *)this + 4)).FUN_005fc660(m_34);
    if (!((unsigned short)((unsigned)m_14 >> 8) & 1))
    {
        if (distance < 0.0f)
            return false;
    }
    double absolute = fabs(distance);
    return absolute < m_24 && ((RHUnk0042fde0 *)((char *)this + 4))->FUN_0060b640(point);
}

// FUNCTION: GAME 0x00520c50
void RHMobileUnk00520c50::FUN_00520c50(float first, float second)
{
    m_24 = first + second;
    m_30 = first;
    m_28 = 1.0f / (m_24 - first);
    m_2c = -(m_28 * first);
}

// FUNCTION: GAME 0x005214b0
RHUnk005214b0::RHUnk005214b0()
{
    ((RHUnk0051f0f0 *)this)->RHUnk0051f0f0::RHUnk0051f0f0();
    int value = m_14;
    *(unsigned *)this = 0x679120;
    value |= 2;
    m_20 = 0xffff;
    m_14 = value;
}

// FUNCTION: GAME 0x005214d0
void *RHUnk005214b0::FUN_005214d0(unsigned flags)
{
    this->RHUnk005214b0::~RHUnk005214b0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005214f0
RHUnk005214b0::~RHUnk005214b0()
{
    *(unsigned *)this = 0x679120;
    ((RHUnk0051f0f0 *)this)->RHUnk0051f0f0::~RHUnk0051f0f0();
}

class RHUnk00521500
{
public:
    void *FUN_00521520(unsigned flags);
    RHUnk00521500();
    ~RHUnk00521500();
    char m_00[0x14];
    int m_14;
    char m_18;
};

// FUNCTION: GAME 0x00521500
RHUnk00521500::RHUnk00521500()
{
    ((RHUnk0051f0f0 *)this)->RHUnk0051f0f0::RHUnk0051f0f0();
    *(unsigned *)this = 0x679128;
    m_14 = 0x40;
    m_18 = 1;
}

// FUNCTION: GAME 0x00521520
void *RHUnk00521500::FUN_00521520(unsigned flags)
{
    this->~RHUnk00521500();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00521540
RHUnk00521500::~RHUnk00521500()
{
    *(unsigned *)this = 0x679128;
    ((RHUnk0051f0f0 *)this)->RHUnk0051f0f0::~RHUnk0051f0f0();
}

class RHUnk00521550Part
{
public:
    RHUnk00521550Part();
    char m_0[0xc];
};

class RHUnk00521550
{
public:
    RHUnk00521550();
    void *FUN_00521570(unsigned flags);
    ~RHUnk00521550();
    unsigned m_0;
    char m_4[0x10];
    RHUnk00521550Part m_14;
    SBGeoBoundingBox2D m_20;
};

// FUNCTION: GAME 0x00521550
RHUnk00521550::RHUnk00521550()
{
    *(unsigned *)this = 0x679130;
}

// FUNCTION: GAME 0x00521570
void *RHUnk00521550::FUN_00521570(unsigned flags)
{
    this->~RHUnk00521550();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00521590
RHUnk00521550::~RHUnk00521550()
{
    *(unsigned *)this = 0x679130;
}

void EmitRHUnk0051fc10(void *storage)
{
    ((RHUnk0051fc10 *)storage)->RHUnk0051fc10::RHUnk0051fc10();
    ((RHUnk005214b0 *)storage)->RHUnk005214b0::RHUnk005214b0();
    ((RHUnk00521500 *)storage)->RHUnk00521500::RHUnk00521500();
    ((RHUnk005214b0 *)storage)->RHUnk005214b0::~RHUnk005214b0();
    ((RHUnk00521500 *)storage)->RHUnk00521500::~RHUnk00521500();
    ((RHUnk0051fc10 *)storage)->FUN_0051fc40(0);
    ((RHUnk00521550 *)storage)->FUN_00521570(0);
}

// FUNCTION: GAME 0x005504d0
RHMobileUnk005504d0::RHMobileUnk005504d0()
{
    undefined value;
    m_c = value;
    RHMobileNode005504d0 *node = (RHMobileNode005504d0 *)::operator new(0x1c);
    node->next = node;
    node->previous = node;
    m_10 = node;
    m_14 = 0;
    *(volatile bool *)&m_1c = true;
    m_0 = false;
    m_1 = false;
    m_4 = 0;
    m_2 = true;
    m_8 = 0xffff;
}

// Parked: position-state x87 scheduling and temporary lifetimes require comparison.
// STUB: GAME 0x0055fc20
void RHMobilePosition::FUN_0055fc20(bool updateDirection)
{
    unsigned &state = RHMobileField<unsigned>(this, 8);
    if (state == 7)
        return;
    bool stationary = false;
    float &x = RHMobileField<float>(this, 0x60);
    float &y = RHMobileField<float>(this, 0x64);
    float &elevation = RHMobileField<float>(this, 0x68);
    RHUnk005fc3b0 &movement = RHMobileField<RHUnk005fc3b0>(this, 0x6c);
    if ((state >> 1) & 1)
    {
        movement.m_x = x;
        movement.m_y = y - elevation;
    }
    else
    {
        bool project = true;
        if (!(state & 1))
        {
            movement.FUN_005fc430(RHMobileField<SBGeoPoint2D>(this, 0x44).Unk005fc110(RHMobileField<SBGeoPoint2D>(this, 0x20)));
            stationary = movement.FUN_005fc700(1.0f) < 1.0f;
            if (movement.m_x == 0.0f && movement.m_y == 0.0f)
                project = false;
            else
                movement.FUN_005fc7c0(1.0f);
        }
        if (project)
        {
            void *area = RHMobileField<void *>(this, 0xec);
            x = movement.m_x;
            if (area)
            {
                float height = (RHMobileField<float>(area, 0x4c) * movement.m_x +
                    RHMobileField<float>(area, 0x50) * movement.m_y) /
                    (1.0f - RHMobileField<float>(area, 0x50));
                elevation = height;
                y = height + movement.m_y;
            }
            else
            {
                y = movement.m_y;
                elevation = 0;
            }
        }
    }
    if (updateDirection && !stationary)
    {
        if (RHMobileField<bool>(this, 0x74))
            RHMobileField<unsigned short>(this, 0xd6) = (RHUnk005fc3b0(x, y).FUN_005fcc50(1.0f) ^ 8) & 15;
        else
            RHMobileField<unsigned short>(this, 0xd6) = RHUnk005fc3b0(x, y).FUN_005fcc50(1.0f) & 15;
    }
    state = 7;
}

// Parked: cached-list cursor lowering and counted geometry callees remain non-exact.
// STUB: GAME 0x005a5960
void RHMobileUnk005a5960::FUN_005a5960(const SBGeoPoint2D &value)
{
    RHMobilePointList &points = RHMobileField<RHMobilePointList>(this, 0x4c);
    unsigned short count = (unsigned short)points.m_8;
    for (int i = 0; i < count; ++i)
    {
        points.FUN_005c8e40(i);
        points.m_c->value.m_x += value.m_x;
        points.GoToInline(i, count);
        points.m_c->value.m_y += value.m_y;
    }
    RHMobileField<RHMobileUnk005dfaa0>(this, 0xa8).FUN_005dfaa0(value);
    RHMobileField<RHMobileUnk005dfaa0>(this, 0x100).FUN_005dfaa0(value);
    RHMobileField<float>(this, 0xc) += value.m_x;
    RHMobileField<float>(this, 0x10) += value.m_x;
    RHMobileField<float>(this, 0x14) += value.m_y;
    RHMobileField<float>(this, 0x18) += value.m_y;
    RHMobileField<RHMobileUnk006091b0>(this, 0x24).FUN_006091b0(value);
    RHMobileField<RHMobileUnk006091b0>(this, 0x38).FUN_006091b0(value);
}

// FUNCTION: GAME 0x005a87f0
void RHSound::FUN_005a87f0(RHSoundSource *source)
{
    unsigned char &active = *(unsigned char *)((char *)source + 0x4c);
    if (!active)
    {
        active = 1;
        FUN_005a7110(source);
    }
}

// FUNCTION: GAME 0x005a8810
void RHSound::FUN_005a8810(void *value)
{
    RHMobileSoundNode *head = (RHMobileSoundNode *)m_24c;
    RHMobileSoundNode *node = head->next;
    for (;; node = node->next)
    {
        if (node == head)
            return;
        if (node->m_8 == 1 && node->m_1c == value)
            break;
    }
    FUN_005a8420(node->m_20);
    node->previous->next = node->next;
    node->next->previous = node->previous;
    ((RHSoundPendingData *)&node->m_8)->FUN_0052c5a0();
    ::operator delete(node);
    --m_250;
}

// FUNCTION: GAME 0x005b4fa0
int RHMobileUnk005b4fa0::FUN_005b4fa0(RHSoundSource *value)
{
    m_18 = false;
    m_20 = value;
    int count = m_8 == 0 ? 0 : m_c - m_8;
    m_14 = m_8;
    int index = 0;
    m_19 = true;
    for (; index < count; ++index, ++m_14)
        if (*m_14 == value)
            break;
    m_1c = index < count ? index : -1;
    return m_1c;
}

// FUNCTION: GAME 0x005fc0e0
bool SBGeoPoint2D::FUN_005fc0e0(const SBGeoPoint2D &other) const
{
    return m_x != other.m_x || m_y != other.m_y;
}

// FUNCTION: GAME 0x005fc1e0
SBGeoPoint2D &SBGeoPoint2D::FUN_005fc1e0(const SBGeoPoint2D &other)
{
    m_x = other.m_x + m_x;
    m_y = other.m_y + m_y;
    return *this;
}

// FUNCTION: GAME 0x00607da0
RHMobileUnk00607da0 &RHMobileUnk00607da0::FUN_00607da0(const RHMobileUnk00607da0 &other)
{
    if (this != &other)
    {
        ((SBGeoPoint2D *)this)->~SBGeoPoint2D();
        FUN_00607990(other);
    }
    return *this;
}

// Parked: explicit construction removes EH but not argument-slot copies.
// STUB: GAME 0x00607e90
void SBGeoBoundingBox2D::FUN_00607e90(const SBGeoBoundingBox2D &other)
{
    undefined storage[8];
    SBGeoPoint2D *point = (SBGeoPoint2D *)storage;
    point->SBGeoPoint2D::SBGeoPoint2D(other.m_0.m_x, other.m_0.m_y);
    Unk00607dc0(*point);
    point->~SBGeoPoint2D();
    point->SBGeoPoint2D::SBGeoPoint2D(other.m_8.m_x, other.m_8.m_y);
    Unk00607dc0(*point);
    point->~SBGeoPoint2D();
}

// FUNCTION: GAME 0x006091b0
RHMobileUnk006091b0 &RHMobileUnk006091b0::FUN_006091b0(const SBGeoPoint2D &value)
{
    m_0.FUN_005fc1e0(value);
    m_8.FUN_005fc1e0(value);
    return *this;
}

// LIBRARY: GAME 0x0060a750
// ?_Construct@std@@YAXPADABD@Z

// FUNCTION: GAME 0x0060a820
SBGeoSegment2D::SBGeoSegment2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
{
    ((RHMobileUnk0060a820 *)this)->FUN_006158b0(first, second);
}

#include "RHGameInputTranslator.h"

// FUNCTION: GAME 0x0060a880
bool RHGameInputSegment::FUN_0060a880(const SBGeoPoint2D &point) const
{
    if (!SBGeoBoundingBox2D(*(const SBGeoSegment2D *)this).FUN_00608400(point))
        return false;
    const SBGeoPoint2D &first = *(const SBGeoPoint2D *)m_00;
    return ((const RHUnk005fc3b0 &)((const SBGeoPoint2D *)(m_00 + 8))->Unk005fc110(first)).FUN_005fc680(
        (const RHUnk005fc3b0 &)point.Unk005fc110(first), 1.0f) == 0.0f;
}

// FUNCTION: GAME 0x006100e0
RHMobileUnk006100e0::~RHMobileUnk006100e0()
{
    FUN_00578c50();
    ((SBGeoPoint2D *)m_8)->~SBGeoPoint2D();
}

// FUNCTION: GAME 0x00611360
void RHMobileUnk00611360::FUN_00611360(const SBGeoPoint2D &value)
{
    unsigned short count = Size();
    for (unsigned short i = 0; i < count; ++i)
        m_4[i].FUN_005fc1e0(value);
}

void RHElementMobile::Emit(SBFile &file)
{
    ExecuteMacroCommand();
    InitializeFromMissionStream(file);
    Serialize(file);
    CheckForLineCrossing();
}

void RHElementMobile::TranslateGeometry(const SBGeoVector2D &value)
{
    RHMobileField<RHMobileUnk006091b0>(this, 0xec).FUN_006091b0(value);
    RHMobileField<RHMobileUnk00611360>(this, 0x120).FUN_00611360(value);
    SBGeoBoundingBox2D &bounds = RHMobileField<SBGeoBoundingBox2D>(this, 0x1e0);
    RHMobileField<RHMobileUnk00607da0>(this, 0x1e0).FUN_00607da0(*(RHMobileUnk00607da0 *)&bounds.FUN_006090d0(value));
    unsigned offsets[3] = {0xcc, 0x164, 0x144};
    for (unsigned group = 0; group < 3; ++group)
    {
        unsigned offset = offsets[group];
        void **first = RHMobileField<void **>(this, offset + 4);
        void **last = RHMobileField<void **>(this, offset + 8);
        unsigned short count = first ? last - first : 0;
        for (unsigned short i = 0; i < count; ++i)
        {
            if (group == 0)
                ((RHMobileUnk005a5960 *)first[i])->FUN_005a5960(value);
            else
            {
                RHMobileField<SBGeoPoint2D>(first[i], 4).FUN_005fc1e0(value);
                if (group == 1)
                    RHMobileField<SBGeoPoint2D>(first[i], 0xc).FUN_005fc1e0(value);
            }
        }
    }
    RHMobileField<float>(this, 0x204) += value.m_x;
    RHMobileField<float>(this, 0x208) += value.m_y;
}
