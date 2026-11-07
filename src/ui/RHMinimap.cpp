// RHMinimap.cpp — translation unit with __FILE__ evidence at 0x00549a80
// ("P:\\Robin Hood\\RHminimap.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x00549a80 -> RHMinimap::SerializeHighlightedElement(
//                     SBFile&, RHMinimap::HighlightedElement&)):
//   - TU:        rhminimap.cpp (embedded __FILE__ string 0x006b11b8,
//                referenced by this function and its caller 0x00549650).
//   - Class:     RHMinimap (symbols/oracle-correlation.tsv:
//                rhminimap -> class RHMinimap, 30 methods).
//   - Signature: RHMinimap::SerializeHighlightedElement(
//                SBFile&, RHMinimap::HighlightedElement&)
//                (symbols/mac-RH.txt line 3106 and
//                symbols/mac-functions-by-file.tsv line 131).
//   - Signals:
//       * the argument shape is two stack args and NO `this`: the callee
//         loads file from [esp+8] (-> esi, drives Access/GetError) and
//         element from [esp+0xc] (-> edi, advanced by +4). The caller
//         0x00549650 pushes (file, element) with no `mov ecx,this`, so this
//         is a non-`this`-call — the two-arg member serialiser the Mac map
//         names SerializeHighlightedElement;
//       * the first act is `mov ecx,*(void**)0x006c0a88; push &element;
//         push file; call 0x004c3a10` — the RHEngine singleton's
//         SerializeElementPointer (0x004c3a10 lives in rhengine.cpp,
//         symbols/functions-by-file.tsv) called with (SBFile&, RHElement*&),
//         result discarded;
//       * the remaining access is a single 1-byte SBFile::Access on
//         `&element[+4]` (assert line 153 = 0x99), returning true on success
//         and the assert path (empty fallback 0x006773d0, format 0x006a7390)
//         on failure — the exact serializer idiom seen in RHGraphicConfig;
//       * the caller walks an 8-byte vector element (`add ebx,0x8`,
//         0x005499a9) and passes its base as `element`, so +0x0 is an
//         RHElement* and +0x4 is the serialised char — consistent with the
//         macro definition.
//
// The `// STRING:` marker pins this TU's own __FILE__ literal to its original
// Game.exe address: the original is a fixed-base EXE, so its absolute string
// pointers carry no relocation records and reccmp cannot discover them by
// scanning. The shared "" (0x006773d0) and "Serialize failed reason is %s"
// (0x006a7390) are annotated once in src/RHSword.cpp; this function's
// references resolve to the same pooled entities.

#include "SBNullstr.h"
#include "RHMinimap.h"
#include "../engine/SBUIRenderer.h"

bool FUN_0054ae80(const RHMinimapHighlightedElement &element);

extern RHMinimap *g_unk0x6c0c50;
class RHMapResources;
extern RHMapResources *g_unk0x006c1840;

// FUNCTION: GAME 0x005493e0
RHMinimap::RHMinimap() : m_dc(0), m_e0(false)
{
    *(unsigned *)this = 0x00679b70;
    m_120 = false;
    m_124 = 0;
    g_unk0x6c0c50 = this;
    m_128 = 0;
    m_visible = true;
    m_b0 = false;
    m_b1 = false;
    m_122 = false;
    m_e1 = false;
    m_b2 = false;
}

