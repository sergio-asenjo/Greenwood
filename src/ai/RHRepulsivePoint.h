#ifndef RHREPULSIVEPOINT_H
#define RHREPULSIVEPOINT_H

#include "SB.h"
#include "Decomp.h"
#include "RHFastFindGeometry.h"

// SIZE 0x14
class __declspec(novtable) RHUnk005209d0 : public SBGeoPoint2D
{
public:
    RHUnk005209d0(int type);
    RHUnk005209d0(SBGeoPoint2D point, int type);
    RHUnk005209d0(const RHUnk005209d0 &other)
        : SBGeoPoint2D(other), m_0c(other.m_0c), m_10(other.m_10)
    {
        *(unsigned *)this = 0x678b58;
    }
    virtual ~RHUnk005209d0(); // vtable+0x00
    void *FUN_004fdc70(unsigned flags);
    int m_0c; // +0x0c
    undefined m_10; // +0x10
};

// VTABLE: GAME 0x00678b54
// SIZE 0x40
class RHUnk00520ae0 : public RHUnk005209d0
{
public:
    RHUnk00520ae0();
    RHUnk00520ae0(const SBGeoPoint2D &point, float first, float second);
    virtual ~RHUnk00520ae0(); // vtable+0x00
    void FUN_00520c80(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    RHUnk005fc3b0 m_14; // +0x14
    RHUnk005fc3b0 m_1c; // +0x1c
    int m_24;
    int m_28;
    int m_2c;
    int m_30;
    undefined m_34; // +0x34
    undefined m_35; // +0x35
    undefined m_36; // +0x36
    undefined m_37; // +0x37
    undefined m_38; // +0x38
    unsigned long m_id; // +0x3c
};

#endif
