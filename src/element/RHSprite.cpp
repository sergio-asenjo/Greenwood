#include "SBNullstr.h"
#include "RHSprite.h"
#include <stdlib.h>
#include <stddef.h>
#include "RHSpriteRow.h"

DECOMP_SIZE_ASSERT(RHSpriteListNode, 0x0c)
DECOMP_SIZE_ASSERT(RHSpriteListIterator, 0x04)
DECOMP_SIZE_ASSERT(RHSpriteList, 0x18)
DECOMP_SIZE_ASSERT(RHUnk005b5ed0, 0x22c)
DECOMP_SIZE_ASSERT(RHSprite, 0x22c)
DECOMP_SIZE_ASSERT(RHSpriteText<true>, 0x10)
DECOMP_SIZE_ASSERT(RHSpriteText<false>, 0x10)
DECOMP_SIZE_ASSERT(RHUnkSpriteRow, 0x64)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_144) == 0x144)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_164) == 0x164)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_174) == 0x174)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_1a0) == 0x1a0)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_1e0) == 0x1e0)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_204) == 0x204)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_228) == 0x228)
DECOMP_SIZE_ASSERT(RHOrder, 0x3c)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHUnk005df4f0, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x0c)

struct RHSpriteGraphEntry
{
    undefined m_00[8];
};

struct RHSpriteFrameSpan
{
    int m_0;
    unsigned short *m_4;
    unsigned short *m_8;
};

class RHUnk005069a0;
class RHFrameHolder
{
public:
    unsigned short FUN_005046a0(unsigned long);
    unsigned short FUN_005046c0(unsigned long);
    RHUnk005069a0 *FUN_00505170(unsigned long);
    bool FUN_005058a0(unsigned long);
};

// GLOBAL: GAME 0x006c0cd4
RHSpriteGraphEntry *g_unk0x006c0cd4 = 0;
// GLOBAL: GAME 0x006c0cd8
RHSpriteGraphEntry *g_unk0x006c0cd8 = 0;

// STRING: GAME 0x006b8748
#define g_spriteFile "P:\\Robin Hood\\RHsprite.cpp"


// FUNCTION: GAME 0x0049b2c0
int RHSprite::FUN_0049b2c0()
{
    unsigned short result = FUN_005bdcd0(m_184);
    return m_186 < result;
}

// FUNCTION: GAME 0x004d9090
unsigned RHSpriteEngineCalls::FUN_004d9090()
{
    if (!g_unk0x006c0cd4)
        return 0;
    return g_unk0x006c0cd8 - g_unk0x006c0cd4;
}

extern int g_unk0x6c0c6c;

// FUNCTION: GAME 0x0054e510
RHOrder::RHOrder() : m_34(g_unk0x6c0c6c)
{
    ++g_unk0x6c0c6c;
    m_24 = 0x123;
    m_28 = 0;
    m_2a = 1;
    m_2b = 0;
    m_2c = 0;
    m_29 = 0;
    m_2e[0] = 0;
    m_38 = 0;
    m_30 = 0;
    SBGeoPoint2D &point = m_14;
    point.m_x = 0.0f;
    point.m_y = 0.0f;
    RHUnk00613e90 &vector = m_08;
    vector.m_0 = 0.0f;
    vector.m_4 = 0.0f;
    vector.m_8 = 0.0f;
    m_2d = 0;
    m_04 = 0;
}

// FUNCTION: GAME 0x0054e5e0
RHOrder::RHOrder(RHOrder &other)
{
    m_04 = other.m_04;
    m_08 = other.m_08;
    m_14 = other.m_14;
    ((RHUnk005fc3b0 *)&m_1c)->FUN_005fc430(other.m_1c);
    m_24 = other.m_24;
    m_28 = other.m_28;
    m_29 = other.m_29;
    m_2a = other.m_2a;
    m_2b = other.m_2b;
    m_2c = other.m_2c;
    m_2d = other.m_2d;
    m_30 = other.m_30;
    extern int g_unk0x6c0c6c;
    m_34 = g_unk0x6c0c6c;
    ++g_unk0x6c0c6c;
    m_38 = other.m_38;
}

// FUNCTION: GAME 0x00563e90
bool RHSpritePositionCalls::FUN_00563e90()
{
    return RHSpriteField<unsigned short>(this, 0x100) > 50;
}

// FUNCTION: GAME 0x00563ea0
void RHSpritePositionCalls::FUN_00563ea0()
{
    RHSpriteField<SBGeoBoundingBox2D>(this, 0x104).FUN_00607d90();
    undefined4 value = RHSpriteField<undefined4>(this, 0x11c);
    RHSpriteField<unsigned short>(this, 0x100) = 0;
    RHSpriteField<undefined4>(this, 0x118) = value;
}

// Parked: cached-list lookup remains out of line.
// STUB: GAME 0x005859e0
void RHSpriteSequenceCalls::FUN_005859e0(RHOrder *order, unsigned short wanted)
{
    if (order->m_24 == 0x123)
    {
        if (order)
            delete order;
        return;
    }
    RHSpriteOrderList &orders = RHSpriteField<RHSpriteOrderList>(this, 0x18);
    RHSpriteOrderNode *next;
    if (wanted == orders.count)
        next = orders.head;
    else
    {
        orders.Value(wanted);
        next = orders.current.node;
    }
    RHSpriteOrderNode *previous = next->previous;
    RHSpriteOrderNode *node = (RHSpriteOrderNode *)operator new(sizeof(RHSpriteOrderNode));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    RHSpriteOrderNode::CopyData(&node->value, &order);
    ++orders.count;
    orders.dirty = true;
    order->m_38 = this;
}

class RHUnkSpriteBank;
class RHUnk005ef320;
extern RHUnkSpriteBank *g_unk0x006c0b1c;
extern RHUnk005ef320 *g_unk0x6c11d0;

// FUNCTION: GAME 0x005b5890
RHSprite::RHSprite(unsigned long owner) : RHPositionInterface(owner)
{
    m_192 = 0;
    m_193 = 0;
    m_194 = 0;
    m_150 = 0xffff;
    m_1d0 = g_unk0x006c0b1c;
    m_1d4 = g_unk0x6c0a9c;
    m_1d8 = g_unk0x6c11d0;
    m_1dc = 0x11b;
    m_184 = 0;
    m_186 = 0;
    m_188 = 0xffff;
    m_19c = 0;
    m_19a = 0;
    m_18a = 0;
    m_1b4 = 0;
    m_1c0 = false;
    m_1b8 = -1;
    m_1a0.FUN_00609050(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(1.0f, 1.0f));
    m_18c = 0xffff;
    m_18e = 0xffff;
    m_1c4 = 0;
    m_1c8 = 0;
    m_228 = 0;
    m_158 = 0;
    m_154 = 0;
    m_15c = 0;
    m_160 = 0;
    m_195 = true;
}

// SYNTHETIC: GAME 0x005b5a90
// RHSprite::`scalar deleting destructor'

// STUB: GAME 0x005b5bf0
RHSprite::~RHSprite()
{
    if (m_1b4)
        operator delete(m_1b4);
    if (m_195)
    {
        delete (std::vector<RHUnkSpriteRow> *)m_154;
        delete (std::vector<RHUnkSpriteRow> *)m_158;
    }
}

// FUNCTION: GAME 0x005b5e00
void *RHUnk005b5e00::Unk()
{
    if (RHSpriteField<char>(this, 0x194))
        return RHSpriteField<void *>(this, 0x160);
    return RHSpriteField<void *>(this, 0x15c);
}

// FUNCTION: GAME 0x005b5e20
void RHSprite::FUN_005b5e20()
{
    m_144 = m_184;
    m_146 = m_186;
    m_148 = m_188;
    m_14c = m_1dc;
}

// FUNCTION: GAME 0x005b5e60
void RHSprite::FUN_005b5e60()
{
    m_184 = m_144;
    m_186 = m_146;
    m_188 = m_148;
    m_1dc = m_14c;
}

// FUNCTION: GAME 0x005b5ea0
void RHSprite::FUN_005b5ea0(SBFile &file, int kind)
{
    Unk005bc920(file, kind);
    LoadPositionInfoFromFile(file, kind);
}