// FUNCTION: GAME 0x00549510
void *RHMinimap::FUN_00549510(unsigned flags)
{
    this->~RHMinimap();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00549530
RHMinimap::~RHMinimap()
{
    *(unsigned *)this = 0x00679b70;
    ((SBUIUnk005fd4a0 *)g_unk0x006c1840)->FUN_005fd4a0(0x3d);
}

// FUNCTION: GAME 0x00549a80
bool RHMinimap::SerializeHighlightedElement(SBFile &file, RHMinimapHighlightedElement &element){
    g_pEngine->SerializeElementPointer(file, element.m_element);

    if (file.Access(&element.m_0c, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b11b8
                 "P:\\Robin Hood\\RHminimap.cpp",
                 153,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    return true;
}

// FUNCTION: GAME 0x00549ae0
bool FUN_00549ae0(const RHMinimapSortElement *a, const RHMinimapSortElement *b){
    unsigned ka;
    {
        unsigned v = a->m_04;
        bool t2 = (v & 0x3) == 0x3;
        bool t3 = (v & 0xf) == 0xc;
        bool t4 = (v & 7) == 0;
        ka = ((((t2 << 1 | t3) << 1 | (bool)((v & 0x1f) == 0x14)) << 1 |
               (bool)((v & 0x1f) == 0x14))
                  << 2 |
              t4)
             << 11;
    }
    unsigned kb;
    {
        unsigned v = b->m_04;
        bool t2 = (v & 0x3) == 0x3;
        bool t3 = (v & 0xf) == 0xc;
        bool t4 = (v & 7) == 0;
        kb = ((((t2 << 1 | t3) << 1 | (bool)((v & 0x1f) == 0x14)) << 1 |
               (bool)((v & 0x1f) == 0x14))
                  << 2 |
              t4)
             << 11;
    }
    if (ka > kb)
    {
        return false;
    }
    if (ka < kb)
    {
        return true;
    }
    float fa = a->m_50->m_1c4;
    float fb = b->m_50->m_1c4;
    if (fa != fb)
    {
        float ga = a->m_50->m_1c4;
        float gb = b->m_50->m_1c4;
        return ga < gb;
    }
    return a->m_0c < b->m_0c;
}

#include "RHMobileUnk00607da0.h"
#include "SBResourceManager.h"
#include "SBDrawManagerCore.h"
#include "RHPortraitDrawCalls.h"
#include "RHMapWidget.h"
#include "SBFrameWnd.h"
#include "RHPlayerProfileAccess.h"

#include "RHPlayerProfileManagerStorage.h"
extern float g_unk0x006c0c58[2];

// STUB: GAME 0x00549c10
bool RHMinimap::FUN_00549c10(const void *name, const void *box, unsigned long flags)
{
    SBGeoBoundingBox2D bounds;
    RHPortraitRootLifetime::FUN_0061a1e0(*(const RHMapTitleText *)name, *(const RHMapBox *)box, flags);
    m_minimapDraw = (RHUnkFXDraw *)g_unk0x6c11d0;
    m_engine = (char *)g_pEngine;
    m_surface = *(unsigned long *)(m_engine + 0x48c8);
    unsigned long surface;
    ((SBResourceManager *)m_resource)->FUN_00600920(0x3d, 1, surface);
    m_c4 = SBGeoVector2D(m_minimapDraw->FUN_005e56c0(m_surface), m_minimapDraw->FUN_005e5750(m_surface));
    ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0((const RHMobileUnk00607da0 &)((RHMapWidget *)this)->V24());
    bounds.SetMax(bounds.m_p0.Unk005fc190(SBGeoVector2D(m_minimapDraw->FUN_005e56c0(surface),
        m_minimapDraw->FUN_005e5750(surface))));
    ((SBFrameWnd *)this)->FUN_0061ad20(bounds);
    ((RHMobileUnk00607da0 *)&m_10c)->FUN_00607da0((const RHMobileUnk00607da0 &)bounds);
    FUN_0054a0f0(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x6c);
    return true;
}

// FUNCTION: GAME 0x00549e00
void RHMinimap::FUN_00549e00(const void *box)
{
    SBGeoBoundingBox2D bounds;
    ((SBFrameWnd *)this)->FUN_0061ad20(*(const SBGeoBoundingBox2D *)box);
    unsigned long surface;
    ((SBResourceManager *)m_resource)->FUN_00600920(0x3d, 1, surface);
    ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0((const RHMobileUnk00607da0 &)((RHMapWidget *)this)->V24());
    bounds.SetMax(bounds.m_p0.Unk005fc190(SBGeoVector2D(m_minimapDraw->FUN_005e56c0(surface),
        m_minimapDraw->FUN_005e5750(surface))));
    ((SBFrameWnd *)this)->FUN_0061ad20(bounds);
    ((RHMobileUnk00607da0 *)&m_10c)->FUN_00607da0((const RHMobileUnk00607da0 &)bounds);
    FUN_0054a0f0(&m_e4.m_p0);
}

// Parked: same widget base dependency (0x54b150, 0x6090d0/0x609200 geometry and
// the +0x120/+0xe0/+0xe4 members), none of which this TU establishes.
// STUB: GAME 0x00549f50
void RHMinimap::FUN_00549f50()
{
}

// FUNCTION: GAME 0x0054a0f0
bool RHMinimap::FUN_0054a0f0(const void *arg)
{
    const SBGeoPoint2D &point = *(const SBGeoPoint2D *)arg;
    SBGeoBoundingBox2D inner(point.Unk005fc190(*(SBGeoPoint2D *)g_unk0x006c0c58),
        point.Unk005fc190(m_c4).FUN_005fc200(*(SBGeoPoint2D *)g_unk0x006c0c58));
    SBGeoBoundingBox2D bounds(point, point.Unk005fc190(m_c4));
    SBGeoBoundingBox2D screen(SBGeoVector2D(0, 0),
        *(SBGeoPoint2D *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54));
    if ((unsigned char)((RHUnk00608f10 *)&screen)->FUN_00608f10(&inner))
    {
        ((RHMobileUnk00607da0 *)&m_e4)->FUN_00607da0((const RHMobileUnk00607da0 &)bounds);
        char *profile = ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
        *(SBGeoPoint2D *)(profile + 0x6c) = m_e4.m_p0;
        return true;
    }
    if (point == SBGeoPoint2D(65536.0f, 65536.0f) ||
        !(unsigned char)((RHUnk00608f10 *)&screen)->FUN_00608f10(&bounds))
    {
        float left = m_10c.m_p0.m_x;
        float bottom = m_10c.m_p1.m_y;
        float width = m_c4.m_x;
        m_e4.SetMin(SBGeoVector2D(left - width, bottom));
        m_e4.SetMax(m_e4.m_p0.Unk005fc190(m_c4));
    }
    return false;
}

// Parked: VC6 vector-insert specialisation over the 8-byte HighlightedElement
// vector at +0xcc; the _Insert_n branch layout and 0x54ae90 helper differ.
// STUB: GAME 0x0054a440
void RHMinimap::FUN_0054a440(const void *)
{
}

#include "SBUIKeyboardCalls.h"

class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;

// STUB: GAME 0x0054a640
SBFrameInputEvent *RHMinimap::FUN_0054a640(const void *arg)
{
    m_input.widget = this;
    m_input.data = 0;
    SBFrameInputEvent *event = &m_input;
    m_input.type = 11;
    m_input.next = 0;
    const SBGeoPoint2D &point = *(const SBGeoPoint2D *)arg;
    if (!((RHMapWidget *)this)->V44())
    {
        if (!((RHMapWidget *)this)->V24().FUN_006085a0(point) &&
            ((RHMapWidget *)this)->V24().FUN_00608400(point) &&
            IsRealPoint(point.Unk005fc110(((RHMapWidget *)this)->V24().Min())))
            return event;
        return 0;
    }
    if ((unsigned short)m_a4 != 0 &&
        (*(RHGameWidgetInputCalls *const *)((const char *)arg + 0xc))->FUN_0060e240((unsigned short)m_a4) == 2)
    {
        if (m_120 == true)
        {
            m_128 = 2;
            m_121 = false;
            m_124 = 0.1f;
        }
        else
        {
            m_124 = 1.0f;
            m_121 = true;
        }
        return event;
    }
    if (m_120 == true)
        ((SBFrameWnd *)this)->FUN_0061ad20(m_e4);
    else
        ((SBFrameWnd *)this)->FUN_0061ad20(m_10c);
    if (m_b0 && (*(const unsigned short *)((const char *)arg + 0xa) & 0x40) && m_120)
    {
        FUN_0054c1e0(point);
        return event;
    }
    if (!((RHMapWidget *)this)->V24().FUN_006085a0(point) &&
        ((RHMapWidget *)this)->V24().FUN_00608400(point) &&
        IsRealPoint(point.Unk005fc110(((RHMapWidget *)this)->V24().Min())))
    {
        *(RHMinimap **)((char *)g_unk0x6c0b3c + 0x185c) = this;
        m_122 = true;
        unsigned short flags = *(const unsigned short *)((const char *)arg + 0xa);
        if ((flags & 0x40) && m_b2)
        {
            FUN_0054c1e0(point);
            return event;
        }
        if (flags & 9)
            ManageClick(point);
        if ((*(const unsigned short *)((const char *)arg + 0xa) & 2) && m_120 == true)
        {
            m_121 = false;
            m_124 = 0.1f;
            m_highlighted.erase(m_highlighted.begin(), m_highlighted.end());
        }
        if (*(const unsigned short *)((const char *)arg + 0xa) == 0)
        {
            m_128 = 1;
            m_b2 = true;
        }
        return event;
    }
    m_b2 = false;
    m_128 = 0;
    if (m_122)
    {
        char *game = (char *)g_unk0x6c0b3c;
        *(void **)(game + 0x1858) = 0;
        *(void **)(game + 0x185c) = 0;
        m_122 = false;
    }
    return 0;
}

// Parked: same widget base dependency (0x61ad20, 0x54b1f0 and the +0x120/+0xe4/
// +0x10c members); the x87 box scaling cannot be reconstructed without the base.
// STUB: GAME 0x0054a920
void RHMinimap::FUN_0054a920()
{
}

// FUNCTION: GAME 0x0054ae80
bool FUN_0054ae80(const RHMinimapHighlightedElement &element)
{
    return element.m_0c == 0;
}

// FUNCTION: GAME 0x0054ae90
bool RHMinimap::FUN_0054ae90(RHElement *element)
{
    RHMinimapHighlightedElement *entry = *(RHMinimapHighlightedElement **)((char *)this + 0xd0);
    RHMinimapHighlightedElement *end = *(RHMinimapHighlightedElement **)((char *)this + 0xd4);
    for (; entry != end; ++entry)
    {
        if (entry->m_element == element)
            return true;
    }
    return false;
}

#include "SBDrawViewport.h"
#include "SBDrawUnk005e5ec0.h"

// FUNCTION: GAME 0x0054aec0
bool RHMinimap::IsRealPoint(const SBGeoPoint2D &point)
{
    SBDrawViewport view;
    unsigned long surface;
    if (!m_120)
        ((SBResourceManager *)m_resource)->FUN_00600920(0x3d, 1, surface);
    else
        surface = m_surface;
    if (surface && ((SBDrawManager *)m_minimapDraw)->FUN_005e5a00(surface, view, 0))
    {
        unsigned x = *(const unsigned *)&point.m_x;
        unsigned short pixel = view.GetPixel((unsigned short)*(const float *)&x, (unsigned short)point.m_y);
        ((SBDrawManager *)m_minimapDraw)->FUN_005e5ea0(view);
        if (pixel != ((SBDrawUnk005e5ec0 *)m_minimapDraw)->FUN_005e5f60(surface))
            return true;
    }
    return false;
}

// STUB: GAME 0x0054afe0
bool RHMinimap::RealToMap(const SBGeoPoint2D &point, SBGeoPoint2D &result)
{
    SBGeoBoundingBox2D bounds;
    ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0((const RHMobileUnk00607da0 &)m_e4);
    ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0((const RHMobileUnk00607da0 &)
        SBGeoBoundingBox2D(bounds.m_p0.Unk005fc190(*(SBGeoPoint2D *)g_unk0x006c0c58),
            bounds.m_p1.FUN_005fc200(*(SBGeoPoint2D *)g_unk0x006c0c58)));
    float x = *(const volatile float *)&point.m_x;
    const char *engine = m_engine;
    float width = *(const volatile float *)(engine + 0x4730);
    x /= width;
    float y = *(const volatile float *)&point.m_y;
    float height = *(const volatile float *)(engine + 0x4734);
    y /= height;
    result.Set((float)(int)((bounds.m_p1.m_x - bounds.m_p0.m_x) * x + bounds.m_p0.m_x),
        (float)(int)((bounds.m_p1.m_y - bounds.m_p0.m_y) * y + bounds.m_p0.m_y));
    return true;
}

// FUNCTION: GAME 0x0054b490
void RHMinimap::FUN_0054b490(const RHMinimapHighlightedElement &element)
{
    if (element.m_0c == 1)
    {
        RHMinimapSortElement *entry = (RHMinimapSortElement *)element.m_element;
        g_unk0x6c0c50->FUN_0054b5e0(*(SBGeoPoint2D *)((char *)entry->m_50 + 0x24), 0x12);
    }
}

#include <algorithm>

class RHUnk0054b150
{
public:
    void FUN_0054b150(bool flag, bool immediate);
};

// FUNCTION: GAME 0x0054b4c0
void RHMinimap::FUN_0054b4c0()
{
    if (m_dc == 0 && !m_highlighted.empty())
    {
        RHMinimapHighlightedElement *entry = std::find_if(m_highlighted.begin(), m_highlighted.end(), &FUN_0054ae80);
        if (entry != m_highlighted.end())
        {
            unsigned remaining = m_highlighted.end() - entry - 1;
            entry->m_0c = 1;
            if (remaining >= 1)
                m_dc = 25;
            else if (m_e0 || remaining == 0)
                m_dc = 50;
        }
        else
        {
            m_highlighted.clear();
            if (m_e0)
            {
                m_e0 = false;
                ((RHUnk0054b150 *)this)->FUN_0054b150(false, false);
            }
        }
    }
    if (m_dc != 0)
        --m_dc;
    std::for_each(m_highlighted.begin(), m_highlighted.end(), &RHMinimap::FUN_0054b490);
}

// FUNCTION: GAME 0x0054b5e0
void RHMinimap::FUN_0054b5e0(const SBGeoPoint2D &point, unsigned short color)
{
    SBGeoPoint2D position;
    unsigned long surface;
    ((SBResourceManager *)m_resource)->FUN_00600920(0x1e, color, surface);
    RealToMap(point, position);
    position = position.FUN_005fc200(SBGeoVector2D(m_minimapDraw->FUN_005e56c0(surface) >> 1,
        m_minimapDraw->FUN_005e5750(surface) >> 1));
    if (((RHMapWidget *)this)->V24().FUN_00608400(position) == true)
    {
        SBGeoBoundingBox2D destination;
        SBGeoBoundingBox2D source(SBGeoVector2D(0, 0),
            SBGeoVector2D(m_minimapDraw->FUN_005e56c0(surface), m_minimapDraw->FUN_005e5750(surface)));
        {
            SBGeoVector2D offset((const SBGeoVector2D &)position);
            ((RHMobileUnk00607da0 *)&destination)->FUN_00607da0((const RHMobileUnk00607da0 &)
                source.FUN_006090d0(offset));
        }
        ((SBDrawManager *)m_minimapDraw)->FUN_005e6000(destination, source);
        if (destination.m_p1.m_x - destination.m_p0.m_x > 0.0f &&
            destination.m_p1.m_y - destination.m_p0.m_y > 0.0f)
        {
            unsigned long display = m_display;
            ((SBDrawManager *)m_minimapDraw)->FUN_005e6440(surface, &source, display, &destination, 1);
        }
    }
}

#include "../ai/RHMalignityActorCalls.h"
#include "../element/RHElementActorCivilianCore.h"

struct RHMinimapRefreshElement
{
    undefined m_00[4];      // 0x00
    unsigned m_04;          // 0x04
    char m_08;              // 0x08
    undefined m_09[3];      // 0x09
    undefined m_0c[4];      // 0x0c
    unsigned short m_10;    // 0x10
    undefined m_12[0x3e];   // 0x12
    void *m_50;             // 0x50
    undefined m_54[0x5c];   // 0x54
    int m_b0;               // 0xb0
    undefined m_b4[0x11a];  // 0xb4
    char m_1ce;             // 0x1ce
};

// STUB: GAME 0x0054b8b0
void RHMinimap::FUN_0054b8b0(RHElement *element)
{
    RHMinimapRefreshElement *entry = (RHMinimapRefreshElement *)element;
    RHMalignityActorCalls *actor = (RHMalignityActorCalls *)element;
    unsigned short color;

    switch (*(unsigned short *)((char *)element + 0x8c))
    {
    case 1:
        if ((entry->m_04 & 7) == 4)
        {
            switch (entry->m_10)
            {
            case 1:
                if (actor->V48() || (*(int *)((char *)entry->m_50 + 0x8c) == 3 && !entry->m_1ce))
                    color = 1;
                else if (entry->m_1ce)
                    color = 2;
                else
                    color = 0;
                break;
            case 0x102:
                if (entry->m_08)
                    color = 3;
                else if (((RHElementActorCivilian *)element)->FUN_00470ce0())
                {
                    if (actor->V48())
                        color = 8;
                    else if (entry->m_1ce)
                        color = 9;
                    else
                        color = 7;
                }
                else if (actor->V48())
                    color = 14;
                else if (entry->m_1ce)
                    color = 15;
                else
                    color = 13;
                break;
            case 0x103:
                if (entry->m_08)
                    color = 3;
                else if (actor->Vf8())
                {
                    if (actor->V48())
                        color = 8;
                    else if (entry->m_1ce)
                        color = 9;
                    else
                        color = 7;
                }
                else if (actor->V48())
                    color = actor->V130() == 1 ? 5 : 11;
                else if (entry->m_1ce)
                    color = actor->V130() == 1 ? 6 : 12;
                else
                    color = actor->V130() == 1 ? 4 : 10;
                break;
            default:
                return;
            }
        }
        else if ((entry->m_04 & 7) == 0)
            color = 16;
        else if ((entry->m_04 & 3) == 3)
        {
            if (entry->m_b0 == 12)
                color = 20;
            else if ((entry->m_04 & 0xf) == 7)
                color = 19;
            else
                color = 17;
        }
        else
            return;
        break;
    case 100:
        color = 0;
        break;
    case 101:
        color = 2;
        break;
    case 102:
        color = 1;
        break;
    case 111:
        if ((entry->m_04 & 7) != 4)
            return;
        if (actor->V48())
            color = 1;
        else if (entry->m_1ce)
            color = 2;
        else
            color = 0;
        break;
    case 200:
        color = 4;
        break;
    case 201:
        color = 6;
        break;
    case 202:
        color = 5;
        break;
    case 222:
        if ((entry->m_04 & 7) != 4)
            return;
        if (actor->V48())
            color = 5;
        else if (entry->m_1ce)
            color = 6;
        else
            color = 4;
        break;
    case 300:
        color = 13;
        break;
    case 301:
        color = 15;
        break;
    case 302:
        color = 14;
        break;
    case 333:
        if ((entry->m_04 & 7) != 4)
            return;
        if (actor->V48())
            color = 14;
        else if (entry->m_1ce)
            color = 15;
        else
            color = 13;
        break;
    case 400:
        color = 7;
        break;
    case 401:
        color = 9;
        break;
    case 402:
        color = 8;
        break;
    case 444:
        if ((entry->m_04 & 7) != 4)
            return;
        if (actor->V48())
            color = 8;
        else if (entry->m_1ce)
            color = 9;
        else
            color = 7;
        break;
    case 500:
        color = 17;
        break;
    case 666:
        color = 16;
        break;
    default:
        return;
    }
    FUN_0054b5e0(*(const SBGeoPoint2D *)((char *)entry->m_50 + 0x24), color);
}

// Force emission: a non-inline static member defined here is emitted into the
// object; this out-of-line call keeps RHMinimap::SerializeHighlightedElement in
// the build.
#include "RHMessenger.h"
#include "RHUnk005fc3b0.h"

extern float g_unk0x006774e4;
RHMessenger *RHUnk00546050();

// FUNCTION: GAME 0x0054bfb0
void RHMinimap::ManageClick(const SBGeoPoint2D &point)
{
    m_b0 = false;
    if (!m_b1)
    {
        if (!m_120)
        {
            m_128 = 2;
            m_124 = 1.0f;
            m_121 = true;
        }
        else
        {
            SBGeoBoundingBox2D bounds;
            ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0((const RHMobileUnk00607da0 &)((RHMapWidget *)this)->V24());
            bounds.SetMin(bounds.Min().Unk005fc190(*(SBGeoPoint2D *)g_unk0x006c0c58));
            bounds.SetMax(bounds.Max().FUN_005fc200(*(SBGeoPoint2D *)g_unk0x006c0c58));
            if (bounds.FUN_00608400(point))
            {
                SBGeoPoint2D delta;
                delta = point.Unk005fc110(bounds.Min());
                float x = delta.m_x / (bounds.m_p1.m_x - bounds.m_p0.m_x);
                float y = delta.m_y / (bounds.m_p1.m_y - bounds.m_p0.m_y);
                if (((RHEngine *)m_engine)->FUN_004c7c90())
                {
                    ((RHEngine *)m_engine)->FUN_004d2330(6);
                    unsigned width = *(unsigned *)(m_engine + 0x4730);
                    float height = *(float *)(m_engine + 0x4734);
                    ((RHEngine *)m_engine)->FUN_004c7f60(&SBGeoPoint2D(*(float *)&width * x, height * y));
                }
            }
        }
    }
    else
        m_b1 = false;
    m_e0 = false;
}

// FUNCTION: GAME 0x0054c1e0
void RHMinimap::FUN_0054c1e0(const SBGeoPoint2D &point)
{
    if (m_120)
    {
        if (!m_b0)
        {
            m_bc = m_e4.Min();
            m_b4 = point;
            m_b0 = true;
            m_e1 = false;
        }
        else
        {
            RHUnk00546050()->RHUnk005460c0(RHUnk5490f0(0x18));
            SBGeoVector2D delta = point.Unk005fc110(m_b4);
            if (((RHUnk005fc3b0 &)delta).Unk005fc6a0(1.0f) > g_unk0x006774e4)
            {
                FUN_0054a0f0(&m_bc.Unk005fc190(delta));
                m_b1 = true;
            }
        }
        m_e0 = false;
    }
}

void RHMinimapEmit(SBFile &file, RHMinimapHighlightedElement &element)
{
    RHMinimap::SerializeHighlightedElement(file, element);
    FUN_0054ae80(element);
}

// Force emission of the element comparator (nothing in this build calls it).
void RHMinimapSortEmit(RHMinimapSortElement *a, RHMinimapSortElement *b)
{
    FUN_00549ae0(a, b);
}

void RHMinimapHighlightEmit(RHMinimap *minimap, RHElement *element)
{
    minimap->FUN_0054ae90(element);
    minimap->RealToMap(minimap->m_b4, minimap->m_bc);
    minimap->IsRealPoint(minimap->m_b4);
    minimap->ManageClick(minimap->m_b4);
}
