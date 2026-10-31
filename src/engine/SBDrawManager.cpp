#include "SBDrawManager.h"
#include "SBResourceManager.h"
#include <string>
#include <list>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "SBDrawViewport.h"

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *);
extern "C" __declspec(dllimport) int __stdcall SetWindowTextA(void *, const char *);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);
extern "C" __declspec(dllimport) void *__stdcall GetStockObject(int);
extern "C" __declspec(dllimport) void *__stdcall SelectObject(void *, void *);
extern "C" __declspec(dllimport) unsigned __stdcall SetTextAlign(void *, unsigned);
extern "C" __declspec(dllimport) int __stdcall SetBkMode(void *, int);
extern "C" __declspec(dllimport) unsigned long __stdcall SetBkColor(void *, unsigned long);
extern "C" __declspec(dllimport) unsigned long __stdcall SetTextColor(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall TextOutA(void *, int, int, const char *, int);
extern "C" __declspec(dllimport) int __stdcall GetClientRect(void *, long *);
extern "C" __declspec(dllimport) int __stdcall ClientToScreen(void *, long *);

void SBAssert(int, const char *, int, const char *, ...);
std::string FUN_005f81d0(long);
void SBSimpleUnk005f9510(void *, const char *, ...);
extern char g_unk0x006c13c0[16];

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int width, int height, int format, bool system);
    bool FUN_005e4f70(unsigned long, unsigned short, unsigned short, unsigned long);
    void Unk005e5160(unsigned long);
    void FUN_005e5260();
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
    void FUN_005e6440(unsigned long, int, int, unsigned long, unsigned long);
    unsigned short UnkField10c() const { return m_depth; }
    char m_00[0x10c];
    unsigned short m_depth;
};

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    float m_x;
    float m_y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};


struct SBDrawUnk005e56c0Iterator
{
    SBDrawUnk005f0090Node *m_node;
    SBDrawUnk005e56c0Iterator(SBDrawUnk005f0090Node *node) : m_node(node) {}
};

inline SBDrawUnk005e56c0Iterator SBDrawFind(SBDrawUnk005f0090 &tree, const unsigned long &key)
{
    SBDrawUnk005e56c0Iterator found(tree.FUN_005f0090(key));
    SBDrawUnk005f0090Node *head = tree.m_head;
    return (found.m_node != head && key >= found.m_node->m_key
        ? found : SBDrawUnk005e56c0Iterator(head));
}

static __forceinline const char *SBDrawStringData(const std::string &value)
{
    const char *buffer = *(const char *const *)((const char *)&value + 4);
    return buffer ? buffer : "";
}

inline SBDrawUnk005efc10Iterator SBDrawFindSurface(SBDrawUnk005efc10 &tree, const unsigned long &key)
{
    SBDrawUnk005efc10Iterator found(tree.FUN_005efc10(key).m_node);
    SBDrawUnk005f0090Node *head = tree.m_head;
    return (found.m_node != head && key >= found.m_node->m_key
        ? found : SBDrawUnk005efc10Iterator(head));
}

// SIZE 0x14
struct SBDrawDriverList
{
    std::list<std::string> m_list; // 0x00
    std::list<std::string>::iterator m_current; // 0x0c
    bool m_dirty; // 0x10
    void Add(const std::string &name)
    {
        m_list.push_back(name);
        m_dirty = true;
    }
};

// FUNCTION: GAME 0x005e3b10
int __stdcall FUN_005e3b10(void *, char *description, char *, void *context, void *)
{
    ((SBDrawDriverList *)context)->Add(std::string(description));
    return 1;
}

struct SBDrawTreeNode;
extern SBDrawTreeNode *g_unk0x006c11dc;

// GLOBAL: GAME 0x006c11d8
unsigned g_unk0x006c11d8;

// FUNCTION: GAME 0x005e3ed0
void SBDrawUnk005efc10::FUN_005e3ed0()
{
    SBDrawUnk005efc10Iterator first(Leftmost());
    SBDrawUnk005efc10Iterator last(m_head);
    FUN_005efa90(first, last);
    operator delete(m_head);
    m_head = 0;
    m_size = 0;
    {
        std::_Lockit lock;
        if (--g_unk0x006c11d8 == 0) {
            operator delete(g_unk0x006c11dc);
            g_unk0x006c11dc = 0;
        }
    }
}

// FUNCTION: GAME 0x005e3f40
bool RHUnk005ef320::FUN_005e3f40(const std::string &title)
{
    return SetWindowTextA(*(void **)((char *)this + 0x100), SBDrawStringData(title)) != 0;
}

// Parked: retry-loop lookup duplication and iterator stores differ.
// STUB: GAME 0x005e3f70
bool RHUnk005ef320::FUN_005e3f70()
{
    SBDrawUnk005efc10 &tree = *(SBDrawUnk005efc10 *)((char *)this + 0x54);
    for (;;) {
        unsigned long key = 0;
        SBDrawUnk005efc10Iterator found = tree.FUN_005efc10(key);
        found.m_node = tree.m_head;
        SBDrawUnk005e5ec0Surface *object = *(SBDrawUnk005e5ec0Surface **)((char *)this + 0x88);
        if (!object) return false;
        long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *))object->m_vtable[25])(object);
        if (result == 0) return true;
        if (result == (long)0x8876024b) {
            object = *(SBDrawUnk005e5ec0Surface **)((char *)this + 0x84);
            result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void *, unsigned long))object->m_vtable[20])(
                object, *(void **)((char *)this + 0x100), 0x413);
            if (result != 0)
                SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x103,
                    // STRING: GAME 0x006b9320
                    "Unable to switch back to exclusive mode DxERR=%s", SBDrawStringData(FUN_005f81d0(result)));
            object = *(SBDrawUnk005e5ec0Surface **)((char *)this + 0x88);
            result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, unsigned long, unsigned long,
                unsigned long, unsigned long, unsigned long))object->m_vtable[21])(
                object, *(unsigned short *)((char *)this + 0x10e), *(unsigned short *)((char *)this + 0x110), 16, 0, 0);
            if (result != 0)
                SBAssert(1, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x109,
                    // STRING: GAME 0x006b92dc
                    "Unable to set the display resolution DxERR=%s resolution( %d, %d )",
                    SBDrawStringData(FUN_005f81d0(result)), *(unsigned short *)((char *)this + 0x10e),
                    *(unsigned short *)((char *)this + 0x110));
        } else {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x110,
                // STRING: GAME 0x006b92ac
                "Unable to restore the primary surface DxERR=%s", SBDrawStringData(FUN_005f81d0(result)));
            return false;
        }
    }
}

// FUNCTION: GAME 0x005e4ed0
unsigned long RHUnkFXDraw::Unk005e4ed0(int width, int height, int format, bool system)
{
    EnterCriticalSection(this);
    unsigned long surface = *(unsigned long *)(m_00 + 0x50);
    if (FUN_005e4f70(surface, width, height, format) == true)
    {
        ++*(unsigned long *)(m_00 + 0x50);
        if (system)
            ((std::list<unsigned long> *)(m_00 + 0x64))->push_back(surface);
        LeaveCriticalSection(this);
        return surface;
    }
    LeaveCriticalSection(this);
    return (unsigned long)-1;
}

// Parked: insert-result temporary adds eight bytes to the target frame.
// STUB: GAME 0x005e4f70
bool RHUnkFXDraw::FUN_005e4f70(unsigned long surface, unsigned short width, unsigned short height, unsigned long flags)
{
    unsigned long description[31];
    memset(description, 0, sizeof(description));
    description[3] = width;
    description[0] = 0x7c;
    description[1] = 7;
    description[2] = height;
    if (flags == 0) flags = 1;
    if (flags & 8) description[26] = 0x20004040;
    if (flags & 2) description[26] = 0x4040;
    if (flags & 1) description[26] = 0x840;
    SBDrawUnk005e4f70Surface info;
    info.m_width = width;
    info.m_height = height;
    info.m_locked = false;
    info.m_section = operator new(0x18);
    InitializeCriticalSection(info.m_section);
    info.m_color = m_depth == 16 ? 0x7c0 : 0x3e0;
    SBDrawUnk005e5ec0Surface *object = *(SBDrawUnk005e5ec0Surface **)(m_00 + 0x88);
    long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void *, void **, void *))object->m_vtable[6])(
        object, description, &info.m_object, 0);
    if (result != 0) {
        if (result == (long)0x8876017c) return FUN_005e4f70(surface, width, height, 1);
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x362,
            // STRING: GAME 0x006b9418
            "Unable to create a directX surface %s", SBDrawStringData(FUN_005f81d0(result)));
        return false;
    }
    object = (SBDrawUnk005e5ec0Surface *)info.m_object;
    ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, unsigned long, unsigned long *))object->m_vtable[29])(
        object, 8, &info.m_color);
    (*(SBDrawUnk005efc10 *)(m_00 + 0x54)).FUN_005ef440(SBDrawUnk005e4f70Pair(surface, info));
    return true;
}

// FUNCTION: GAME 0x005e56c0
unsigned short RHUnkFXDraw::FUN_005e56c0(unsigned long surface)
{
    if (surface == 0) surface = 1;
    SBDrawUnk005f0090 &tree = *(SBDrawUnk005f0090 *)(m_00 + 0x54);
    SBDrawUnk005f0090Node *found = SBDrawFind(tree, surface).m_node;
    if (found == *(SBDrawUnk005f0090Node **)(m_00 + 0x58)) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x490,
            // STRING: GAME 0x006b951c
            "Trying to access an inexisting surface");
        return 0;
    }
    return found->m_width;
}

// FUNCTION: GAME 0x005e5750
unsigned short RHUnkFXDraw::FUN_005e5750(unsigned long surface)
{
    if (surface == 0) surface = 1;
    SBDrawUnk005f0090 &tree = *(SBDrawUnk005f0090 *)(m_00 + 0x54);
    SBDrawUnk005f0090Node *found = SBDrawFind(tree, surface).m_node;
    if (found == *(SBDrawUnk005f0090Node **)(m_00 + 0x58)) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x4b3,
            "Trying to access an inexisting surface");
        return 0;
    }
    return found->m_height;
}

inline SBResourceUnkKeyIterator SBDrawFindExternalEnd(SBDrawUnk005f0090 &tree, const unsigned long &key)
{
    SBResourceUnkKeyIterator found((SBResourceUnkKeyNode *)tree.FUN_005f0090(key));
    SBResourceUnkTreeEnd &view = (SBResourceUnkTreeEnd &)tree;
    return (found.m_node != view.FUN_00617690().m_node && key >= found.m_node->m_key
        ? found : view.FUN_00617690());
}

// FUNCTION: GAME 0x005e57e0
void RHUnk005ef320::FUN_005e57e0(unsigned surface, SBGeoVector2D &size)
{
    if (surface == 0) surface = 1;
    SBDrawUnk005f0090 &tree = *(SBDrawUnk005f0090 *)((char *)this + 0x54);
    const unsigned long &key = *(const unsigned long *)&surface;
    SBDrawUnk005f0090Node *node = (SBDrawUnk005f0090Node *)SBDrawFindExternalEnd(tree, key).m_node;
    if (node == *(SBDrawUnk005f0090Node **)((char *)this + 0x58)) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x4e1,
            "Trying to access an inexisting surface");
        return;
    }
    float height = node->m_height;
    size.m_x = node->m_width;
    size.m_y = height;
}

// FUNCTION: GAME 0x005e5890
bool RHUnk005ef320::FUN_005e5890(unsigned long surface, void **dc, unsigned long flags)
{
    if (surface == 0 && !(flags & 8)) surface = 1;
    SBDrawUnk005efc10 &tree = *(SBDrawUnk005efc10 *)((char *)this + 0x54);
    SBDrawUnk005f0090Node *found = SBDrawFindSurface(tree, surface).m_node;
    if (found == *(SBDrawUnk005f0090Node **)((char *)this + 0x58)) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x505,
            // STRING: GAME 0x006b9568
            "Trying to get a DC on an inexisting surface");
        return false;
    }
    EnterCriticalSection(*(void **)((char *)found + 0x24));
    SBDrawUnk005e5ec0Surface *object = *(SBDrawUnk005e5ec0Surface **)((char *)found + 0x10);
    long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void **))object->m_vtable[17])(object, dc);
    if (result != 0) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x50e,
            // STRING: GAME 0x006b9544
            "Unable to get a surface DC DxErr=%s", SBDrawStringData(FUN_005f81d0(result)));
        return false;
    }
    return true;
}

// Parked: constant-one register allocation and hidden-result scheduling differ.
// STUB: GAME 0x005e5a00
bool SBDrawManager::FUN_005e5a00(unsigned long surface, SBDrawViewport &view, unsigned long flags)
{
    bool locked = true;
    if (surface == 0 && ((!*((char *)this + 0x112) && !(flags & 16))
        || (!*((char *)this + 0x112) && !(flags & 8)))) surface = locked;
    unsigned long description[31];
    memset(description, 0, sizeof(description));
    description[0] = 0x7c;
    SBDrawUnk005efc10 &tree = *(SBDrawUnk005efc10 *)((char *)this + 0x54);
    SBDrawUnk005f0090Node *found = tree.FUN_005efbc0(surface).m_node;
    if (found == *(SBDrawUnk005f0090Node **)((char *)this + 0x58)) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x53b,
            // STRING: GAME 0x006b95b8
            "Trying to get a viewport on an inexisting surface");
        return false;
    }
    EnterCriticalSection(*(void **)((char *)found + 0x24));
    SBDrawUnk005e5ec0Surface *object = *(SBDrawUnk005e5ec0Surface **)((char *)found + 0x10);
    long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void *, void *, unsigned long, void *))object->m_vtable[25])(
        object, 0, description, locked, 0);
    if (result != 0) {
        if (result == (long)0x887601c2) {
            object = *(SBDrawUnk005e5ec0Surface **)((char *)found + 0x10);
            ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *))object->m_vtable[27])(object);
            LeaveCriticalSection(*(void **)((char *)found + 0x24));
            return false;
        }
        LeaveCriticalSection(*(void **)((char *)found + 0x24));
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x54e,
            // STRING: GAME 0x006b9594
            "Unable to lock a surface DxErr=%s", SBDrawStringData(FUN_005f81d0(result)));
        return false;
    }
    *((bool *)found + 0x20) = locked;
    view.m_pixels = (unsigned short *)description[9];
    view.m_width = (unsigned short)description[3];
    *(unsigned short *)((char *)&view + 6) = (unsigned short)description[2];
    *((bool *)&view + 0x14) = locked;
    view.m_pitch = description[4];
    *(unsigned long *)&view = surface;
    view.m_depth = m_10c;
    *(unsigned short *)((char *)&view + 0xe) = *(unsigned short *)((char *)found + 0x18);
    return locked;
}

