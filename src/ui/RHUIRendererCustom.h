// RHUIRendererCustom — declarations for RHUIRendererCustom.cpp (decompiled TU).
//
// BINDING (0x005ca340 -> RHUIRendererCustom::Render(SBResourceWidgetID)):
//   - TU:     rhuirenderercustom.cpp (embedded __FILE__ 0x006b8c74,
//             symbols/functions-by-file.tsv:405).
//   - Class:  RHUIRendererCustom (symbols/oracle-correlation.tsv:87:
//             rhuirenderercustom -> class RHUIRendererCustom, 8 methods).
//   - Method: the Mac map has exactly one rhuirenderercustom.cpp method,
//             Render (symbols/mac-functions-by-file.tsv:413), and
//             symbols/mac-RH.txt:4479 gives
//             RHUIRendererCustom::Render(SBResourceWidgetID).
//   - Signal: `this` arrives in ecx; the function ends in `ret 0x4` (one stack
//             argument). The first instruction group tiles two local
//             SBGeoBoundingBox2D objects, stores the argument at this+0x3c, and
//             the assert string 0x6b8c3c ("Unable to retrieve a resource for the
//             custom renderer") resolves two resources through this+0x4 and
//             blits through this+0x1c — the renderer's resource/blit path. The
//             sibling renderers (RHUIRendererShifting::Render and
//             RHUIRendererPortrait::BlitPicture) share the same shape, and the
//             Zeta-OS oracle's RHUIRendererCustom::Render (x86, unstripped)
//             reproduces the same box/scaling/blit sequence.
//
// Member layout is derived from the target instructions of
// RHUIRendererCustom::Render (0x005ca340). Everything is opaque padding; the
// touched fields are reached through the offset aliases below, and each engine
// sub-object has its own provisional class so its `__thiscall` call shape is
// reproduced.
//
// The engine sub-object classes stay provisional (no __FILE__, tag or string
// names them) and their method identities are unproven; the class names are the
// addresses of the out-of-line targets in Game.exe. Methods already defined by
// a sibling TU's `_stubs.cpp` are only declared here (a second definition would
// be a duplicate symbol); genuinely-new targets are defined in
// RHUIRendererCustom_stubs.cpp.

#include "SB.h"

// SBGeoPoint2D — an 8-byte point (two 32-bit floats). The default ctor
// (0x5fc030), copy ctor (0x5fc3e0 -> 0x5fc030 + 0x5fc390), destructor
// (0x5fc080) and operator= (0x5fc090) are already defined in
// RHGroundMark_stubs.cpp; this TU only declares them.
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();

    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);

    float m_x; // +0
    float m_y; // +4
};

// SBGeoVector2D — a point-shaped displacement. The (float,float) ctor and the
// SBGeoVector2D overload of SBGeoBoundingBox2D::operator+ are defined once in
// RHUIRendererShifting_stubs.cpp; this TU only declares them.
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float x, float y);
    SBGeoVector2D(const SBGeoPoint2D &other);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

// SBGeoBoundingBox2D — 0x14 bytes: two points (+0, +8) and a byte flag at
// +0x10. The default ctor (0x6079c0) and operator= (0x607da0) are defined in
// RHUIRendererShifting_stubs.cpp; operator+ (0x6090d0) likewise. operator-
// (0x609200) is genuinely new and lives in RHUIRendererCustom_stubs.cpp.
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(const SBGeoPoint2D &p0, const SBGeoPoint2D &p1);
    ~SBGeoBoundingBox2D() {}

    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &other);

    SBGeoBoundingBox2D operator-(const SBGeoVector2D &vector) const;
    SBGeoBoundingBox2D operator+(const SBGeoVector2D &vector) const;

    SBGeoPoint2D m_p0; // +0
    SBGeoPoint2D m_p1; // +8
    bool m_flag;       // +0x10
};

// Target 0x00600820, __FILE__ 0x006bb368
// ("P:\Robin Hood\SBLibNG\SBResourceManager.cpp"). Called as `mov ecx,[esi+4]`
// with three stack arguments (ret 0xc): the long resource id, the widget id and
// &surface. Returns bool in `al`. Defined once in RHUIRendererShifting_stubs.cpp.
class SBResourceManager
{
public:
    bool GetSurfaceForResource(long resourceId, unsigned int widgetId, unsigned int &surface);
};

#ifndef RHUNK00600820_VIEW
#define RHUNK00600820_VIEW
class RHUnk00600820
{
public:
    bool ResolveSurface(void *surface, unsigned int id, float *value);
};
#endif

// Target 0x005e6440, __FILE__ 0x006b9264
// ("P:\Robin Hood\SBLibNG\SBDrawManager.cpp"). Called as `mov ecx,[esi+0x1c]`
// with five stack arguments (target `ret 0x14`): a surface handle, the widget
// box, this+0x20, the displaced box and the constant 1. The Windows shape has
// five integer/pointer arguments (the surface handle is pushed directly, no
// float conversion). Defined in RHUIRendererCustom_stubs.cpp; the Zeta-OS
// oracle names the same draw-manager entry SBDrawManager::Blit.
class RHUnk005e6440
{
public:
    void Blit(unsigned long surface, SBGeoBoundingBox2D *box, unsigned long unk20,
              SBGeoBoundingBox2D *displaced, unsigned long flag);
};

class RHUIRendererCustom
{
public:
    bool Render(unsigned int id);

    void Emit();

    // Total size is irrelevant: the fields the matched function touches are
    // reached through the offset aliases below.
    char m_bytes[0x60];
};

// Resource manager sub-object pointer (target `mov ecx,[esi+0x4]`).
#define m_resource (*(SBResourceManager **)((char *)this + 0x4))

// Widget bounding box (target `lea edi,[esi+0x8]`; source of the origin copy
// and the `this` of the box subtraction).
#define m_box (*(SBGeoBoundingBox2D *)((char *)this + 0x8))

// Draw manager sub-object pointer (target `mov ecx,[esi+0x1c]`).
#define m_draw (*(RHUnk005e6440 **)((char *)this + 0x1c))

// Third blit argument (target `mov ecx,[esi+0x20]`).
#define m_20 (*(unsigned long *)((char *)this + 0x20))

// First resource id (target `mov ecx,[esi+0x38]`).
#define m_resourceId (*(long *)((char *)this + 0x38))

// Widget id stored at entry (target `mov [esi+0x3c],edi`).
#define m_id (*(unsigned int *)((char *)this + 0x3c))

// Scale ratio numerator/denominator (target `fld [esi+0x4c]; fdiv [esi+0x50]`).
#define m_ratioNum (*(float *)((char *)this + 0x4c))
#define m_ratioDen (*(float *)((char *)this + 0x50))

// Second resource id (target `mov eax,[esi+0x54]`).
#define m_resourceId2 (*(long *)((char *)this + 0x54))

// The .rdata zero constant the two width tests compare against (target
// `fcomp ds:0x677488`). It is already pinned with a `// GLOBAL:` marker in
// RHSoundGeometry.cpp, so it is only declared here (a second definition would
// be a duplicate symbol).
extern float g_unk0x00677488;
