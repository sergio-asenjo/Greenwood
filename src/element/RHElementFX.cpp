#include "SBNullstr.h"
#include "RHElementFX.h"
#include "RHCivilianSpriteView.h"
#include "RHPlayerProfileAccess.h"
#include <stddef.h>

DECOMP_STATIC_ASSERT(offsetof(RHElementFX, m_d4) == 0xd4)
DECOMP_STATIC_ASSERT(offsetof(RHElementFX, m_f8) == 0xf8)

#include "RHPlayerProfileManagerStorage.h"

inline void FXBlit(SBDrawManager *const &draw, RHUnkFXEngine *engine, SBGeoBoundingBox2D *box,
                   const unsigned long &handle, SBGeoBoundingBox2D *source)
{
    unsigned long surface = engine->m_48c4;
    ((SBDrawManager *)draw)->FUN_005e6440(surface, box, handle, source, 0);
}

inline void FXRestore(SBDrawManager *const &draw, RHUnkFXEngine *engine, const unsigned long &handle,
                      SBGeoBoundingBox2D *box, SBGeoBoundingBox2D *target)
{
    unsigned long surface = engine->m_48c4;
    ((SBDrawManager *)draw)->FUN_005e6440(handle, box, surface, target, 0);
}

#include "RHMobileUnk00607da0.h"
#include "RHMobileUnk006091b0.h"
#include "RHUnk00608f10.h"
#include "SBGeoIntersection2D.h"
#include "SBGeoSegment2D.h"
#include "RHSectorCore.h"
#include "RHElementActor.h"
#include "RHTargetResourceCalls.h"
#include "RHEngineWidenedCalls.h"

extern SBDrawManager *g_unk0x6c11d0;

