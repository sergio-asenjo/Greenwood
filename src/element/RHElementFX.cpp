#include "SBNullstr.h"
#include "RHElementFX.h"
#include "RHCivilianSpriteView.h"
#include "RHPlayerProfileAccess.h"
#include <stddef.h>

DECOMP_STATIC_ASSERT(offsetof(RHElementFX, m_d4) == 0xd4)
DECOMP_STATIC_ASSERT(offsetof(RHElementFX, m_f8) == 0xf8)

extern unsigned char g_unk0x006c0e48[];

inline void FXBlit(RHUnkFXDraw *const &draw, RHUnkFXEngine *engine, SBGeoBoundingBox2D *box,
                   const unsigned long &handle, SBGeoBoundingBox2D *source)
{
    unsigned long surface = engine->m_48c4;
    ((SBDrawManager *)draw)->FUN_005e6440(surface, box, handle, source, 0);
}

inline void FXRestore(RHUnkFXDraw *const &draw, RHUnkFXEngine *engine, const unsigned long &handle,
                      SBGeoBoundingBox2D *box, SBGeoBoundingBox2D *target)
{
    unsigned long surface = engine->m_48c4;
    ((SBDrawManager *)draw)->FUN_005e6440(handle, box, surface, target, 0);
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
    typedef unsigned long (RHUnkFXDraw::*CreateSurface)(unsigned short, unsigned short, int, bool);
    *(unsigned long *)((char *)this + 0x54) = (fx_draw->*reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(((RHCivilianSpriteView *)fx_sprite)->FUN_005bdef0(), ((RHCivilianSpriteView *)fx_sprite)->FUN_005bdf20(), 0, false);
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

class RHPatch
{
public:
    void FUN_00550070(bool mode);
};

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
