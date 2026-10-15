#ifndef RHUIRENDERER_005CB220_H
#define RHUIRENDERER_005CB220_H

#include "Decomp.h"

class SBGeoPoint2D
{
public:
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    float m_x; // 0x00
    float m_y; // 0x04
};

class SBGeoVector2D : public SBGeoPoint2D
{
};

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    void SetMax(const SBGeoPoint2D &point)
    {
        m_10 = true;
        m_max = point;
    }
    SBGeoPoint2D m_min;   // 0x00
    SBGeoPoint2D m_max;   // 0x08
    bool m_10;            // 0x10
    undefined m_11[3];    // 0x11
};

class RHUnk005ef320
{
public:
    void FUN_005e57e0(unsigned surface, SBGeoVector2D &size);
    bool FUN_005e6440(unsigned long surface, int source, unsigned long target, SBGeoBoundingBox2D *box, int flags);
};

class SBUIUnk006006f0
{
public:
    bool FUN_006006f0(long, RHUnk005fc3b0 &);
};

// SIZE 0x4c
class SBUIUnk0060da20
{
public:
    bool FUN_0060da20(unsigned int id);
    undefined4 m_vptr;              // 0x00
    SBUIUnk006006f0 *m_resource;    // 0x04
    SBGeoBoundingBox2D m_box;       // 0x08
    RHUnk005ef320 *m_draw;          // 0x1c
    unsigned long m_target;         // 0x20
    undefined m_24[0x14];           // 0x24
    long m_resourceId;              // 0x38
    undefined m_3c[4];              // 0x3c
    long m_40;                      // 0x40
    long m_44;                      // 0x44
    undefined m_48[4];              // 0x48
};

class RHPictureRenderer0060d9f0 : public SBUIUnk0060da20
{
public:
    RHPictureRenderer0060d9f0();
};

// SIZE 0x50
class RHGameRenderer005cb220 : public RHPictureRenderer0060d9f0
{
public:
    RHGameRenderer005cb220();
    ~RHGameRenderer005cb220();
    void *FUN_005cb240(unsigned flags);
    long m_alternate; // 0x4c
};

class RHGameWidgetRendererCalls : public RHGameRenderer005cb220
{
public:
    bool FUN_005cb270(unsigned id);
};

class RHPortraitRendererCalls : public RHGameRenderer005cb220
{
public:
    void FUN_005cb2a0();
    void FUN_005cb2b0(int value);
};

#endif
