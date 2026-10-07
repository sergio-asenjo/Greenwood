#include "RHSprite.h"

// STRING: GAME 0x006b8748
#define g_spriteFile "P:\\Robin Hood\\RHsprite.cpp"

// GLOBAL: GAME 0x00677db8
float g_unk0x00677db8 = 0.7f;
// GLOBAL: GAME 0x00679e40
float g_unk0x00679e40 = 0.6f;

// deferred: unannotated pending reccmp #534
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
    sprite.m_1a0.FUN_00607c70(file);
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
            float centerX = (x0 + x1) * g_unk0x006775d8;
            float centerY = (y0 + y1) * g_unk0x006775d8;
            box.m_10 = true;
            box.m_00 = SBGeoPoint2D(x0 - centerX, y0 - centerY);
            box.m_10 = true;
            box.m_08 = SBGeoPoint2D(x1 - centerX, y1 - centerY);
            RHSpriteField<SBGeoBoundingBox2D>(this, 0x98) = box;
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
            centerX = (x0 + x1) * g_unk0x006775d8;
            centerY = (y0 + y1) * g_unk0x006775d8;
            ((RHUnk005fc3b0 *)&RHSpriteField<SBGeoPoint2D>(this, 0x84))->FUN_005fc430(SBGeoVector2D(centerX, centerY));
            box.m_10 = true;
            box.m_00 = SBGeoPoint2D(x0 - centerX, y0 - centerY);
            box.m_10 = true;
            box.m_08 = SBGeoPoint2D(x1 - centerX, y1 - centerY);
            RHSpriteField<SBGeoBoundingBox2D>(this, 0xac) = box;
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
            RHSpriteField<SBGeoBoundingBox2D>(this, 0x98) = SBGeoBoundingBox2D(SBGeoVector2D(-2.0f, -2.0f), SBGeoVector2D(2.0f, 2.0f));
            ((RHBonusInfoBase *)position)->FUN_0055f290();
            ((RHBonusInfo *)this)->FUN_005bd560(0, true);
        }
        break;
    }
}

// Parked: effective-only instruction scheduling at the depth update.
// STUB: GAME 0x005b8050
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
            (unsigned short)animation, m_168 ? m_168 : "");
        return 4;
    }
    unsigned short frame = ((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->Frame(animation);
    m_184 = frame + m_d8;
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
        FUN_005bd450();
        result = 3;
    }
    return result;
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
            (unsigned short)animation, m_168 ? m_168 : "");
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
            m_184 = ((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->Frame(animation) + m_d8;
            FUN_005b7300(animation, progression);
            FUN_005bd450();
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
    m_184 = m_d8 + ((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->Frame(animation);
    FUN_005b7300(animation, progression);
    bool finished = FUN_005b7820(progression);
    float distance = m_188 == 0 ? (float)FUN_005bdc20(m_184, m_186) : g_unk0x00677488;
    if (method == 3)
    {
        distance *= 2;
        finished |= FUN_005b7820(progression);
        if (m_188 == 0)
            distance = (distance + FUN_005bdc20(m_184, m_186)) * 2;
    }
    distance *= speed;
    if (distance != g_unk0x00677488)
    {
        moved = true;
        if (m_d8 != S(unsigned short, 0xda))
        {
            if (method == 6)
            {
                distance *= 2;
                FUN_005b7820(progression);
            }
            else
                distance *= g_unk0x00679e40;
            if (distance < g_unk0x00677db8)
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
            S(SBGeoBoundingBox2D, 0xc4) = ((SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)position)->Unk0055fa10(S(int, 0x8c)))->FUN_006090d0(SBGeoVector2D(S(SBGeoPoint2D, 0x24)));
            S(int, 8) = 2;
        }
        ((RHBonusInfoBase *)position)->FUN_0055f290();
        ((RHBonusInfo *)this)->FUN_005bd560(0, true);
        calls->FUN_00560780(distance, FUN_005bdbf0(m_184, m_186) + 1);
        if (S(int, 0xfc) == 5 && distance > g_unk0x006774f4)
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
        if (ready && distance != g_unk0x00677488
            && (S(SBGeoPoint2D, 0x70).m_x != g_unk0x00677488 || S(SBGeoPoint2D, 0x70).m_y != g_unk0x00677488))
        {
            S(int, 0xc) = 1;
            ((RHUnk005fc3b0 *)&S(SBGeoPoint2D, 0x70))->FUN_005fc430(SBGeoVector2D(0.0f, 0.0f));
            S(int, 0xc) = 2;
            S(RHUnk005df4f0, 0x64) = RHUnk005df4f0(0.0f, 0.0f, 0.0f);
            S(int, 0xc) = 7;
            if (!S(bool, 0x102) && S(float, 0x7c) != g_unk0x00677488)
            {
                S(SBGeoPoint2D, 0x24) = S(SBGeoPoint2D, 0x48);
                S(SBGeoBoundingBox2D, 0xc4) = ((SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)position)->Unk0055fa10(S(int, 0x8c)))->FUN_006090d0(SBGeoVector2D(S(SBGeoPoint2D, 0x48)));
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
                    && (RHSpriteField<SBGeoPoint2D>(candidate, 0x14).m_x != g_unk0x00677488
                        || RHSpriteField<SBGeoPoint2D>(candidate, 0x14).m_y != g_unk0x00677488))
                {
                    replacement = RHSpriteField<int>(candidate, 0x24);
                    break;
                }
                if (selected == 1
                    && (RHSpriteField<RHUnk005df4f0>(candidate, 8).m_0 != g_unk0x00677488
                        || RHSpriteField<RHUnk005df4f0>(candidate, 8).m_4 != g_unk0x00677488
                        || RHSpriteField<RHUnk005df4f0>(candidate, 8).m_8 != g_unk0x00677488))
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
        if (!S(bool, 0x102) && S(float, 0x7c) != g_unk0x00677488)
        {
            S(SBGeoPoint2D, 0x24) = S(SBGeoPoint2D, 0x48);
            S(SBGeoBoundingBox2D, 0xc4) = ((SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)position)->Unk0055fa10(S(int, 0x8c)))->FUN_006090d0(SBGeoVector2D(S(SBGeoPoint2D, 0x48)));
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

void RHSprite::Emit(SBFile &file)
{
    FUN_005b5ed0(file);
    LoadPositionInfoFromFile(file, 0);
    PerformAction(0, 0, 0, false);
    PerformMotion(0, 0, 0, 0, 0.0f, 0, false);
}
