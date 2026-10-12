#ifndef SB_UI_RENDERER_INPUT_FIELD_H
#define SB_UI_RENDERER_INPUT_FIELD_H

#include "Decomp.h"
#include <string>

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    SBGeoPoint2D(const SBGeoPoint2D &);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &) const;
    float m_x; // 0x00
    float m_y; // 0x04
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(const SBGeoPoint2D &);
    ~SBGeoVector2D() {}
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    ~SBGeoBoundingBox2D() {}
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &) const;
    bool FUN_006084a0(const SBGeoBoundingBox2D &);
    SBGeoPoint2D m_00; // 0x00
    SBGeoPoint2D m_08; // 0x08
    char m_10; // 0x10
};

// SIZE 0x14
class RHMapBox
{
public:
    RHMapBox(float, float, float, float);
    SBGeoPoint2D m_0; // 0x00
    SBGeoPoint2D m_8; // 0x08
    bool m_10; // 0x10
};

class RHMobileUnk0060a820
{
public:
    RHMobileUnk0060a820 &FUN_0060a820(const SBGeoPoint2D &, const SBGeoPoint2D &);
};

// SIZE 0x10
class RHMobileUnk006100e0 : public SBGeoPoint2D
{
public:
    ~RHMobileUnk006100e0();
    undefined m_08[8]; // 0x08
};

// SIZE 0x14
class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &);
    undefined m_00[0x14]; // 0x00
};

class SBUIInputFieldBoxCalls
{
public:
    bool FUN_00608450(const SBGeoBoundingBox2D &);
    void FUN_0060a860(const RHMobileUnk006100e0 &);
};

// SIZE 0x30
class SBUIInputFieldDrawUnk
{
public:
    SBUIInputFieldDrawUnk();
    bool FUN_00614bf0(void *, std::wstring *, const SBGeoPoint2D &, unsigned int);
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
class RHMapWideText
{
public:
    RHMapWideText() { Tidy(false); }
    RHMapWideText(const RHMapWideText &other) : m_allocator(other.m_allocator)
    {
        Tidy(false);
        typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
        Assign assign = &std::wstring::assign;
        (((std::wstring *)this)->*assign)((const std::wstring &)other, 0, std::wstring::npos);
    }
    ~RHMapWideText()
    {
        if (m_chars)
        {
            unsigned char &references = *((unsigned char *)m_chars - 1);
            if (references == 0 || references == 255)
                operator delete(m_chars - 1);
            else
                --references;
        }
        m_chars = 0;
        m_size = 0;
        m_capacity = 0;
    }
    void Tidy(bool);
    bool Grow(unsigned int, bool);
    void FUN_004580c0(const std::wstring &, unsigned int, unsigned int);
    std::allocator<unsigned short> m_allocator; // 0x00
    unsigned short *m_chars; // 0x04
    unsigned int m_size; // 0x08
    unsigned int m_capacity; // 0x0c
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
    RHMapWideText FUN_0061dd50(unsigned int, unsigned int);
    char FUN_0061e230();
    unsigned int FUN_0061df50();
    void FUN_0061e320(unsigned char);
    void FUN_0061e240(unsigned int);
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

    void FUN_00621430(unsigned int);
    void FUN_00621440(SBUIInputFieldUnkResource *);
    bool FUN_00621470(unsigned int);
    bool FUN_00621c30(const SBGeoBoundingBox2D &);
    void FUN_0061e4b0();
    RHMapWideText FUN_0061df60();
    void FUN_0061e060(RHMapWideText *);
    void FUN_0061e340();
};

std::wstring FUN_005d0880(const std::wstring &, const std::wstring &);
int FUN_00613c50(const unsigned short *, const unsigned short *, unsigned int);
bool FUN_00613e40(unsigned char, const void *, unsigned int, const void *);
bool FUN_006141e0(void *, const std::wstring &, float);
unsigned int FUN_00613940(void *, int **, int **, int **, int **, unsigned char *, unsigned int, int);

#endif
