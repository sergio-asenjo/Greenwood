#ifndef RHMENUCAMPAIGNMAP_H
#define RHMENUCAMPAIGNMAP_H

#include <string>
#include <vector>
#include "SB.h"

class RHMapWideText
{
public:
    std::allocator<unsigned short> m_allocator;
    unsigned short *m_chars;
    unsigned m_size;
    unsigned m_capacity;
    RHMapWideText(const std::allocator<unsigned short> &allocator = std::allocator<unsigned short>())
        : m_allocator(allocator) { Tidy(false); }
    void Tidy(bool);
    bool Grow(unsigned, bool);
    void End(unsigned);
    ~RHMapWideText()
    {
        if (m_chars == 0)
            ;
        else if (*((unsigned char *)m_chars - 1) == 0 || *((unsigned char *)m_chars - 1) == 255)
            operator delete(m_chars - 1);
        else
            --*((unsigned char *)m_chars - 1);
        m_chars = 0, m_size = 0, m_capacity = 0;
    }
};

unsigned short *FUN_00419940(unsigned short *, const unsigned short *, unsigned);

class RHMapTitleText
{
public:
    std::allocator<unsigned short> m_allocator;
    unsigned short *m_chars;
    unsigned m_size;
    unsigned m_capacity;
    RHMapTitleText(const unsigned short *text,
                   const std::allocator<unsigned short> &allocator = std::allocator<unsigned short>())
        : m_allocator(allocator)
    {
        RHMapWideText *string = (RHMapWideText *)this;
        string->Tidy(false);
        unsigned size = wcslen(text);
        if (string->Grow(size, true))
        {
            FUN_00419940(m_chars, text, size);
            string->End(size);
        }
    }
    ~RHMapTitleText() { ((RHMapWideText *)this)->Tidy(true); }
};

struct RHMapByte
{
    signed char value;
};

class SBGeoPoint2D
{
public:
    ~SBGeoPoint2D();
    float m_x;
    float m_y;
};

class RHMapBox
{
public:
    RHMapBox(float, float, float, float);
    ~RHMapBox() {}
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
    bool m_10;
};

class RHMapWidget
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual bool V30(const std::wstring &, const RHMapBox &, unsigned, unsigned);
    char m_04[0xc8]; // +0x04; sizeof = 0xcc
};

class RHMapLocation
{
public:
    char m_00[0xe0];
    RHMapWidget m_e0; // +0xe0
    RHMapWidget m_1ac; // +0x1ac
    char m_278[4]; // sizeof = 0x27c
};

class RHMapCampaign
{
public:
    std::vector<void *> FUN_00528050();
    unsigned FUN_004577a0();
    void FUN_004577b0();
    RHMapByte UnkState() const { return m_100; }
    char m_00[0x100];
    RHMapByte m_100; // +0x100
    char m_101[0xab];
    unsigned m_1ac; // +0x1ac
};

class RHMapWindow
{
public:
    unsigned FUN_0053baa0(unsigned);
    void FUN_0053bb30(unsigned);
    void FUN_0053bbe0();
    void FUN_0053c7e0();
};

class RHMapDescription
{
public:
    RHMapDescription();
    ~RHMapDescription();
    bool FUN_0063cda0(unsigned);
    struct Entry
    {
        char m_00[0x30];
        unsigned m_30; // +0x30
        char m_34[4];
        unsigned m_38; // +0x38
        char m_3c[0x0c]; // sizeof = 0x48
    };
    Entry *FUN_0063c9e0(unsigned);
    char m_00[0x1c]; // sizeof = 0x1c
};

class RHMapResources
{
public:
    bool FUN_00600fc0(unsigned);
    bool FUN_006009e0(unsigned, unsigned, RHMapWideText &);
};

class RHMenuCampaignMap
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30(void *);
    virtual void V34();
    virtual void V38(void *);
    bool Create();
    void DisplayPseudoMissionDebriefing();
    bool FUN_00544b40(const RHMapTitleText &, const RHMapBox &, unsigned);
    void FUN_00527a70(RHMapByte);
    void FUN_00527ae0(RHMapByte);
    void FUN_00527c00(const std::vector<void *> &);
    void FUN_005284b0();
    void FUN_00528810();
    void Emit();
    char m_04[0x26fc]; // +0x04; this+0x5d flag, +0xb4 window, +0xcc widget
    unsigned m_2700; // +0x2700; location array +0x19c (stride 0x27c), arrows +0x1a74 (stride 0xcc), widget +0x25ec
};

class RHUnk00452030;
extern RHUnk00452030 *g_unk0x6c07fc;
extern std::string g_unk0x006c0660;
extern RHMapResources *g_unk0x006c1840;
std::wstring FUN_005e23d0(unsigned long);
void FUN_00529e60(RHMapWindow *, const RHMapWideText &, bool, unsigned);

#endif
