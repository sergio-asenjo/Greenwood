// RHOrder — declarations for RHOrder.cpp (decompiled TU).
//
// BINDING (0x0054e750): RHOrder::Serialize(SBFile&, RHSequenceElement*).
// BINDING (0x0054e9a0): RHOrder::SerializeStaticStuff(SBFile&).
// See src/RHOrder.cpp for the evidence chain of both.
//
// The Windows codegen calls SerializeStaticStuff WITHOUT a `this` (the body
// never uses ecx as this), so on this build it is a static member. Serialize is
// a real __thiscall: `mov edi,ecx` at entry and `ret 8` at exit.

#include "SB.h"

// Embedded point sub-object (two 4-byte fields). Its Serialize is the target
// 0x005fc2a0 (__FILE__ P:\Robin Hood\SBLibNG\SBGeoPoint2D.cpp); defined once in
// RHGraphicConfig_stubs.cpp.
#ifndef SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    bool Serialize(SBFile &file);

private:
    char m_unk[0x8];
};
#endif

// Vector sub-object (three 4-byte fields). Its Serialize is the target
// 0x005df510 (three 4-byte Access calls; oracle: SBGeoVector3D::Serialize).
// Defined once in RHTitbits_stubs.cpp as RHUnk005df510::Serialize.
class RHUnk005df510
{
public:
    int m_0;
    int m_4;
    int m_8;

    bool Serialize(SBFile &file);
};

class RHElement;
class RHSequenceElementCalls;

// The engine singleton's element-pointer serialiser. Target 0x004c3a10
// (thiscall receiver read from 0x006c0a88). Defined once in
// RHMinimap_stubs.cpp. The base instantiation is used here.
class RHEngine
{
public:
    bool SerializeElementPointer(SBFile &file, RHElement *&element); // 0x004c3a10
    void FUN_004ca410(RHSequenceElementCalls *element);
};

extern RHEngine *g_pEngine;

class RHOrder;

// List iterator shaped like MSVC6's _List_iterator: constructs from a node
// pointer, trivial copy, returned by value through a hidden pointer.
class RHUnkIter
{
public:
    void *m_p;

    RHUnkIter(void *p) : m_p(p) {}
};

// Order list wrapper: the oracle binds the loading block to
// `std::list<RHOrder*>::insert(iterator, RHOrder* const&)`. Target 0x00424410
// reads `[ecx+4]` as the end node and increments `[ecx+8]`, with a flag at
// +0x10 (MSVC6 std::list layout: _Head at +0x4, _Size at +0x8).
class RHUnkList
{
public:
    RHUnkIter insert(RHUnkIter pos, RHOrder *const &value); // 0x00424410

    RHUnkIter end() { return RHUnkIter(m_4); }

    char m_pad0[4];
    void *m_4;     // [0x4] end/sentinel node
    int m_8;       // [0x8] count
    char m_pad1[4];
    char m_flag10; // [0x10]
};

// The singleton object held by the global at 0x006c1040. Only the list at
// +0x148 is touched by RHOrder::Serialize; the rest stays opaque.
class RHUnk6c1040
{
public:
    char m_pad0[0x148];
    RHUnkList m_148; // [0x148]
};

// The global pointer at 0x006c1040. The // GLOBAL: marker sits on its
// definition in RHOrder.cpp.
extern RHUnk6c1040 *g_unk0x6c1040;

class RHSequenceElement;

class RHOrder
{
public:
    bool Serialize(SBFile &file, RHSequenceElement *element); // 0x0054e750

    static bool SerializeStaticStuff(SBFile &file);

    void Emit(SBFile &file);

    char m_pad0[4];          // [0x00] vptr/base sub-object (opaque)
    int m_4;                 // [0x04]
    RHUnk005df510 m_8;       // [0x08]
    SBGeoPoint2D m_14;       // [0x14]
    SBGeoPoint2D m_1c;       // [0x1c]
    int m_24;                // [0x24]
    char m_28;               // [0x28]
    char m_29;               // [0x29]
    char m_2a;               // [0x2a]
    char m_2b;               // [0x2b]
    char m_2c;               // [0x2c]
    char m_2d;               // [0x2d]
    char m_pad2e[2];         // [0x2e]
    RHElement *m_30;         // [0x30]
    int m_34;                // [0x34]
    RHSequenceElement *m_38; // [0x38]
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);

// The 4-byte global accessed by SerializeStaticStuff (original 0x006c0c6c).
// The // GLOBAL: marker sits on its definition in RHOrder.cpp.
extern int g_unk0x6c0c6c;
