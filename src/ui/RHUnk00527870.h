#ifndef RHUNK00527870_H
#define RHUNK00527870_H

#include <windows.h>
#include "RHGameWidgetLifetime.h"

// VTABLE: GAME 0x00679270
class RHUnk00527870 : public RHGameLifetime00516430
{
public:
    RHUnk00527870() : m_cc(false), m_cd(false), m_d0(GetTickCount()), m_d4(0), m_d8(0), m_dc(true) {}
    ~RHUnk00527870() {}
    void *FUN_00528c70(unsigned flags);
    bool m_cc;
    bool m_cd;
    unsigned long m_d0;
    int m_d4;
    int m_d8;
    bool m_dc;
};

// SIZE 0x278
class RHUnk005276d0
{
public:
    RHUnk005276d0();
    ~RHUnk005276d0();
    RHUnk00527870 m_location;
    RHGameLifetime00515f00 m_e0;
    RHGameLifetime00515f00 m_1ac;
};

#endif
