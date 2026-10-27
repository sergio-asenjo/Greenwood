#ifndef RHPORTRAITBUTTON_H
#define RHPORTRAITBUTTON_H

#include "RHPortraitButtonBase.h"
#include "RHPortraitAnimated.h"
#include "RHPortraitStrategyCalls.h"

class RHPortraitButton;
struct RHPortraitWidgetEvent;
struct RHPortraitWidgetInput;

class __declspec(novtable) RHPortraitButtonStrategy
{
public:
    RHPortraitButtonStrategy()
    {
        ((RHPortraitStrategyCalls *)this)->RHPortraitStrategyCalls::RHPortraitStrategyCalls();
    }
    virtual RHPortraitWidgetEvent *FUN_005d1de0();
    virtual RHPortraitButton *FUN_005d1f30();
    virtual void FUN_005d1f40(bool value);
    virtual int FUN_005d1f50(const SBGeoPoint2D &point);
    virtual int FUN_005d1ff0();
    virtual RHPortraitWidgetEvent *FUN_005d2370(bool value);
    virtual RHPortraitWidgetEvent *FUN_005d23d0(bool value);
};

// VTABLE: GAME 0x0067a054 RHPortraitButtonBase
// VTABLE: GAME 0x0067a08c RHPortraitButtonStrategy
class RHPortraitButton : public RHPortraitButtonBase, public RHPortraitAnimated, public RHPortraitButtonStrategy
{
public:
    RHPortraitButton();
    ~RHPortraitButton();
    void *FUN_005d1ce0(unsigned flags);
    bool FUN_005d1e30(int mode, const std::wstring &text, int resource);
    RHPortraitWidgetEvent *FUN_005d2000(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d2090(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d2120(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d21f0(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d22c0(const RHPortraitWidgetInput &input);
    int FUN_005d23f0();
    SBGeoBoundingBox2D &Box() { return *(SBGeoBoundingBox2D *)((char *)this + 0x30); }
    RHPortraitWidgetEvent &Event() { return *(RHPortraitWidgetEvent *)((char *)this + 0x4c); }
    void SetEnabled(bool enabled) { m_04 = enabled; }
    int m_f8;
    char m_fc;
};

#endif
