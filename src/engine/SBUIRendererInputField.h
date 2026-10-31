#ifndef SB_UI_RENDERER_INPUT_FIELD_H
#define SB_UI_RENDERER_INPUT_FIELD_H

#include "Decomp.h"
#include <string>

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
class SBGeoVector2D;

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    SBGeoPoint2D(const SBGeoPoint2D &);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &) const;
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &) const;
    float m_x; // 0x00
    float m_y; // 0x04
};
#endif

#ifndef SBGEO_VECTOR2D_VIEW
#define SBGEO_VECTOR2D_VIEW
// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float, float);
    SBGeoVector2D(const SBGeoPoint2D &);
    ~SBGeoVector2D() {}
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
    SBGeoBoundingBox2D(float, float, float, float);
    ~SBGeoBoundingBox2D() {}
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &) const;
    SBGeoBoundingBox2D &operator-=(const SBGeoVector2D &);
    bool FUN_006084a0(const SBGeoBoundingBox2D &);
    bool FUN_00608400(const SBGeoPoint2D &) const;
    SBGeoPoint2D m_00; // 0x00
    SBGeoPoint2D m_08; // 0x08
    char m_10; // 0x10
};
#endif

// SIZE 0x14
#include "RHMapBox.h"

class RHMobileUnk006100e0;

#include "SBGeoSegment2D.h"

#include "RHMobileUnk006100e0.h"

#include "RHMobileUnk00607da0.h"

#include "SBUIInputFieldBoxCalls.h"

// SIZE 0x30
class SBUIInputFieldDrawUnk
{
public:
    SBUIInputFieldDrawUnk();
    bool FUN_00614bf0(void *, std::wstring *, const SBGeoPoint2D &, unsigned int);
    void FUN_00614d70(char value);
    unsigned short FUN_00614230(void *, std::wstring *, const SBGeoBoundingBox2D &, unsigned int, unsigned int, unsigned int);
    void FUN_00613c90(void *, void *, void *, void *);
    unsigned short FUN_00613ea0(void *, std::wstring *, const SBGeoBoundingBox2D &, unsigned int, unsigned int);
    RHMapBox *FUN_00613e70();
    unsigned int FUN_00613e80();
    std::wstring m_00; // 0x00
    undefined4 m_10; // 0x10
    char m_14; // 0x14
    unsigned int m_18; // 0x18
    RHMapBox m_1c; // 0x1c
};

// SIZE 0x10
struct SBUIInputFieldNode
{
    SBUIInputFieldNode *m_00; // 0x00
    SBUIInputFieldNode *m_04; // 0x04
    undefined2 m_08; // 0x08
    undefined2 m_0a; // 0x0a
    unsigned int m_0c; // 0x0c
};

// SIZE 0x20
class SBUIInputFieldTextUnk
{
public:
    undefined m_00[8]; // 0x00
    SBUIInputFieldNode *m_08; // 0x08
    undefined4 m_0c; // 0x0c
    SBUIInputFieldNode *m_10; // 0x10
    void *m_14; // 0x14
    undefined4 m_18; // 0x18
    char m_1c; // 0x1c

    unsigned int FUN_0061dd00();
    std::wstring FUN_0061dd50(unsigned int, unsigned int);
    char FUN_0061e230();
    unsigned int FUN_0061df50();
    void FUN_0061e320(unsigned char);
    void FUN_0061e2b0(unsigned int);
};

// SIZE 0x04
class SBUIInputFieldUnkObject
{
public:
    virtual void v0() = 0; // vtable+0x00
    virtual void v1() = 0; // vtable+0x04
    virtual void v2(unsigned int) = 0; // vtable+0x08
};

// SIZE 0x1c
struct SBUIInputFieldUnkResource
{
    undefined m_00[0x14]; // 0x00
    SBUIInputFieldUnkObject *m_14; // 0x14
    void *m_18; // 0x18
};

// SIZE 0x90
class SBUIInputFieldUnk00621440
{
public:
    undefined m_00[0x64]; // 0x00
    SBUIInputFieldUnkObject *m_64; // 0x64
    void *m_68; // 0x68
    SBUIInputFieldUnkResource *m_6c; // 0x6c
    SBGeoBoundingBox2D m_70; // 0x70
    char m_84; // 0x84
    SBGeoVector2D m_88; // 0x88

    void FUN_00621440(SBUIInputFieldUnkResource *);
    bool FUN_00621470(unsigned int);
    bool FUN_00621c30(const SBGeoBoundingBox2D &);
    void FUN_0061e4b0();
    std::wstring FUN_0061df60();
    void FUN_0061e340();
};

std::wstring FUN_005d0880(const std::wstring &, const std::wstring &);
int FUN_00613c50(const unsigned short *, const unsigned short *, unsigned int);
bool FUN_00613e40(unsigned char, unsigned int, const void *, const void *);
bool FUN_006141e0(void *, const std::wstring &, float);
unsigned int FUN_00613940(void *, int **, int **, int **, int **, unsigned char *, unsigned int, int);

#endif
