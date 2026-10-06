// RHUIRendererShifting — declarations for RHUIRendererShifting.cpp (decompiled TU).
//
// BINDING (0x005cbe60 -> RHUIRendererShifting::Render(SBResourceWidgetID)):
//   - TU:     rhuirenderershifting.cpp (embedded __FILE__ 0x006b8d30,
//             symbols/functions-by-file.tsv:407).
//   - Class:  RHUIRendererShifting (symbols/oracle-correlation.tsv:89:
//             rhuirenderershifting -> class RHUIRendererShifting, 8 methods).
//   - Method: the Mac map has exactly one rhuirenderershifting.cpp method,
//             Render (symbols/mac-functions-by-file.tsv:415), and
//             symbols/mac-RH.txt:4506 gives
//             RHUIRendererShifting::Render(SBResourceWidgetID).
//   - Signal: `this` arrives in ecx; the function ends in `ret 0x4` (one stack
//             argument). The first instruction group tiles a local
//             SBGeoBoundingBox2D, stores the argument at this+0x3c, and the
//             assert string 0x6b8d58 ("Unable to retrieve a resource for the
//             bitmap renderer") resolves a resource through this+0x4 and blits
//             through this+0x1c — the renderer's resource/blit path. The
//             sibling renderers (SBUIRendererBitmap::Render and
//             RHUIRendererPortrait::BlitPicture) share the same shape.
//
// The engine sub-object classes stay provisional where nothing on the Windows
// side names them; their layout is derived from the target instructions and
// corroborated by the Zeta-OS oracle (x86, unstripped), whose
// Render(SBResourceWidgetID) uses the same SBGeoPoint2D / SBGeoVector2D /
// SBGeoBoundingBox2D / SBResourceManager / SBDrawManager call sequence.
//
// Everything in the hero class is opaque padding; the touched fields are
// reached through offset aliases below, so the exact engine padding does not
// matter and every offset is taken from the target.

#include "SB.h"

// SBGeoPoint2D — an 8-byte point (two 32-bit floats). Target ctor 0x5fc030
// zeroes both dwords; 0x5fc060 stores the two incoming dwords; 0x5fc080 is its
// (empty, ICF-merged) destructor; 0x5fc090 is operator= and 0x5fc190 is
// operator+(const SBGeoVector2D&). Zeta: SBGeoPoint2D(float,float) etc.
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();

    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);

    float m_x; // +0
    float m_y; // +4
};

// SBGeoVector2D — a point-shaped displacement. Target ctor 0x5fc3c0 wraps the
// SBGeoPoint2D(float,float) base ctor and returns `this` (ret 8); Zeta's
// SBGeoVector2D::SBGeoVector2D(float,float) does the same.
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float x, float y);
    ~SBGeoVector2D() {}
};

// SBGeoPoint2D's vector sum (target 0x5fc190, ret 8, returns a point by value).
SBGeoPoint2D operator+(const SBGeoPoint2D &point, const SBGeoVector2D &vector);

// SBGeoBoundingBox2D — 0x14 bytes: two points (+0, +8) and a byte flag at
// +0x10. Target ctors 0x6079c0 (default) and 0x607ba0 (from two points);
// destructor 0x5fc080-family; operator= 0x607da0 (Destroy+Copy, ret 4);
// Copy 0x607990; operator+ 0x6090d0 (ret 8, member returning a box by value,
// built from the two SBGeoPoint2D+SBGeoVector2D sums).
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(const SBGeoPoint2D &p0, const SBGeoPoint2D &p1);
    ~SBGeoBoundingBox2D() {}

    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &other);
    void Copy(const SBGeoBoundingBox2D &other);

    SBGeoBoundingBox2D operator+(const SBGeoVector2D &vector) const;

    SBGeoPoint2D m_p0; // +0
    SBGeoPoint2D m_p1; // +8
    bool m_flag;       // +0x10
};

// Target 0x600820, __FILE__ 0x006bb368
// ("P:\Robin Hood\SBLibNG\SBResourceManager.cpp"). Called as `mov ecx,[esi+4]`
// with three stack arguments (ret 0xc): the long resource id at this+0x38, the
// widget id and &surface. Returns bool in `al` (target `cmp al,1`). Zeta names
// it SBResourceManager::GetSurfaceForResource(long, SBResourceWidgetID, unsigned&).
class SBResourceManager
{
public:
    bool GetSurfaceForResource(long resourceId, unsigned int widgetId, unsigned int &surface);
};

// Target 0x5ec5f0, __FILE__ 0x006b9264
// ("P:\Robin Hood\SBLibNG\SBDrawManager.cpp"). Called as `mov ecx,[esi+0x1c]`
// with seven stack arguments (ret 0x1c). Zeta names it
// SBDrawManager::BlitAlphaKeying(unsigned long, SBGeoBoundingBox2D*,
// unsigned long, unsigned long, unsigned short, unsigned short, unsigned long).
class SBDrawManager
{
public:
    void BlitAlphaKeying(unsigned long surface, unsigned long a, unsigned long b,
                         SBGeoBoundingBox2D *box, unsigned short c, unsigned short d,
                         unsigned long e);
};

class RHUIRendererShifting
{
public:
    bool Render(unsigned int id);

    void Emit();

    // Total size is irrelevant: the fields the matched function touches are
    // reached through the offset aliases below.
    char m_bytes[0x54];
};

// Resource manager sub-object pointer (target `mov ecx,[esi+0x4]`).
#define m_resource (*(SBResourceManager **)((char *)this + 0x4))

// Bounding-box member added to the displacement (target `lea ecx,[esi+0x8]`).
#define m_box (*(SBGeoBoundingBox2D *)((char *)this + 0x8))

// Draw manager sub-object pointer (target `mov ecx,[esi+0x1c]`).
#define m_draw (*(SBDrawManager **)((char *)this + 0x1c))

// Fourth blit argument (target `push ecx` after `mov ecx,[esi+0x20]`).
#define m_unk20 (*(unsigned long *)((char *)this + 0x20))

// Long resource id passed to the resource manager (target `mov edx,[esi+0x38]`).
#define m_resourceId (*(long *)((char *)this + 0x38))

// Widget id stored at entry (target `mov [esi+0x3c],eax`).
#define m_id (*(unsigned int *)((char *)this + 0x3c))

// Double-buffered surface handles (target `mov [esi+eax*4+0x40]`).
#define m_handles (*(unsigned int *)((char *)this + 0x40))

// Double-buffer selector (target `mov eax,[esi+0x48]; and eax,1`).
#define m_index (*(unsigned int *)((char *)this + 0x48))

// Blit source rectangle words. The sampled word at +0x50 is turned into a
// float for the displacement vector; the words at +0x4c/+0x4e become the blit
// source origin.
#define m_word4c (*(unsigned short *)((char *)this + 0x4c))
#define m_word4e (*(unsigned short *)((char *)this + 0x4e))
#define m_word50 (*(unsigned short *)((char *)this + 0x50))