// STUB: GAME 0x004a8300
void *RHElementFX::Refresh(unsigned long surface, float value, const SBGeoBoundingBox2D &box,
                           unsigned long flags)
{
    RHspriteRenderingInfo info;
    SBGeoBoundingBox2D sourceBox;
    SBGeoBoundingBox2D destinationBox;
    void *result;
    if (!*((char *)this + 0x12) || !(unsigned char)FUN_004aa930())
        return 0;
    unsigned short frame = fx_sprite->FUN_005bb5f0();
    if (frame != 0)
    {
        m_14.FUN_0045abf0(frame, ((RHElementActor *)this)->FUN_00462920(), 9, 0);
        result = &m_14;
    }
    else
        result = 0;
    if (m_c8 && m_cc != -1 && (unsigned char)fx_sprite->FUN_005bd940())
    {
        {
            SBGeoBoundingBox2D shadow = m_b4.FUN_006090d0(
                SBGeoVector2D((const SBGeoVector2D &)fx_sprite->m_18));
            if (((RHUnk00608f10 *)&box)->FUN_00608f10(&shadow)
                && FUN_004aa420((SBGeoBoundingBox2D *)&box, value, &sourceBox, &destinationBox))
                fx_draw->FUN_005e6440(m_cc, &sourceBox, surface, &destinationBox, 1);
        }
        {
            SBGeoBoundingBox2D shadow = m_b4.FUN_006090d0(
                SBGeoVector2D((const SBGeoVector2D &)fx_sprite->m_18));
            FXRestore(fx_draw, (RHUnkFXEngine *)g_pEngine, m_cc, &m_b4, &shadow);
        }
        m_c8 = 0;
        goto refreshDone;
    }
    if (!fx_sprite->FUN_005b9b60(box, value))
    {
        ((RHEngineWidenedCalls *)fx_sprite)->FUN_005bd450();
        goto refreshDone;
    }
    info.m_surface = m_54;
    info.m_05 = 1;
    if (*((char *)this + 0x92))
        info.m_flags = 4;
    fx_sprite->CreateTargetSprite(info);
    if (!fx_sprite->FUN_005ba130(box, value, sourceBox, destinationBox))
        goto refreshDone;
    if (m_a8 == 1)
    {
        if (*((char *)this + 0x8e) == 1)
            ((SBDrawManager *)fx_draw)->BlitAlphaKeying(
                m_54, &sourceBox, surface, &destinationBox,
                *((unsigned short *)((char *)this + 0x90)),
                *((unsigned short *)(*(char **)((char *)this + 0x68) + 0x48)), 1);
        else
            fx_draw->FUN_005e6440(m_54, &sourceBox, surface, &destinationBox, 1);
    }
    else
        fx_draw->FUN_005e6440(m_54, &sourceBox, surface, &destinationBox, 1);
    if (m_ac)
    {
        char *patch = (char *)m_ac;
        if (patch[0x19c])
        {
            if (!patch[0xb])
            {
                void *sector = patch[0] ? *(void **)(patch + 0x154) : *(void **)(patch + 0x150);
                if (sector)
                    ((RHSector *)sector)->DisplayAlpha(0x60d0, 0x60, false);
            }
            unsigned count = (*(int *)(patch + 0x160) - *(int *)(patch + 0x15c)) >> 2;
            for (unsigned index = 0; index < count; ++index)
            {
                RHSector *sector =
                    *(RHSector **)(*(char **)(*(int *)(patch + 0x15c) + index * 4) + 0xac);
                if (sector)
                    sector->DisplayAlpha(0x60d0, 0x60, false);
            }
        }
    }
refreshDone:
    if (*((char *)this + 0x92))
    {
        SBGeoVector2D shift;
        unsigned short key = fx_draw->FUN_005e5f60(m_58);
        fx_draw->FUN_005e61e0(m_58, 0, key, 0);
        fx_sprite->FUN_005bb850(
            m_58, *((unsigned short *)((char *)this + 0x94 + *(int *)((char *)this + 0xa0) * 2)),
            *((unsigned short *)((char *)this + 0xa4)), shift, 1);
        fx_sprite->FUN_005ba6c0(box, value, sourceBox, destinationBox, shift);
        fx_draw->FUN_005e6440(m_58, &sourceBox, 0, &destinationBox, 1);
        *((char *)this + 0x92) = 0;
    }
    if (*((char *)g_pEngine + 0x4b33) && m_b4.Unk00608f30() && m_b4.FUN_006090a0())
    {
        SBGeoBoundingBox2D shadow = m_b4.FUN_006090d0(
            SBGeoVector2D((const SBGeoVector2D &)fx_sprite->m_18));

        SBGeoSegment2D segment(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f));
        RHUnk0060fbf0 clipped;
        SBGeoPoint2D first;
        SBGeoPoint2D second;

        segment.First() = shadow.m_p0;
        segment.Second() = SBGeoPoint2D(shadow.m_p1.m_x, shadow.m_p0.m_y);
        clipped.FUN_0060fca0(box.FUN_006093f0(segment.Line()));
        if (clipped.FUN_0063b9a0() == 4)
        {
            first = ((SBGeoPoint2D *)clipped.FUN_0053bf20())->Unk005fc110(box.m_p0);
            second = (((SBGeoPoint2D *)clipped.FUN_0053bf20()) + 1)->Unk005fc110(box.m_p0);
            if (value != 1.0f)
            {
                first.m_x *= value;
                first.m_y *= value;
                second.m_x *= value;
                second.m_y *= value;
            }
            g_unk0x6c11d0->FUN_005ecbd0(0, first, second, 0xffff);
        }
        segment.First() = SBGeoPoint2D(shadow.m_p1.m_x, shadow.m_p0.m_y);
        segment.Second() = shadow.m_p1;
        clipped.FUN_0060fca0(box.FUN_006093f0(segment.Line()));
        if (clipped.FUN_0063b9a0() == 4)
        {
            first = ((SBGeoPoint2D *)clipped.FUN_0053bf20())->Unk005fc110(box.m_p0);
            second = (((SBGeoPoint2D *)clipped.FUN_0053bf20()) + 1)->Unk005fc110(box.m_p0);
            if (value != 1.0f)
            {
                first.m_x *= value;
                first.m_y *= value;
                second.m_x *= value;
                second.m_y *= value;
            }
            g_unk0x6c11d0->FUN_005ecbd0(0, first, second, 0xffff);
        }
        segment.First() = shadow.m_p1;
        segment.Second() = SBGeoPoint2D(shadow.m_p0.m_x, shadow.m_p1.m_y);
        clipped.FUN_0060fca0(box.FUN_006093f0(segment.Line()));
        if (clipped.FUN_0063b9a0() == 4)
        {
            first = ((SBGeoPoint2D *)clipped.FUN_0053bf20())->Unk005fc110(box.m_p0);
            second = (((SBGeoPoint2D *)clipped.FUN_0053bf20()) + 1)->Unk005fc110(box.m_p0);
            if (value != 1.0f)
            {
                first.m_x *= value;
                first.m_y *= value;
                second.m_x *= value;
                second.m_y *= value;
            }
            g_unk0x6c11d0->FUN_005ecbd0(0, first, second, 0xffff);
        }
        segment.First() = SBGeoPoint2D(shadow.m_p0.m_x, shadow.m_p1.m_y);
        segment.Second() = shadow.m_p0;
        clipped.FUN_0060fca0(box.FUN_006093f0(segment.Line()));
        if (clipped.FUN_0063b9a0() == 4)
        {
            first = ((SBGeoPoint2D *)clipped.FUN_0053bf20())->Unk005fc110(box.m_p0);
            second = (((SBGeoPoint2D *)clipped.FUN_0053bf20()) + 1)->Unk005fc110(box.m_p0);
            if (value != 1.0f)
            {
                first.m_x *= value;
                first.m_y *= value;
                second.m_x *= value;
                second.m_y *= value;
            }
            g_unk0x6c11d0->FUN_005ecbd0(0, first, second, 0xffff);
        }

        shadow = SBGeoBoundingBox2D(SBGeoPoint2D(),
                                    SBGeoPoint2D((float)fx_sprite->FUN_005bdd50(),
                                                 (float)fx_sprite->FUN_005bdd70()));
        ((RHMobileUnk006091b0 *)&shadow)->FUN_006091b0(
            SBGeoVector2D(fx_sprite->m_18.Unk005fc190(*fx_sprite->FUN_005bdd90())));

        segment.First() = shadow.m_p0;
        segment.Second() = SBGeoPoint2D(shadow.m_p1.m_x, shadow.m_p0.m_y);
        clipped.FUN_0060fca0(box.FUN_006093f0(segment.Line()));
        if (clipped.FUN_0063b9a0() == 4)
        {
            first = ((SBGeoPoint2D *)clipped.FUN_0053bf20())->Unk005fc110(box.m_p0);
            second = (((SBGeoPoint2D *)clipped.FUN_0053bf20()) + 1)->Unk005fc110(box.m_p0);
            if (value != 1.0f)
            {
                first.m_x *= value;
                first.m_y *= value;
                second.m_x *= value;
                second.m_y *= value;
            }
            g_unk0x6c11d0->FUN_005ecbd0(0, first, second, 0xfa00);
        }
        segment.First() = SBGeoPoint2D(shadow.m_p1.m_x, shadow.m_p0.m_y);
        segment.Second() = shadow.m_p1;
        clipped.FUN_0060fca0(box.FUN_006093f0(segment.Line()));
        if (clipped.FUN_0063b9a0() == 4)
        {
            first = ((SBGeoPoint2D *)clipped.FUN_0053bf20())->Unk005fc110(box.m_p0);
            second = (((SBGeoPoint2D *)clipped.FUN_0053bf20()) + 1)->Unk005fc110(box.m_p0);
            if (value != 1.0f)
            {
                first.m_x *= value;
                first.m_y *= value;
                second.m_x *= value;
                second.m_y *= value;
            }
            g_unk0x6c11d0->FUN_005ecbd0(0, first, second, 0xfa00);
        }
        segment.First() = shadow.m_p1;
        segment.Second() = SBGeoPoint2D(shadow.m_p0.m_x, shadow.m_p1.m_y);
        clipped.FUN_0060fca0(box.FUN_006093f0(segment.Line()));
        if (clipped.FUN_0063b9a0() == 4)
        {
            first = ((SBGeoPoint2D *)clipped.FUN_0053bf20())->Unk005fc110(box.m_p0);
            second = (((SBGeoPoint2D *)clipped.FUN_0053bf20()) + 1)->Unk005fc110(box.m_p0);
            if (value != 1.0f)
            {
                first.m_x *= value;
                first.m_y *= value;
                second.m_x *= value;
                second.m_y *= value;
            }
            g_unk0x6c11d0->FUN_005ecbd0(0, first, second, 0xfa00);
        }
        segment.First() = SBGeoPoint2D(shadow.m_p0.m_x, shadow.m_p1.m_y);
        segment.Second() = shadow.m_p0;
        clipped.FUN_0060fca0(box.FUN_006093f0(segment.Line()));
        if (clipped.FUN_0063b9a0() == 4)
        {
            first = ((SBGeoPoint2D *)clipped.FUN_0053bf20())->Unk005fc110(box.m_p0);
            second = (((SBGeoPoint2D *)clipped.FUN_0053bf20()) + 1)->Unk005fc110(box.m_p0);
            if (value != 1.0f)
            {
                first.m_x *= value;
                first.m_y *= value;
                second.m_x *= value;
                second.m_y *= value;
            }
            g_unk0x6c11d0->FUN_005ecbd0(0, first, second, 0xfa00);
        }
    }
    if (*(int *)((char *)this + 0xb0) != 0x11b)
    {
        ((RHUnkTargetSprite *)fx_sprite)->FUN_005b76e0(*(int *)((char *)this + 0xb0), 0);
        *(int *)((char *)this + 0xb0) = 0x11b;
    }
    return result;
}

