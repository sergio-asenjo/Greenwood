#ifndef RHPORTRAITUNK005D3880_H
#define RHPORTRAITUNK005D3880_H

#include "Decomp.h"
#include <string>

class SBGeoPoint2D;
struct RHPortraitWidgetInput;

struct RHPortraitWidgetEvent
{
    int type;
    void *widget;
    int value;
    RHPortraitWidgetEvent *next;
};

class RHPortraitUnk005d3880
{
public:
    int FUN_005d3880(const SBGeoPoint2D &point);
    RHPortraitWidgetEvent *FUN_005d3a10(const RHPortraitWidgetInput &input);
    void FUN_005d3a60(const RHPortraitWidgetInput &input);
    void FUN_005d3a80(const void *stop);
    void FUN_005d3ab0(RHPortraitUnk005d3880 *linked);
    bool FUN_005d3b00(char value);
    void *FUN_005d3b10();
    RHPortraitWidgetEvent *FUN_005d3b20(const void *input);
    int FUN_005d3b60(const SBGeoPoint2D &point);
    int FUN_005d4db0(const SBGeoPoint2D &point);
    RHPortraitWidgetEvent *FUN_005d4d60(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d4e50(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d4ec0(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d4f30(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d4f80(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d4fe0(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d4cb0(const RHPortraitWidgetInput &input);
    bool FUN_005d4bb0(int mode, const std::wstring &text, const SBGeoPoint2D &origin, int resource);
    int FUN_005d5230();
    int FUN_005d52d0();
    RHPortraitWidgetEvent *FUN_005d53b0(const RHPortraitWidgetInput &input);
    undefined m_00[0x4c];
    RHPortraitWidgetEvent m_event;
    undefined m_5c[0x7c - 0x5c];
    int m_state;
    undefined m_80[0xb8 - 0x80];
    void *m_b8;
    undefined m_bc[0xd8 - 0xbc];
    char m_selected;
    undefined m_d9[0x110 - 0xd9];
    RHPortraitUnk005d3880 *m_linked;
};

#endif
