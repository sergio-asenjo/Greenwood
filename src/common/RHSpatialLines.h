#ifndef RHSPATIALLINES_H
#define RHSPATIALLINES_H

#include "RHUnk0051f0f0.h"
#include "RHUnk005fc3b0.h"

class __declspec(novtable) RHUnk005214b0 : public RHUnk0051f0f0
{
public:
    void *FUN_005214d0(unsigned flags);
    RHUnk005214b0();
    virtual ~RHUnk005214b0();
    void SetSector(unsigned short sector) { m_20 = sector; }
    unsigned short m_20;
};

// VTABLE: GAME 0x006790f8
class RHMobileUnk0051fd10 : public RHUnk005214b0
{
public:
    RHMobileUnk0051fd10(float first, float second);
    virtual ~RHMobileUnk0051fd10();
    virtual void FUN_00520480(SBDrawManager *draw, SBGeoBoundingBox2D box, float scale, unsigned short color);
    void FUN_0051fdc0();
    bool FUN_0051fea0(const SBGeoPoint2D &point, float &distance);
    float m_24;
    float m_28;
    float m_2c;
    float m_30;
    RHUnk005fc3b0 m_34;
    RHUnk005fc3b0 m_3c;
};

class __declspec(novtable) RHUnk0051fc10 : public RHUnk0051f0f0
{
public:
    RHUnk0051fc10();
    ~RHUnk0051fc10();
    void *FUN_0051fc40(unsigned flags);
    char m_20;
    char m_21[3];
    int m_24;
    int m_28;
    int m_2c;
    int m_30;
};

class __declspec(novtable) RHUnk00521500 : public RHUnk0051f0f0
{
public:
    void *FUN_00521520(unsigned flags);
    RHUnk00521500();
    ~RHUnk00521500();
    void SetTarget(void *target) { m_20 = target; }
    void *m_20;
};

#endif
