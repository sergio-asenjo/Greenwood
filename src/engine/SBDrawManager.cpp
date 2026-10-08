#include "SBDrawManager.h"
#include "SBResourceManager.h"
#include <string>

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
