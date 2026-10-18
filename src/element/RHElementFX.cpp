#include "SBNullstr.h"
#include "RHElementFX.h"
#include "RHPlayerProfileAccess.h"

extern unsigned char g_unk0x006c0e48[];

inline void FXBlit(RHUnkFXDraw *const &draw, RHUnkFXEngine *engine, SBGeoBoundingBox2D *box,
                   const unsigned long &handle, SBGeoBoundingBox2D *source)
{
    unsigned long surface = engine->m_48c4;
    ((RHUnk005e6440 *)draw)->Blit(surface, box, handle, source, 0);
}

// FUNCTION: GAME 0x004aa0a0
void RHElementFX::InitializeBackgroundRestoration()
{
    if (m_cc == -1)
    {
        {
            SBGeoVector2D vector(fx_sprite->m_1c);
            m_b4 = fx_sprite->Unk005bd970() + vector;
        }
        m_b4 = fx_clip.Unk006092c0(m_b4);
        {
            SBGeoVector2D vector(fx_sprite->m_1c);
            m_b4 -= vector;
        }
        if (!m_b4.Unk00608f30() || m_b4.m_p0.m_x < g_unk0x00677488 || m_b4.m_p0.m_y < g_unk0x00677488)
        {
            m_cc = -1;
            SBAssert(0,
                     // STRING: GAME 0x006aea80
                     "P:\\Robin Hood\\RHelementfx.cpp", 760,
                     // STRING: GAME 0x006aeaa0
                     "DAS GEHT NICHT ! RHElementFX has left time-space continuum (%f,%f) !",
                     fx_sprite->m_24, fx_sprite->m_28);
        }
        int x = *(int *)&m_b4.m_p1.m_x;
        m_cc = fx_draw->Unk005e4ed0((int)*(float *)&x, (int)m_b4.m_p1.m_y, 0, 0);
        {
            SBGeoVector2D vector(fx_sprite->m_1c);
            FXBlit(fx_draw, (RHUnkFXEngine *)g_pEngine,
                   &(m_b4 + vector), m_cc, &m_b4);
        }
    }
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
    if (m_d0 || m_ac || *(float *)((char *)fx_sprite + 0x18) != g_unk0x00677488 ||
        (*(unsigned *)((char *)this + 4) & 0xf) == 5 ||
        ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0()[0x50] == 1)
        return 1;
    return 0;
}

void RHElementFX::Emit(SBFile &file)
{
    InitializeBackgroundRestoration();
    Serialize(file);
    FUN_004aa930();
}
