#ifndef RHUIRENDERER_005CADC0_H
#define RHUIRENDERER_005CADC0_H

#include "Decomp.h"
#include <string>

class SBGeoPoint2D
{
public:
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    float m_x; // 0x00
    float m_y; // 0x04
};

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

// SIZE 0x14
class RHMapBox
{
public:
    RHMapBox(float, float, float, float);
    SBGeoPoint2D m_0; // 0x00
    SBGeoPoint2D m_8; // 0x08
    bool m_10;        // 0x10
};

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

class RHPortraitTextResourceCalls
{
public:
    void *FUN_0053be80(const std::string &name);
};

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

// SIZE 0x50
class RHPortraitRenderer0060dab0
{
public:
    RHPortraitRenderer0060dab0();
    ~RHPortraitRenderer0060dab0();
    undefined4 m_vptr;      // 0x00
    undefined m_04[0x24];   // 0x04
    std::wstring m_text;    // 0x28
    undefined m_38[0x18];   // 0x38
};

// SIZE 0x58
class RHPortraitRenderer005cadc0 : public RHPortraitRenderer0060dab0
{
public:
    RHPortraitRenderer005cadc0();
    ~RHPortraitRenderer005cadc0();
    void *FUN_005cade0(unsigned flags);
    SBUIListboxUnk0061e890 *m_enabled;  // 0x50
    SBUIListboxUnk0061e890 *m_disabled; // 0x54
};

class RHPortraitRendererCalls : public RHPortraitRenderer005cadc0
{
public:
    void FUN_005cae10(int screen);
    bool FUN_005cafa0(unsigned id);
};

#endif
