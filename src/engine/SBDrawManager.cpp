#include "SBDrawManager.h"
#include "Toolbox.h"
#include "SBResourceManager.h"

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

void EmitSBDrawManager(SBDrawUnk005e8450 *draw, void *buffer)
{
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
