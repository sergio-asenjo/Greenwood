#ifndef RHPORTRAITINPUTRENDERER_H
#define RHPORTRAITINPUTRENDERER_H

#include "RHPortraitRenderer0060d470.h"

class SBFontUnk0061e840;

// VTABLE: GAME 0x0067ae1c
// SIZE 0x84
class RHPortraitInputRenderer : public RHPortraitRenderer0060d470
{
public:
    RHPortraitInputRenderer();
    ~RHPortraitInputRenderer();
    int CurrentRenderCode() const;
    int ResolveRenderCode(unsigned id);
    void *FUN_0061c590(unsigned flags);
    bool FUN_0061c610(unsigned long surface);
    bool FUN_0061d570(unsigned short position, int limit);
    unsigned FUN_0061d5e0();
    SBGeoBoundingBox2D FUN_0061d3f0(unsigned short line, int value);
    SBGeoBoundingBox2D FUN_0061d7c0();
    SBGeoBoundingBox2D FUN_0061d620();
    unsigned FUN_0061d950();
    bool FUN_0061d1c0();
    bool FUN_0061d1d0(std::wstring *text, unsigned flags);
    bool FUN_0061d980(SBFontUnk0061e840 *normal, SBFontUnk0061e840 *focused,
        SBFontUnk0061e840 *selected, bool alternate);
    SBFontUnk0061e840 *m_4c;
    SBFontUnk0061e840 *m_50;
    SBFontUnk0061e840 *m_54;
    SBFontUnk0061e840 *m_58;
    SBFontUnk0061e840 *m_5c;
    SBFontUnk0061e840 *m_60;
    int m_64;
    int m_68;
    SBGeoPoint2D m_6c;
    char m_74[0xa];
    unsigned short m_7e;
    unsigned short m_80;
    unsigned short m_82;
};

#endif
