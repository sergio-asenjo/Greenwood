#ifndef RHMENUCAMPAIGNMAP_H
#define RHMENUCAMPAIGNMAP_H

#include <string>
#include <vector>
#include <list>
#include <deque>
#include "SB.h"
#include "RHMenuCampaignMapClass.h"
#include "RHMenuScreenTimer.h"

typedef unsigned char undefined;
typedef unsigned short undefined2;
typedef unsigned int undefined4;

// SIZE 0x10
class RHMapWideText
{
public:
    std::allocator<unsigned short> m_allocator; // 0x00
    unsigned short *m_chars; // 0x04
    unsigned m_size; // 0x08
    unsigned m_capacity; // 0x0c
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

// SIZE 0x10
class RHMapTitleText
{
public:
    std::allocator<unsigned short> m_allocator; // 0x00
    unsigned short *m_chars; // 0x04
    unsigned m_size; // 0x08
    unsigned m_capacity; // 0x0c
    RHMapTitleText(const unsigned short *text,
                   const std::allocator<unsigned short> &allocator = std::allocator<unsigned short>())
        : m_allocator(allocator)
    {
        RHMapWideText *string = (RHMapWideText *)this;
        string->Tidy(false);
        unsigned size = wcslen(text);
        if (string->Grow(size, true))
        {
            wmemcpy(m_chars, text, size);
            string->End(size);
        }
    }
    ~RHMapTitleText() { ((RHMapWideText *)this)->Tidy(true); }
};

// SIZE 0x08
class SBGeoPoint2D
{
public:
    ~SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    float m_x; // 0x00
    float m_y; // 0x04
};

// SIZE 0x14
class RHMapBox
{
public:
    RHMapBox(float, float, float, float);
    ~RHMapBox() {}
    SBGeoPoint2D m_0; // 0x00
    SBGeoPoint2D m_8; // 0x08
    bool m_10; // 0x10
};

// SIZE 0xcc
class RHMapWidget
{
public:
    virtual void V00(); // vtable+0x00
    virtual void V04(); // vtable+0x04
    virtual void V08(); // vtable+0x08
    virtual void V0c(); // vtable+0x0c
    virtual void V10(); // vtable+0x10
    virtual void V14(); // vtable+0x14
    virtual void V18(); // vtable+0x18
    virtual void V1c(); // vtable+0x1c
    virtual void V20(); // vtable+0x20
    virtual void V24(); // vtable+0x24
    virtual void V28(); // vtable+0x28
    virtual void V2c(const RHMapTitleText &); // vtable+0x2c
    virtual bool V30(const std::wstring &, const RHMapBox &, unsigned, unsigned); // vtable+0x30
    virtual void V34(); // vtable+0x34
    virtual void V38(); // vtable+0x38
    virtual void V3c(); // vtable+0x3c
    virtual void V40(); // vtable+0x40
    virtual void V44(); // vtable+0x44
    virtual void V48(); // vtable+0x48
    virtual void V4c(); // vtable+0x4c
    virtual void V50(); // vtable+0x50
    virtual void V54(bool); // vtable+0x54
    char m_04[0xc8]; // +0x04; sizeof = 0xcc
};

// SIZE 0x27c
class RHMapLocation
{
public:
    undefined m_00[0xe0]; // 0x00
    RHMapWidget m_e0; // +0xe0
    RHMapWidget m_1ac; // +0x1ac
    void *m_278; // 0x278
};

// SIZE 0x1b0
class RHMapCampaign
{
public:
    std::vector<void *> FUN_00528050();
    std::vector<void *> FUN_005286b0();
    unsigned FUN_004577a0();
    void FUN_004577b0();
    RHMapByte UnkState() const { return m_100; }
    undefined m_00[0x100]; // 0x00
    RHMapByte m_100; // +0x100
    undefined m_101[0x53]; // 0x101
    std::vector<void *> m_154; // 0x154
    undefined m_164[0x44]; // 0x164
    unsigned m_1a8; // 0x1a8
    unsigned m_1ac; // +0x1ac
};

#include "RHMapWindowPart.h"

// SIZE 0x1990
class RHMapWindow
{
public:
    static unsigned long FUN_0053b6b0(unsigned long source, bool colorize, bool pause);
    static void FUN_0053b330(unsigned long surface, unsigned short amount, float factor);
    unsigned FUN_0053baa0(unsigned);
    void FUN_0053bb30(unsigned);
    void FUN_0053bbe0();
    void FUN_0053c7e0();
    typedef RHMenuScreenTimer Timer;
    undefined m_00[0x191c]; // 0x00
    std::deque<std::vector<void *> > m_191c; // 0x191c
    undefined m_194c[0x34]; // 0x194c
    std::list<Timer> m_1980; // 0x1980
    unsigned m_198c; // 0x198c
};

// SIZE 0x1c
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

class RHUnk00452030
{
public:
    int Get(int);
};
extern RHUnk00452030 *g_unk0x6c07fc;
extern std::string g_unk0x006c0660;
extern char *g_unk0x006c0664;
extern RHMapResources *g_unk0x006c1840;
std::wstring FUN_005e23d0(unsigned long);
unsigned FUN_00527cc0(unsigned);
void FUN_00529e60(RHMapWindow *, const RHMapWideText &, bool, bool);

#endif
