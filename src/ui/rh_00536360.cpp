#include "SBNullstr.h"
#include "RHPortraitRootLifetime.h"
#include "RHGameWidgetLifetime.h"
#include "SBUIUnkSurface.h"
#include "SBGeoPoint2D.h"
#include "SBDrawManagerCore.h"
#include "SBFont.h"
#include "RHMenuScreenView.h"
#include "RHMenuWindow.h"
#include "RHMessenger.h"
#include "RHGame.h"
#include <stddef.h>
#include <string>

class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;
extern SBDrawManager *g_unk0x6c11d0;
RHMessenger *RHUnk00546050();
SBGeoVector2D FUN_005fc580(const SBGeoVector2D &point, float factor);

class RHUnk00536360Sub
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c(int arg);
};

// VTABLE: GAME 0x006796d4
// SIZE 0x478
class RHUnk00536360 : public RHPortraitRootLifetime
{
public:
    virtual ~RHUnk00536360();
    virtual void FUN_0061a570();
    void FUN_00536360(int arg);
    void FUN_00536380(char opening);
    void FUN_005368d0();

    unsigned long m_surface;
    SBGeoPoint2D m_a4;
    std::string m_ac;
    void *m_bc;
    bool m_c0;
    undefined m_c1[3];
    void *m_c4;
    bool m_c8;
    bool m_c9;
    undefined m_ca[6];
    float m_d0;
    SBGeoBoundingBox2D m_bounds;
    SBFontUnk0061e840 *m_font;
    SBUIUnkSurface m_ec;
    RHGameLifetime00515d30 m_10c;
    RHGameLifetime00515d30 m_1dc;
    RHGameLifetime00525560 m_2ac;
    RHGameLifetime00515f00 m_3ac;
};

DECOMP_SIZE_ASSERT(RHUnk00536360, 0x478)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_a4) == 0xa4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_ac) == 0xac)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_d0) == 0xd0)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_c4) == 0xc4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_c8) == 0xc8)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_bounds) == 0xd4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_font) == 0xe8)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_ec) == 0xec)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_10c) == 0x10c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_1dc) == 0x1dc)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_2ac) == 0x2ac)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00536360, m_3ac) == 0x3ac)

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

// FUNCTION: GAME 0x00536360
void RHUnk00536360::FUN_00536360(int arg)
{
    ((RHUnk00536360Sub *)&m_2ac)->V2c(arg);
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
        RHUnk5490f0 message((int)m_bc);
        RHUnk00546050()->RHUnk005460c0(message);
    } else {
        FUN_00536380(0);
    }
}
