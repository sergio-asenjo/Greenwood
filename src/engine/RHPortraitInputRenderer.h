#ifndef RHPORTRAITINPUTRENDERER_H
#define RHPORTRAITINPUTRENDERER_H

#include "RHPortraitRenderer0060d470.h"

// VTABLE: GAME 0x0067ae1c
// SIZE 0x84
class RHPortraitInputRenderer : public RHPortraitRenderer0060d470
{
public:
    RHPortraitInputRenderer();
    ~RHPortraitInputRenderer();
    void *FUN_0061c590(unsigned flags);
    void FUN_0061c610(unsigned long surface);
    bool FUN_0061d570(unsigned short position, int limit);
    unsigned FUN_0061d5e0();
    SBGeoBoundingBox2D FUN_0061d3f0(unsigned short line, int value);
    SBGeoBoundingBox2D FUN_0061d7c0();
    SBGeoBoundingBox2D FUN_0061d620();
    unsigned FUN_0061d950();
    char m_4c[0x18];
    int m_64;
    int m_68;
    SBGeoPoint2D m_6c;
    char m_74[0xe];
    unsigned short m_82;
};

#endif