// FUNCTION: GAME 0x005e5bd0
bool RHUnk005ef320::FUN_005e5bd0(unsigned long surface, void *dc)
{
    if (surface == 0) surface = 1;
    SBDrawUnk005f0090 &tree = *(SBDrawUnk005f0090 *)((char *)this + 0x54);
    SBDrawUnk005f0090Node *found = SBDrawFind(tree, surface).m_node;
    if (found == *(SBDrawUnk005f0090Node **)((char *)this + 0x58)) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x59e,
            // STRING: GAME 0x006b962c
            "Trying to release the DC of an inexistant surface");
        return false;
    }
    SBDrawUnk005e5ec0Surface *object = *(SBDrawUnk005e5ec0Surface **)((char *)found + 0x10);
    long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void *))object->m_vtable[26])(object, dc);
    if (result != 0) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x5a6,
            // STRING: GAME 0x006b95ec
            "Unable to release the gdi compatible DC of a surface DxErr=%s", FUN_005f81d0(result));
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x005e5d30
bool RHUnk005ef320::FUN_005e5d30(unsigned long surface)
{
    if (surface == 0) surface = 1;
    SBDrawUnk005efc10 &tree = *(SBDrawUnk005efc10 *)((char *)this + 0x54);
    SBDrawUnk005f0090Node *found = SBDrawFindSurface(tree, surface).m_node;
    if (found == *(SBDrawUnk005f0090Node **)((char *)this + 0x58)) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x5ca,
            // STRING: GAME 0x006b9688
            "Trying to release an inexisting surface");
        return false;
    }
    SBDrawUnk005e5ec0Surface *object = *(SBDrawUnk005e5ec0Surface **)((char *)found + 0x10);
    long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void *))object->m_vtable[32])(object, 0);
    if (result != 0) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x5d3,
            // STRING: GAME 0x006b9660
            "Unable to unlock surface %d DxErr=%s", surface, SBDrawStringData(FUN_005f81d0(result)));
        return false;
    }
    *((volatile char *)found + 0x20) = 0;
    LeaveCriticalSection(*(void **)((char *)found + 0x24));
    return true;
}

// FUNCTION: GAME 0x005e5ea0
void SBDrawManager::FUN_005e5ea0(SBDrawViewport &view)
{
    *(char *)((char *)&view + 0x14) = 0;
    ((RHUnk005ef320 *)this)->FUN_005e5d30(*(unsigned long *)&view);
}

// FUNCTION: GAME 0x005e5ec0
bool SBDrawUnk005e5ec0::FUN_005e5ec0(unsigned long surface, unsigned long key)
{
    if (surface == 0) surface = 1;
    SBDrawUnk005f0090 &tree = *(SBDrawUnk005f0090 *)(m_00 + 0x54);
    SBDrawUnk005f0090Node *found = SBDrawFind(tree, surface).m_node;
    if (found == *(SBDrawUnk005f0090Node **)(m_00 + 0x58)) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x609,
            // STRING: GAME 0x006b96b0
            "Setting the color key of an unexisting surface");
        return false;
    }
    unsigned long *color = (unsigned long *)((char *)found + 0x18);
    *color = key & 0xffff;
    SBDrawUnk005e5ec0Surface *object = *(SBDrawUnk005e5ec0Surface **)((char *)found + 0x10);
    ((int (__stdcall *)(SBDrawUnk005e5ec0Surface *, unsigned long, unsigned long *))object->m_vtable[29])(
        object, 8, color);
    return true;
}

// FUNCTION: GAME 0x005e5f60
unsigned short SBDrawUnk005e5ec0::FUN_005e5f60(unsigned long surface)
{
    if (surface == 0) return m_10c == 16 ? 0x7c0 : 0x3e0;
    SBDrawUnk005f0090 &tree = *(SBDrawUnk005f0090 *)(m_00 + 0x54);
    SBDrawUnk005f0090Node *found = SBDrawFind(tree, surface).m_node;
    if (found == *(SBDrawUnk005f0090Node **)(m_00 + 0x58)) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x634,
            // STRING: GAME 0x006b96e0
            "Getting the color key of an unexisting surface");
        return 0;
    }
    return *(unsigned short *)((char *)found + 0x18);
}

#define SBGEO_POINT2D_VIEW
#include "SBGeoBoundingBox2DCore.h"

// STUB: GAME 0x005e6000
bool SBDrawManager::FUN_005e6000(SBGeoBoundingBox2D &destination, SBGeoBoundingBox2D &source)
{
    SBGeoVector2D offset;
    offset.m_x = destination.m_p0.m_x < 0.0f ? -destination.m_p0.m_x : 0.0f;
    offset.m_y = destination.m_p0.m_y < 0.0f ? -destination.m_p0.m_y : 0.0f;
    destination.SetMin(destination.m_p0.Unk005fc190(offset));
    source.SetMin(source.m_p0.Unk005fc190(offset));
    {
        float maximum = destination.m_p1.m_x;
        float width;
        *(volatile float *)&width = (float)m_10e;
        if (maximum > *(const float *)&width)
            offset.m_x = *(const float *)&width - destination.m_p1.m_x;
        else
            offset.m_x = 0.0f;
    }
    {
        float maximum = destination.m_p1.m_y;
        float height;
        *(volatile float *)&height = (float)m_110;
        if (maximum > *(const float *)&height)
            offset.m_y = *(const float *)&height - destination.m_p1.m_y;
        else
            offset.m_y = 0.0f;
    }
    destination.SetMax(destination.m_p1.Unk005fc190(offset));
    source.SetMax(source.m_p1.Unk005fc190(offset));
    return true;
}

// FUNCTION: GAME 0x005e61e0
bool SBDrawManager::FUN_005e61e0(unsigned long surface, const SBGeoBoundingBox2D *box, unsigned short color, unsigned long flags)
{
    if (surface == 0 && !*((unsigned char *)this + 0x112) && !(flags & 8))
        surface = 1;
    typedef SBDrawUnk005efc10Iterator (SBDrawUnk005efc10::*Find)(const unsigned long &);
    SBDrawUnk005efc10Iterator found = ((*(SBDrawUnk005efc10 *)((char *)this + 0x54)).*static_cast<Find>(&SBDrawUnk005efc10::FUN_005efbc0))(surface);
    if (found.m_node == *(SBDrawUnk005f0090Node **)((char *)this + 0x58))
    {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x6d3,
            // STRING: GAME 0x006b9734
            "Invalid surface for the fill");
        return false;
    }
    long rectangle[4];
    long client[4];
    long *destination;
    if (box)
    {
        const float *coordinates = (const float *)box;
        rectangle[0] = (long)coordinates[0];
        rectangle[2] = (long)coordinates[2];
        rectangle[1] = (long)coordinates[1];
        rectangle[3] = (long)coordinates[3];
        if (rectangle[0] == rectangle[2] || rectangle[1] == rectangle[3])
            return false;
        destination = rectangle;
    }
    else
        destination = 0;
    if (!*((unsigned char *)this + 0x80) && *((unsigned char *)this + 0x112) == 1)
    {
        GetClientRect(*(void **)((char *)this + 0x100), client);
        ClientToScreen(*(void **)((char *)this + 0x100), client);
        ClientToScreen(*(void **)((char *)this + 0x100), client + 2);
        if (box)
        {
            if (surface == 0)
            {
                rectangle[0] += client[0];
                rectangle[2] += client[0];
                rectangle[1] += client[1];
                rectangle[3] += client[1];
            }
        }
        else if (surface == 0)
        {
            rectangle[0] = client[0];
            rectangle[2] = client[2];
            rectangle[1] = client[1];
            rectangle[3] = client[3];
            destination = rectangle;
        }
    }
    unsigned long effect[25];
    effect[0] = 100;
    effect[20] = color & 0xffff;
    SBDrawUnk005e5ec0Surface *object = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
    long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, long *, void *, void *, unsigned long, void *))object->m_vtable[5])(
        object, destination, 0, 0, 0x1000400, effect);
    if (result != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x70d,
            // STRING: GAME 0x006b9710
            "Error during the fill DxErr = %s", SBDrawStringData(FUN_005f81d0(result)));
        return false;
    }
    return true;
}

// Parked at 0.4690; unannotated because callers retain divergent blit views.
bool SBDrawManager::FUN_005e6440(unsigned long source, const SBGeoBoundingBox2D *sourceBox,
    unsigned long destination, const SBGeoBoundingBox2D *destinationBox, unsigned char flags)
{
    unsigned char options = *(volatile unsigned char *)&flags;
    unsigned long blitFlags = 0x200;
    if (options & 1)
        blitFlags = 0x8200;
    if (source == 0 && !*((unsigned char *)this + 0x112) && !(options & 0x10))
        source = 1;
    if (destination == 0 && !*((unsigned char *)this + 0x112) && !(options & 8))
        destination = 1;
    typedef SBDrawUnk005efc10Iterator (SBDrawUnk005efc10::*Find)(const unsigned long &);
    SBDrawUnk005efc10 &tree = *(SBDrawUnk005efc10 *)((char *)this + 0x54);
    SBDrawUnk005f0090Node *sourceNode = (tree.*static_cast<Find>(&SBDrawUnk005efc10::FUN_005efbc0))(source).m_node;
    SBDrawUnk005f0090Node *destinationNode = (tree.*static_cast<Find>(&SBDrawUnk005efc10::FUN_005efbc0))(destination).m_node;
    if (sourceNode == *(SBDrawUnk005f0090Node **)((char *)this + 0x58))
    {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x767,
            // STRING: GAME 0x006b97a4
            "Invalid surface for the blit (Source)");
        return false;
    }
    if (destinationNode == *(SBDrawUnk005f0090Node **)((char *)this + 0x58))
    {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x76d,
            // STRING: GAME 0x006b9778
            "Invalid surface for the blit (Destination)");
        return false;
    }
    long sourceRectangle[4];
    long destinationRectangle[4];
    long client[4];
    long *target;
    if (destinationBox)
    {
        destinationRectangle[0] = (long)((const float *)destinationBox)[0];
        destinationRectangle[2] = (long)((const float *)destinationBox)[2];
        destinationRectangle[1] = (long)((const float *)destinationBox)[1];
        destinationRectangle[3] = (long)((const float *)destinationBox)[3];
        if (destinationRectangle[0] == destinationRectangle[2] || destinationRectangle[1] == destinationRectangle[3])
            return false;
        target = destinationRectangle;
    }
    else if (blitFlags & 0x8000)
    {
        destinationRectangle[0] = 0;
        destinationRectangle[2] = destinationNode->m_width;
        destinationRectangle[1] = 0;
        destinationRectangle[3] = destinationNode->m_height;
        target = destinationRectangle;
    }
    else
        target = 0;
    const float *originalSourceBox = (const float *)sourceBox;
    if (originalSourceBox)
    {
        sourceRectangle[0] = (long)originalSourceBox[0];
        sourceRectangle[2] = (long)originalSourceBox[2];
        sourceRectangle[1] = (long)originalSourceBox[1];
        sourceRectangle[3] = (long)originalSourceBox[3];
        if (sourceRectangle[0] == sourceRectangle[2] || sourceRectangle[1] == sourceRectangle[3])
            return false;
        sourceBox = (const SBGeoBoundingBox2D *)sourceRectangle;
    }
    else if (blitFlags & 0x8000)
    {
        sourceRectangle[0] = 0;
        sourceRectangle[2] = sourceNode->m_width;
        sourceRectangle[1] = 0;
        sourceRectangle[3] = sourceNode->m_height;
        sourceBox = (const SBGeoBoundingBox2D *)sourceRectangle;
    }
    else
        sourceBox = 0;
    if (!*((unsigned char *)this + 0x80))
    {
        GetClientRect(*(void **)((char *)this + 0x100), client);
        ClientToScreen(*(void **)((char *)this + 0x100), client);
        ClientToScreen(*(void **)((char *)this + 0x100), client + 2);
        if (originalSourceBox)
        {
            if (source == 0 && (*((unsigned char *)this + 0x112) == 1 || (*(volatile unsigned char *)&flags & 0x10)))
            {
                sourceRectangle[0] += client[0];
                sourceRectangle[2] += client[0];
                sourceRectangle[1] += client[1];
                sourceRectangle[3] += client[1];
            }
        }
        else if (source == 0 && (*((unsigned char *)this + 0x112) == 1 || (*(volatile unsigned char *)&flags & 0x10)))
        {
            sourceRectangle[0] = client[0];
            sourceRectangle[2] = client[2];
            sourceRectangle[1] = client[1];
            sourceRectangle[3] = client[3];
            sourceBox = (const SBGeoBoundingBox2D *)sourceRectangle;
        }
        if (destinationBox)
        {
            if (destination == 0 && (*((unsigned char *)this + 0x112) == 1 || (*(volatile unsigned char *)&flags & 8)))
            {
                destinationRectangle[0] += client[0];
                destinationRectangle[2] += client[0];
                destinationRectangle[1] += client[1];
                destinationRectangle[3] += client[1];
            }
        }
        else if (destination == 0 && (*((unsigned char *)this + 0x112) == 1 || (*(volatile unsigned char *)&flags & 8)))
        {
            destinationRectangle[1] = client[1];
            destinationRectangle[0] = client[0];
            destinationRectangle[2] = client[2];
            destinationRectangle[3] = client[3];
            target = destinationRectangle;
        }
    }
    EnterCriticalSection(*(void **)((char *)destinationNode + 0x24));
    SBDrawUnk005e5ec0Surface *object = *(SBDrawUnk005e5ec0Surface **)((char *)destinationNode + 0x10);
    long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, long *, void *, const void *, unsigned long, void *))object->m_vtable[5])(
        object, target, *(void **)((char *)sourceNode + 0x10), sourceBox, blitFlags, 0);
    LeaveCriticalSection(*(void **)((char *)destinationNode + 0x24));
    if (result != 0)
    {
        if (result == (long)0x887601c2)
        {
            object = *(SBDrawUnk005e5ec0Surface **)((char *)destinationNode + 0x10);
            ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *))object->m_vtable[27])(object);
            return false;
        }
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x7f5,
            // STRING: GAME 0x006b9754
            "Error during the blit DxErr = %s", SBDrawStringData(FUN_005f81d0(result)));
        return false;
    }
    return true;
}

