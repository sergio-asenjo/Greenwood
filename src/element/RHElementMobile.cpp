#include "RHElementMobile.h"

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(RHMobilePath, 0x08)
DECOMP_SIZE_ASSERT(RHMobileNode005504d0, 0x1c)
DECOMP_SIZE_ASSERT(RHMobileUnk005504d0, 0x20)
DECOMP_SIZE_ASSERT(RHMobileSoundNode, 0x24)
DECOMP_SIZE_ASSERT(RHSound, 0x254)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHElementMobile, 0x258)
DECOMP_SIZE_ASSERT(RHUnk004af060, 0x258)

// GLOBAL: GAME 0x006c0960
bool g_mobileAssertDoubleBond = false;

// FUNCTION: GAME 0x0042fde0
SBGeoPoint2D RHUnk0042fde0::FUN_0042fde0() const
{
    return m_8.Unk005fc110(m_0);
}

// FUNCTION: GAME 0x0048f170
void *FUN_0048f170(void *value)
{
    return value;
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
        ((RHUnk004af1d0 *)this)->Unk(speed != g_unk0x00677488);
        return true;
    }
    case 130:
    {
        SBGeoPoint2D position;
        SBGeoPoint2D destination;
        m_1a0 = *(float *)m_190;
        if (m_1a0 == g_unk0x00677488)
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
        m_1a4 = (m_19c + m_1a0) * (m_1a0 - m_19c) * g_unk0x006775d8 / distance;
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

// Parked: mission-stream body has not been reconstructed.
// STUB: GAME 0x004ad5f0
void RHElementMobile::InitializeFromMissionStream(SBFile &file)
{
    (void)file;
}

// Parked: x87 conversion ordering and live temporary scheduling differ.
// STUB: GAME 0x004ae380
SBGeoVector2D RHMobilePath::FUN_004ae380() const
{
    SBGeoVector2D result;
    RHMobileElement *last = m_4->m_4[(unsigned short)(Size() - 1)];
    result.m_x = last->m_64;
    result.m_y = last->m_66;
    RHMobileElement *first = m_4->m_4[0];
    result.m_x -= first->m_64;
    result.m_y -= first->m_66;
    return result;
}

// Parked: serialization body has not been reconstructed.
// STUB: GAME 0x004ae470
bool RHElementMobile::Serialize(SBFile &file)
{
    (void)file;
    return false;
}

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

// STUB: GAME 0x004af170
void RHElementMobile::FUN_004af170(void *value)
{
    unsigned short count = Size();
    for (unsigned short i = 0; i < count; ++i)
        ((RHMobilePosition *)((char *)m_b0[i]->m_50 + 4))->FUN_0055fa20(value);
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
            if (((RHUnk005fc3b0 *)&((RHUnk0042fde0 *)&first)->FUN_0042fde0())->FUN_005fc680(movement, 1.0f) == g_unk0x00677488)
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

// FUNCTION: GAME 0x004b06f0
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

// FUNCTION: GAME 0x0051fd90
void RHMobileUnk0051fd90::FUN_0051fd90(float first, float second)
{
    m_24 = first + second;
    m_28 = first;
    m_2c = g_unk0x0067749c / (m_24 - first);
    m_30 = -(m_2c * first);
}

// FUNCTION: GAME 0x00520c50
void RHMobileUnk00520c50::FUN_00520c50(float first, float second)
{
    m_24 = first + second;
    m_30 = first;
    m_28 = g_unk0x0067749c / (m_24 - first);
    m_2c = -(m_28 * first);
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

// Parked: named callee operand and redundant post-search sentinel check.
// STUB: GAME 0x005a8810
void RHSound::FUN_005a8810(void *value)
{
    RHMobileSoundNode *head = m_24c;
    RHMobileSoundNode *node = head->next;
    for (; node != head; node = node->next)
        if (node->m_8 == 1 && node->m_1c == value)
            break;
    if (node != head)
    {
        FUN_005a8420(node->m_20);
        node->previous->next = node->next;
        node->next->previous = node->previous;
        ((RHSoundPendingData *)&node->m_8)->FUN_0052c5a0();
        ::operator delete(node);
        --m_250;
    }
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

// deferred: unannotated pending reccmp #534 (0x005fc1e0).
SBGeoPoint2D &SBGeoPoint2D::FUN_005fc1e0(const SBGeoPoint2D &other)
{
    m_x = other.m_x + m_x;
    m_y = other.m_y + m_y;
    return *this;
}

// deferred: unannotated pending reccmp #534 (0x005fc430).
RHUnk005fc3b0 &RHUnk005fc3b0::FUN_005fc430(const SBGeoPoint2D &other)
{
    if (this != &other)
    {
        SBGeoPoint2D::~SBGeoPoint2D();
        FUN_005fc390(other);
    }
    return *this;
}

// FUNCTION: GAME 0x005fc680
float RHUnk005fc3b0::FUN_005fc680(const RHUnk005fc3b0 &other, float value) const
{
    return (other.m_y * m_x - m_y * other.m_x) / value;
}

// deferred: unannotated pending reccmp #534 (0x00607da0).
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

// FUNCTION: GAME 0x0060a820
RHMobileUnk0060a820 &RHMobileUnk0060a820::FUN_0060a820(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
{
    FUN_006158b0(first, second);
    return *this;
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
