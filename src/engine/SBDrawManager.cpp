#include "SBDrawManager.h"
#include "SBResourceManager.h"
#include <string>

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *);

void SBAssert(int, const char *, int, const char *, ...);
std::string FUN_005f81d0(long);

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    ~RHUnk00613e90();
    char m_00[4];
    unsigned short m_width;
    char m_06[2];
    unsigned long m_pitch;
    unsigned short m_depth;
    char m_0e[2];
    unsigned short *m_data;
    char m_14[4];
};

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int, int, int, int);
    bool FUN_005e4f70(unsigned long, unsigned short, unsigned short, unsigned long);
    void Unk005e5160(unsigned long);
    void FUN_005e5260();
    bool Unk005e5a00(unsigned long, RHUnk00613e90 &, unsigned long);
    void Unk005e5ea0(RHUnk00613e90 &);
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
    void FUN_005e61e0(unsigned long, unsigned long, unsigned long, unsigned long);
    void FUN_005e6440(unsigned long, int, int, unsigned long, unsigned long);
    unsigned short UnkField10c() const { return m_depth; }
    char m_00[0x10c];
    unsigned short m_depth;
};

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    ~SBGeoPoint2D();
    float m_x;
    float m_y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
};

extern float g_unk0x006774f4;
extern float g_unk0x006775d8;

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
bool RHUnkFXDraw::Unk005e5a00(unsigned long surface, RHUnk00613e90 &view, unsigned long flags)
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
    view.m_data = (unsigned short *)description[9];
    view.m_width = (unsigned short)description[3];
    *(unsigned short *)((char *)&view + 6) = (unsigned short)description[2];
    *((bool *)&view + 0x14) = locked;
    view.m_pitch = description[4];
    *(unsigned long *)&view = surface;
    view.m_depth = m_depth;
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

// FUNCTION: GAME 0x005e7880
bool SBDrawUnk005e8450::FUN_005e7880(void *arg1, void *arg2, void *arg3,
    int arg4, int arg5, int arg6, int arg7, int arg8, int arg9)
{
    FUN_00623850(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
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

// FUNCTION: GAME 0x005e7f60
bool SBDrawUnk005e8450::FUN_005e7f60(void *arg1, void *arg2, void *arg3,
    int arg4, int arg5, int arg6, int arg7, int arg8, int arg9)
{
    FUN_00622800(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
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
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_00622fd4(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
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
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_00623360(source, destination, width, height, sourceStride, destinationStride);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
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
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_00622ca0(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
        FUN_00622db4(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x1628,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005e92f0
bool SBDrawUnk005e8450::FUN_005e92f0(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_00622924(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
        FUN_00622a7c(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x1872,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005e9790
bool SBDrawUnk005e8450::FUN_005e9790(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_00624030(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
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
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_006243c0(source, destination, width, height, sourceStride, destinationStride);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
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
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_00623cfc(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
        FUN_00623e10(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x1b03,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005ea5a0
bool SBDrawUnk005e8450::FUN_005ea5a0(void *source, void *destination, void *alpha,
    int arg4, int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY)
{
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_00623978(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
        FUN_00623ad4(source, destination, alpha, width, height,
            sourceStride, destinationStride, sourceStride);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x1d4d,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// FUNCTION: GAME 0x005ec230
bool SBDrawUnk005e8450::FUN_005ec230(void *source, void *destination,
    int width, int height, int sourceStride, int destinationStride,
    float stretchX, float stretchY, unsigned arg9, unsigned arg10)
{
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_00622380(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
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
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_006220ec(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
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
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_00623668(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
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
    if (stretchX == g_unk0x006774f4 && stretchY == g_unk0x006774f4) {
        FUN_0062261c(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    if (stretchX == g_unk0x006775d8 && stretchY == g_unk0x006775d8) {
        FUN_00622720(source, destination, width, height, sourceStride,
            destinationStride, arg10 & 0xffff, arg9 & 0xffff);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x26be,
        "This method is not supported for stretching factors different of 2 or 0.5 !");
    return true;
}

// Parked: scanline frame, callback selection, and active-edge scheduling differ.
// STUB: GAME 0x005eec00
bool RHUnk005ef320::FUN_005eec00(unsigned long destination, unsigned long source, void *polygon,
    unsigned long scale, unsigned long offsetX, unsigned long offsetY, unsigned long color, unsigned long alpha)
{
    SBDrawUnk005fc3b0Point point;
    RHUnk00613e90 destinationView;
    RHUnk00613e90 sourceView;
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
    if (!draw->Unk005e5a00(source, sourceView, 0)) {
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
    unsigned short *sourceData = sourceView.m_data;
    unsigned long destinationPitch;
    unsigned short *destinationData;
    if (destination != source) {
        if (!draw->Unk005e5a00(destination, destinationView, 0)) {
            draw->Unk005e5ea0(sourceView);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBDrawManager.cpp", 0x342a,
                "Cannot get source surface viewport");
            return false;
        }
        destinationPitch = destinationView.m_pitch >> 1;
        destinationData = destinationView.m_data;
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
    if (source != destination) draw->Unk005e5ea0(destinationView);
    draw->Unk005e5ea0(sourceView);
    return true;
}

void EmitSBDrawManager(SBDrawUnk005e8450 *draw, void *buffer)
{
    ((RHUnkFXDraw *)draw)->FUN_005e4f70(0, 0, 0, 0);
    ((RHUnk005ef320 *)draw)->FUN_005e5890(0, (void **)buffer, 0);
    ((RHUnk005ef320 *)draw)->FUN_005e5d30(0);
    ((RHUnk005ef320 *)draw)->FUN_005e5bd0(0, buffer);
    ((RHUnk005ef320 *)draw)->FUN_005e3f70();
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
    draw->FUN_005e92f0(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e9790(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e9860(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005e9920(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005ea5a0(buffer, buffer, buffer, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005ec230(buffer, buffer, 0, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005ec320(buffer, buffer, 0, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005ec410(buffer, buffer, 0, 0, 0, 0, 0, 0, 0, 0);
    draw->FUN_005ec500(buffer, buffer, 0, 0, 0, 0, 0, 0, 0, 0);
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