// Parked: frame is 8 bytes larger (extra spilled locals); jump offsets shift throughout.
// STUB: GAME 0x005b5ed0
bool RHUnk005b5ed0::FUN_005b5ed0(SBFile &file)
{
#define sprite (*this)
    char previous = sprite.m_194;
    int unused;
    RHSerializeName(file,
        // STRING: GAME 0x006b8764
        "RHSprite");
#define ACCESS(member, size, line) \
    if (file.Access(&(member), size) < 0) { \
        SBString *error = file.GetError(); \
        SBAssert(0, g_spriteFile, line, "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }
    ACCESS(sprite.m_184, 2, 0xf2);
    ACCESS(sprite.m_186, 2, 0xf3);
    ACCESS(sprite.m_188, 2, 0xf4);
    ACCESS(sprite.m_19c, 2, 0xf5);
    ACCESS(sprite.m_19a, 2, 0xf6);
    ACCESS(sprite.m_1dc, 4, 0xf7);
    ACCESS(sprite.m_192, 1, 0xf8);
    ACCESS(sprite.m_194, 1, 0xf9);
    ACCESS(sprite.m_193, 1, 0xfa);
    ACCESS(sprite.m_1c4, 4, 0xfd);
    ACCESS(unused, 4, 0xfe);
    ACCESS(sprite.m_1cc, 1, 0xff);
    g_pEngine->SerializeElementPointer(file, sprite.m_1c8);
    ACCESS(sprite.m_18c, 2, 0x102);
    ACCESS(sprite.m_18e, 2, 0x103);
    ACCESS(sprite.m_190, 2, 0x104);
    ACCESS(sprite.m_18a, 2, 0x105);
    ACCESS(sprite.m_150, 4, 0x107);
    sprite.m_1a0.Serialize(file);
    unsigned count;
    int first;
    int second;
    if (file.m_bLoading)
    {
        RHSpriteList &animations = sprite.m_1e0;
        animations.Clear();
        sprite.m_204.Clear();
        ACCESS(count, 4, 0x112);
        for (unsigned i = 0; i < count; ++i)
        {
            ACCESS(first, 4, 0x117);
            ACCESS(second, 4, 0x118);
            animations.Append(first);
            sprite.m_204.Append(second);
        }
        if (sprite.m_194 != previous)
        {
            sprite.m_194 = previous;
            sprite.FUN_005bd8b0();
            return ((RHPositionInterface *)((char *)this + 4))->Serialize(file);
        }
    }
    else
    {
        count = sprite.m_1e0.count;
        ACCESS(count, 4, 0x12a);
        for (int i = 0; (unsigned)i < count; ++i)
        {
            sprite.m_1e0.GoTo(i);
            first = sprite.m_1e0.current.node->value;
            sprite.m_204.GoTo(i);
            second = sprite.m_204.current.node->value;
            ACCESS(first, 4, 0x131);
            ACCESS(second, 4, 0x132);
        }
    }
#undef ACCESS
    return ((RHPositionInterface *)((char *)this + 4))->Serialize(file);
#undef sprite
}

// Parked: local/EH layout and control-flow reconstruction do not match.
// STUB: GAME 0x005b6790
void RHSprite::LoadPositionInfoFromFile(SBFile &file, int kind)
{
    SBGeoPoint2D point;
    SBGeoBoundingBox2D box;
    short x;
    short y;
    unsigned short value;
    void *area;
    unsigned char byte;
    switch (kind)
    {
    case 2:
        {
            file.Access(&x, 2);
            file.Access(&y, 2);
            file.Access(&value, 2);
            RHUnk005df4f0 source(x + RHSpriteField<SBGeoPoint2D>(this, 0x84).m_x,
                y + RHSpriteField<SBGeoPoint2D>(this, 0x84).m_y + value, (float)value);
            RHPositionInterface *position = (RHPositionInterface *)((char *)this + 4);
            RHSpriteField<int>(position, 4) = 1;
            RHSpriteField<RHUnk005df4f0>(this, 0x10) = source;
            ((RHBonusInfoBase *)position)->FUN_0055f290();
            ((RHBonusInfo *)this)->FUN_005bd560(0, true);
        }
        break;
    case 0:
    case 1:
        {
            RHPositionInterface *position = (RHPositionInterface *)((char *)this + 4);
            unsigned char index;
            unsigned short x0, y0, x1, y1;
            file.Access(&index, 1);
            RHSpriteField<unsigned short>(this, 0x94) = index;
            file.Access(&x0, 2);
            file.Access(&y0, 2);
            file.Access(&x1, 2);
            file.Access(&y1, 2);
            if (((RHSpriteEngineCalls *)g_pEngine)->FUN_004d9090() <= index)
                SBAssert(1, g_spriteFile, 0x17b,
                    // STRING: GAME 0x006b8924
                    "VERBOTEN : Pathfinder graph does not contain the index %d corresponding to box ((%d,%d),(%d,%d)) !",
                    index, x0, y0, x1, y1);
            float centerX = (x0 + x1) * 0.5f;
            float centerY = (y0 + y1) * 0.5f;
            box.m_10 = true;
            box.m_00 = SBGeoPoint2D(x0 - centerX, y0 - centerY);
            box.m_10 = true;
            box.m_08 = SBGeoPoint2D(x1 - centerX, y1 - centerY);
            ((RHMobileUnk00607da0 *)&RHSpriteField<SBGeoBoundingBox2D>(this, 0x98))->FUN_00607da0((const RHMobileUnk00607da0 &)box);
            file.Access(&index, 1);
            RHSpriteField<unsigned short>(this, 0x96) = index;
            file.Access(&x0, 2);
            file.Access(&y0, 2);
            file.Access(&x1, 2);
            file.Access(&y1, 2);
            if (((RHSpriteEngineCalls *)g_pEngine)->FUN_004d9090() <= index)
                SBAssert(1, g_spriteFile, 0x18f,
                    // STRING: GAME 0x006b88b4
                    "VERBOTEN : Pathfinder graph does not contain the (alternate) index %d corresponding to box ((%d,%d),(%d,%d)) !",
                    index, x0, y0, x1, y1);
            centerX = (x0 + x1) * 0.5f;
            centerY = (y0 + y1) * 0.5f;
            ((RHUnk005fc3b0 *)&RHSpriteField<SBGeoPoint2D>(this, 0x84))->FUN_005fc430(SBGeoVector2D(centerX, centerY));
            box.m_10 = true;
            box.m_00 = SBGeoPoint2D(x0 - centerX, y0 - centerY);
            box.m_10 = true;
            box.m_08 = SBGeoPoint2D(x1 - centerX, y1 - centerY);
            ((RHMobileUnk00607da0 *)&RHSpriteField<SBGeoBoundingBox2D>(this, 0xac))->FUN_00607da0((const RHMobileUnk00607da0 &)box);
            file.Access(&x, 2);
            file.Access(&y, 2);
            {
                SBGeoPoint2D source((float)x, (float)y);
                RHSpriteField<float>(this, 0x1c) = (float)FUN_006433ab(source.m_x);
                RHSpriteField<float>(this, 0x20) = (float)FUN_006433ab(source.m_y);
                RHSpriteField<int>(position, 4) = 4;
            }
            ((RHSpritePositionCalls *)position)->FUN_0055f550();
            file.Access(&value, 2);
            RHSpriteField<unsigned short>(this, 0xde) = value;
            ((RHUnkPathGeometry *)RHSpriteField<void *>(this, 0x1d4))->Unk004fbec0(file, area);
            RHSpriteField<void *>(this, 0xe0) = area;
            unsigned flags = RHSpriteField<unsigned>(area, 0x30);
            if (!((flags >> 1) & 1) || !(flags & 1))
                SBAssert(1, g_spriteFile, 0x1ad,
                    // STRING: GAME 0x006b887c
                    "VERBOTEN : Character not lying on motion area (%f,%f) !",
                    RHSpriteField<SBGeoPoint2D>(this, 0x24).m_x, RHSpriteField<SBGeoPoint2D>(this, 0x24).m_y);
            file.Access(&value, 2);
            if (value)
            {
                void *view = RHSpriteField<void **>(RHSpriteField<void *>(this, 0x1d4), 0x4044)[value];
                if (!(RHSpriteField<unsigned>(view, 0) & 4))
                    SBAssert(1, g_spriteFile, 0x1b9,
                        // STRING: GAME 0x006b8844
                        "VERBOTEN : Character not lying on view area (%f,%f) !",
                        RHSpriteField<SBGeoPoint2D>(this, 0x24).m_x, RHSpriteField<SBGeoPoint2D>(this, 0x24).m_y);
                ((RHBonusInfoBase *)position)->FUN_0055fa20((RHBonusProjection *)view);
                if (!RHSpriteField<SBGeoBoundingBox2D>(view, 0x38).FUN_00608400(
                    RHSpriteField<SBGeoPoint2D>(this, 0x1c).Unk005fc190(RHSpriteField<SBGeoPoint2D>(this, 0x84))))
                    SBAssert(1, g_spriteFile, 0x1c1,
                        // STRING: GAME 0x006b880c
                        "VERBOTEN : Character lying on wrong view area (%f,%f) !",
                        RHSpriteField<SBGeoPoint2D>(this, 0x24).m_x, RHSpriteField<SBGeoPoint2D>(this, 0x24).m_y);
            }
            else
                ((RHBonusInfoBase *)position)->FUN_0055fa20(0);
            file.Access(&byte, 1);
            RHSpriteField<int>(this, 0xfc) = byte;
            ((RHBonusInfoBase *)position)->FUN_0055f290();
            ((RHBonusInfo *)this)->FUN_005bd560(0, true);
            RHSpriteField<RHUnk005df4f0>(this, 0x2c) = RHSpriteField<RHUnk005df4f0>(this, 0x10);
            RHSpriteField<SBGeoPoint2D>(this, 0x40) = RHSpriteField<SBGeoPoint2D>(this, 0x24);
            file.Access(&byte, 1);
            RHSpriteField<unsigned short>(this, 0xd8) = byte & 15;
            RHSpriteField<unsigned short>(this, 0xda) = byte & 15;
            m_184 = byte;
            m_186 = 0;
        }
        break;
    case 3:
        {
            RHPositionInterface *position = (RHPositionInterface *)((char *)this + 4);
            file.Access(&byte, 1);
            RHSpriteField<bool>(this, 0x196) = byte == 0;
            file.Access(&RHSpriteField<unsigned short>(this, 0x198), 2);
            {
                SBGeoPoint2D source(0.0f, 0.0f);
                RHSpriteField<float>(this, 0x1c) = (float)FUN_006433ab(source.m_x);
                RHSpriteField<float>(this, 0x20) = (float)FUN_006433ab(source.m_y);
                RHSpriteField<int>(position, 4) = 4;
            }
            if (byte == 1)
            {
                file.Access(&x, 2);
                file.Access(&y, 2);
                {
                    SBGeoPoint2D source((float)x, (float)y);
                    RHSpriteField<float>(this, 0x1c) = (float)FUN_006433ab(source.m_x);
                    RHSpriteField<float>(this, 0x20) = (float)FUN_006433ab(source.m_y);
                    RHSpriteField<int>(position, 4) = 4;
                }
                file.Access(&value, 2);
                RHSpriteField<unsigned short>(this, 0xde) = value;
                ((RHUnkPathGeometry *)RHSpriteField<void *>(this, 0x1d4))->Unk004fbec0(file, area);
                RHSpriteField<void *>(this, 0xe0) = area;
                file.Access(&value, 2);
                if (value)
                {
                    void *view = RHSpriteField<void **>(RHSpriteField<void *>(this, 0x1d4), 0x4044)[value];
                    if (!(RHSpriteField<unsigned>(view, 0) & 4))
                        SBAssert(1, g_spriteFile, 0x205,
                            // STRING: GAME 0x006b87d8
                            "VERBOTEN : Object not lying on view area (%f,%f) !",
                            RHSpriteField<SBGeoPoint2D>(this, 0x24).m_x, RHSpriteField<SBGeoPoint2D>(this, 0x24).m_y);
                    ((RHBonusInfoBase *)position)->FUN_0055fa20((RHBonusProjection *)view);
                    ((RHBonusInfoBase *)position)->FUN_0055f290();
                    if (!RHSpriteField<SBGeoBoundingBox2D>(view, 0x38).FUN_00608400(
                        RHSpriteField<SBGeoPoint2D>(this, 0x1c).Unk005fc190(RHSpriteField<SBGeoPoint2D>(this, 0x84))))
                        SBAssert(1, g_spriteFile, 0x210,
                            // STRING: GAME 0x006b87a0
                            "VERBOTEN : Object lying on wrong view area (%f,%f) !",
                            RHSpriteField<SBGeoPoint2D>(this, 0x24).m_x, RHSpriteField<SBGeoPoint2D>(this, 0x24).m_y);
                }
                file.Access(&value, 2);
                RHSpriteField<unsigned short>(this, 0xd8) = value & 15;
                RHSpriteField<unsigned short>(this, 0xda) = value & 15;
                file.Access(&value, 2);
                if (((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->Frame(value) != 0xffff)
                    ((RHUnkTargetSprite *)this)->FUN_005b76e0(value, 0);
                else
                    SBAssert(1, g_spriteFile, 0x220,
                        // STRING: GAME 0x006b8770
                        "VERBOTEN : Initial animation does not exist !");
            }
            ((RHMobileUnk00607da0 *)&RHSpriteField<SBGeoBoundingBox2D>(this, 0x98))->FUN_00607da0((const RHMobileUnk00607da0 &)SBGeoBoundingBox2D(SBGeoVector2D(-2.0f, -2.0f), SBGeoVector2D(2.0f, 2.0f)));
            ((RHBonusInfoBase *)position)->FUN_0055f290();
            ((RHBonusInfo *)this)->FUN_005bd560(0, true);
        }
        break;
    }
}

// Parked: VC6 compresses the switch into a byte-index table.
// STUB: GAME 0x005b7300
bool RHSprite::FUN_005b7300(int animation, int progression)
{
    if (animation == m_1dc)
        return false;
    m_1dc = animation;
    switch (progression)
    {
    case 0: case 1: case 2: case 3: case 4: case 5:
    case 7: case 8: case 9: case 11:
        m_188 = 0xffff;
        m_186 = 0;
        break;
    case 6:
        m_188 = 0xffff;
        m_186 = FUN_005bdcd0(RHSpriteField<unsigned short *>(((RHUnk005b5e00 *)this)->Unk(), 4)[animation]);
        break;
    case 12: case 13:
        m_186 = FUN_005bdcf0(m_184) - 1;
        m_188 = 0xffff;
        break;
    case 10:
        m_188 = 0;
        m_186 = 0;
        break;
    }
    RHSpriteField<int>(this, 0x138) = 0;
    RHSpriteField<int>(this, 0x13c) = 0;
    RHSpriteField<int>(this, 0x140) = 0;
    return true;
}

// FUNCTION: GAME 0x005b76e0
bool RHUnkTargetSprite::FUN_005b76e0(unsigned animation, unsigned short direction)
{
    unsigned short frame = RHSpriteField<unsigned short *>(((RHUnk005b5e00 *)this)->Unk(), 4)[animation] + direction;
    RHSpriteField<int>(this, 0x1dc) = animation;
    RHSpriteField<unsigned short>(this, 0x184) = frame;
    RHSpriteField<unsigned short>(this, 0x186) = 0;
    RHSpriteField<unsigned short>(this, 0x188) = 0;
    return true;
}

// SYNTHETIC: GAME 0x005b7600
// ??1RHUnkSpriteRow@@QAE@XZ

// TEMPLATE: GAME 0x005be610
// ??4RHUnkSpriteRow@@QAEAAU0@ABU0@@Z

// FUNCTION: GAME 0x005b7720
void RHSprite::FUN_005b7720(int animation)
{
    unsigned short frame = RHSpriteField<unsigned short *>(((RHUnk005b5e00 *)this)->Unk(), 4)[animation];
    m_18c = FUN_005bdcd0(frame);
    m_18e = 0;
    if (FUN_005bdcf0(frame) == 1 && FUN_005bdbf0(frame, 0) <= 1)
    {
        m_18c = 0x2f9;
        m_18e = 0x7c0;
        return;
    }
    if (*(volatile unsigned short *)&m_18c == 0)
    {
        if (FUN_005bdbf0(frame, 0) == 0)
            m_18c = 1;
        else
            m_18e = 1;
        return;
    }
    unsigned short previous = m_18c;
    if (previous >= FUN_005bdcf0(frame) - 1)
    {
        if (previous > 1)
        {
            m_18c = FUN_005bdcf0(frame) - 2;
            m_18e = FUN_005bdbf0(frame, m_18c);
        }
        else
            m_18c = 0xffff;
    }
}

// Parked: switch sharing and progression registers differ.
// STUB: GAME 0x005b7820
bool RHSprite::FUN_005b7820(int progression)
{
    if (RHSpriteField<char>(g_pEngine, 0x4d84))
        return false;
    switch (progression)
    {
    case 0: case 6:
        ++m_188;
        if (m_188 > FUN_005bdbf0(m_184, m_186))
        {
            ++m_186;
            m_188 = 0;
        }
        if (m_186 >= FUN_005bdcf0(m_184))
            m_186 = 0;
        if (m_186 == FUN_005bdcf0(m_184) - 1)
            return m_188 == FUN_005bdbf0(m_184, m_186) || FUN_005bdbf0(m_184, m_186) == 0;
        break;
    case 1:
        ++m_188;
        if (m_188 > FUN_005bdbf0(m_184, m_186))
        {
            ++m_186;
            m_188 = 0;
        }
        if (m_186 >= FUN_005bdcf0(m_184))
            m_186 = 0;
        break;
    case 2:
        ++m_186;
        m_188 = 0;
        if (m_186 > FUN_005bdcf0(m_184))
            m_186 = 0;
        return m_186 == FUN_005bdcf0(m_184);
    case 3:
        ++m_188;
        if (m_188 > FUN_005bdbf0(m_184, m_186))
        {
            m_186 += 2;
            m_188 = 0;
        }
        if (m_186 == FUN_005bdcf0(m_184))
            m_186 = 0;
        if (m_186 == FUN_005bdcf0(m_184) - 2)
            return m_188 == FUN_005bdbf0(m_184, m_186);
        break;
    case 4: case 5:
        if (m_188 + m_186 <= 0 && rand() >= (progression == 4 ? 0x83 : 0x147))
            break;
        ++m_188;
        if (m_188 > FUN_005bdbf0(m_184, m_186))
        {
            ++m_186;
            m_188 = 0;
        }
        if (m_186 >= FUN_005bdcf0(m_184))
            m_186 = 0;
        break;
    case 7:
        if (m_186 == FUN_005bdcd0(m_184))
        {
            ++m_188;
            if (m_188 <= 8)
            {
                short direction = m_d4 - 2;
                if (direction < 0)
                    direction += 16;
                m_d4 = direction & 15;
                RHSpriteField<unsigned short>(this, 0xda) = m_d4;
            }
            else
            {
                m_188 = 0;
                ++m_186;
            }
        }
        else
        {
            ++m_188;
            if (m_188 > FUN_005bdbf0(m_184, m_186))
            {
                ++m_186;
                m_188 = 0;
            }
            if (m_186 >= FUN_005bdcf0(m_184))
                m_186 = 0;
            if (m_186 == FUN_005bdcf0(m_184) - 1)
                return m_188 == FUN_005bdbf0(m_184, m_186);
        }
        break;
    case 8: case 9: case 14:
        if (m_186 < FUN_005bdcf0(m_184) - (progression == 8 ? 1 : 2))
        {
            ++m_188;
            if (m_188 > FUN_005bdbf0(m_184, m_186))
            {
                m_186 += progression == 14 ? 2 : 1;
                m_188 = 0;
            }
        }
        break;
    case 11:
        m_186 = 0;
        break;
    case 12:
        m_186 = FUN_005bdcf0(m_184) - 1;
        break;
    case 13:
        ++m_188;
        if (m_188 > FUN_005bdbf0(m_184, m_186))
        {
            --m_186;
            m_188 = 0;
        }
        if ((short)m_186 < 0)
            m_186 = FUN_005bdcf0(m_184) - 1;
        if (m_186 == 0)
            return m_188 == FUN_005bdbf0(m_184, 0) || FUN_005bdbf0(m_184, m_186) == 0;
        break;
    }
    return false;
}

#include "RHEngineWidenedCalls.h"

// FUNCTION: GAME 0x005b7f60
int RHEngineWidenedCalls::FUN_005b7f60(unsigned long progression)
{
    RHSprite *sprite = (RHSprite *)this;
    if (RHSpriteField<char>(g_pEngine, 0x4d84))
        return 2;
    int result = 2;
    bool finished = sprite->FUN_005b7820(progression);
    if (sprite->m_188 == 0 && sprite->m_186 == sprite->FUN_005bdcd0(sprite->m_184))
        result = 0;
    if (finished == true)
        result = 3;
    return result;
}

// FUNCTION: GAME 0x005b7e40
bool RHSprite::FUN_005b7e40(float modulation, int progression)
{
    if (!RHSpriteField<char>(g_pEngine, 0x4d84) && (progression == 0 || progression == 6)) {
        ++m_188;
        if (m_188 > (unsigned short)(FUN_005bdbf0(m_184, m_186) * modulation)) {
            ++m_186;
            m_188 = 0;
        }
        if (m_186 >= FUN_005bdcf0(m_184))
            m_186 = 0;
        unsigned short frame = m_186;
        if (frame == FUN_005bdcf0(m_184) - 1 &&
            (m_188 == (unsigned short)(FUN_005bdbf0(m_184, frame) * modulation) || FUN_005bdbf0(m_184, m_186) == 0))
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x005b7fd0
int RHSprite::FUN_005b7fd0(float modulation, int progression)
{
    if (RHSpriteField<char>(g_pEngine, 0x4d84))
        return 2;
    int result = 2;
    bool finished = FUN_005b7e40(modulation, progression);
    if (m_188 == 0 && m_186 == FUN_005bdcd0(m_184))
        result = 0;
    if (finished == true)
    {
        ((RHEngineWidenedCalls *)this)->FUN_005bd450();
        result = 3;
    }
    return result;
}

// FUNCTION: GAME 0x005b8050
int RHSprite::PerformAction(RHOrder *order, int animation, int progression, bool reset)
{
    if (*((char *)g_pEngine + 0x4d84))
        return 2;
    int size = *(volatile int *)&m_1e0.count;
    int result = 2;
    if (size > 0)
    {
        m_200 = animation;
        RHSpriteListNode *sentinel = m_1e0.head;
        int searchSize = m_1e0.count;
        m_1f8 = true;
        m_1e0.Find(m_200, m_1fc, sentinel, searchSize);
        int selected = *(volatile int *)&m_1fc;
        if ((unsigned short)selected != 0xffff)
            animation = m_204.Value((unsigned short)selected);
    }
    if (((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->Frame(animation) == 0xffff)
    {
        SBAssert(1, g_spriteFile, 0x479,
            // STRING: GAME 0x006b8988
            "Trying to play non-existing animation %i of sprite %s",
            (unsigned short)animation, RHSpriteField<char *>(this, 0x168) ? RHSpriteField<char *>(this, 0x168) : "");
        return 4;
    }
    unsigned short *entries = ((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->m_04;
    m_184 = entries[animation] + m_d4;
    bool finished;
    if (order && m_150 != *(int *)((char *)order + 0x34))
    {
        m_150 = *(int *)((char *)order + 0x34);
        result = 1;
        FUN_005b7720(animation);
        if (reset)
            ((RHUnk005bd5b0 *)this)->Unk(false);
        else
            FUN_005b7300(animation, progression);
        finished = false;
    }
    else
    {
        FUN_005b7300(animation, progression);
        finished = FUN_005b7820(progression);
    }
    if (m_186 == m_18c && m_188 == m_18e)
        result = 0;
    if (finished == true)
    {
        ((RHEngineWidenedCalls *)this)->FUN_005bd450();
        result = 3;
    }
    return result;
}

// FUNCTION: GAME 0x005b8420
unsigned short RHSprite::FUN_005b8420()
{
    if (m_186 >= m_18c)
    {
        if (m_186 > m_18c || m_188 > m_18e)
            return 0xffff;
        return m_18e - m_188;
    }
    unsigned short total = FUN_005bdbf0(m_184, m_186) - m_188;
    for (unsigned short frame = m_186 + 1; frame < m_18c; ++frame)
        total += FUN_005bdbf0(m_184, frame);
    total += m_18e;
    return total;
}

// FUNCTION: GAME 0x005b84b0
unsigned short RHSprite::FUN_005b84b0(int animation)
{
    unsigned short row = ((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->m_04[animation];
    unsigned short action = FUN_005bdcd0(row);
    unsigned short count = FUN_005bdcf0(row);
    unsigned short total = 0;
    for (unsigned short frame = 0; frame <= action; ++frame)
    {
        if (frame >= count)
            break;
        total += FUN_005bdbf0(row, frame);
    }
    return total;
}

// Parked: local coloring, register allocation and control flow do not match.
// STUB: GAME 0x005b86b0
int RHSprite::PerformMotion(RHOrder *order, RHOrder *following, int animation, int method, float speed, int progression, bool reset)
{
#define S(type, offset) RHSpriteField<type>(this, offset)
#define O(type, offset) RHSpriteField<type>(order, offset)
    bool moved = false;
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    if (*((char *)g_pEngine + 0x4d84))
        return 2;
    if (m_1e0.count > 0)
    {
        RHSpriteListNode *sentinel = m_1e0.head;
        int count = m_1e0.count;
        m_200 = animation;
        m_1f8 = true;
        m_1e0.current = RHSpriteListIterator(sentinel->next);
        int i;
        for (i = 0; i < count; ++i, m_1e0.current++)
            if (*m_1e0.current == m_200)
                break;
        if (i < count)
        {
            m_1fc = i;
            m_1e0.dirty = false;
            m_1e0.index = i;
        }
        else
        {
            m_1e0.dirty = true;
            m_1fc = -1;
        }
        int selected = *(volatile int *)&m_1fc;
        if ((unsigned short)selected != 0xffff)
            animation = m_204.Value((unsigned short)selected);
    }
    if (((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->Frame(animation) == 0xffff)
    {
        SBAssert(1, g_spriteFile, 0x594,
            // STRING: GAME 0x006b89f4
            "Trying to play non-existing animation %u of sprite %s",
            (unsigned short)animation, RHSpriteField<char *>(this, 0x168) ? RHSpriteField<char *>(this, 0x168) : "");
        return 4;
    }
    RHPositionInterface *position = (RHPositionInterface *)((char *)this + 4);
    RHSpritePositionCalls *calls = (RHSpritePositionCalls *)position;
    int result;
    if (m_150 != O(int, 0x34))
    {
        FUN_005b7720(animation);
        if (reset)
            ((RHUnk005bd5b0 *)this)->Unk(false);
        if (method != 5 && O(SBGeoPoint2D, 0x14) == S(SBGeoPoint2D, 0x24))
        {
            m_184 = ((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->Frame(animation) + m_d4;
            FUN_005b7300(animation, progression);
            ((RHEngineWidenedCalls *)this)->FUN_005bd450();
            return 3;
        }
        m_150 = O(int, 0x34);
        result = 1;
        S(SBGeoPoint2D, 0x48) = O(SBGeoPoint2D, 0x14);
        S(int, 0xc) = 0;
        S(bool, 0x78) = O(bool, 0x29);
        void *sequence = O(void *, 0x38);
        S(int, 0x7c) = O(int, 4);
        S(bool, 0x80) = RHSpriteField<unsigned char>(sequence, 4) == 4
            ? ((RHSpriteField<unsigned>(sequence, 0x88) >> 16) & 1) != 0 : false;
        ((RHMobilePosition *)position)->FUN_0055fc20(O(bool, 0x2a));
        S(int, 0x124) = O(int, 0x30);
        calls->FUN_00563ea0();
        if (following && RHSpriteField<int>(following, 0x24) == O(int, 0x24))
        {
            S(SBGeoPoint2D, 0x50) = RHSpriteField<SBGeoPoint2D>(following, 0x14);
            S(bool, 0x100) = true;
        }
        else
            S(bool, 0x100) = false;
    }
    else
        result = 2;
    m_184 = m_d4 + ((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->Frame(animation);
    FUN_005b7300(animation, progression);
    bool finished = FUN_005b7820(progression);
    float distance = m_188 == 0 ? (float)FUN_005bdc20(m_184, m_186) : 0.0f;
    if (method == 3)
    {
        distance *= 2;
        finished |= FUN_005b7820(progression);
        if (m_188 == 0)
            distance = (distance + FUN_005bdc20(m_184, m_186)) * 2;
    }
    distance *= speed;
    if (distance != 0.0f)
    {
        moved = true;
        if (m_d4 != S(unsigned short, 0xda))
        {
            if (method == 6)
            {
                distance *= 2;
                FUN_005b7820(progression);
            }
            else
                distance *= 0.6f;
            if (distance < 0.7f)
                distance = 0.7f;
        }
        void *actor = RHSpriteField<void *>(O(void *, 0x38), 0x48);
        if (S(bool, 0x101) && RHSpriteField<bool>(actor, 0x12) && method != 7 && method != 8)
        {
            unsigned short index;
            calls->FUN_00561040(actor, distance, index, O(bool, 0x29));
            if (calls->FUN_00563e90())
            {
                ((RHBonusInfoBase *)position)->FUN_0055f290();
                SBAssert(0, g_spriteFile, 0x695,
                    // STRING: GAME 0x006b89c0
                    "CARAMBA ! Anticollision error : Blocked (%f,%f) !",
                    S(SBGeoPoint2D, 0x24).m_x, S(SBGeoPoint2D, 0x24).m_y);
                return 4;
            }
        }
        else
        {
            S(SBGeoPoint2D, 0x24).FUN_005fc1e0(distance * S(SBGeoVector2D, 0x70));
            ((RHMobileUnk00607da0 *)&S(SBGeoBoundingBox2D, 0xc4))->FUN_00607da0((const RHMobileUnk00607da0 &)((SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)position)->Unk0055fa10(S(int, 0x8c)))->FUN_006090d0(SBGeoVector2D(S(SBGeoPoint2D, 0x24))));
            S(int, 8) = 2;
        }
        ((RHBonusInfoBase *)position)->FUN_0055f290();
        ((RHBonusInfo *)this)->FUN_005bd560(0, true);
        calls->FUN_00560780(distance, FUN_005bdbf0(m_184, m_186) + 1);
        if (S(int, 0xfc) == 5 && distance > 2.0f)
        {
            if (m_228 >= 2)
            {
                ((RHScriptBatchCalls *)g_unk0x6c10e8)->Unk005c2ec0(&S(RHUnk005df4f0, 0x10), S(unsigned short, 0xde), 7, 0, 0, 0, 0, -1);
                m_228 = 0;
            }
            else
                ++m_228;
        }
    }
    if (m_186 == m_18c && m_188 == m_18e && result != 1)
        result = 0;
    if (method == 5)
    {
        bool ready = calls->FUN_00560460();
        if (ready && distance != 0.0f
            && (S(SBGeoPoint2D, 0x70).m_x != 0.0f || S(SBGeoPoint2D, 0x70).m_y != 0.0f))
        {
            S(int, 0xc) = 1;
            ((RHUnk005fc3b0 *)&S(SBGeoPoint2D, 0x70))->FUN_005fc430(SBGeoVector2D(0.0f, 0.0f));
            S(int, 0xc) = 2;
            S(RHUnk005df4f0, 0x64) = RHUnk005df4f0(0.0f, 0.0f, 0.0f);
            S(int, 0xc) = 7;
            if (!S(bool, 0x102) && S(float, 0x7c) != 0.0f)
            {
                S(SBGeoPoint2D, 0x24) = S(SBGeoPoint2D, 0x48);
                ((RHMobileUnk00607da0 *)&S(SBGeoBoundingBox2D, 0xc4))->FUN_00607da0((const RHMobileUnk00607da0 &)((SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)position)->Unk0055fa10(S(int, 0x8c)))->FUN_006090d0(SBGeoVector2D(S(SBGeoPoint2D, 0x48))));
                S(int, 8) = 2;
                ((RHBonusInfoBase *)position)->FUN_0055f290();
                ((RHBonusInfo *)this)->FUN_005bd560(0, true);
            }
            if (following && RHSpriteField<int>(following, 0x24) == O(int, 0x24))
                return 3;
        }
        if (finished)
        {
            if (ready)
                return 3;
            void *sequence = O(void *, 0x38);
            RHSpriteOrderList &orders = RHSpriteField<RHSpriteOrderList>(sequence, 0x18);
            unsigned count = orders.count;
            unsigned selected = 1;
            int replacement = 0x11b;
            for (; selected < count; ++selected)
            {
                RHOrder *candidate = orders.Value((unsigned short)selected);
                if (RHSpriteField<int>(candidate, 0x24) != O(int, 0x24)
                    && (RHSpriteField<SBGeoPoint2D>(candidate, 0x14).m_x != 0.0f
                        || RHSpriteField<SBGeoPoint2D>(candidate, 0x14).m_y != 0.0f))
                {
                    replacement = RHSpriteField<int>(candidate, 0x24);
                    break;
                }
                if (selected == 1
                    && (RHSpriteField<RHUnk005df4f0>(candidate, 8).m_0 != 0.0f
                        || RHSpriteField<RHUnk005df4f0>(candidate, 8).m_4 != 0.0f
                        || RHSpriteField<RHUnk005df4f0>(candidate, 8).m_8 != 0.0f))
                    return 3;
            }
            if (selected >= count || replacement == 0x11b)
            {
                if (count > 1)
                {
                    --count;
                    while (count != 0)
                    {
                        orders.RemoveFirst();
                        --count;
                    }
                }
                return 3;
            }
            for (unsigned i = 1; i < count; ++i)
            {
                RHOrder *candidate = orders.Value((unsigned short)i);
                if (RHSpriteField<int>(candidate, 0x24) == O(int, 0x24))
                {
                    if (i == selected)
                    {
                        ((RHSpriteSequenceCalls *)sequence)->FUN_005859e0(new RHOrder(*order), (unsigned short)selected);
                        ++i;
                    }
                    else if (i > selected)
                        RHSpriteField<int>(candidate, 0x24) = replacement;
                }
                else
                {
                    RHOrder *copy = new RHOrder(*order);
                    ((RHSpriteSequenceCalls *)sequence)->FUN_005859e0(copy, (unsigned short)selected);
                    RHSpriteField<int>(copy, 0x24) = replacement;
                    return 3;
                }
            }
            return 3;
        }
    }
    else if (moved && calls->FUN_00560460() == true)
    {
        if (!S(bool, 0x102) && S(float, 0x7c) != 0.0f)
        {
            S(SBGeoPoint2D, 0x24) = S(SBGeoPoint2D, 0x48);
            ((RHMobileUnk00607da0 *)&S(SBGeoBoundingBox2D, 0xc4))->FUN_00607da0((const RHMobileUnk00607da0 &)((SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)position)->Unk0055fa10(S(int, 0x8c)))->FUN_006090d0(SBGeoVector2D(S(SBGeoPoint2D, 0x48))));
            S(int, 8) = 2;
            ((RHBonusInfoBase *)position)->FUN_0055f290();
            ((RHBonusInfo *)this)->FUN_005bd560(0, true);
        }
        return 3;
    }
    else
        ((RHBonusInfoBase *)position)->FUN_0055f290();
    return result;
#undef O
#undef S
}

// Parked: large movement/init routine (5 args, EH frame, path/geometry lists); not reconstructed within budget.
// STUB: GAME 0x005b94d0
void RHSprite::FUN_005b94d0(unsigned short, void *, void *, void *, int)
{
}

#include "RHUnk00608f10.h"

// FUNCTION: GAME 0x005b9b60
unsigned char RHSprite::FUN_005b9b60(const SBGeoBoundingBox2D &view, float scale)
{
    SBGeoVector2D size;
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    float height = (float)FUN_005bdd70();
    size.m_x = (float)FUN_005bdd50();
    size.m_y = height;
    if (!((RHPositionInterface *)((char *)this + 4))->IsSpriteValid())
        ((RHPositionInterface *)((char *)this + 4))->ComputePositionSprite();
    SBGeoPoint2D &position = RHSpriteField<SBGeoPoint2D>(this, 0x1c);
#define FRAMEPOINT() (*(std::vector<RHUnkSpriteRow> *)holder)[m_184].m_positions[m_186]
    m_1a0.FUN_00609050(position.Unk005fc190(FRAMEPOINT()), position.Unk005fc190(FRAMEPOINT()).Unk005fc190(size));
#undef FRAMEPOINT
    return ((RHUnk00608f10 *)&view)->FUN_00608f10(&m_1a0);
}

// FUNCTION: GAME 0x005b9ce0
void RHSprite::FUN_005b9ce0()
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
#define FRAMEPOINT() (*(std::vector<RHUnkSpriteRow> *)holder)[m_184].m_positions[m_186]
    m_1a0.FUN_00609050(RHSpriteField<SBGeoPoint2D>(this, 0x1c).Unk005fc190(FRAMEPOINT()), RHSpriteField<SBGeoPoint2D>(this, 0x1c).Unk005fc190(FRAMEPOINT()).Unk005fc190(SBGeoVector2D((float)FUN_005bdd50(), (float)FUN_005bdd70())));
#undef FRAMEPOINT
}

// Parked: 3-arg visibility/collision test (box contains + engine lookup); geometry/EH wall.
// STUB: GAME 0x005b9e30
bool RHSprite::FUN_005b9e30(void *, void *, bool)
{
    return false;
}

static __forceinline void RHSpriteSetVector(SBGeoVector2D &value, float x, float y)
{
    value.m_x = x;
    value.m_y = y;
}

// FUNCTION: GAME 0x005ba130
bool RHSprite::FUN_005ba130(const SBGeoBoundingBox2D &view, float scale, SBGeoBoundingBox2D &source, SBGeoBoundingBox2D &destination)
{
    SBGeoVector2D size;
    SBGeoVector2D offset;
    SBGeoPoint2D origin;
    SBGeoPoint2D previous;
    SBGeoPoint2D position;
    ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    unsigned row = m_184;
    position = RHSpriteField<SBGeoPoint2D>(this, 0x1c).Unk005fc190(
        (*(std::vector<RHUnkSpriteRow> *)((RHUnk005b5e00 *)this)->FUN_005b5de0())[row].m_positions[m_186]);
    RHSpriteSetVector(size, (float)m_19a, (float)m_19c);
    origin = view.m_00;
    destination.FUN_00609050(position, position.Unk005fc190(size));
    previous = destination.m_00;
    ((RHMobileUnk00607da0 *)&destination)->FUN_00607da0((const RHMobileUnk00607da0 &)view.FUN_006092c0(destination));
    if (!destination.Unk00608f30())
        return false;
    offset = destination.m_00.Unk005fc110(previous);
    if (scale == 0.5f)
    {
        int left = (int)(destination.m_00.m_x - origin.m_x);
        int top = (int)(destination.m_00.m_y - origin.m_y);
        int right = (int)(destination.m_08.m_x - origin.m_x);
        int bottom = (int)(destination.m_08.m_y - origin.m_y);
        int x = (int)floor(offset.m_x);
        int y = (int)floor(offset.m_y);
        if (left & 1)
        {
            ++left;
            ++x;
        }
        if (top & 1)
        {
            ++top;
            ++y;
        }
        if (!(right & 1))
            --right;
        if (!(bottom & 1))
            --bottom;
        destination.FUN_00609050(SBGeoPoint2D((float)(left >> 1), (float)(top >> 1)), SBGeoPoint2D((float)(right >> 1), (float)(bottom >> 1)));
        RHSpriteSetVector(offset, (float)x, (float)y);
        source.FUN_00609050(offset, SBGeoPoint2D((destination.m_08.m_x - destination.m_00.m_x) * 2.0f, (destination.m_08.m_y - destination.m_00.m_y) * 2.0f).Unk005fc190(offset));
    }
    else
    {
        source.FUN_00609050(offset, SBGeoPoint2D(destination.m_08.m_x - destination.m_00.m_x, destination.m_08.m_y - destination.m_00.m_y).Unk005fc190(offset));
        if (scale == 2.0f)
            destination.FUN_00609050(SBGeoPoint2D((destination.m_00.GetX() - origin.m_x) * 2.0f, (destination.m_00.GetY() - origin.m_y) * 2.0f), SBGeoPoint2D((destination.m_08.GetX() - origin.m_x) * 2.0f, (destination.m_08.GetY() - origin.m_y) * 2.0f));
        else
            destination.FUN_00609050(destination.m_00.Unk005fc110(origin), destination.m_08.Unk005fc110(origin));
    }
    return destination.FUN_006090a0() && source.FUN_006090a0();
}

// STUB: GAME 0x005ba6c0
bool RHSprite::FUN_005ba6c0(const SBGeoBoundingBox2D &view, float scale, SBGeoBoundingBox2D &source, SBGeoBoundingBox2D &destination, SBGeoVector2D &shift)
{
    SBGeoVector2D size;
    SBGeoVector2D offset;
    SBGeoPoint2D origin;
    SBGeoPoint2D previous;
    SBGeoPoint2D position;
    unsigned row = m_184;
    SBGeoVector2D *positions = (*(std::vector<RHUnkSpriteRow> *)((RHUnk005b5e00 *)this)->FUN_005b5de0())[row].m_positions.begin();
    position = RHSpriteField<SBGeoPoint2D>(this, 0x1c).FUN_005fc200(shift).Unk005fc190(positions[m_186]);
    RHSpriteSetVector(size, (float)m_19a, (float)m_19c);
    size.FUN_005fc1e0(SBGeoVector2D((const SBGeoVector2D &)shift.Unk005fc190(SBGeoVector2D(3.0f, 0.0f))));
    origin = view.m_00;
    destination.FUN_00609050(position, position.Unk005fc190(size));
    previous = destination.m_00;
    ((RHMobileUnk00607da0 *)&destination)->FUN_00607da0((const RHMobileUnk00607da0 &)view.FUN_006092c0(destination));
    if (!destination.Unk00608f30())
        return false;
    offset = destination.m_00.Unk005fc110(previous);
    if (scale == 0.5f)
    {
        int left = (int)(destination.m_00.m_x - origin.m_x);
        int top = (int)(destination.m_00.m_y - origin.m_y);
        int right = (int)(destination.m_08.m_x - origin.m_x);
        int bottom = (int)(destination.m_08.m_y - origin.m_y);
        int x = (int)floor(offset.m_x);
        int y = (int)floor(offset.m_y);
        if (left & 1)
        {
            ++left;
            ++x;
        }
        if (top & 1)
        {
            ++top;
            ++y;
        }
        if (!(right & 1))
            --right;
        if (!(bottom & 1))
            --bottom;
        destination.FUN_00609050(SBGeoPoint2D((float)(left >> 1), (float)(top >> 1)), SBGeoPoint2D((float)(right >> 1), (float)(bottom >> 1)));
        RHSpriteSetVector(offset, (float)x, (float)y);
        source.FUN_00609050(offset, SBGeoPoint2D((destination.m_08.m_x - destination.m_00.m_x) * 2.0f, (destination.m_08.m_y - destination.m_00.m_y) * 2.0f).Unk005fc190(offset));
    }
    else
    {
        source.FUN_00609050(offset, SBGeoPoint2D(destination.m_08.m_x - destination.m_00.m_x, destination.m_08.m_y - destination.m_00.m_y).Unk005fc190(offset));
        if (scale == 2.0f)
            destination.FUN_00609050(SBGeoPoint2D((destination.m_00.GetX() - origin.m_x) * 2.0f, (destination.m_00.GetY() - origin.m_y) * 2.0f), SBGeoPoint2D((destination.m_08.GetX() - origin.m_x) * 2.0f, (destination.m_08.GetY() - origin.m_y) * 2.0f));
        else
            destination.FUN_00609050(destination.m_00.Unk005fc110(origin), destination.m_08.Unk005fc110(origin));
    }
    return source.FUN_006090a0() && destination.FUN_006090a0();
}

template<class T>
static __forceinline void RHSpriteResize(std::vector<T> &values, unsigned count, const T &value)
{
    unsigned (std::vector<T>::*size)() const = &std::vector<T>::size;
    void (std::vector<T>::*insert)(T *, unsigned, const T &) = &std::vector<T>::insert;
    T *(std::vector<T>::*erase)(T *, T *) = &std::vector<T>::erase;
    if ((values.*size)() < count)
        (values.*insert)(values.end(), count - (values.*size)(), value);
    else if (count < (values.*size)())
        (values.*erase)(values.begin() + count, values.end());
}

// STUB: GAME 0x005bad10
bool RHSprite::FUN_005bad10(unsigned long first, unsigned short count, unsigned short rate, unsigned short sound, const void *offsets)
{
    RHSpriteField<std::vector<RHUnkSpriteRow> *>(this, 0x154) = new std::vector<RHUnkSpriteRow>;
    m_19c = 0;
    m_19a = 0;
#define ROWS() (*RHSpriteField<std::vector<RHUnkSpriteRow> *>(this, 0x154))
    RHSpriteResize(ROWS(), 1, RHUnkSpriteRow());
    RHSpriteResize(ROWS()[0].m_frames, count, (unsigned short)0);
    RHSpriteResize(ROWS()[0].m_rates, count, (unsigned short)0);
    RHSpriteResize(ROWS()[0].m_resources, count, 0);
    RHSpriteResize(ROWS()[0].m_positions, count, SBGeoVector2D());
    RHSpriteResize(ROWS()[0].m_flags, count, (unsigned short)0);
    ROWS()[0].m_00 = 0;
    SBGeoPoint2D &position = ROWS()[0].m_position;
    position.m_x = 0.0f;
    position.m_y = 0.0f;
    for (int i = 0; i < count; ++i)
    {
        if (RHSpriteField<RHFrameHolder *>(this, 0x1d0)->FUN_005046a0(first + i) > m_19a)
            m_19a = RHSpriteField<RHFrameHolder *>(this, 0x1d0)->FUN_005046a0(first + i);
        if (RHSpriteField<RHFrameHolder *>(this, 0x1d0)->FUN_005046c0(first + i) > m_19c)
            m_19c = RHSpriteField<RHFrameHolder *>(this, 0x1d0)->FUN_005046c0(first + i);
        ROWS()[0].m_frames[i] = rate;
        ROWS()[0].m_rates[i] = sound;
        ROWS()[0].m_resources[i] = first + i;
        ROWS()[0].m_positions[i] = (*(const std::vector<SBGeoVector2D> *)offsets)[i];
        ROWS()[0].m_flags[i] = 0;
    }
#undef ROWS
    return true;
}

// Parked: 6-arg script-row initializer (InitializeScriptRowFromLoadedFrame candidate).
// STUB: GAME 0x005bb180
void RHSprite::FUN_005bb180(unsigned short, unsigned long, unsigned short, unsigned short, unsigned short, void *)
{
}

#include "RHUnk005bb520.h"

// FUNCTION: GAME 0x005bb520
SBGeoPoint2D RHUnk005bb520::FUN_005bb520()
{
    SBGeoPoint2D result;
    {
        const SBGeoVector2D &offset = SBGeoVector2D(*(SBGeoVector2D *)((RHUnk005b5e00 *)this)->Unk005bdd30(RHSpriteField<unsigned short>(this, 0x184)));
        result = RHSpriteField<SBGeoPoint2D>(this, 0x1c).Unk005fc190(offset);
    }
    return result;
}

// SIZE 0x64
struct RHSpriteFrameEntry
{
    undefined m_00[0x18]; // 0x00
    unsigned *first; // 0x18
    unsigned *last; // 0x1c
    undefined m_20[8]; // 0x20
    unsigned short *durations; // 0x28
    unsigned short *durationsEnd; // 0x2c
    undefined m_30[0x34]; // 0x30
};
DECOMP_SIZE_ASSERT(RHSpriteFrameEntry, 0x64)

// FUNCTION: GAME 0x005bd3a0
bool RHSprite::FUN_005bd3a0(RHSprite &other)
{
    RHSpriteField<int>(this, 0x154) = RHSpriteField<int>(&other, 0x154);
    RHSpriteField<int>(this, 0x158) = RHSpriteField<int>(&other, 0x158);
    RHSpriteField<int>(this, 0x15c) = RHSpriteField<int>(&other, 0x15c);
    RHSpriteField<int>(this, 0x160) = RHSpriteField<int>(&other, 0x160);
    RHSpriteField<std::string>(this, 0x164) = RHSpriteField<std::string>(&other, 0x164);
    m_19a = other.m_19a;
    m_19c = other.m_19c;
    RHSpriteField<SBGeoVector2D>(this, 0x84) = RHSpriteField<SBGeoVector2D>(&other, 0x84);
    ((RHMobileUnk00607da0 *)&RHSpriteField<SBGeoBoundingBox2D>(this, 0x98))->FUN_00607da0(
        *(const RHMobileUnk00607da0 *)((RHUnkPathActorInfoBase *)((char *)&other + 4))->Unk0055fa10(RHSpriteField<int>(&other, 0x8c)));
    RHSpriteField<char>(this, 0x195) = 0;
    return true;
}

// SIZE 0x10
struct RHSpriteFrameVector
{
    undefined m_00[4]; // 0x00
    RHSpriteFrameEntry *first; // 0x04
    RHSpriteFrameEntry *last; // 0x08
    RHSpriteFrameEntry *end; // 0x0c
    unsigned size() const { return first == 0 ? 0 : last - first; }
};

// FUNCTION: GAME 0x005bd450
bool RHEngineWidenedCalls::FUN_005bd450()
{
    RHSpriteFrameVector *frames = (RHSpriteFrameVector *)((RHUnk005b5e00 *)this)->FUN_005b5de0();
    if (RHSpriteField<void *>(this, 0x154) && frames->size() != 0)
    {
        for (unsigned *current = frames->first[((RHSprite *)this)->m_184].first;
             current != frames->first[((RHSprite *)this)->m_184].last; ++current)
            RHSpriteField<RHSpriteFrameCalls *>(this, 0x1d0)->FUN_00505940(*current);
    }
    return true;
}

#include "RHEngineSpriteCalls.h"

// FUNCTION: GAME 0x005bd4e0
void RHEngineSpriteCalls::FUN_005bd4e0()
{
    RHSpriteFrameVector *frames = (RHSpriteFrameVector *)((RHUnk005b5e00 *)this)->FUN_005b5de0();
    if (frames->size() != 0)
    {
        for (unsigned *current = frames->first[((RHSprite *)this)->m_184].first;
             current != frames->first[((RHSprite *)this)->m_184].last; ++current)
            RHSpriteField<RHFrameHolder *>(this, 0x1d0)->FUN_005058a0(*current);
    }
}

// FUNCTION: GAME 0x005bd5b0
bool RHUnk005bd5b0::Unk(bool last)
{
    if (last)
    {
        unsigned short frame = ((RHSprite *)this)->FUN_005bdcf0(RHSpriteField<unsigned short>(this, 0x184)) - 1;
        RHSpriteField<unsigned short>(this, 0x188) = 0xffff;
        RHSpriteField<unsigned short>(this, 0x186) = frame;
        return true;
    }
    RHSpriteField<unsigned short>(this, 0x186) = 0;
    RHSpriteField<unsigned short>(this, 0x188) = 0xffff;
    return true;
}

// Parked: frame-table indexing and duration-count registers differ.
// STUB: GAME 0x005bd8b0
void RHUnk005b5ed0::FUN_005bd8b0()
{
    m_194 = !m_194;
    if (m_1dc != 0x11b)
    {
        void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
        int animation = m_1dc;
        m_184 = RHSpriteField<unsigned short *>(((RHUnk005b5e00 *)this)->Unk(), 4)[animation] + m_d8;
        RHSpriteFrameEntry &entry = RHSpriteField<RHSpriteFrameEntry *>(holder, 4)[m_184];
        unsigned count = entry.durations ? entry.durationsEnd - entry.durations : 0;
        if (m_186 >= count)
            m_186 = 0;
    }
}

// FUNCTION: GAME 0x005bd940
int RHSprite::FUN_005bd940()
{
    return FUN_005bdd50() == 1 && FUN_005bdd70() == 1;
}

// FUNCTION: GAME 0x005bd970
SBGeoBoundingBox2D RHSprite::GetGlobalBoundingBox()
{
    SBGeoBoundingBox2D box;
    SBGeoPoint2D point;
    SBGeoVector2D size;
    unsigned count = ((RHSpriteFrameVector *)((RHUnk005b5e00 *)this)->FUN_005b5de0())->size();
    for (unsigned animation = 0; animation < count; ++animation)
    {
        unsigned frames = FUN_005bdcf0(animation);
        for (unsigned frame = 0; frame < frames; ++frame)
        {
            point = *FUN_005bdc80(animation, frame);
            box.Unk00607dc0(point);
            box.Unk00607dc0(point.Unk005fc190(SBGeoVector2D((float)FUN_005bdb40(animation, frame), (float)FUN_005bdb80(animation, frame))));
        }
    }
    return box;
}

// FUNCTION: GAME 0x005bdb40
unsigned short RHSprite::FUN_005bdb40(unsigned short animation, unsigned short frame)
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    unsigned *table = RHSpriteField<unsigned *>(entries + animation * 0x64, 0x18);
    return ((RHFrameHolder *)RHSpriteField<RHFrameHolder *>(this, 0x1d0))->FUN_005046a0(table[frame]);
}

// FUNCTION: GAME 0x005bdb80
unsigned short RHSprite::FUN_005bdb80(unsigned short animation, unsigned short frame)
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    unsigned *table = RHSpriteField<unsigned *>(entries + animation * 0x64, 0x18);
    return ((RHFrameHolder *)RHSpriteField<RHFrameHolder *>(this, 0x1d0))->FUN_005046c0(table[frame]);
}

// FUNCTION: GAME 0x005bdbc0
unsigned RHSprite::FUN_005bdbc0(unsigned short animation, unsigned short frame)
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    return RHSpriteField<unsigned *>(entries + animation * 0x64, 0x18)[frame];
}

// FUNCTION: GAME 0x005bdbf0
unsigned short RHSprite::FUN_005bdbf0(unsigned short animation, unsigned short frame)
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    return RHSpriteField<unsigned short *>(entries + animation * 0x64, 0x28)[frame];
}

// FUNCTION: GAME 0x005bdc20
short RHSprite::FUN_005bdc20(unsigned short animation, unsigned short frame)
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    return RHSpriteField<short *>(entries + animation * 0x64, 0x38)[frame];
}

// FUNCTION: GAME 0x005bdc50
unsigned short RHSprite::FUN_005bdc50(unsigned short animation, unsigned short frame)
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    return RHSpriteField<unsigned short *>(entries + animation * 0x64, 0x58)[frame];
}

// FUNCTION: GAME 0x005bdc80
const SBGeoPoint2D *RHSprite::FUN_005bdc80(unsigned short animation, unsigned short frame)
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    return RHSpriteField<SBGeoPoint2D *>(entries + animation * 0x64, 0x48) + frame;
}

// FUNCTION: GAME 0x005bdcb0
float RHSprite::FUN_005bdcb0()
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    return RHSpriteField<float>(entries + m_184 * 0x64, 0x4);
}

// FUNCTION: GAME 0x005bdcd0
unsigned short RHSprite::FUN_005bdcd0(unsigned short animation)
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    return RHSpriteField<unsigned short>(entries + animation * 0x64, 0);
}

// FUNCTION: GAME 0x005bdcf0
unsigned short RHSprite::FUN_005bdcf0(unsigned short animation)
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    RHSpriteFrameSpan &span = RHSpriteField<RHSpriteFrameSpan>(entries + animation * 0x64, 0x24);
    return span.m_4 == 0 ? 0 : span.m_8 - span.m_4;
}

// FUNCTION: GAME 0x005bdd50
unsigned short RHSprite::FUN_005bdd50()
{
    return FUN_005bdb40(m_184, m_186);
}

// FUNCTION: GAME 0x005bdd70
unsigned short RHSprite::FUN_005bdd70()
{
    return FUN_005bdb80(m_184, m_186);
}

// FUNCTION: GAME 0x005bdd90
const SBGeoPoint2D *RHSprite::FUN_005bdd90()
{
    return FUN_005bdc80(m_184, m_186);
}

// FUNCTION: GAME 0x005bddb0
unsigned short RHSprite::FUN_005bddb0(unsigned index)
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    unsigned short *table = RHSpriteField<unsigned short *>(((RHUnk005b5e00 *)this)->Unk(), 4);
    unsigned short animation = table[index];
    return *(unsigned short *)((char *)RHSpriteField<void *>(holder, 4) + animation * 0x64 + 0x10);
}

// FUNCTION: GAME 0x005bddf0
unsigned short RHSprite::FUN_005bddf0()
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    undefined *span = entries + m_184 * 0x64 + 0x44;
    SBGeoPoint2D *first = RHSpriteField<SBGeoPoint2D *>(span, 4);
    unsigned short count = first == 0 ? 0 : RHSpriteField<SBGeoPoint2D *>(span, 8) - first;
    unsigned short maximum = 0;
    for (int index = 0; index < count; ++index)
    {
        if (FUN_005bdb40(m_184, index) > maximum)
            maximum = FUN_005bdb40(m_184, index);
    }
    return maximum;
}

// FUNCTION: GAME 0x005bde70
unsigned short RHSprite::FUN_005bde70()
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    undefined *span = entries + m_184 * 0x64 + 0x44;
    SBGeoPoint2D *first = RHSpriteField<SBGeoPoint2D *>(span, 4);
    unsigned short count = first == 0 ? 0 : RHSpriteField<SBGeoPoint2D *>(span, 8) - first;
    unsigned short maximum = 0;
    for (int index = 0; index < count; ++index)
    {
        if (FUN_005bdb80(m_184, index) > maximum)
            maximum = FUN_005bdb80(m_184, index);
    }
    return maximum;
}

// Parked: volatile table/frame probes change registers or still hoist the frame index before the table load.
// STUB: GAME 0x005bdf30
void RHSprite::FUN_005bdf30()
{
    void *holder = ((RHUnk005b5e00 *)this)->FUN_005b5de0();
    undefined *entries = RHSpriteField<undefined *>(holder, 4);
    unsigned *table = RHSpriteField<unsigned *>(entries + m_184 * 0x64, 0x18);
    ((RHFrameHolder *)RHSpriteField<RHFrameHolder *>(this, 0x1d0))->FUN_00505170(
        table[*(volatile unsigned short *)((char *)this + 0x186)]);
}

// Duplicate of the annotated RHUnk00613e90 (float, float, float) constructor (0x005df4f0).
RHUnk005df4f0::RHUnk005df4f0(float x, float y, float z)
{
    m_0 = x;
    m_4 = y;
    m_8 = z;
}

// FUNCTION: GAME 0x005fc3c0
SBGeoVector2D::SBGeoVector2D(float x, float y) : SBGeoPoint2D(x, y)
{
}

void RHSprite::Emit(SBFile &file)
{
    ((RHEngineWidenedCalls *)this)->FUN_005b7f60(0);
    FUN_005b7fd0(1.0f, 0);
    FUN_005b8420();
    FUN_005b84b0(0);
    ((RHUnk005bb520 *)this)->FUN_005bb520();
    FUN_005bddf0();
    FUN_005bde70();
    FUN_0049b2c0();
    FUN_005b5e20();
    FUN_005b5e60();
    FUN_005b5ea0(file, 0);
    ((RHUnk005b5ed0 *)this)->FUN_005b5ed0(file);
    LoadPositionInfoFromFile(file, 0);
    PerformAction(0, 0, 0, false);
    PerformMotion(0, 0, 0, 0, 0.0f, 0, false);
    ((RHSpriteEngineCalls *)g_pEngine)->FUN_004d9090();
    ((RHSpritePositionCalls *)this)->FUN_00563e90();
    ((RHSpritePositionCalls *)this)->FUN_00563ea0();
    FUN_005b94d0(0, 0, 0, 0, 0);
    FUN_005b9b60(m_1a0, 0.0f);
    FUN_005b9ce0();
    FUN_005b9e30(0, 0, false);
    FUN_005ba130(m_1a0, 0.0f, m_1a0, m_1a0);
    FUN_005ba6c0(m_1a0, 0.0f, m_1a0, m_1a0, *(SBGeoVector2D *)&m_1a0.m_00);
    FUN_005bad10(0, 0, 0, 0, 0);
    FUN_005bb180(0, 0, 0, 0, 0, 0);
}
