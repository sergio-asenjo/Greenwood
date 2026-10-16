#ifndef RH_DRAW_MANAGER_H
#define RH_DRAW_MANAGER_H

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &other) const;
    SBGeoPoint2D &FUN_005fc1e0(const SBGeoPoint2D &other);
    float m_x; // 0x00
    float m_y; // 0x04
};

extern float g_unk0x00677488;
extern float g_unk0x0067749c;
extern double g_unk0x006774b8;
extern float g_actorStepScale;
extern double g_unk0x00677670;

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float x, float y);
    SBGeoVector2D(const SBGeoPoint2D &other);
};

SBGeoVector2D operator*(float factor, const SBGeoVector2D &point);

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other);
    RHUnk005fc3b0 &FUN_005fc4d0(float factor);
    float Unk005fc6a0(float value);
};

class RHMobileUnk0060a820
{
public:
    RHMobileUnk0060a820 &FUN_0060a820(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
};

class RHMobileUnk006100e0
{
public:
    ~RHMobileUnk006100e0();
};

// SIZE 0x10
class SBGeoSegment2D
{
public:
    SBGeoSegment2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
    {
        ((RHMobileUnk0060a820 *)this)->FUN_0060a820(first, second);
    }
    ~SBGeoSegment2D()
    {
        ((RHMobileUnk006100e0 *)this)->~RHMobileUnk006100e0();
    }
    SBGeoPoint2D &First() { return *(SBGeoPoint2D *)&m_00[0]; }
    SBGeoPoint2D &Second() { return *(SBGeoPoint2D *)&m_00[8]; }
    unsigned char m_00[0x10]; // 0x00
};

#include "SBGeoPolyLine2DList.h"

// SIZE 0x0c
class RHUnk0060fbf0
{
public:
    RHUnk0060fbf0();
    ~RHUnk0060fbf0();
    RHUnk0060fbf0 &FUN_0060fca0(const RHUnk0060fbf0 &other);
    unsigned char m_00[0x0c]; // 0x00
};

class RHUnk0053bf20
{
public:
    void *FUN_0053bf20() const;
};

class SCQuadArg
{
public:
    unsigned char GetType();
};

class RHUnk00608f10
{
public:
    int FUN_00608f10(void *value);
};

class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D &FUN_00607da0(const SBGeoBoundingBox2D &other);
    bool Unk00608f30() const;
    int FUN_00609050(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    void SetMin(const SBGeoPoint2D &point)
    {
        m_10 = true;
        m_min = point;
    }
    void SetMax(const SBGeoPoint2D &point)
    {
        m_10 = true;
        m_max = point;
    }
    void FUN_006092a0(const SBGeoVector2D &offset);
    SBGeoBoundingBox2D FUN_006092c0(const SBGeoBoundingBox2D &other) const;
    RHUnk0060fbf0 FUN_006093f0(const SBGeoSegment2D &segment) const;
    SBGeoPoint2D m_min; // 0x00
    SBGeoPoint2D m_max; // 0x08
    bool m_10; // 0x10
};

// SIZE 0x14
class SBDrawViewport
{
public:
    unsigned char m_00[4]; // 0x00
    unsigned short m_width; // 0x04
    unsigned short m_height; // 0x06
    unsigned long m_pitch; // 0x08
    unsigned char m_0c[4]; // 0x0c
    unsigned short *m_pixels; // 0x10
};

class SBDrawManager
{
public:
    unsigned char m_00[0x10c]; // 0x000
    unsigned short m_10c; // 0x10c
    void FUN_005e61e0(unsigned long surface, const SBGeoBoundingBox2D &box, unsigned short color, unsigned long flags);
    bool FUN_005ecbd0(unsigned long surface, const SBGeoPoint2D &first, const SBGeoPoint2D &second, unsigned short color);
};

// SIZE 0x20
class RHDrawManager : public SBGeoBoundingBox2D
{
public:
    RHDrawManager(SBDrawManager *drawManager);
    bool CheckPointForDrawing(short x, short y, unsigned short width, unsigned short height);
    void DrawSegment(const SBGeoSegment2D &segment, unsigned short color);
    void DrawPolyLine(const SBGeoPolyLine2DList &list, unsigned short color);
    void FillBox(const SBGeoBoundingBox2D &box, unsigned short color);
    void DrawEllipsePoints(const SBDrawViewport &viewport, const SBGeoPoint2D &center, short x, short y, unsigned short color);
    void DrawDottedLine(const SBGeoPoint2D &from, const SBGeoPoint2D &to, float &phase, float dash, float thickness, unsigned short color);
    unsigned short GetPackedColor(unsigned long color);
    void DrawEllipse(const SBDrawViewport &viewport, const SBGeoPoint2D &center, unsigned short radius, unsigned short color);
    void DrawCircle(const SBDrawViewport &viewport, const SBGeoPoint2D &center, unsigned short radius, unsigned short color);

    static RHDrawManager *mpDrawManager;

    float m_14; // 0x14
    unsigned long m_18; // 0x18
    SBDrawManager *m_drawManager; // 0x1c
};

#endif