void EmitSBDrawManagerBlit(SBDrawManager *draw, unsigned long source, unsigned long destination)
{
    draw->FUN_005e6440(source, 0, destination, 0, 0);
}

// FUNCTION: GAME 0x005e7880
bool SBDrawUnk005e8450::FUN_005e7880(void *arg1, void *arg2, void *arg3,
    int arg4, int arg5, int arg6, int arg7, int arg8, int arg9)
{
    FUN_00623850(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    return true;
}

#define SBDRAW_BLEND_PIXEL_FUNCTION(Name, RedShift, GreenShift, GreenMask, SourceGreenMask) \
static __forceinline unsigned short Name(unsigned short source, unsigned short destination, unsigned short weight) \
{ \
    unsigned short sourceRed = (source >> RedShift) & 0xf8; \
    unsigned short sourceGreen = (source >> GreenShift) & SourceGreenMask; \
    unsigned short sourceBlue = (source & 0x1f) << 3; \
    int red = sourceRed * weight >> 8; \
    int green = sourceGreen * weight >> 8; \
    int blue = sourceBlue * weight >> 8; \
    unsigned short inverse = 256 - weight; \
    unsigned short destinationRed = (destination >> RedShift) & 0xf8; \
    unsigned short destinationGreen = (destination >> GreenShift) & GreenMask; \
    unsigned short destinationBlue = (destination & 0x1f) << 3; \
    unsigned char finalRed = (destinationRed * inverse >> 8) + red; \
    unsigned char finalGreen = (destinationGreen * inverse >> 8) + green; \
    unsigned short finalBlue = (destinationBlue * inverse >> 8) + blue; \
    return (((finalRed & 0xf8) << 5) + (finalGreen & GreenMask)) * (1 << GreenShift) + (finalBlue >> 3); \
}

SBDRAW_BLEND_PIXEL_FUNCTION(SBDrawBlendPixel15, 7, 2, 0xf8, 0xf8)
SBDRAW_BLEND_PIXEL_FUNCTION(SBDrawBlendPixel16, 8, 3, 0xfc, 0xfc)
SBDRAW_BLEND_PIXEL_FUNCTION(SBDrawBlendPixel16Green, 8, 3, 0xfc, 0xf8)

#undef SBDRAW_BLEND_PIXEL_FUNCTION

// Parked: component live ranges add a frame slot and reorder source/alpha/destination reads.
// STUB: GAME 0x005e78c0
bool SBDrawUnk005e8450::FUN_005e78c0(unsigned short *source, unsigned short *destination, unsigned short *alpha,
    unsigned width, unsigned height, unsigned sourceStride, unsigned destinationStride, unsigned alphaStride)
{
    for (unsigned rows = height; rows > 0; --rows)
    {
        for (unsigned columns = width; columns > 0; --columns)
        {
            *destination = SBDrawBlendPixel15(*source, *destination, (*alpha >> 2) & 0xf8);
            ++destination;
            ++alpha;
            ++source;
        }
        source = (unsigned short *)((char *)source + sourceStride);
        alpha = (unsigned short *)((char *)alpha + alphaStride);
        destination = (unsigned short *)((char *)destination + destinationStride);
    }
    return true;
}

// Parked: component live ranges and loop-parameter reload scheduling differ.
// STUB: GAME 0x005e7a30
bool SBDrawUnk005e8450::FUN_005e7a30(unsigned short *source, unsigned short *destination, unsigned short *alpha,
    unsigned width, unsigned height, unsigned sourceStride, unsigned destinationStride, unsigned alphaStride, unsigned short key)
{
    for (unsigned rows = height; rows > 0; --rows)
    {
        for (unsigned columns = width; columns > 0; --columns)
        {
            if (*source != key)
            {
                unsigned short weight = (*alpha >> 1) & 0x1f0;
                if (weight > 255)
                    weight = 255;
                *destination = SBDrawBlendPixel15(*source, *destination, weight);
            }
            ++destination;
            ++alpha;
            ++source;
        }
        source = (unsigned short *)((char *)source + sourceStride);
        alpha = (unsigned short *)((char *)alpha + alphaStride);
        destination = (unsigned short *)((char *)destination + destinationStride);
    }
    return true;
}

// Parked: component live ranges and loop-parameter reload scheduling differ.
// STUB: GAME 0x005e7bc0
bool SBDrawUnk005e8450::FUN_005e7bc0(unsigned short *source, unsigned short *destination, unsigned short *alpha,
    unsigned width, unsigned height, unsigned sourceStride, unsigned destinationStride, unsigned alphaStride)
{
    for (unsigned rows = height; rows > 0; --rows)
    {
        for (unsigned columns = width; columns > 0; --columns)
        {
            *destination = SBDrawBlendPixel15(*source, *destination, (*(unsigned char *)alpha & 0x1f) << 3);
            ++destination;
            ++alpha;
            ++source;
        }
        source = (unsigned short *)((char *)source + sourceStride);
        alpha = (unsigned short *)((char *)alpha + alphaStride);
        destination = (unsigned short *)((char *)destination + destinationStride);
    }
    return true;
}

// FUNCTION: GAME 0x005e7d30
bool SBDrawUnk005e8450::FUN_005e7d30(void *arg1, void *arg2, void *arg3,
    int arg4, int arg5, int arg6, int arg7, int arg8, int arg9)
{
    FUN_00623f10(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    return true;
}

// FUNCTION: GAME 0x005e7d70
bool SBDrawUnk005e8450::FUN_005e7d70(void *arg1, void *arg2, void *arg3,
    int arg4, int arg5, int arg6, int arg7, int arg8, int arg9)
{
    FUN_006242c4(arg1, arg2, arg4, arg5, arg6, arg7);
    return true;
}

// FUNCTION: GAME 0x005e7da0
bool SBDrawUnk005e8450::FUN_005e7da0(void *arg1, void *arg2, void *arg3,
    int arg4, int arg5, int arg6, int arg7, int arg8, int arg9)
{
    FUN_00623c1c(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    return true;
}

// Parked: component live ranges and loop-parameter reload scheduling differ.
// STUB: GAME 0x005e7de0
bool SBDrawUnk005e8450::FUN_005e7de0(unsigned short *source, unsigned short *destination, unsigned short *alpha,
    unsigned width, unsigned height, unsigned sourceStride, unsigned destinationStride, unsigned alphaStride)
{
    for (unsigned rows = height; rows > 0; --rows)
    {
        for (unsigned columns = width; columns > 0; --columns)
        {
            *destination = SBDrawBlendPixel16(*source, *destination, ((unsigned char *)alpha)[1] & 0xf8);
            ++destination;
            ++alpha;
            ++source;
        }
        source = (unsigned short *)((char *)source + sourceStride);
        alpha = (unsigned short *)((char *)alpha + alphaStride);
        destination = (unsigned short *)((char *)destination + destinationStride);
    }
    return true;
}

// FUNCTION: GAME 0x005e7f60
bool SBDrawUnk005e8450::FUN_005e7f60(void *arg1, void *arg2, void *arg3,
    int arg4, int arg5, int arg6, int arg7, int arg8, int arg9)
{
    FUN_00622800(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    return true;
}

// Parked: component live ranges add a frame slot and reorder source/alpha/destination reads.
// STUB: GAME 0x005e7fa0
bool SBDrawUnk005e8450::FUN_005e7fa0(unsigned short *source, unsigned short *destination, unsigned short *alpha,
    unsigned width, unsigned height, unsigned sourceStride, unsigned destinationStride, unsigned alphaStride)
{
    for (unsigned rows = height; rows > 0; --rows)
    {
        for (unsigned columns = width; columns > 0; --columns)
        {
            *destination = SBDrawBlendPixel16Green(*source, *destination, (*alpha >> 3) & 0xfc);
            ++destination;
            ++alpha;
            ++source;
        }
        source = (unsigned short *)((char *)source + sourceStride);
        alpha = (unsigned short *)((char *)alpha + alphaStride);
        destination = (unsigned short *)((char *)destination + destinationStride);
    }
    return true;
}

// Parked: component live ranges and loop-parameter reload scheduling differ.
// STUB: GAME 0x005e82a0
bool SBDrawUnk005e8450::FUN_005e82a0(unsigned short *source, unsigned short *destination, unsigned short *alpha,
    unsigned width, unsigned height, unsigned sourceStride, unsigned destinationStride, unsigned alphaStride)
{
    for (unsigned rows = height; rows > 0; --rows)
    {
        for (unsigned columns = width; columns > 0; --columns)
        {
            *destination = SBDrawBlendPixel16(*source, *destination, (*(unsigned char *)alpha & 0x1f) << 3);
            ++destination;
            ++alpha;
            ++source;
        }
        source = (unsigned short *)((char *)source + sourceStride);
        alpha = (unsigned short *)((char *)alpha + alphaStride);
        destination = (unsigned short *)((char *)destination + destinationStride);
    }
    return true;
}

// FUNCTION: GAME 0x005e8410
bool SBDrawUnk005e8450::FUN_005e8410(void *arg1, void *arg2, void *arg3,
    int arg4, int arg5, int arg6, int arg7, int arg8, int arg9)
{
    FUN_00622eb4(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    return true;
}

// FUNCTION: GAME 0x005e8450
bool SBDrawUnk005e8450::FUN_005e8450(void *source, void *destination, void *alpha,
    int width, int height, int sourceStride, int destinationStride, int arg8, int arg9)
{
    if (alpha != source)
        SBAssert(1,
            // STRING: GAME 0x006b9264
            "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x141c,
            // STRING: GAME 0x006b9aa0
            "This method does not support different alpha & source pointer");
    FUN_00623268(source, destination, width, height, sourceStride, destinationStride);
    return true;
}

// FUNCTION: GAME 0x005e84a0
bool SBDrawUnk005e8450::FUN_005e84a0(void *arg1, void *arg2, void *arg3,
    int arg4, int arg5, int arg6, int arg7, int arg8, int arg9)
{
    FUN_00622bc0(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    return true;
}

// FUNCTION: GAME 0x005e84e0
bool SBDrawUnk005e8450::FUN_005e84e0(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_00622fd4(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_00623128(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x14ca,
        // STRING: GAME 0x006b9ae0
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005e85b0
bool SBDrawUnk005e8450::FUN_005e85b0(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_00623360(source, destination, width, height, sourceStride, destinationStride);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_0062348c(source, destination, width, height, sourceStride, destinationStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x1578,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005e8670
bool SBDrawUnk005e8450::FUN_005e8670(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_00622ca0(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_00622db4(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x1628,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

extern "C" double __cdecl floor(double);

// FUNCTION: GAME 0x005e8740
bool SBDrawUnk005e8450::FUN_005e8740(unsigned short *source, unsigned short *destination,
    unsigned short *alpha, unsigned width, unsigned height, unsigned sourceStride,
    unsigned destinationStride, float stretchX, float stretchY)
{
    unsigned short *previous = 0;
    float vertical = 0.0f;
    unsigned short originalWidth = width;
    height = (unsigned short)floor(height / stretchY);
    width = (unsigned short)floor(width / stretchX);
    unsigned short pixel;
    for (unsigned short row = 0; row < height; ++row) {
        unsigned short *destinationRow = destination;
        unsigned short *sourceRow = source;
        unsigned short *alphaRow = alpha;
        float horizontal = 0.0f;
        if (previous != destination) {
            for (unsigned short column = 0; column < width; ++column) {
                if (previous != destination) {
                    unsigned short foreground = *source;
                    unsigned short opacity = (*alpha & 0x1f) << 3;
                    unsigned short background = *destination;
                    unsigned short inverse = 0x100 - opacity;
                    unsigned short sourceRed = (foreground >> 8) & 0xf8;
                    unsigned short destinationRed = (background >> 8) & 0xf8;
                    unsigned short sourceGreen = (foreground >> 3) & 0xfc;
                    unsigned short destinationGreen = (background >> 3) & 0xfc;
                    unsigned short sourceBlue = (foreground & 0x1f) << 3;
                    unsigned short destinationBlue = (background & 0x1f) << 3;
                    sourceRed = sourceRed * opacity >> 8;
                    destinationRed = destinationRed * inverse >> 8;
                    sourceGreen = sourceGreen * opacity >> 8;
                    destinationGreen = destinationGreen * inverse >> 8;
                    sourceBlue = sourceBlue * opacity >> 8;
                    destinationBlue = destinationBlue * inverse >> 8;
                    pixel = (((((sourceRed & 0xf8) + (destinationRed & 0xf8)) << 5)
                        + (sourceGreen & 0xfc) + (destinationGreen & 0xfc)) << 3)
                        + (unsigned short)(sourceBlue >> 3) + (unsigned short)(destinationBlue >> 3);
                    *destination = pixel;
                }
                previous = destination;
                horizontal += stretchX;
                ++source;
                ++alpha;
                if (horizontal >= 1.0f) {
                    ++destination;
                    double repetitions = horizontal - 1.0f;
                    unsigned short repeat = 0;
                    if (floor(repetitions) > 0.0) {
                        do {
                            *destination++ = pixel;
                            ++repeat;
                        } while (repeat < floor(repetitions));
                    }
                    horizontal -= floor(horizontal);
                }
            }
        }
        destination = destinationRow;
        previous = destinationRow;
        source = sourceRow + (sourceStride >> 1);
        alpha = alphaRow + (sourceStride >> 1);
        vertical += stretchY;
        if (vertical >= 1.0f) {
            destination += destinationStride >> 1;
            double repetitions = vertical - 1.0f;
            unsigned short repeat = 0;
            if (floor(repetitions) > 0.0) {
                do {
                    memcpy(destination, destinationRow, originalWidth << 1);
                    destination += destinationStride >> 1;
                    ++repeat;
                } while (repeat < floor(repetitions));
            }
            vertical -= floor(vertical);
        }
    }
    return true;
}

#define SBDRAW_SCALED_BLEND_PIXEL(RedShift, GreenShift, SourceGreenMask, DestinationGreenMask) \
    unsigned short sourceRed = (foreground >> RedShift) & 0xf8; \
    unsigned short destinationRed = (background >> RedShift) & 0xf8; \
    unsigned short sourceGreen = (foreground >> GreenShift) & SourceGreenMask; \
    unsigned short destinationGreen = (background >> GreenShift) & DestinationGreenMask; \
    unsigned short sourceBlue = (foreground & 0x1f) << 3; \
    unsigned short destinationBlue = (background & 0x1f) << 3; \
    sourceRed = sourceRed * opacity >> 8; \
    destinationRed = destinationRed * inverse >> 8; \
    sourceGreen = sourceGreen * opacity >> 8; \
    destinationGreen = destinationGreen * inverse >> 8; \
    sourceBlue = sourceBlue * opacity >> 8; \
    destinationBlue = destinationBlue * inverse >> 8; \
    pixel = (((((sourceRed & 0xf8) + (destinationRed & 0xf8)) << 5) \
        + (sourceGreen & SourceGreenMask) + (destinationGreen & DestinationGreenMask)) << GreenShift) \
        + (unsigned short)(sourceBlue >> 3) + (unsigned short)(destinationBlue >> 3);

#define SBDRAW_SCALED_ALPHA_BODY(RedShift, GreenShift, SourceGreenMask, DestinationGreenMask, Opacity) \
    unsigned short *previous = 0; \
    float vertical = 0.0f; \
    unsigned short originalWidth = width; \
    height = (unsigned short)floor(height / stretchY); \
    width = (unsigned short)floor(width / stretchX); \
    unsigned short pixel; \
    for (unsigned short row = 0; row < height; ++row) { \
        unsigned short *destinationRow = destination; \
        unsigned short *sourceRow = source; \
        unsigned short *alphaRow = alpha; \
        float horizontal = 0.0f; \
        if (previous != destination) { \
            for (unsigned short column = 0; column < width; ++column) { \
                if (previous != destination) { \
                    unsigned short foreground = *source; \
                    unsigned short opacity = Opacity; \
                    unsigned short background = *destination; \
                    unsigned short inverse = 0x100 - opacity; \
                    SBDRAW_SCALED_BLEND_PIXEL(RedShift, GreenShift, SourceGreenMask, DestinationGreenMask) \
                    *destination = pixel; \
                } \
                previous = destination; \
                horizontal += stretchX; \
                ++source; \
                ++alpha; \
                if (horizontal >= 1.0f) { \
                    ++destination; \
                    double repetitions = horizontal - 1.0f; \
                    unsigned short repeat = 0; \
                    if (floor(repetitions) > 0.0) { \
                        do { \
                            *destination++ = pixel; \
                            ++repeat; \
                        } while (repeat < floor(repetitions)); \
                    } \
                    horizontal -= floor(horizontal); \
                } \
            } \
        } \
        destination = destinationRow; \
        previous = destinationRow; \
        source = sourceRow + (sourceStride >> 1); \
        alpha = alphaRow + (sourceStride >> 1); \
        vertical += stretchY; \
        if (vertical >= 1.0f) { \
            destination += destinationStride >> 1; \
            double repetitions = vertical - 1.0f; \
            unsigned short repeat = 0; \
            if (floor(repetitions) > 0.0) { \
                do { \
                    memcpy(destination, destinationRow, originalWidth << 1); \
                    destination += destinationStride >> 1; \
                    ++repeat; \
                } while (repeat < floor(repetitions)); \
            } \
            vertical -= floor(vertical); \
        } \
    } \
    return true;

#define SBDRAW_SCALED_KEYED_ALPHA_BODY(RedShift, GreenShift, SourceGreenMask, DestinationGreenMask, Opacity) \
    unsigned short *previous = 0; \
    float vertical = 0.0f; \
    unsigned short originalWidth = width; \
    height = (unsigned short)floor(height / stretchY); \
    width = (unsigned short)floor(width / stretchX); \
    unsigned short pixel; \
    for (unsigned short row = 0; row < height; ++row) { \
        unsigned short *destinationRow = destination; \
        unsigned short *sourceRow = source; \
        unsigned short *alphaRow = alpha; \
        float horizontal = 0.0f; \
        if (previous != destination) { \
            for (unsigned short column = 0; column < width; ++column) { \
                if (previous != destination) { \
                    unsigned short foreground = *source; \
                    if (foreground != (unsigned short)key) { \
                        unsigned short opacity = Opacity; \
                        if (opacity > 255) opacity = 255; \
                        unsigned short inverse = 0x100 - opacity; \
                        unsigned short background = *destination; \
                        SBDRAW_SCALED_BLEND_PIXEL(RedShift, GreenShift, SourceGreenMask, DestinationGreenMask) \
                        *destination = pixel; \
                    } else \
                        pixel = key; \
                } \
                previous = destination; \
                horizontal += stretchX; \
                ++source; \
                ++alpha; \
                if (horizontal >= 1.0f) { \
                    ++destination; \
                    if (pixel != (unsigned short)key) { \
                        unsigned short repeat = 0; \
                        double repetitions = horizontal - 1.0f; \
                        if (floor(repetitions) > 0.0) { \
                            do { \
                                *destination++ = pixel; \
                                ++repeat; \
                            } while (repeat < floor(repetitions)); \
                        } \
                    } else \
                        destination += (unsigned short)floor(horizontal - 1.0f); \
                    horizontal -= floor(horizontal); \
                } \
            } \
        } \
        destination = destinationRow; \
        previous = destinationRow; \
        source = sourceRow + (sourceStride >> 1); \
        alpha = alphaRow + (sourceStride >> 1); \
        vertical += stretchY; \
        if (vertical >= 1.0f) { \
            destination += destinationStride >> 1; \
            double repetitions = vertical - 1.0f; \
            unsigned short repeat = 0; \
            if (floor(repetitions) > 0.0) { \
                do { \
                    memcpy(destination, destinationRow, originalWidth << 1); \
                    destination += destinationStride >> 1; \
                    ++repeat; \
                } while (repeat < floor(repetitions)); \
            } \
            vertical -= floor(vertical); \
        } \
    } \
    return true;

// FUNCTION: GAME 0x005e8b10
bool SBDrawUnk005e8450::FUN_005e8b10(unsigned short *source, unsigned short *destination,
    unsigned short *alpha, unsigned key, unsigned width, unsigned height, unsigned sourceStride,
    unsigned destinationStride, float stretchX, float stretchY)
{
    SBDRAW_SCALED_KEYED_ALPHA_BODY(8, 3, 0xfc, 0xfc, (*alpha & 0x7c0) >> 2)
}

// FUNCTION: GAME 0x005e8f20
bool SBDrawUnk005e8450::FUN_005e8f20(unsigned short *source, unsigned short *destination,
    unsigned short *alpha, unsigned width, unsigned height, unsigned sourceStride,
    unsigned destinationStride, float stretchX, float stretchY)
{
    SBDRAW_SCALED_ALPHA_BODY(8, 3, 0xfc, 0xfc, (*alpha & 0x7c0) >> 3)
}

// FUNCTION: GAME 0x005e92f0
bool SBDrawUnk005e8450::FUN_005e92f0(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_00622924(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_00622a7c(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x1872,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005e93c0
bool SBDrawUnk005e8450::FUN_005e93c0(unsigned short *source, unsigned short *destination,
    unsigned short *alpha, unsigned width, unsigned height, unsigned sourceStride,
    unsigned destinationStride, float stretchX, float stretchY)
{
    SBDRAW_SCALED_ALPHA_BODY(8, 3, 0xfc, 0xfc, (*alpha >> 8) & 0xf8)
}

// FUNCTION: GAME 0x005e9790
bool SBDrawUnk005e8450::FUN_005e9790(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_00624030(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_00624184(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x19a7,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005e9860
bool SBDrawUnk005e8450::FUN_005e9860(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_006243c0(source, destination, width, height, sourceStride, destinationStride);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_006244ec(source, destination, width, height, sourceStride, destinationStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x1a58,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005e9920
bool SBDrawUnk005e8450::FUN_005e9920(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_00623cfc(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_00623e10(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x1b03,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005e99f0
bool SBDrawUnk005e8450::FUN_005e99f0(unsigned short *source, unsigned short *destination,
    unsigned short *alpha, unsigned width, unsigned height, unsigned sourceStride,
    unsigned destinationStride, float stretchX, float stretchY)
{
    SBDRAW_SCALED_ALPHA_BODY(7, 2, 0xfc, 0xf8, (*alpha & 0x1f) << 3)
}

// FUNCTION: GAME 0x005e9dc0
bool SBDrawUnk005e8450::FUN_005e9dc0(unsigned short *source, unsigned short *destination,
    unsigned short *alpha, unsigned key, unsigned width, unsigned height, unsigned sourceStride,
    unsigned destinationStride, float stretchX, float stretchY)
{
    SBDRAW_SCALED_KEYED_ALPHA_BODY(7, 2, 0xf8, 0xf8, (*alpha & 0x7c0) >> 2)
}

// FUNCTION: GAME 0x005ea1d0
bool SBDrawUnk005e8450::FUN_005ea1d0(unsigned short *source, unsigned short *destination,
    unsigned short *alpha, unsigned width, unsigned height, unsigned sourceStride,
    unsigned destinationStride, float stretchX, float stretchY)
{
    SBDRAW_SCALED_ALPHA_BODY(7, 2, 0xfc, 0xf8, (*alpha & 0x7c0) >> 3)
}

// FUNCTION: GAME 0x005ea5a0
bool SBDrawUnk005e8450::FUN_005ea5a0(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_00623978(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_00623ad4(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x1d4d,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005ea670
bool SBDrawUnk005e8450::FUN_005ea670(unsigned short *source, unsigned short *destination,
    unsigned short *alpha, unsigned width, unsigned height, unsigned sourceStride,
    unsigned destinationStride, float stretchX, float stretchY)
{
    SBDRAW_SCALED_ALPHA_BODY(7, 2, 0xf8, 0xf8, (*alpha >> 8) & 0xf8)
}

#undef SBDRAW_SCALED_KEYED_ALPHA_BODY
#undef SBDRAW_SCALED_ALPHA_BODY
#undef SBDRAW_SCALED_BLEND_PIXEL

static __forceinline unsigned short SBDrawScaledColor15(unsigned short color, unsigned short opacity)
{
    unsigned short red = (color >> 7) & 0xf8;
    unsigned short green = (color >> 2) & 0xf8;
    unsigned short blue = (color & 0x1f) << 3;
    red = red * opacity >> 8;
    green = green * opacity >> 8;
    blue = blue * opacity >> 8;
    return ((((red & 0xf8) << 5) | (green & 0xf8)) << 2) | ((blue >> 3) & 0x1f);
}

static __forceinline unsigned short SBDrawScaledColor16(unsigned short color, unsigned short opacity)
{
    unsigned short red = (color >> 8) & 0xf8;
    unsigned short green = (color >> 3) & 0xfc;
    unsigned short blue = (color & 0x1f) << 3;
    red = red * opacity >> 8;
    green = green * opacity >> 8;
    blue = blue * opacity >> 8;
    return ((((red & 0xfff8) << 5) | (green & 0xfc)) << 3) | ((blue >> 3) & 0x1f);
}

#define SBDRAW_SCALED_CONSTANT_BODY(Depth, Key) \
    unsigned short *previous = 0; \
    float vertical = 0.0f; \
    unsigned short originalWidth = width; \
    height = (unsigned short)floor(height / stretchY); \
    width = (unsigned short)floor(width / stretchX); \
    unsigned inverse = 0x100 - opacity; \
    unsigned short foreground; \
    unsigned short pixel; \
    for (unsigned short row = 0; row < height; ++row) { \
        unsigned short *destinationRow = destination; \
        unsigned short *sourceRow = source; \
        float horizontal = 0.0f; \
        if (previous != destination) { \
            for (unsigned short column = 0; column < width; ++column) { \
                if (previous != destination && (foreground = *source) != Key) { \
                    pixel = SBDrawScaledColor##Depth(foreground, opacity) \
                        + SBDrawScaledColor##Depth(*destination, inverse); \
                    *destination = pixel; \
                } else \
                    pixel = Key; \
                previous = destination; \
                horizontal += stretchX; \
                if (horizontal >= 1.0f) { \
                    ++destination; \
                    double repetitions = horizontal - 1.0f; \
                    unsigned short repeat = 0; \
                    if (floor(repetitions) > 0.0) { \
                        do { \
                            if (foreground != Key) *destination = pixel; \
                            ++destination; \
                            ++repeat; \
                        } while (repeat < floor(repetitions)); \
                    } \
                    horizontal -= floor(horizontal); \
                } \
                ++source; \
            } \
        } \
        previous = destinationRow; \
        destination = destinationRow; \
        source = sourceRow + (sourceStride >> 1); \
        vertical += stretchY; \
        if (vertical >= 1.0f) { \
            destination += destinationStride >> 1; \
            double repetitions = vertical - 1.0f; \
            unsigned short repeat = 0; \
            if (floor(repetitions) > 0.0) { \
                do { \
                    memcpy(destination, destinationRow, originalWidth << 1); \
                    destination += destinationStride >> 1; \
                    ++repeat; \
                } while (repeat < floor(repetitions)); \
            } \
            vertical -= floor(vertical); \
        } \
    } \
    return true;

// FUNCTION: GAME 0x005eb450
bool SBDrawUnk005e8450::FUN_005eb450(unsigned short *source, unsigned short *destination,
    unsigned opacity, unsigned width, unsigned height, unsigned sourceStride,
    unsigned destinationStride, float stretchX, float stretchY)
{
    SBDRAW_SCALED_CONSTANT_BODY(15, 0x3e0)
}

// FUNCTION: GAME 0x005eb800
bool SBDrawUnk005e8450::FUN_005eb800(unsigned short *source, unsigned short *destination,
    unsigned opacity, unsigned width, unsigned height, unsigned sourceStride,
    unsigned destinationStride, float stretchX, float stretchY)
{
    SBDRAW_SCALED_CONSTANT_BODY(16, 0x7c0)
}

#undef SBDRAW_SCALED_CONSTANT_BODY

// FUNCTION: GAME 0x005ec230
bool SBDrawUnk005e8450::FUN_005ec230(void *source, void *destination,
    int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY, unsigned arg9, unsigned arg10)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_00622380(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_00622478(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x24ba,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005ec320
bool SBDrawUnk005e8450::FUN_005ec320(void *source, void *destination,
    int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY, unsigned arg9, unsigned arg10)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_006220ec(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_006221e4(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x2566,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005ec410
bool SBDrawUnk005e8450::FUN_005ec410(void *source, void *destination,
    int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY, unsigned arg9, unsigned arg10)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_00623668(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_0062376c(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x2612,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005ec500
bool SBDrawUnk005e8450::FUN_005ec500(void *source, void *destination,
    int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY, unsigned arg9, unsigned arg10)
{
    if (stretchX == 2.0f && stretchY == 2.0f) {
        FUN_0062261c(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    if (stretchX == 0.5f && stretchY == 0.5f) {
        FUN_00622720(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x26be,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005ed270
bool RHUnk005ef320::FUN_005ed270(const RHMobileUnk00607da0 &bounds)
{
    if (!*(bool *)((char *)this + 0x114))
    {
        Sleep(1000);
        typedef unsigned long (RHUnkFXDraw::*CreateSurface)(unsigned short, unsigned short, unsigned long, bool);
        *(unsigned long *)((char *)this + 0x78) = (((RHUnkFXDraw *)this)->*reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(
            *(unsigned short *)((char *)this + 0x10e), *(unsigned short *)((char *)this + 0x110), 0, false);
        ((RHMobileUnk00607da0 *)((char *)this + 0x118))->FUN_00607da0(bounds);
        *(void **)((char *)this + 0x104) = GetStockObject(10);
        *(void **)((char *)this + 0x108) = GetStockObject(12);
        *(short *)((char *)this + 0x12c) = 12;
        *(bool *)((char *)this + 0x114) = true;
        return true;
    }
    return false;
}

// Parked at 0.9130: the lower-bound result shares the end() temporary slot, so the frame is 8 bytes short.
// STUB: GAME 0x005ed2f0
bool FUN_005ed2f0(RHUnk005ef320 *draw, unsigned short x, unsigned short y, const char *format, ...)
{
    if (*(int *)((char *)draw + 0x48) == 0)
    {
        char buffer[132];
        va_list arguments;
        va_start(arguments, format);
        vsprintf(buffer, format, arguments);
        unsigned long key = 1;
        SBDrawUnk005efc10Iterator found = SBDrawFindSurface(*(SBDrawUnk005efc10 *)((char *)draw + 0x54), key);
        if (found == (*(SBDrawUnk005efc10 *)((char *)draw + 0x54)).End())
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x2c82,
                // STRING: GAME 0x006b9c5c
                "Trying to output text without any surfaces");
        void *context;
        SBDrawUnk005e5ec0Surface *surface = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
        long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void **))surface->m_vtable[17])(surface, &context);
        if (result != 0)
        {
            SBSimpleUnk005f9510(g_unk0x006c13c0, "%d", result);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x2c89,
                // STRING: GAME 0x006b9c1c
                "Unable to retrieve a drawing context from a surface DxERR=%s", SBDrawStringData(FUN_005f81d0(result)));
        }
        if (SelectObject(context, *(void **)((char *)draw + 0x104)))
        {
            SetTextAlign(context, 0);
            SetBkMode(context, 1);
            SetTextColor(context, 0xffffff);
            TextOutA(context, x, y, buffer, strlen(buffer));
            surface = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
            ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void *))surface->m_vtable[26])(surface, context);
        }
        else
        {
            surface = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
            ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void *))surface->m_vtable[26])(surface, context);
        }
    }
    return true;
}

// Parked at 0.7968: shared lower-bound/end() temporary slot shortens the frame and moves callee saves.
// STUB: GAME 0x005ed500
bool FUN_005ed500(RHUnk005ef320 *draw, unsigned short x, unsigned short y, const char *format, ...)
{
    char buffer[132];
    va_list arguments;
    va_start(arguments, format);
    vsprintf(buffer, format, arguments);
    if (*(int *)((char *)draw + 0x4c) == 0)
    {
        unsigned long key = 1;
        SBDrawUnk005efc10Iterator found = SBDrawFindSurface(*(SBDrawUnk005efc10 *)((char *)draw + 0x54), key);
        if (found == (*(SBDrawUnk005efc10 *)((char *)draw + 0x54)).End())
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x2d25,
                "Trying to output text without any surfaces");
        void *context;
        SBDrawUnk005e5ec0Surface *surface = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
        long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void **))surface->m_vtable[17])(surface, &context);
        if (result != 0)
        {
            SBSimpleUnk005f9510(g_unk0x006c13c0, "%d", result);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x2d2c,
                "Unable to retrieve a drawing context from a surface DxERR=%s", SBDrawStringData(FUN_005f81d0(result)));
        }
        if (SelectObject(context, *(void **)((char *)draw + 0x108)))
        {
            SetTextAlign(context, 0);
            SetBkMode(context, 1);
            SetTextColor(context, 0);
            TextOutA(context, x + 1, y + 1, buffer, strlen(buffer));
            SetTextColor(context, 0xffffff);
            TextOutA(context, x, y, buffer, strlen(buffer));
        }
        surface = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
        ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void *))surface->m_vtable[26])(surface, context);
    }
    return true;
}

// Parked at 0.8431: rectangle locals and callee-save scheduling differ.
// STUB: GAME 0x005edae0
bool FUN_005edae0(RHUnk005ef320 *draw, const char *format, ...)
{
    if (!*(bool *)((char *)draw + 0x114))
        return false;
    char buffer[132];
    va_list arguments;
    va_start(arguments, format);
    vsprintf(buffer, format, arguments);
    typedef SBDrawUnk005efc10Iterator (SBDrawUnk005efc10::*Find)(const unsigned long &);
    SBDrawUnk005efc10Iterator found = ((*(SBDrawUnk005efc10 *)((char *)draw + 0x54)).*static_cast<Find>(&SBDrawUnk005efc10::FUN_005efbc0))(
        *(unsigned long *)((char *)draw + 0x78));
    if (found.m_node == *(SBDrawUnk005f0090Node **)((char *)draw + 0x58))
    {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x2e12,
            "Trying to output text without any surfaces");
        return false;
    }
    long destination[4];
    long source[4];
    destination[0] = (long)*(float *)((char *)draw + 0x118);
    destination[2] = (long)*(float *)((char *)draw + 0x120);
    source[1] = (long)*(float *)((char *)draw + 0x11c);
    source[3] = (long)*(float *)((char *)draw + 0x124);
    unsigned height = *(unsigned short *)((char *)draw + 0x12c);
    destination[1] = source[1] + height;
    destination[3] = source[3] - height * 2;
    source[0] = destination[0];
    source[2] = destination[2];
    source[3] -= height * 3;
    SBDrawUnk005e5ec0Surface *surface = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
    long result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, long *, SBDrawUnk005e5ec0Surface *, long *, unsigned long, void *))surface->m_vtable[5])(
        surface, source, surface, destination, 0x1000000, 0);
    if (result != 0)
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x2e24,
            // STRING: GAME 0x006b9c88
            "Error during blitting DxERR=%s", SBDrawStringData(FUN_005f81d0(result)));
    destination[1] = source[3];
    unsigned long effect[25] = {0};
    effect[0] = 100;
    effect[20] = 0;
    surface = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
    ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, long *, void *, void *, unsigned long, void *))surface->m_vtable[5])(
        surface, destination, 0, 0, 0x1000400, effect);
    void *context;
    surface = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
    result = ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void **))surface->m_vtable[17])(surface, &context);
    if (result != 0)
    {
        SBSimpleUnk005f9510(g_unk0x006c13c0, "%d", result);
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x2e35,
            "Unable to retrieve a drawing context from a surface DxERR=%s", SBDrawStringData(FUN_005f81d0(result)));
    }
    if (SelectObject(context, *(void **)((char *)draw + 0x104)))
    {
        SetTextAlign(context, 8);
        SetBkColor(context, 0);
        SetTextColor(context, 0xffffff);
        TextOutA(context, (int)*(float *)((char *)draw + 0x118),
            (int)(*(float *)((char *)draw + 0x124) - *(unsigned short *)((char *)draw + 0x12c) * 2), buffer, strlen(buffer));
        surface = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
        ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void *))surface->m_vtable[26])(surface, context);
    }
    else
    {
        surface = *(SBDrawUnk005e5ec0Surface **)((char *)found.m_node + 0x10);
        ((long (__stdcall *)(SBDrawUnk005e5ec0Surface *, void *))surface->m_vtable[26])(surface, context);
    }
    if (*(unsigned char *)((char *)draw + 0x113) == 1)
        ((RHUnkFXDraw *)draw)->FUN_005e5260();
    return true;
}

// Parked: scanline frame, callback selection, and active-edge scheduling differ.
// STUB: GAME 0x005eec00
bool RHUnk005ef320::FUN_005eec00(unsigned long destination, unsigned long source, void *polygon,
    unsigned long scale, unsigned long offsetX, unsigned long offsetY, unsigned long color, unsigned long alpha)
{
    SBDrawUnk005fc3b0Point point;
    SBDrawViewport destinationView;
    SBDrawViewport sourceView;
    if (source == 0 && !*(unsigned char *)((char *)this + 0x112)) {
        source = 1;
        if (destination == 0) destination = 1;
    }
    point.m_x = 0;
    point.m_y = 0;
    if (!FUN_005ee640(polygon, point)) return false;
    unsigned long tint = ((((color >> 16) & 0xff) * alpha) & 0xff00) << 8;
    tint |= ((color & 0xff) * alpha) >> 8;
    tint |= (((color >> 8) & 0xff) * alpha) & 0xff00;
    unsigned long inverseAlpha = 0x100 - alpha;
    RHUnkFXDraw *draw = (RHUnkFXDraw *)this;
    if (!((SBDrawManager *)draw)->FUN_005e5a00(source, sourceView, 0)) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x33f6,
            // STRING: GAME 0x006b98b4
            "Cannot get source surface viewport");
        return false;
    }
    switch (sourceView.m_depth) {
    case 16:
        if (scale == 1) color = 0x00624748;
        else if (scale == 2) color = 0x006245fc;
        else color = 0x0062469c;
        break;
    case 15:
        if (scale == 1) color = 0x00624934;
        else if (scale == 2) color = 0x006247e8;
        else color = 0x00624888;
        break;
    }
    unsigned long sourcePitch = sourceView.m_pitch >> 1;
    unsigned short *sourceData = sourceView.m_pixels;
    unsigned long destinationPitch;
    unsigned short *destinationData;
    if (destination != source) {
        if (!((SBDrawManager *)draw)->FUN_005e5a00(destination, destinationView, 0)) {
            ((SBDrawManager *)draw)->FUN_005e5ea0(sourceView);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x342a,
                "Cannot get source surface viewport");
            return false;
        }
        destinationPitch = destinationView.m_pitch >> 1;
        destinationData = destinationView.m_pixels;
    } else {
        destinationPitch = sourcePitch;
        destinationData = sourceData;
    }
    SBDrawUnk005eec00Edge *&edges = *(SBDrawUnk005eec00Edge **)((char *)this + 0x134);
    unsigned long *&active = *(unsigned long **)((char *)this + 0x13c);
    unsigned long y = *(unsigned long *)((char *)this + 0x144);
    unsigned long &endY = *(unsigned long *)((char *)this + 0x14c);
    unsigned long &activeCount = *(unsigned long *)((char *)this + 0x138);
    unsigned long &edgeCount = *(unsigned long *)((char *)this + 0x130);
    typedef void (__cdecl *Blit)(unsigned short *, unsigned short *, unsigned long,
        unsigned long, unsigned long, unsigned long);
    while (y < endY) {
        unsigned long nextY = ~0UL;
        for (unsigned long i = 0; i < activeCount; ++i)
            if (edges[active[i]].m_10 < nextY) nextY = edges[active[i]].m_10;
        for (i = 0; i < edgeCount; ++i)
            if (!edges[i].m_00 && edges[i].m_08 > y && edges[i].m_08 < nextY)
                nextY = edges[i].m_08;
        unsigned long rows = nextY - y;
        if (rows != 0) {
            unsigned long sourceRow = y * scale;
            unsigned long destinationRow = y * destinationPitch;
            unsigned long sourceOffset = scale * offsetY;
            y += rows;
            do {
                unsigned long sourceBase = ((sourceRow - sourceOffset) >> 1) * sourcePitch;
                for (i = 0; i < (activeCount >> 1); ++i) {
                    unsigned long x = (unsigned long)edges[active[i * 2]].m_14 >> 16;
                    unsigned long right = (unsigned long)edges[active[i * 2 + 1]].m_14 >> 16;
                    ((Blit)color)(destinationData + destinationRow + x,
                        sourceData + sourceBase + (((x - offsetX) * scale) >> 1),
                        sourcePitch * 2, right - x + 1, inverseAlpha, tint);
                }
                for (i = 0; i < activeCount; ++i)
                    edges[active[i]].m_14 += edges[active[i]].m_18;
                sourceRow += scale;
                destinationRow += destinationPitch;
            } while (--rows != 0);
        }
        for (i = 0; i < activeCount; ++i)
            if (edges[active[i]].m_10 == y) edges[active[i]].m_00 = 1;
        activeCount = 0;
        for (i = 0; i < edgeCount; ++i)
            if (!edges[i].m_00 && edges[i].m_08 <= y) active[activeCount++] = i;
        if (activeCount != 0) {
            unsigned long passes = activeCount - 1;
            while (passes != 0) {
                for (i = 0; i < passes; ++i) {
                    unsigned long left = active[i];
                    unsigned long right = active[i + 1];
                    int difference = edges[left].m_14 - edges[right].m_14;
                    if (difference > 0 || (difference == 0 && edges[left].m_18 > edges[right].m_18)) {
                        active[i + 1] = left;
                        active[i] = right;
                    }
                }
                --passes;
            }
        }
    }
    if (y == endY) {
        unsigned long sourceBase = (((y - offsetY) * scale) >> 1) * sourcePitch;
        unsigned long destinationRow = y * destinationPitch;
        for (unsigned long i = 0; i < (activeCount >> 1); ++i) {
            unsigned long x = (unsigned long)edges[active[i * 2]].m_14 >> 16;
            unsigned long right = (unsigned long)edges[active[i * 2 + 1]].m_14 >> 16;
            ((Blit)color)(destinationData + destinationRow + x,
                sourceData + sourceBase + (((x - offsetX) * scale) >> 1),
                sourcePitch * 2, right - x + 1, inverseAlpha, tint);
        }
    }
    if (source != destination) ((SBDrawManager *)draw)->FUN_005e5ea0(destinationView);
    ((SBDrawManager *)draw)->FUN_005e5ea0(sourceView);
    return true;
}

struct SBDrawTreeNode
{
    SBDrawTreeNode *m_left;
    SBDrawTreeNode *m_parent;
    SBDrawTreeNode *m_right;
    unsigned long m_key;
};

// FUNCTION: GAME 0x005ef380
bool RHUnk005ef320::FUN_005ef380(int value)
{
    *((unsigned char *)this + 0x113) = (unsigned char)value;
    return true;
}

// GLOBAL: GAME 0x006c11dc
SBDrawTreeNode *g_unk0x006c11dc;

struct SBDrawDecIterator
{
    SBDrawDecNode *m_node;
    void FUN_005f00e0();
};

// FUNCTION: GAME 0x005ef440
SBDrawUnk005ef440Result SBDrawUnk005efc10::FUN_005ef440(const SBDrawUnk005e4f70Pair &value)
{
    SBDrawDecNode *parent = (SBDrawDecNode *)m_head;
    SBDrawDecNode *node = InsertRoot();
    bool left = true;
    {
        std::_Lockit lock;
        while (node != (SBDrawDecNode *)g_unk0x006c11dc) {
            parent = node;
            left = value.first < node->m_0c;
            node = left ? node->m_00 : node->m_08;
        }
    }
    if (*(bool *)&m_08) {
        SBDrawUnk005ef440Result result(FUN_005efcc0(node, parent, (const SBDrawSurfaceEntry &)value), true);
        return result;
    }
    SBDrawDecIterator previous;
    previous.m_node = parent;
    if (left) {
        if (previous.m_node == (SBDrawDecNode *)Leftmost()) {
            SBDrawUnk005ef440Result result(FUN_005efcc0(node, parent, (const SBDrawSurfaceEntry &)value), true);
            return result;
        }
        previous.FUN_005f00e0();
    }
    if (previous.m_node->m_0c < value.first) {
        SBDrawUnk005ef440Result result(FUN_005efcc0(node, parent, (const SBDrawSurfaceEntry &)value), true);
        return result;
    }
    SBDrawUnk005ef440Result result(SBDrawUnk005efc10Iterator((SBDrawUnk005f0090Node *)previous.m_node), false);
    return result;
}

static inline SBDrawDecNode *SBDrawEraseMinimum(SBDrawDecNode *node)
{
    std::_Lockit lock;
    while (node->m_00 != (SBDrawDecNode *)g_unk0x006c11dc)
        node = node->m_00;
    return node;
}

static inline SBDrawDecNode *SBDrawEraseMaximum(SBDrawDecNode *node)
{
    std::_Lockit lock;
    while (node->m_08 != (SBDrawDecNode *)g_unk0x006c11dc)
        node = node->m_08;
    return node;
}

// FUNCTION: GAME 0x005ef570
SBDrawUnk005efc10Iterator SBDrawUnk005efc10::FUN_005ef570(SBDrawUnk005efc10Iterator position)
{
    Node *x;
    Node *y = (Node *)(position++).m_node;
    Node *z = y;
    std::_Lockit lock;
    if (Left(y) == (Node *)g_unk0x006c11dc)
        x = Right(y);
    else if (Right(y) == (Node *)g_unk0x006c11dc)
        x = Left(y);
    else
    {
        y = SBDrawEraseMinimum(Right(y));
        x = Right(y);
    }
    {
        if (y != z)
        {
            Parent(Left(z)) = y;
            Left(y) = Left(z);
            if (y == Right(z))
                Parent(x) = y;
            else
            {
                Parent(x) = Parent(y);
                Left(Parent(y)) = x;
                Right(y) = Right(z);
                Parent(Right(z)) = y;
            }
            if (InsertRoot() == z)
                InsertRoot() = y;
            else if (Left(Parent(z)) == z)
                Left(Parent(z)) = y;
            else
                Right(Parent(z)) = y;
            Parent(y) = Parent(z);
            std::swap(Color(y), Color(z));
            y = z;
        }
        else
        {
            Parent(x) = Parent(y);
            if (InsertRoot() == z)
                InsertRoot() = x;
            else if (Left(Parent(z)) == z)
                Left(Parent(z)) = x;
            else
                Right(Parent(z)) = x;
            if (EraseLeftmost() == z)
            {
                if (Right(z) == (Node *)g_unk0x006c11dc)
                    EraseLeftmost() = Parent(z);
                else
                    EraseLeftmost() = SBDrawEraseMinimum(x);
            }
            if (EraseRightmost() == z)
            {
                if (Left(z) == (Node *)g_unk0x006c11dc)
                    EraseRightmost() = Parent(z);
                else
                    EraseRightmost() = SBDrawEraseMaximum(x);
            }
        }
        if (Color(y) == 1)
        {
            while (x != InsertRoot() && Color(x) == 1)
            {
                if (x == Left(Parent(x)))
                {
                    Node *w = Right(Parent(x));
                    if (Color(w) == 0)
                    {
                        Color(w) = 1;
                        Color(Parent(x)) = 0;
                        Lrotate(Parent(x));
                        w = Right(Parent(x));
                    }
                    if (Color(Left(w)) == 1 && Color(Right(w)) == 1)
                    {
                        Color(w) = 0;
                        x = Parent(x);
                    }
                    else
                    {
                        if (Color(Right(w)) == 1)
                        {
                            Color(Left(w)) = 1;
                            Color(w) = 0;
                            Rrotate(w);
                            w = Right(Parent(x));
                        }
                        Color(w) = Color(Parent(x));
                        Color(Parent(x)) = 1;
                        Color(Right(w)) = 1;
                        Lrotate(Parent(x));
                        break;
                    }
                }
                else
                {
                    Node *w = Left(Parent(x));
                    if (Color(w) == 0)
                    {
                        Color(w) = 1;
                        Color(Parent(x)) = 0;
                        Rrotate(Parent(x));
                        w = Left(Parent(x));
                    }
                    if (Color(Right(w)) == 1 && Color(Left(w)) == 1)
                    {
                        Color(w) = 0;
                        x = Parent(x);
                    }
                    else
                    {
                        if (Color(Left(w)) == 1)
                        {
                            Color(Right(w)) = 1;
                            Color(w) = 0;
                            Lrotate(w);
                            w = Left(Parent(x));
                        }
                        Color(w) = Color(Parent(x));
                        Color(Parent(x)) = 1;
                        Color(Left(w)) = 1;
                        Rrotate(Parent(x));
                        break;
                    }
                }
            }
            Color(x) = 1;
        }
    }
    operator delete(y);
    --m_size;
    return position;
}

// FUNCTION: GAME 0x005efa90
SBDrawUnk005efc10Iterator SBDrawUnk005efc10::FUN_005efa90(SBDrawUnk005efc10Iterator first, SBDrawUnk005efc10Iterator last)
{
    if (m_size != 0 && first.m_node == *(SBDrawUnk005f0090Node **)m_head && last.m_node == m_head) {
        std::_Lockit lock;
        SBDrawUnk005f0090Node *node = Root();
        {
            std::_Lockit inner;
            for (SBDrawUnk005f0090Node *next = node; next != (SBDrawUnk005f0090Node *)g_unk0x006c11dc; node = next) {
                FUN_005efc30(*(SBDrawUnk005f0090Node **)((char *)next + 8));
                next = *(SBDrawUnk005f0090Node **)next;
                operator delete(node);
            }
        }
        Root() = (SBDrawUnk005f0090Node *)g_unk0x006c11dc;
        m_size = 0;
        Leftmost() = m_head;
        Rightmost() = m_head;
        return Begin();
    }
    while (first != last)
        FUN_005ef570(first++);
    return first;
}

// FUNCTION: GAME 0x005efbc0
SBDrawUnk005efc10Iterator SBDrawUnk005efc10::FUN_005efbc0(const unsigned long &key)
{
    SBDrawUnk005efc10Iterator found(((SBDrawUnk005f0090 *)this)->FUN_005f0090(key));
    return found.m_node == m_head || key < found.m_node->m_key ? SBDrawUnk005efc10Iterator(m_head) : found;
}

// FUNCTION: GAME 0x005efc10
SBDrawUnk005efc10Iterator SBDrawUnk005efc10::FUN_005efc10(const unsigned long &key)
{
    return SBDrawUnk005efc10Iterator(((SBDrawUnk005f0090 *)this)->FUN_005f0090(key));
}

void FUN_005f0320(SBDrawSurfaceEntry *, const SBDrawSurfaceEntry &);

// FUNCTION: GAME 0x005efc30
void SBDrawUnk005efc10::FUN_005efc30(SBDrawUnk005f0090Node *node)
{
    std::_Lockit lock;
    for (SBDrawUnk005f0090Node *next = node; next != (SBDrawUnk005f0090Node *)g_unk0x006c11dc; node = next) {
        FUN_005efc30(*(SBDrawUnk005f0090Node **)((char *)next + 8));
        next = *(SBDrawUnk005f0090Node **)next;
        operator delete(node);
    }
}

inline void SBDrawUnk005efc10::Lrotate(SBDrawDecNode *x)
{
    std::_Lockit lock;
    SBDrawDecNode *y = x->m_08;
    x->m_08 = y->m_00;
    if (y->m_00 != (SBDrawDecNode *)g_unk0x006c11dc)
        y->m_00->m_04 = x;
    y->m_04 = x->m_04;
    if (x == InsertRoot())
        InsertRoot() = y;
    else if (x == x->m_04->m_00)
        x->m_04->m_00 = y;
    else
        x->m_04->m_08 = y;
    y->m_00 = x;
    x->m_04 = y;
}

inline void SBDrawUnk005efc10::Rrotate(SBDrawDecNode *x)
{
    std::_Lockit lock;
    SBDrawDecNode *y = x->m_00;
    x->m_00 = y->m_08;
    if (y->m_08 != (SBDrawDecNode *)g_unk0x006c11dc)
        y->m_08->m_04 = x;
    y->m_04 = x->m_04;
    if (x == InsertRoot())
        InsertRoot() = y;
    else if (x == x->m_04->m_08)
        x->m_04->m_08 = y;
    else
        x->m_04->m_00 = y;
    y->m_08 = x;
    x->m_04 = y;
}

// FUNCTION: GAME 0x005efcc0
SBDrawUnk005efc10Iterator SBDrawUnk005efc10::FUN_005efcc0(SBDrawDecNode *x, SBDrawDecNode *y, const SBDrawSurfaceEntry &value)
{
    std::_Lockit lock;
    SBDrawDecNode *z = (SBDrawDecNode *)operator new(sizeof(SBDrawDecNode));
    z->m_04 = y;
    z->m_28 = 0;
    z->m_00 = (SBDrawDecNode *)g_unk0x006c11dc;
    z->m_08 = (SBDrawDecNode *)g_unk0x006c11dc;
    FUN_005f0320((SBDrawSurfaceEntry *)&z->m_0c, value);
    ++m_size;
    if (y == (SBDrawDecNode *)m_head || x != (SBDrawDecNode *)g_unk0x006c11dc || *(const unsigned long *)&value < y->m_0c)
    {
        y->m_00 = z;
        if (y == (SBDrawDecNode *)m_head)
        {
            InsertRoot() = z;
            ((SBDrawDecNode *)m_head)->m_08 = z;
        }
        else if (y == ((SBDrawDecNode *)m_head)->m_00)
            ((SBDrawDecNode *)m_head)->m_00 = z;
    }
    else
    {
        y->m_08 = z;
        if (y == ((SBDrawDecNode *)m_head)->m_08)
            ((SBDrawDecNode *)m_head)->m_08 = z;
    }
    for (x = z; x != InsertRoot() && x->m_04->m_28 == 0; )
        if (x->m_04 == SBDrawDecNode::Left(x->m_04->m_04))
        {
            y = x->m_04->m_04->m_08;
            if (y->m_28 == 0)
            {
                x->m_04->m_28 = 1;
                y->m_28 = 1;
                x->m_04->m_04->m_28 = 0;
                x = x->m_04->m_04;
            }
            else
            {
                if (x == x->m_04->m_08)
                {
                    x = x->m_04;
                    Lrotate(x);
                }
                x->m_04->m_28 = 1;
                x->m_04->m_04->m_28 = 0;
                Rrotate(x->m_04->m_04);
            }
        }
        else
        {
            y = SBDrawDecNode::Left(x->m_04->m_04);
            if (y->m_28 == 0)
            {
                x->m_04->m_28 = 1;
                y->m_28 = 1;
                x->m_04->m_04->m_28 = 0;
                x = x->m_04->m_04;
            }
            else
            {
                if (x == x->m_04->m_00)
                {
                    x = x->m_04;
                    Rrotate(x);
                }
                x->m_04->m_28 = 1;
                x->m_04->m_04->m_28 = 0;
                Lrotate(x->m_04->m_04);
            }
        }
    InsertRoot()->m_28 = 1;
    return SBDrawUnk005efc10Iterator((SBDrawUnk005f0090Node *)z);
}

void EmitSBDrawInsert(SBDrawUnk005efc10 &tree, const SBDrawSurfaceEntry &value)
{
    tree.FUN_005efcc0(0, 0, value);
    tree.FUN_005e3ed0();
}

// FUNCTION: GAME 0x005f0070
SBDrawUnk005efc10Iterator SBDrawUnk005efc10::FUN_005f0070(const unsigned long &key)
{
    return SBDrawUnk005efc10Iterator(((SBDrawUnk005f0090 *)this)->FUN_005f01a0(key));
}

static inline SBDrawDecNode *SBDrawMinimum(SBDrawDecNode *node)
{
    std::_Lockit lock;
    while (node->m_00 != (SBDrawDecNode *)g_unk0x006c11dc)
        node = node->m_00;
    return node;
}

// FUNCTION: GAME 0x005effc0
void SBDrawUnk005efc10Iterator::FUN_005effc0()
{
    std::_Lockit lock;
#define drawNode (*(SBDrawDecNode **)&m_node)
    if (drawNode->m_08 != (SBDrawDecNode *)g_unk0x006c11dc)
        drawNode = SBDrawMinimum(drawNode->m_08);
    else {
        SBDrawDecNode *parent;
        while (drawNode == (parent = drawNode->m_04)->m_08)
            drawNode = parent;
        if (drawNode->m_08 != parent)
            drawNode = parent;
    }
#undef drawNode
}

// FUNCTION: GAME 0x005f0090
SBDrawUnk005f0090Node *SBDrawUnk005f0090::FUN_005f0090(const unsigned long &key)
{
    std::_Lockit lock;
    SBDrawTreeNode *node = ((SBDrawTreeNode *)m_head)->m_parent;
    SBDrawTreeNode *result = (SBDrawTreeNode *)m_head;
    while (node != g_unk0x006c11dc)
    {
        if (node->m_key < key)
            node = node->m_right;
        else
            result = node, node = node->m_left;
    }
    return (SBDrawUnk005f0090Node *)result;
}

static inline SBDrawDecNode *&SBDrawDecLeft(SBDrawDecNode *value) { return value->m_00; }

static inline SBDrawDecNode *SBDrawDecMax(SBDrawDecNode *node)
{
    std::_Lockit lock;
    while (node->m_08 != (SBDrawDecNode *)g_unk0x006c11dc)
        node = node->m_08;
    return node;
}

// FUNCTION: GAME 0x005f00e0
void SBDrawDecIterator::FUN_005f00e0()
{
    std::_Lockit lock;
    if (m_node->m_28 == 0 && m_node->m_04->m_04 == m_node)
        m_node = m_node->m_08;
    else if (SBDrawDecLeft(m_node) != (SBDrawDecNode *)g_unk0x006c11dc)
        m_node = SBDrawDecMax(SBDrawDecLeft(m_node));
    else
    {
        SBDrawDecNode *parent;
        while (m_node == (parent = m_node->m_04)->m_00)
            m_node = parent;
        m_node = parent;
    }
}

void EmitSBDrawDec()
{
    SBDrawDecIterator iterator;
    iterator.FUN_005f00e0();
}

// FUNCTION: GAME 0x005f01a0
SBDrawUnk005f0090Node *SBDrawUnk005f0090::FUN_005f01a0(const unsigned long &key)
{
    std::_Lockit lock;
    SBDrawTreeNode *node = ((SBDrawTreeNode *)m_head)->m_parent;
    SBDrawTreeNode *result = (SBDrawTreeNode *)m_head;
    while (node != g_unk0x006c11dc)
    {
        if (key < node->m_key)
            result = node, node = node->m_left;
        else
            node = node->m_right;
    }
    return (SBDrawUnk005f0090Node *)result;
}

typedef SBDrawUnk005efc10Iterator SBDrawTreeIterator;
typedef SBDrawUnk005efc10Iterator SBDrawTreeIteratorB;

// FUNCTION: GAME 0x005f02f0
void FUN_005f02f0(SBDrawTreeIterator first, SBDrawTreeIterator last, int &count)
{
    SBDrawTreeIterator current;
    current.m_node = first.m_node;
    for (; current != last; ++current)
        ++count;
}

struct SBDrawSurfaceEntry
{
    unsigned long m_values[7];
};

// FUNCTION: GAME 0x005f0320
void FUN_005f0320(SBDrawSurfaceEntry *entry, const SBDrawSurfaceEntry &value)
{
    if (entry != 0)
        *entry = value;
}

// FUNCTION: GAME 0x005f0440
void FUN_005f0440(SBDrawTreeIteratorB first, SBDrawTreeIteratorB last, int &count)
{
    for (; first != last; ++first)
        ++count;
}

void EmitSBDrawManager(SBDrawUnk005e8450 *draw, void *buffer)
{
    ((RHUnkFXDraw *)draw)->FUN_005e4f70(0, 0, 0, 0);
    ((RHUnk005ef320 *)draw)->FUN_005e5890(0, (void **)buffer, 0);
    ((RHUnk005ef320 *)draw)->FUN_005e5d30(0);
    ((RHUnk005ef320 *)draw)->FUN_005e5bd0(0, buffer);
    ((RHUnk005ef320 *)draw)->FUN_005e3f70();
    ((RHUnk005ef320 *)draw)->FUN_005e3f40(*(const std::string *)buffer);
    ((RHUnk005ef320 *)draw)->FUN_005eec00(0, 0, buffer, 0, 0, 0, 0, 0);
    draw->FUN_005e7880(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e7d30(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e7d70(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e7da0(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e7f60(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e8410(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e8450(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e84a0(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e84e0(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e85b0(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e8670(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e8740((unsigned short *)buffer, (unsigned short *)buffer,
        (unsigned short *)buffer, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e92f0(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e9790(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e9860(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e9920(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005ea5a0(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005ec230(buffer, buffer, 0, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005ec320(buffer, buffer, 0, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005ec410(buffer, buffer, 0, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005ec500(buffer, buffer, 0, 0, 0, 0, 0, 0, 0, 0);
    ((SBDrawUnk005efc10 *)buffer)->FUN_005efbc0(0);
    ((SBDrawUnk005efc10 *)buffer)->FUN_005efa90(
        ((SBDrawUnk005efc10 *)buffer)->Begin(), SBDrawUnk005efc10Iterator(0));
    ((SBDrawUnk005efc10 *)buffer)->FUN_005f0070(0);
    int count = 0;
    FUN_005f02f0(*(SBDrawTreeIterator *)buffer, *(SBDrawTreeIterator *)buffer, count);
    FUN_005f0320((SBDrawSurfaceEntry *)buffer, *(SBDrawSurfaceEntry *)buffer);
    FUN_005f0440(*(SBDrawTreeIteratorB *)buffer, *(SBDrawTreeIteratorB *)buffer, count);
}

// GLOBAL: GAME 0x006c11b8
unsigned __int64 g_unk0x006c11b8;

// GLOBAL: GAME 0x006c11c8
unsigned __int64 g_unk0x006c11c8;

inline unsigned __int64 SBDrawMultiplyHigh(unsigned __int64 left, unsigned __int64 right)
{
    union Channels {
        unsigned __int64 packed;
        unsigned short lane[4];
    } lhs, rhs, result;
    lhs.packed = left;
    rhs.packed = right;
    for (unsigned i = 0; i < 4; ++i) {
        int product = (short)lhs.lane[i] * (short)rhs.lane[i];
        result.lane[i] = (unsigned short)(product >> 16);
    }
    return result.packed;
}

inline unsigned __int64 SBDrawSaturatedAdd(unsigned __int64 left, unsigned __int64 right)
{
    union Channels {
        unsigned __int64 packed;
        unsigned short lane[4];
    } lhs, rhs, result;
    lhs.packed = left;
    rhs.packed = right;
    for (unsigned i = 0; i < 4; ++i) {
        unsigned sum = lhs.lane[i] + rhs.lane[i];
        if (sum > 0xffff) sum = 0xffff;
        result.lane[i] = (unsigned short)sum;
    }
    return result.packed;
}

inline unsigned SBDrawDoubleBytes(unsigned value)
{
    unsigned result = 0;
    for (unsigned shift = 0; shift < 32; shift += 8) {
        unsigned doubled = (unsigned char)(value >> shift) * 2;
        if (doubled > 0xff) doubled = 0xff;
        result |= doubled << shift;
    }
    return result;
}

template<int Depth>
inline unsigned short SBDrawScalarScale(unsigned short pixel, unsigned short alpha)
{
    unsigned short red = (pixel & (Depth == 16 ? 0xf800 : 0x7c00)) >> (Depth == 16 ? 11 : 10);
    unsigned short green = (pixel & (Depth == 16 ? 0x7e0 : 0x3e0)) >> 5;
    unsigned short blue = pixel & 0x1f;
    red = (unsigned short)(red * alpha) >> 8;
    green = (unsigned short)(green * alpha) >> 8;
    blue = (unsigned short)(blue * alpha) >> 8;
    return (unsigned short)((red << (Depth == 16 ? 11 : 10)) | (green << 5) | blue);
}

#define SBDRAW_SCALAR_KEYING_BODY(Depth, Transparent) \
    unsigned short *src = (unsigned short *)source; \
    unsigned short *dst = (unsigned short *)destination; \
    unsigned rows = (unsigned short)height; \
    do { \
        unsigned columns = (unsigned short)width; \
        do { \
            unsigned short pixel = *src++; \
            if (pixel == 0x1f) pixel = SBDrawScalarScale<Depth>(*dst, (unsigned short)alpha); \
            else if (Transparent && pixel == (Depth == 16 ? 0x7c0 : 0x3e0)) { \
                ++dst; \
                continue; \
            } \
            *dst++ = pixel; \
        } while ((columns = (unsigned short)(columns - 1)) != 0); \
        src = (unsigned short *)((char *)src + sourceStride); \
        dst = (unsigned short *)((char *)dst + destinationStride); \
    } while ((rows = (unsigned short)(rows - 1)) != 0);

// FUNCTION: GAME 0x00621d80
__declspec(naked) void FUN_00621d80()
{
    __asm {
        push ebp
        _emit 0x89
        _emit 0xe5
        pushad
        pushfd
        pop eax
        _emit 0x89
        _emit 0xc3
        xor eax, 00200000h
        push eax
        popfd
        pushfd
        pop eax
        _emit 0x39
        _emit 0xd8
        je unsupported
        _emit 0x31
        _emit 0xc0
        cpuid
        mov eax, 1
        cpuid
        test edx, 00080000h
        je unsupported
        mov eax, 1
        jmp $ + 7
    unsupported:
        _emit 0x31
        _emit 0xc0
        popad
        pop ebp
        ret
    }
}

// Parked: handwritten pusha/bswap register packing differs from VC6 C++.
// STUB: GAME 0x00621db8
void FUN_00621db8(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned unused)
{
    SBDRAW_SCALAR_KEYING_BODY(16, true)
}

// Parked: handwritten pusha/bswap register packing differs from VC6 C++.
// STUB: GAME 0x00621e5c
void FUN_00621e5c(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned unused)
{
    SBDRAW_SCALAR_KEYING_BODY(16, false)
}

// Parked: handwritten pusha/bswap register packing differs from VC6 C++.
// STUB: GAME 0x00621ef0
void FUN_00621ef0(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned unused)
{
    SBDRAW_SCALAR_KEYING_BODY(15, true)
}

// Parked: handwritten pusha/bswap register packing differs from VC6 C++.
// STUB: GAME 0x00621f94
void FUN_00621f94(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned unused)
{
    SBDRAW_SCALAR_KEYING_BODY(15, false)
}

#undef SBDRAW_SCALAR_KEYING_BODY

template<int Depth>
inline unsigned __int64 SBDrawUnpackPixel(unsigned short pixel)
{
    unsigned channels = (pixel & (Depth == 16 ? 0x7ff : 0x3ff)) << 3;
    unsigned char green = (unsigned char)(channels >> 8);
    green <<= Depth == 16 ? 1 : 2;
    channels = (channels & 0xffff0000) | ((unsigned)green << 8) | ((unsigned char)channels >> 1);
    channels |= (pixel & (Depth == 16 ? 0xf800 : 0x7c00)) << (Depth == 16 ? 7 : 8);
    return ((unsigned __int64)(unsigned char)channels << 8) |
        ((unsigned __int64)(unsigned char)(channels >> 8) << 24) |
        ((unsigned __int64)(unsigned char)(channels >> 16) << 40) |
        ((unsigned __int64)(unsigned char)(channels >> 24) << 56);
}

template<int Depth>
inline unsigned short SBDrawPackPixel(unsigned __int64 channels)
{
    channels &= Depth == 16 ? g_unk0x006c11c8 : g_unk0x006c11b8;
    unsigned low = (unsigned)channels;
    unsigned pixel = (unsigned char)(low >> 8) | (low >> (Depth == 16 ? 18 : 19));
    pixel |= (unsigned)(channels >> (Depth == 16 ? 29 : 30));
    return (unsigned short)pixel;
}

inline unsigned __int64 SBDrawConstantWeight(unsigned alpha)
{
    unsigned weight = alpha << 6;
    weight |= weight << 16;
    return ((unsigned __int64)weight << 32) | weight;
}

inline unsigned __int64 SBDrawChannelWeight(unsigned alpha)
{
    unsigned char value = (unsigned char)alpha;
    return ((unsigned __int64)value << 8) | ((unsigned __int64)value << 24) |
        ((unsigned __int64)value << 40);
}

template<int Depth, int Mode>
inline unsigned short SBDrawAlphaPixel(unsigned short source, unsigned short destination, unsigned short alpha)
{
    unsigned weight;
    if (Mode == 0) {
        unsigned value = Depth == 16 ? alpha : (unsigned)alpha * 2;
        weight = SBDrawDoubleBytes(value) >> 10;
    } else if (Mode == 3) {
        weight = (source & 0x1f) * 2;
    } else {
        weight = (alpha & 0x1f) * 2;
    }
    if (Mode == 1)
        return SBDrawPackPixel<Depth>(SBDrawMultiplyHigh(SBDrawUnpackPixel<Depth>(destination), SBDrawChannelWeight(weight)));
    unsigned sourceWeight = Mode == 3 ? ((weight ^ 0x3f) + 1) : weight;
    unsigned destinationWeight = Mode == 3 ? weight : ((weight ^ 0x3f) + 1);
    unsigned __int64 foreground = SBDrawMultiplyHigh(SBDrawUnpackPixel<Depth>(source), SBDrawChannelWeight(sourceWeight));
    unsigned __int64 background = SBDrawMultiplyHigh(SBDrawUnpackPixel<Depth>(destination), SBDrawChannelWeight(destinationWeight));
    return SBDrawPackPixel<Depth>(SBDrawSaturatedAdd(foreground, background));
}

#define SBDRAW_RECTANGLE_SETUP(Scale) \
    unsigned columns = (unsigned)width; \
    unsigned rows = (unsigned)height; \
    if (Scale == 2) { columns >>= 1; rows >>= 1; } \
    if (columns == 0 || rows == 0) return; \
    unsigned short *src = (unsigned short *)source; \
    unsigned short *dst = (unsigned short *)destination; \
    int destinationRow = destinationStride; \
    if (Scale == 2) { \
        sourceStride -= columns * 2; \
        destinationStride = (destinationStride - columns * 2) * 2; \
    } else if (Scale == 0) { \
        sourceStride = (sourceStride - columns * 2) * 2; \
        destinationStride -= columns * 2; \
    }

#define SBDRAW_STORE_PIXEL(Scale, Pixel) \
    if (Scale == 2) { \
        unsigned pair = (unsigned)(Pixel) | ((unsigned)(Pixel) << 16); \
        *(unsigned *)dst = pair; \
        *(unsigned *)((char *)dst + destinationRow) = pair; \
    } else *dst = (Pixel);

#define SBDRAW_KEYING_BODY(Depth, Scale, Transparent) \
    SBDRAW_RECTANGLE_SETUP(Scale) \
    unsigned __int64 weight = SBDrawConstantWeight(alpha); \
    do { \
        for (unsigned count = columns; count != 0; --count) { \
            unsigned short pixel = *src; \
            if (!Transparent || pixel != (Depth == 16 ? 0x7c0 : 0x3e0)) { \
                if ((unsigned)pixel == key) pixel = SBDrawPackPixel<Depth>(SBDrawMultiplyHigh(SBDrawUnpackPixel<Depth>(*dst), weight)); \
                SBDRAW_STORE_PIXEL(Scale, pixel) \
            } \
            src += Scale == 0 ? 2 : 1; \
            dst += Scale == 2 ? 2 : 1; \
        } \
        src = (unsigned short *)((char *)src + sourceStride); \
        dst = (unsigned short *)((char *)dst + destinationStride); \
    } while (--rows != 0);

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622028
void FUN_00622028(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(16, 1, false)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x006220ec
void FUN_006220ec(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(16, 2, false)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x006221e4
void FUN_006221e4(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(16, 0, false)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x006222bc
void FUN_006222bc(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(15, 1, false)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622380
void FUN_00622380(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(15, 2, false)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622478
void FUN_00622478(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(15, 0, false)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622550
void FUN_00622550(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(16, 1, true)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x0062261c
void FUN_0062261c(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(16, 2, true)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622720
void FUN_00622720(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(16, 0, true)
}

#define SBDRAW_ALPHA_BODY(Depth, Scale, Mode) \
    SBDRAW_RECTANGLE_SETUP(Scale) \
    unsigned short *mask = (unsigned short *)alpha; \
    if (Scale == 2) alphaStride -= columns * 2; \
    else if (Scale == 0) alphaStride = (alphaStride - columns * 2) * 2; \
    do { \
        for (unsigned count = columns; count != 0; --count) { \
            unsigned short pixel = *src; \
            if (pixel != (Depth == 16 ? 0x7c0 : 0x3e0)) { \
                pixel = SBDrawAlphaPixel<Depth, Mode>(pixel, *dst, *mask); \
                SBDRAW_STORE_PIXEL(Scale, pixel) \
            } \
            src += Scale == 0 ? 2 : 1; \
            dst += Scale == 2 ? 2 : 1; \
            mask += Scale == 0 ? 2 : 1; \
        } \
        src = (unsigned short *)((char *)src + sourceStride); \
        dst = (unsigned short *)((char *)dst + destinationStride); \
        mask = (unsigned short *)((char *)mask + alphaStride); \
    } while (--rows != 0);

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622800
void FUN_00622800(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(16, 1, 0)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622924
void FUN_00622924(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(16, 2, 0)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622a7c
void FUN_00622a7c(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(16, 0, 0)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622bc0
void FUN_00622bc0(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(16, 1, 1)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622ca0
void FUN_00622ca0(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(16, 2, 1)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622db4
void FUN_00622db4(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(16, 0, 1)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622eb4
void FUN_00622eb4(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(16, 1, 2)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00622fd4
void FUN_00622fd4(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(16, 2, 2)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623128
void FUN_00623128(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(16, 0, 2)
}

#define SBDRAW_INVERSE_ALPHA_BODY(Depth, Scale) \
    SBDRAW_RECTANGLE_SETUP(Scale) \
    do { \
        for (unsigned count = columns; count != 0; --count) { \
            unsigned short pixel = *src; \
            if (pixel != (Depth == 16 ? 0x7c0 : 0x3e0)) { \
                pixel = SBDrawAlphaPixel<Depth, 3>(pixel, *dst, 0); \
                SBDRAW_STORE_PIXEL(Scale, pixel) \
            } \
            src += Scale == 0 ? 2 : 1; \
            dst += Scale == 2 ? 2 : 1; \
        } \
        src = (unsigned short *)((char *)src + sourceStride); \
        dst = (unsigned short *)((char *)dst + destinationStride); \
    } while (--rows != 0);

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623268
void FUN_00623268(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride)
{
    SBDRAW_INVERSE_ALPHA_BODY(16, 1)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623360
void FUN_00623360(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride)
{
    SBDRAW_INVERSE_ALPHA_BODY(16, 2)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x0062348c
void FUN_0062348c(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride)
{
    SBDRAW_INVERSE_ALPHA_BODY(16, 0)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623598
void FUN_00623598(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(15, 1, true)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623668
void FUN_00623668(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(15, 2, true)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x0062376c
void FUN_0062376c(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride, unsigned alpha, unsigned key)
{
    SBDRAW_KEYING_BODY(15, 0, true)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623850
void FUN_00623850(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(15, 1, 0)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623978
void FUN_00623978(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(15, 2, 0)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623ad4
void FUN_00623ad4(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(15, 0, 0)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623c1c
void FUN_00623c1c(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(15, 1, 1)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623cfc
void FUN_00623cfc(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(15, 2, 1)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623e10
void FUN_00623e10(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(15, 0, 1)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00623f10
void FUN_00623f10(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(15, 1, 2)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00624030
void FUN_00624030(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(15, 2, 2)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00624184
void FUN_00624184(void *source, void *destination, void *alpha, int width, int height,
    int sourceStride, int destinationStride, int alphaStride)
{
    SBDRAW_ALPHA_BODY(15, 0, 2)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x006242c4
void FUN_006242c4(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride)
{
    SBDRAW_INVERSE_ALPHA_BODY(15, 1)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x006243c0
void FUN_006243c0(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride)
{
    SBDRAW_INVERSE_ALPHA_BODY(15, 2)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x006244ec
void FUN_006244ec(void *source, void *destination, int width, int height,
    int sourceStride, int destinationStride)
{
    SBDRAW_INVERSE_ALPHA_BODY(15, 0)
}

#define SBDRAW_TINTED_LINE_BODY(Depth, Scale) \
    if (Scale == 0) width = (unsigned)width >> 1; \
    if (width <= 0) return; \
    unsigned short *src = (unsigned short *)source; \
    unsigned short *dst = (unsigned short *)destination; \
    unsigned __int64 tint = ((unsigned __int64)(unsigned char)color << 5) | \
        ((unsigned __int64)(unsigned char)(color >> 8) << 21) | \
        ((unsigned __int64)(unsigned char)(color >> 16) << 37) | \
        ((unsigned __int64)(unsigned char)(color >> 24) << 53); \
    unsigned __int64 weight = SBDrawConstantWeight(alpha); \
    for (; width != 0; --width) { \
        unsigned short pixel = SBDrawPackPixel<Depth>(SBDrawSaturatedAdd(SBDrawMultiplyHigh(SBDrawUnpackPixel<Depth>(*src), weight), tint)); \
        SBDRAW_STORE_PIXEL(Scale, pixel) \
        src += Scale == 0 ? 2 : 1; \
        dst += Scale == 2 ? 2 : 1; \
    }

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x006245fc
void FUN_006245fc(void *source, void *destination, int destinationRow, int width,
    unsigned color, unsigned alpha)
{
    SBDRAW_TINTED_LINE_BODY(16, 1)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x0062469c
void FUN_0062469c(void *source, void *destination, int destinationRow, int width,
    unsigned color, unsigned alpha)
{
    SBDRAW_TINTED_LINE_BODY(16, 2)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00624748
void FUN_00624748(void *source, void *destination, int destinationRow, int width,
    unsigned color, unsigned alpha)
{
    SBDRAW_TINTED_LINE_BODY(16, 0)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x006247e8
void FUN_006247e8(void *source, void *destination, int destinationRow, int width,
    unsigned color, unsigned alpha)
{
    SBDRAW_TINTED_LINE_BODY(15, 1)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00624888
void FUN_00624888(void *source, void *destination, int destinationRow, int width,
    unsigned color, unsigned alpha)
{
    SBDRAW_TINTED_LINE_BODY(15, 2)
}

// Parked: handwritten pusha/MMX/emms differs from scalar VC6 C++.
// STUB: GAME 0x00624934
void FUN_00624934(void *source, void *destination, int destinationRow, int width,
    unsigned color, unsigned alpha)
{
    SBDRAW_TINTED_LINE_BODY(15, 0)
}

#undef SBDRAW_TINTED_LINE_BODY
#undef SBDRAW_INVERSE_ALPHA_BODY
#undef SBDRAW_ALPHA_BODY
#undef SBDRAW_KEYING_BODY
#undef SBDRAW_STORE_PIXEL
#undef SBDRAW_RECTANGLE_SETUP