// STUB: GAME 0x004a9990
void RHElementFX::FUN_004a9990()
{
    RHspriteRenderingInfo info;
    SBGeoBoundingBox2D first;
    SBGeoBoundingBox2D second;
    if (!*((char *)this + 0x12)
        || !m_ac && *(float *)((char *)fx_sprite + 0x18) == 0.0f
            && !((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0()[0x50])
        return;
    if (m_c8 && m_cc != -1 && (unsigned char)fx_sprite->FUN_005bd940())
    {
        {
            SBGeoVector2D vector((const SBGeoVector2D &)fx_sprite->m_18);
            FXRestore(fx_draw, (RHUnkFXEngine *)g_pEngine, m_cc, &m_b4, &m_b4.FUN_006090d0(vector));
        }
        m_c8 = 0;
    }
    else
    {
        unsigned long surface = ((RHUnkFXEngine *)g_pEngine)->m_48c4;
        SBGeoBoundingBox2D source;
        SBGeoBoundingBox2D destination;
        SBGeoVector2D hotspot(*fx_sprite->FUN_005bdd90());
        source.FUN_00609050(SBGeoPoint2D(0.0f, 0.0f),
                            SBGeoVector2D((float)fx_sprite->FUN_005bdd50(), (float)fx_sprite->FUN_005bdd70()));
        ((RHMobileUnk00607da0 *)&destination)->FUN_00607da0((const RHMobileUnk00607da0 &)source);
        ((RHMobileUnk006091b0 *)&destination)->FUN_006091b0(SBGeoVector2D(fx_sprite->m_18.Unk005fc190(hotspot)));
        info.m_surface = *(unsigned long *)((char *)this + 0x54);
        info.m_05 = 1;
        fx_sprite->CreateTargetSprite(info);
        m_c8 = 1;
        switch (m_a8)
        {
        case 1:
            if (*((char *)this + 0x8e) == 1)
            {
                ((SBDrawManager *)fx_draw)->BlitAlphaKeying(*(unsigned long *)((char *)this + 0x54), &source, surface, &destination,
                    *(unsigned short *)((char *)this + 0x90), *(unsigned short *)(*(char **)((char *)this + 0x68) + 0x48), 1);
                break;
            }
        default:
            ((SBDrawManager *)fx_draw)->FUN_005e6440(*(unsigned long *)((char *)this + 0x54), &source, surface, &destination, 1);
        }
    }
    *((char *)g_pEngine + 0x48d1) = 0;
}

// FUNCTION: GAME 0x004a9df0
void RHElementFX::RestoreBackground()
{
    if (m_cc != -1)
    {
        {
            SBGeoVector2D vector((const SBGeoVector2D &)fx_sprite->m_18);
            FXRestore(fx_draw, (RHUnkFXEngine *)g_pEngine, m_cc, &m_b4, &m_b4.FUN_006090d0(vector));
        }
        m_c8 = 0;
    }
}

// STUB: GAME 0x004a9ec0
void RHElementFX::InitializeFromProtoStream(SBFile &file)
{
    bool enabled;
    char flag;
    unsigned short count;
    short x;
    short y;
    fx_sprite->FUN_005b5ea0(file, 2);
    *(SBGeoPoint2D *)((char *)fx_sprite + 0x40) = *(SBGeoPoint2D *)((char *)fx_sprite + 0x1c);
    file.Access(&enabled, 1);
    if (enabled)
        m_a8 = 1;
    else
        m_a8 = 0;
    file.Access((char *)this + 0x12, 1);
    file.Access(&m_d0, 1);
    *(unsigned *)&m_f8 = 0x58635fa9;
    file.Access(&flag, 1);
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        file.Access(&x, 2);
        file.Access(&y, 2);
        m_d4.FUN_00611100(SBGeoPoint2D((float)x, (float)y));
        float height = (float)y;
        if (height < m_f8)
            m_f8 = height;
    }
    file.Access(&flag, 1);
    *(unsigned long *)((char *)this + 0x54) = fx_draw->Unk005e4ed0(((RHCivilianSpriteView *)fx_sprite)->FUN_005bdef0(), ((RHCivilianSpriteView *)fx_sprite)->FUN_005bdf20(), 0, false);
    if ((*(unsigned *)((char *)this + 4) & 3) == 1 && (*(unsigned *)((char *)this + 4) & 15) != 5 && *(float *)((char *)fx_sprite + 0x18) == 0.0f)
        InitializeBackgroundRestoration();
}

// FUNCTION: GAME 0x004aa0a0
void RHElementFX::InitializeBackgroundRestoration()
{
    if (m_cc == -1)
    {
        {
            SBGeoVector2D vector((const SBGeoVector2D &)fx_sprite->m_18);
            ((RHMobileUnk00607da0 *)&m_b4)->FUN_00607da0((const RHMobileUnk00607da0 &)fx_sprite->GetGlobalBoundingBox().FUN_006090d0(vector));
        }
        ((RHMobileUnk00607da0 *)&m_b4)->FUN_00607da0((const RHMobileUnk00607da0 &)fx_clip.FUN_006092c0(m_b4));
        {
            SBGeoVector2D vector((const SBGeoVector2D &)fx_sprite->m_18);
            m_b4 -= vector;
        }
        if (!m_b4.Unk00608f30() || m_b4.m_p0.m_x < 0.0f || m_b4.m_p0.m_y < 0.0f)
        {
            m_cc = -1;
            SBAssert(0,
                     // STRING: GAME 0x006aea80
                     "P:\\Robin Hood\\RHelementfx.cpp", 760,
                     // STRING: GAME 0x006aeaa0
                     "DAS GEHT NICHT ! RHElementFX has left time-space continuum (%f,%f) !",
                       fx_sprite->m_20.m_x, fx_sprite->m_20.m_y);
        }
        int x = *(int *)&m_b4.m_p1.m_x;
        m_cc = fx_draw->Unk005e4ed0((int)*(float *)&x, (int)m_b4.m_p1.m_y, 0, 0);
        {
            SBGeoVector2D vector((const SBGeoVector2D &)fx_sprite->m_18);
            FXBlit(fx_draw, (RHUnkFXEngine *)g_pEngine,
                   &m_b4.FUN_006090d0(vector), m_cc, &m_b4);
        }
    }
}

#include "RHEngineWidenedCalls.h"

#include "RHPatchClass.h"

// FUNCTION: GAME 0x004aa2f0
bool RHElementFX::FUN_004aa2f0()
{
    if (*((char *)this + 0x12))
    {
        char *patch = (char *)m_ac;
        if (patch)
        {
            int state;
            if (patch[0] && patch[0xb])
                state = (*(RHEngineWidenedCalls **)((char *)this + 0x50))->FUN_005b7f60(0xd);
            else
                state = (*(RHEngineWidenedCalls **)((char *)this + 0x50))->FUN_005b7f60(0);
            if (state == 3 && ((char *)m_ac)[0xb])
            {
                ((char *)m_ac)[0xb] = 0;
                ((RHPatch *)m_ac)->FUN_00550070(false);
                return true;
            }
        }
        else
            (*(RHEngineWidenedCalls **)((char *)this + 0x50))->FUN_005b7f60(0);
    }
    return true;
}

// FUNCTION: GAME 0x004aa360
bool RHElementFX::Serialize(SBFile &file)
{
    // STRING: GAME 0x006aeae8
    RHSerializeName(file, "RHElementFX");
    ((RHFastFindGrid *)g_unk0x6c0a9c)->Unk004efbb0(file, &m_ac);
    if (file.Access(&m_d0, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementfx.cpp", 856, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_c8, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementfx.cpp", 857, "Serialize failed reason is %s", reason);
        return false;
    }
    return RHElement::Serialize(file);
}

// STUB: GAME 0x004aa420
bool RHElementFX::FUN_004aa420(SBGeoBoundingBox2D *clip, float scale, SBGeoBoundingBox2D *first,
                               SBGeoBoundingBox2D *second)
{
    SBGeoVector2D offset;
    SBGeoPoint2D origin;
    SBGeoPoint2D boxOrigin;
    SBGeoPoint2D unused;

    {
        SBGeoVector2D spriteOffset((const SBGeoVector2D &)fx_sprite->m_18);
        ((RHMobileUnk00607da0 *)first)->FUN_00607da0(
            (const RHMobileUnk00607da0 &)m_b4.FUN_006090d0(spriteOffset));
    }
    origin = clip->m_p0;
    boxOrigin = first->m_p0;
    ((RHMobileUnk00607da0 *)second)->FUN_00607da0(
        (const RHMobileUnk00607da0 &)clip->FUN_006092c0(*first));
    if (!second->Unk00608f30())
        return false;
    offset = second->m_p0.Unk005fc110(boxOrigin);
    if (scale == 0.5f)
    {
        int minX = (int)(second->m_p0.m_x - origin.m_x);
        int minY = (int)(second->m_p0.m_y - origin.m_y);
        int maxX = (int)(second->m_p1.m_x - origin.m_x);
        int maxY = (int)(second->m_p1.m_y - origin.m_y);
        int offsetX = (int)floor(offset.m_x);
        int offsetY = (int)floor(offset.m_y);
        if (minX & 1)
        {
            ++minX;
            ++offsetX;
        }
        if (minY & 1)
        {
            ++minY;
            ++offsetY;
        }
        if (!(maxX & 1))
            --maxX;
        if (!(maxY & 1))
            --maxY;
        second->FUN_00609050(SBGeoPoint2D((float)(minX >> 1), (float)(minY >> 1)),
                             SBGeoPoint2D((float)(maxX >> 1), (float)(maxY >> 1)));
        offset.m_x = (float)offsetX;
        offset.m_y = (float)offsetY;
        first->FUN_00609050(offset,
                            SBGeoPoint2D((second->m_p1.m_x - second->m_p0.m_x) * 2.0f,
                                         (second->m_p1.m_y - second->m_p0.m_y) * 2.0f)
                                .Unk005fc190(offset));
    }
    else
    {
        first->FUN_00609050(offset,
                            SBGeoPoint2D(second->m_p1.m_x - second->m_p0.m_x,
                                         second->m_p1.m_y - second->m_p0.m_y)
                                .Unk005fc190(offset));
        if (scale == 2.0f)
            second->FUN_00609050(SBGeoPoint2D((second->m_p0.m_x - origin.m_x) * 2.0f,
                                              (second->m_p0.m_y - origin.m_y) * 2.0f),
                                 SBGeoPoint2D((second->m_p1.m_x - origin.m_x) * 2.0f,
                                              (second->m_p1.m_y - origin.m_y) * 2.0f));
        else
            second->FUN_00609050(second->m_p0.Unk005fc110(origin),
                                 second->m_p1.Unk005fc110(origin));
    }
    return second->FUN_006090a0() && first->FUN_006090a0();
}

// FUNCTION: GAME 0x004aa930
int RHElementFX::FUN_004aa930()
{
    if (m_d0 || m_ac || *(float *)((char *)fx_sprite + 0x18) != 0.0f ||
        (*(unsigned *)((char *)this + 4) & 0xf) == 5 ||
        ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0()[0x50] == 1)
        return 1;
    return 0;
}

// STUB: GAME 0x004aa980
bool RHElementFX::IsElementBehind(RHElement *element)
{
    unsigned long last;
    unsigned long index;
    SBGeoPoint2D position(*(SBGeoPoint2D *)(*(char **)((char *)element + 0x50) + 0x24));
    SBGeoPoint2D point;
    RHUnkSectorPoints &line = (RHUnkSectorPoints &)m_d4;
    last = ((RHMobileUnk00611360 &)line).FUN_00610f30();
    if (!last)
        return position.m_y < *(float *)((char *)fx_sprite + 0x28);
    point = line.FUN_006112c0(0);
    if (position.m_x < point.m_x)
        return position.m_y < point.m_y;
    point = line.FUN_006112c0(--last);
    if (position.m_x > point.m_x)
        return position.m_y < point.m_y;
    index = 1;
    float x = position.m_x;
    while (line.FUN_006112c0(index).m_x < x)
    {
        ++index;
        x = position.m_x;
    }
    point = line.FUN_006112c0(index - 1);
    return ((const RHUnk005fc3b0 &)line.FUN_006112c0(index).Unk005fc110(point)).FUN_005fc680((const RHUnk005fc3b0 &)position.Unk005fc110(point), 1.0f) < 0.0f;
}

void RHElementFX::Emit(SBFile &file)
{
    InitializeFromProtoStream(file);
    InitializeBackgroundRestoration();
    FUN_004aa2f0();
    Serialize(file);
    FUN_004aa930();
    IsElementBehind(this);
}
