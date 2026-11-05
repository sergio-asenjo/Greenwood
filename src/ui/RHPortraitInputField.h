#ifndef RHPORTRAITINPUTFIELD_H
#define RHPORTRAITINPUTFIELD_H

#include "Decomp.h"
#include "RHPortraitUnk005d3880.h"
#include "RHPortraitInputRenderer.h"

class RHPortraitBoxEvent;

class RHPortraitInputField
{
public:
    void FUN_005cf300();
    void FUN_005cf380();
    RHPortraitBoxEvent *FUN_005cf880(unsigned value);
    RHPortraitWidgetEvent *FUN_005cf980(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d0a10(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d0a90(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d0d00(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d1090(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d1270(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d14e0(const RHPortraitWidgetInput &input);
    bool FUN_005d1630(const RHPortraitWidgetInput &input, unsigned short key);
    void FUN_005d1670();
    void FUN_005d1700();
    bool FUN_005d1790(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d1810(const RHPortraitWidgetInput &input);
    unsigned short FUN_005d18f0(const SBGeoPoint2D &point);
    RHPortraitInputRenderer &Renderer() { return *(RHPortraitInputRenderer *)((char *)this + 0x80); }
    undefined m_00[0x4c];
    RHPortraitWidgetEvent m_event;
    undefined m_5c[0x7c - 0x5c];
    int m_state;
    undefined m_80[0x10c - 0x80];
    int m_10c;
    undefined m_110[0x13c - 0x110];
    unsigned m_13c;
    undefined m_140[0x188 - 0x140];
    unsigned short m_188;
    unsigned short m_18a;
    unsigned short m_18c;
};

#endif
