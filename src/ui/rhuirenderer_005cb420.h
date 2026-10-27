#ifndef RHUIRENDERER_005CB420_H
#define RHUIRENDERER_005CB420_H

#include "Decomp.h"
#include <string>

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
class SBGeoVector2D;
class SBGeoPoint2D
{
public:
    ~SBGeoPoint2D();
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    float m_x; // 0x00
    float m_y; // 0x04
};
#endif

#if !defined(SBGEO_VECTOR2D_VIEW) && !defined(SBGEOVECTOR2D_H)
#define SBGEO_VECTOR2D_VIEW
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float x, float y);
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};
#endif

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#define SBGEO_BOUNDINGBOX2D_VIEW
// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &other);
    ~SBGeoBoundingBox2D() {}
    SBGeoBoundingBox2D &FUN_00607da0(const SBGeoBoundingBox2D &other);
    bool FUN_006083b0(const SBGeoPoint2D &point) const;
    void SetMaxX(float x)
    {
        m_10 = true;
        m_08.m_x = x;
    }
    void SetMinY(float y)
    {
        m_10 = true;
        m_00.m_y = y;
    }
    void SetMaxY(float y)
    {
        m_10 = true;
        m_08.m_y = y;
    }
    SBGeoPoint2D m_00; // 0x00
    SBGeoPoint2D m_08; // 0x08
    bool m_10;         // 0x10
};
#endif

#include "RHPortraitRenderer0060dab0.h"

// SIZE 0x14
#include "RHMapBox.h"

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
    unsigned short FUN_00614230(void *, std::wstring *, const SBGeoBoundingBox2D &, unsigned int, unsigned short, unsigned int);
    unsigned int FUN_00613e80();
    std::wstring &FUN_00613e90();
    std::wstring m_00; // 0x00
    undefined4 m_10;   // 0x10
    char m_14;         // 0x14
    unsigned int m_18; // 0x18
    RHMapBox m_1c;     // 0x1c
};

#include "RHPopupRenderer0060dbc0.h"

// SIZE 0x9c
// VTABLE: GAME 0x00679e9c
class RHUnk005cba10 : public RHPopupRenderer0060dbc0
{
public:
    RHUnk005cba10();
    void *FUN_005cb4a0(unsigned flags);
    SBGeoBoundingBox2D FUN_005cb550(SBUIListboxUnk0061e890 *font, bool clip) const;
    void FUN_005cb700(SBUIListboxUnk0061e890 *font);
    void FUN_005cb9d0(unsigned long width, unsigned long height);
    bool FUN_005cba10(unsigned id);
    SBGeoVector2D m_dropped;    // 0x7c
    std::wstring m_rendered;    // 0x84
    unsigned int m_characters;  // 0x94
    unsigned int m_lines;       // 0x98
};

// SYNTHETIC: GAME 0x005cb4c0
// RHUnk005cba10::~RHUnk005cba10

#endif
