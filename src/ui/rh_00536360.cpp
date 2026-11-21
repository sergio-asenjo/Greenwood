#include "SBNullstr.h"
#include "SBGeoPoint2D.h"
#include "RHMissionResultMenu.h"
#include "SBDrawManagerCore.h"
#include "SBFont.h"
#include "RHFontManager.h"
#include "SBUIRenderer.h"
#include "SBResourceManager.h"
#include "RHMenuScreenView.h"
#include "RHMenuWindow.h"
#include "RHMessenger.h"
#include "RHGame.h"
#include "RHMapResources.h"
#include "RHPlayerProfile.h"
#include "RHPlayerProfileManager.h"
#include "RHPlayerProfileManagerStorage.h"
#include "RHUnk005fc3b0.h"
#include <stddef.h>
#include <string>

class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;
extern SBDrawManager *g_unk0x6c11d0;
RHMessenger *RHUnk00546050();
SBGeoVector2D FUN_005fc580(const SBGeoVector2D &point, float factor);

DECOMP_SIZE_ASSERT(RHUnk00536360, 0x478)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_a4) == 0xa4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_ac) == 0xac)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_d0) == 0xd0)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_c4) == 0xc4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_c8) == 0xc8)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_cc) == 0xcc)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_bounds) == 0xd4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_font) == 0xe8)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_ec) == 0xec)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_10c) == 0x10c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_1dc) == 0x1dc)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_2ac) == 0x2ac)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_3ac) == 0x3ac)
DECOMP_SIZE_ASSERT(RHGameLifetime00515d30, 0xd0)
DECOMP_SIZE_ASSERT(RHGameLifetime00525560, 0x100)
DECOMP_SIZE_ASSERT(RHGameLifetime00515f00, 0xcc)
DECOMP_STATIC_ASSERT(offsetof(RHGameLifetime00515d30, m_renderer) == 0x80)
DECOMP_STATIC_ASSERT(offsetof(RHGameLifetime00525560, m_renderer) == 0x80)
DECOMP_STATIC_ASSERT(offsetof(RHGameLifetime00525560, m_fc) == 0xfc)
DECOMP_STATIC_ASSERT(offsetof(RHGameLifetime00515f00, m_renderer) == 0x80)

// STUB: GAME 0x00535a30
RHUnk00536360::RHUnk00536360() : m_ec(0), m_2ac(RHGameLifetime00525560::SeparateBase)
{
    SBDrawManager *draw = g_unk0x6c11d0;
    RHPortraitBitmapWidget *ok = &m_10c;
    RHPortraitBitmapWidget *cancel = &m_1dc;
    RHPortraitBitmapWidget *text = &m_2ac;
    RHPortraitBitmapWidget *background = &m_3ac;
    {
        std::wstring label(L"OK");
        ok->Create(label, RHMapBox(150.0f, 130.0f, 150.0f, 130.0f), 0, 0x91);
    }
    {
        // STRING: GAME 0x006b0eec
        std::wstring label(L"Cancel");
        cancel->Create(label, RHMapBox(209.0f, 130.0f, 209.0f, 130.0f), 0, 0x92);
    }
    {
        // STRING: GAME 0x006b0ee0
        std::wstring label(L"Text");
        text->Create(label, RHMapBox(25.0f, 50.0f, 375.0f, 120.0f), 0, -1);
    }
    {
        // STRING: GAME 0x006b0ec8
        std::wstring label(L"Background");
        background->Create(label, RHMapBox(0.0f, 0.0f, 0.0f, 0.0f), 0, 0xed);
    }
    static_cast<SBResourceManager *>(m_resource)->FUN_00600920(0xed, 0, m_cc);
    static_cast<RHMapResources *>(m_resource)->FUN_006006f0(0xed, m_a4);
    m_surface = draw->Unk005e4ed0((unsigned short)m_a4.GetX(), (unsigned short)m_a4.GetY(), 0, false);
    draw->FUN_005e61e0(m_surface, 0, draw->FUN_005e5f60(0), 0);
    m_font = RHFontManager::FUN_005024f0()->GetFont(std::string("PopupScroll"));
    m_font->AttachToRenderContext(&m_ec, 0);
    m_2ac.m_renderer.FUN_0060e0d0(m_font, m_font, m_font, m_font);
}

// FUNCTION: GAME 0x00535f60
RHUnk00536360::~RHUnk00536360()
{
    RHPortraitRootLifetime::FUN_0061a920(&m_10c);
    RHPortraitRootLifetime::FUN_0061a920(&m_1dc);
    RHPortraitRootLifetime::FUN_0061a920(&m_2ac);
    RHPortraitRootLifetime::FUN_0061a920(&m_3ac);
    g_unk0x6c11d0->FUN_005e5160(m_surface);
    m_font->DetachFromRenderContext();
    delete m_font;
}

// SYNTHETIC: GAME 0x00535f40
// ??_GRHUnk00536360@@UAEPAXI@Z

