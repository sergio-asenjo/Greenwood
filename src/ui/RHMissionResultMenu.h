#ifndef RHMISSIONRESULTMENU_H
#define RHMISSIONRESULTMENU_H

#include "RHPortraitRootLifetime.h"
#include "RHGameWidgetLifetime.h"
#include "RHUnk005fc3b0.h"
#include "SBUIUnkSurface.h"

class SBFontUnk0061e840;

// VTABLE: GAME 0x006796d4
// SIZE 0x478
class RHUnk00536360 : public RHPortraitRootLifetime
{
public:
    RHUnk00536360();
    virtual ~RHUnk00536360();
    virtual void FUN_0061a570();
    bool FUN_00536140();
    void FUN_00536360(const std::wstring &text);
    void FUN_00536380(char opening);
    void FUN_005364f0(int message);
    void FUN_005368d0();

    unsigned long m_surface;
    RHUnk005fc3b0 m_a4;
    std::string m_ac;
    int m_bc;
    char m_c0;
    undefined m_c1[3];
    RHGameWidgetLifetimeBase *m_c4;
    bool m_c8;
    bool m_c9;
    undefined m_ca[2];
    unsigned long m_cc;
    float m_d0;
    SBGeoBoundingBox2D m_bounds;
    SBFontUnk0061e840 *m_font;
    SBUIUnkSurface m_ec;
    RHGameLifetime00515d30 m_10c;
    RHGameLifetime00515d30 m_1dc;
    RHGameLifetime00525560 m_2ac;
    RHGameLifetime00515f00 m_3ac;
};

#endif
