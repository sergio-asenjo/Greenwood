#ifndef RHUIRENDERER_005CADC0_H
#define RHUIRENDERER_005CADC0_H

#include "Decomp.h"
#include <string>
#include "RHMenuScreenView.h"

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    float m_x; // 0x00
    float m_y; // 0x04
};
#endif

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#define SBGEO_BOUNDINGBOX2D_VIEW
// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &other);
    ~SBGeoBoundingBox2D() {}
    void SetMinY(float y)
    {
        m_00.m_y = y;
        m_10 = true;
    }
    void SetMaxY(float y)
    {
        m_08.m_y = y;
        m_10 = true;
    }
    SBGeoPoint2D m_00; // 0x00
    SBGeoPoint2D m_08; // 0x08
    bool m_10;         // 0x10
};
#endif

// SIZE 0x14
#include "RHMapBox.h"

#include "RHPortraitRenderer005cadc0.h"

class SBUIListboxUnk0061e890
{
public:
    int FUN_0061e890();
};

// SIZE 0x30
class SBUIInputFieldDrawUnk
{
public:
    SBUIInputFieldDrawUnk();
    unsigned short FUN_00614230(void *, std::wstring *, const SBGeoBoundingBox2D &, unsigned int, unsigned int, unsigned int);
    std::wstring m_00; // 0x00
    undefined4 m_10;   // 0x10
    char m_14;         // 0x14
    unsigned int m_18; // 0x18
    RHMapBox m_1c;     // 0x1c
};

typedef RHMenuScreenView RHPortraitTextResourceCalls;

class SBUIUnk0060d530
{
public:
    void *FUN_0060d690();
};

class SBUIUnk0060dae0
{
public:
    bool FUN_0060dae0(unsigned int id);
};

#endif
