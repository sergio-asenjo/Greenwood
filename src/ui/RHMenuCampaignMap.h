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

#include "RHMapWideText.h"

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
#define SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    SBGeoPoint2D &FUN_005fc250(const SBGeoPoint2D &other);
    float m_x; // 0x00
    float m_y; // 0x04
};

#include "RHMapBox.h"

#include "SBGeoBoundingBox2DCore.h"

// SIZE 0xcc

#include "RHMapWidget.h"

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
#include "RHMapWindowClass.h"

#include "RHMapDescription.h"

#include "RHMapResources.h"

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
