#include "SBNullstr.h"
#include "RHMenuBuyBlazons.h"
#include "RHMenuScreenView.h"
#include "RHMapBox.h"
#include "SBUIRenderer.h"

extern wchar_t g_unk0x006c0b50[1];
std::wstring FUN_005e23d0(unsigned long);

class RHBuyBlazonsWidgetCalls
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
    virtual void V2c();
    virtual bool V30(const std::wstring &, const RHMapBox &, unsigned, unsigned);
};

inline void RHBuyBlazonsSetText(RHPortraitButton &button, const std::wstring &text)
{
    typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
    Assign assign = &std::wstring::assign;
    *((bool *)&button + 8) = true;
    (((std::wstring *)((char *)&button + 0x20))->*assign)(text, 0, std::wstring::npos);
}

DECOMP_SIZE_ASSERT(RHMenuBuyBlazons, 0x44c)

// Parked at 0.8023: first string boundary and register scheduling differ.
// STUB: GAME 0x00524990
RHMenuBuyBlazons::RHMenuBuyBlazons(RHMenuWindow *parent, RHMenuWindowScreen *screen)
    : RHMenuWindowFocus(parent, screen, 0xed, 1, true), m_444(0),
      m_448(screen->FUN_0053be80(std::string("Debrief")))
{
    m_cancel.FUN_005d1e30((int)m_screen, std::wstring(g_unk0x006c0b50), 0x92);
    m_ok.FUN_005d1e30((int)m_screen, std::wstring(g_unk0x006c0b50), 0x91);
    {
        const std::wstring price(
            // STRING: GAME 0x006b0900
            L"Price");
        ((RHBuyBlazonsWidgetCalls *)&m_title)->V30(price, RHMapBox(50.0f, 50.0f, 350.0f, 125.0f), 0, unsigned(-1));
    }
    RHBuyBlazonsSetText(m_ok, FUN_005e23d0(0x14a));
    RHBuyBlazonsSetText(m_cancel, FUN_005e23d0(0x14b));
    ((SBUIUnk0060dd00 *)&m_title.m_renderer)->FUN_0060e0d0(parent, parent, parent, parent);
    *(bool *)((char *)&m_title + 0xf8) = true;
}

// FUNCTION: GAME 0x00524cf0
void *RHMenuBuyBlazons::FUN_00524cf0(unsigned flags)
{
    this->~RHMenuBuyBlazons();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00524d10
RHMenuBuyBlazons::~RHMenuBuyBlazons()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_ok);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_title);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_cancel);
}