// STUB: GAME 0x00536140
bool RHUnk00536360::FUN_00536140()
{
    bool initialized;
    {
        // STRING: GAME 0x006b0efc
        std::wstring title(L"Mission lost,won,start,interrupt");
        initialized = RHPortraitRootLifetime::FUN_0061a1e0(title,
            RHMapBox(0.0f, 0.0f, 629.0f, 480.0f), 0);
    }
    if (initialized) {
        FUN_0061a800(&m_3ac);
        FUN_0061a800(&m_2ac);
        FUN_0061a800(&m_10c);
        FUN_0061a800(&m_1dc);
        RHUnk005fc3b0 size;
        static_cast<RHMapResources *>(m_resource)->FUN_006006f0(0xed, size);
        RHPlayerProfileManager &profiles = RHPlayerProfileManagerStorage::mInstance;
        float height = reinterpret_cast<RHPlayerProfile *>(profiles.FUN_0055dbb0())->m_graphics.m_point.GetY();
        const RHGraphicConfig &graphics = reinterpret_cast<RHPlayerProfile *>(profiles.FUN_0055dbb0())->m_graphics;
        m_bounds.SetMin(SBGeoPoint2D((graphics.m_point.GetX() - size.GetX()) * 0.5f,
            (height - size.GetY()) * 0.5f));
        m_bounds.SetMax(m_bounds.Min().Unk005fc190(size));
        FUN_0061ad20(m_bounds);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00536360
void RHUnk00536360::FUN_00536360(const std::wstring &text)
{
    RHPortraitBitmapWidget *widget = &m_2ac;
    widget->SetWidgetText(text);
}

// STUB: GAME 0x00536380
void RHUnk00536360::FUN_00536380(char opening)
{
    if (opening) {
        FUN_0061a350(m_surface);
        m_ec.FUN_0061b710(m_surface);
        FUN_0050e5d0(1);
        m_c8 = false;
        SBGeoBoundingBox2D bounds(*(SBGeoBoundingBox2D *)FUN_0050e530());
        SBGeoPoint2D origin(0.0f, 0.0f);
        FUN_0061ac80(origin);
        FUN_0061a570();
        FUN_0061ac80(bounds.Min());
        FUN_0061a350(0);
        m_ec.FUN_0061b710(0);
    }
    m_c8 = true;
    m_c9 = opening != 0;
    if (!opening) {
        m_d0 = 0.05f;
        return;
    }
    if (m_c0)
        ((RHGame *)g_unk0x6c0b3c)->FUN_0050eca0(0);
    else
        ((RHGame *)g_unk0x6c0b3c)->FUN_0050eb80(0);
    m_d0 = 1.5f;
}

// FUNCTION: GAME 0x005364f0
void RHUnk00536360::FUN_005364f0(int message)
{
    m_bc = message;
}

// STUB: GAME 0x00536500
void RHUnk00536360::FUN_0061a570()
{
    if (!FUN_0050e5c0())
        return;
    if (m_c8) {
        if (!m_c9) {
            m_d0 *= 1.5f;
            if (m_d0 >= 1.0f)
                m_d0 = 0.8f;
        } else {
            m_d0 *= 0.6666667f;
        }

        SBGeoBoundingBox2D source;
        SBGeoBoundingBox2D target;
        SBGeoBoundingBox2D frame(*(SBGeoBoundingBox2D *)((char *)m_c4 + 0x30));
        target = SBGeoBoundingBox2D(0.0f, 0.0f, m_a4.m_x, m_a4.m_y);
        source.SetMin(m_bounds.Min().Unk005fc190(
            FUN_005fc580(m_bounds.Min().Unk005fc110(target.Min()), 1.0f - m_d0)));
        source.SetMax(m_bounds.Max().Unk005fc190(
            FUN_005fc580(m_bounds.Max().Unk005fc110(target.Max()), 1.0f - m_d0)));

        if (!m_c9) {
            if (m_d0 >= 0.8f) {
                m_c8 = false;
                FUN_0050e5d0(0);
                if (m_c0)
                    ((RHGame *)g_unk0x6c0b3c)->FUN_0050eca0(1);
                else
                    ((RHGame *)g_unk0x6c0b3c)->FUN_0050eb80(1);
            }
        } else if (m_d0 < 0.03f) {
            m_c8 = false;
            FUN_005368d0();
            return;
        }

        g_unk0x6c11d0->FUN_005e6440(m_surface, &source, m_display,
            m_d0 >= 0.05f ? &m_bounds : &frame, 1);
    } else {
        RHPortraitRootLifetime::FUN_0061a570();
    }
}

// STUB: GAME 0x005368d0
void RHUnk00536360::FUN_005368d0()
{
    RHMenuScreenView screen(0, 0, false, true, (char *)g_unk0x6c0b3c + 0x68);
    RHMenuYesNo dialog(&screen, *(const std::wstring *)((char *)this + 0x2bc));
    screen.FUN_0053be40(0);
    dialog.FUN_00545710();
    dialog.FUN_00544b80(true, true);
    if (dialog.FUN_00545ad0() == 1) {
        FUN_0050e5d0(0);
        if (m_c0)
            ((RHGame *)g_unk0x6c0b3c)->FUN_0050eca0(1);
        else
            ((RHGame *)g_unk0x6c0b3c)->FUN_0050eb80(1);
        RHUnk5490f0 message(m_bc);
        RHUnk00546050()->RHUnk005460c0(message);
    } else {
        FUN_00536380(0);
    }
}
