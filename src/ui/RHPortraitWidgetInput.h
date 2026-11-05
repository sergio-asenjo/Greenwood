#ifndef RHPORTRAITWIDGETINPUT_H
#define RHPORTRAITWIDGETINPUT_H

#include "Decomp.h"
#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include "SBUIKeyboardCalls.h"

class RHPortraitUnk005d3880;

struct RHPortraitWidgetUI
{
    undefined m_00[0x17f0];
    RHPortraitUnk005d3880 *m_selected;
    RHPortraitUnk005d3880 *m_captured;
    void Clear()
    {
        m_selected = 0;
        m_captured = 0;
    }
};

struct RHPortraitWidgetInput
{
    SBGeoPoint2D point;
    short wheel;
    unsigned short flags;
    RHGameWidgetInputCalls *shortcuts;
    RHPortraitWidgetUI *ui;
};

#endif
