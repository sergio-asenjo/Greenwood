#include "SBFrameWnd.h"
#include <list>
#include <string>

DECOMP_SIZE_ASSERT(SBFrameWnd, 0xa0)

// FUNCTION: GAME 0x0061a070
void *RHPortraitRootLifetime::FUN_0061a070(unsigned flags)
{
    this->~RHPortraitRootLifetime();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0061a1e0
bool RHMenuCampaignMap::FUN_0061a1e0(const RHMapTitleText &title, const RHMapBox &box, unsigned flags)
{
    m_input.widget = this;
    m_input.data = 0;
    m_input.type = 0xb;
    ((RHMobileUnk00607da0 *)&m_bounds)->FUN_00607da0((const RHMobileUnk00607da0 &)box);
    m_flags = flags;
    ((std::wstring *)((char *)this + 0x24))->assign((const std::wstring &)title, 0, std::wstring::npos);
    m_visible = true;
    std::list<SBFrameWidgetView *> &excluded = *(std::list<SBFrameWidgetView *> *)&m_excluded;
    excluded.erase(excluded.begin(), excluded.end());
    m_excluded.dirty = true;
    return true;
}

// FUNCTION: GAME 0x0061a350
void SBFrameWnd::FUN_0061a350(unsigned long display)
{
    m_draw = g_unk0x6c11d0;
    m_display = display;
    SBFrameWidgetView **first = *(SBFrameWidgetView **volatile *)&m_first;
    unsigned count = first == 0 ? 0 : m_last - first;
    for (unsigned index = 0; index < count; ++index)
        m_first[index]->V04(display);
}

// FUNCTION: GAME 0x0061a3a0
void SBFrameWnd::FUN_0061a3a0()
{
    if (m_enabled) {
        unsigned count = Size();
        for (unsigned index = 0; index < count; ++index) {
            SBFrameWidgetView *widget = m_first[index];
            if (m_excluded.Find(widget, m_excluded.count) == -1)
                widget->V10();
        }
    }
}

// FUNCTION: GAME 0x0061a430
void SBFrameWnd::FUN_0061a430(SBGeoBoundingBox2D &bounds)
{
    if (m_enabled) {
        unsigned count = Size();
        for (unsigned index = 0; index < count; ++index) {
            SBFrameWidgetView *widget = m_first[index];
            const SBGeoBoundingBox2D &source = *(SBGeoBoundingBox2D *)((char *)widget + 0x30);
            SBGeoBoundingBox2D box(source);
            SBFrameWidgetFindList &excluded = m_excluded;
            SBFrameWidgetNode *head = excluded.head;
            int size = excluded.count;
            excluded.current = widget;
            excluded.cursorValid = true;
            excluded.cursor = SBFrameWidgetIterator(head->next);
            if (excluded.Search(size) == -1 &&
                (box.FUN_006084a0(bounds) ||
                 (unsigned char)((RHUnk00608f10 *)&box)->FUN_00608f10(&bounds))) {
                widget->V10();
                widget->V0c();
            }
        }
    }
}

// FUNCTION: GAME 0x0061a570
void SBFrameWnd::FUN_0061a570()
{
    if (m_enabled) {
        unsigned count = Size();
        for (unsigned index = 0; index < count; ++index) {
            SBFrameWidgetView *widget = m_first[index];
            SBFrameWidgetFindList &excluded = m_excluded;
            if (excluded.Find(widget) == -1)
                m_first[index]->V0c();
        }
    }
}

// FUNCTION: GAME 0x0061a610
SBFrameEvent *SBFrameWnd::FUN_0061a610(const void *input)
{
    SBFrameEvent *first = 0;
    SBFrameEvent *last = 0;
    if (!m_enabled)
        return 0;
    unsigned count = Size();
    for (unsigned index = 0; index < count; ++index) {
        SBFrameWidgetView *widget = m_first[index];
        if (m_excluded.Find(widget, m_excluded.count) == -1) {
            SBFrameEvent *event = widget->V14(input);
            if (event != 0) {
                if (last == 0) {
                    first = event;
                    last = event;
                } else {
                    last->next = event;
                    last = event;
                }
            }
        }
    }
    return first;
}

#include <vector>
#include <list>

class RHSaveGame;

template <class T>
class SBArray
{
public:
    void Insert(T *position, unsigned count, const T &value);
};

struct SBFrameWidgetArray
{
    unsigned allocator;
    SBFrameWidgetView **first;
    SBFrameWidgetView **last;
    SBFrameWidgetView **end;
    undefined m_10[4];
    bool dirty;

    unsigned Size() const { return first == 0 ? 0 : last - first; }
    unsigned CountOf() const
    {
        typedef unsigned (std::vector<unsigned long>::*Count)() const;
        Count count = &std::vector<unsigned long>::size;
        return (((const std::vector<unsigned long> *)this)->*count)();
    }
    void Grow(unsigned size)
    {
        SBFrameWidgetView *value = 0;
        if (CountOf() < size) {
            SBFrameWidgetView **position = last;
            ((SBArray<RHSaveGame *> *)this)->Insert(
                (RHSaveGame **)position, size - CountOf(), (RHSaveGame *const &)value);
        } else if (size < CountOf()) {
            typedef std::vector<int> Values;
            int *(Values::*erase)(int *, int *) = &Values::erase;
            Values &values = *(Values *)this;
            (values.*erase)(values.begin() + size, values.end());
        }
        dirty = true;
    }
};

// FUNCTION: GAME 0x0061a6e0
void *RHPortraitRootLifetime::FUN_0061a6e0(const void *input)
{
    if (m_enabled && m_visible) {
        SBFrameInputEvent *first;
        SBFrameInputEvent *last;
        if (m_bounds.FUN_00608400(*(const SBGeoPoint2D *)input) == true) {
            m_input.next = 0;
            first = &m_input;
            last = first;
        } else {
            first = 0;
            last = 0;
        }
        unsigned count = Size();
        for (unsigned index = 0; index < count; ++index) {
            SBFrameWidgetView *widget = m_first[index];
            if (m_excluded.Find(widget, m_excluded.count) == -1) {
                SBFrameInputEvent *event = widget->V18(input);
                if (event != 0) {
                    if (last == 0) {
                        first = event;
                        last = event;
                    } else
                        last->next = event;
                    while (last->next != 0)
                        last = last->next;
                }
            }
        }
        return first;
    }
    return 0;
}

// FUNCTION: GAME 0x0061a800
bool RHPortraitRootLifetime::FUN_0061a800(void *item)
{
    SBFrameWidgetView *widget = (SBFrameWidgetView *)item;
    SBFrameWidgetArray &widgets = *(SBFrameWidgetArray *)m_04;
    unsigned count = widgets.Size();
    widgets.Grow(count + 1);
    SBFrameWidgetView **first = *(SBFrameWidgetView **volatile *)&m_first;
    first[count] = widget;
    if (m_draw != 0)
        widget->V04(m_display);
    SBGeoVector2D offset(*(SBGeoPoint2D *)((char *)widget + 0x30));
    widget->V20(m_bounds.m_0.Unk005fc190(offset));
    return true;
}

// FUNCTION: GAME 0x0061a920
bool RHPortraitRootLifetime::FUN_0061a920(void *item)
{
    SBFrameWidgetView *widget = (SBFrameWidgetView *)item;
    if (widget != 0) {
        SBFrameWidgetArray &widgets = *(SBFrameWidgetArray *)m_04;
        unsigned count = widgets.Size();
        for (unsigned index = 0; index < count; ++index) {
            if (m_first[index] == widget) {
                SBFrameWidgetView *final = m_first[count - 1];
                SBFrameWidgetView *value = 0;
                m_first[index] = final;
                unsigned size = count - 1;
                if (widgets.Size() < size)
                    ((SBArray<RHSaveGame *> *)&widgets)->Insert(
                        (RHSaveGame **)widgets.last, size - widgets.Size(), (RHSaveGame *const &)value);
                else if (size < widgets.Size()) {
                    std::vector<SBFrameWidgetView *> &all = *(std::vector<SBFrameWidgetView *> *)&widgets;
                    all.erase(all.begin() + size, all.end());
                }
                widgets.dirty = true;
                return true;
            }
        }
        return false;
    }
    std::vector<SBFrameWidgetView *> &all = *(std::vector<SBFrameWidgetView *> *)m_04;
    all.erase(all.begin(), all.end());
    ((SBFrameWidgetArray *)m_04)->dirty = true;
    return true;
}

// FUNCTION: GAME 0x0061aa30
bool RHPortraitRootLifetime::FUN_0061aa30(void *item)
{
    SBFrameWidgetView *widget = (SBFrameWidgetView *)item;
    for (unsigned index = 0; index < (unsigned)Size(); ++index) {
        if (m_first[index] == widget && m_excluded.Find(widget, m_excluded.count) == -1) {
            SBFrameWidgetNode *next = m_excluded.head->next;
            SBFrameWidgetNode *previous = next->previous;
            SBFrameWidgetNode *node = (SBFrameWidgetNode *)operator new(sizeof(SBFrameWidgetNode));
            node->next = next != 0 ? next : node;
            node->previous = previous != 0 ? previous : node;
            next->previous = node;
            node->previous->next = node;
            std::_Construct(&node->widget, widget);
            m_excluded.dirty = true;
            ++m_excluded.count;
            return true;
        }
    }
    return false;
}

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

struct RHScriptNode;
struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

class RHUnk0046eb30
{
public:
    RHScriptIter FUN_0046eb80();
    RHScriptIter erase(RHScriptIter position);
};

struct SBFrameWidgetSeekList : SBFrameWidgetFindList
{
    void Advance(SBFrameWidgetNode *start, int distance)
    {
        std::bidirectional_iterator_tag category;
        SBFrameWidgetIterator &it = cursor;
        it.node = start;
        FUN_005c9010((RHUnk005c9010Iterator &)it, distance, category);
    }
    void Advance(int distance)
    {
        std::bidirectional_iterator_tag category;
        FUN_005c9010((RHUnk005c9010Iterator &)cursor, distance, category);
    }
    SBFrameWidgetNode *First() { return (SBFrameWidgetNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node; }
    void Seek(int position)
    {
        int size = count;
        if (dirty) {
            if (position <= (size + 1) / 2)
                Advance(First(), position);
            else
                Advance(head, position - size);
            dirty = false;
        } else {
            int previous = index;
            if (position == previous)
                return;
            if (position < previous) {
                if (position < (previous + 1) / 2)
                    Advance(First(), position);
                else
                    Advance(position - previous);
            } else if (position < (previous + size) / 2)
                Advance(position - previous);
            else
                Advance(head, position - size);
        }
        index = position;
    }
};

// Parked: the cursor address is hoisted into a register across the search and seek.
// STUB: GAME 0x0061ab10
bool SBFrameWnd::FUN_0061ab10(SBFrameWidgetView *widget)
{
    SBFrameWidgetSeekList &excluded = *(SBFrameWidgetSeekList *)&m_excluded;
    int position = excluded.Find(widget, excluded.count);
    if (position != -1) {
        excluded.Seek(position);
        ((RHUnk0046eb30 *)&excluded)->erase(RHScriptIter((RHScriptNode *)excluded.cursor.node));
        excluded.dirty = true;
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x0061ac80
void SBFrameWnd::FUN_0061ac80(const SBGeoPoint2D &position)
{
    SBGeoPoint2D offset = position.Unk005fc110(m_bounds.m_0);
    SBGeoBoundingBox2D box = m_bounds.FUN_006090d0((const SBGeoVector2D &)offset);
    V2c(box);
}

// FUNCTION: GAME 0x0061ad20
void SBFrameWnd::FUN_0061ad20(const SBGeoBoundingBox2D &bounds)
{
    SBGeoPoint2D offset = bounds.m_0.Unk005fc110(m_bounds.m_0);
    for (unsigned index = 0; index < Size(); ++index) {
        SBFrameWidgetView *widget = m_first[index];
        SBGeoBoundingBox2D box(*(SBGeoBoundingBox2D *)((char *)widget + 0x30));
        ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(offset);
        widget->V1c(box);
    }
    ((RHMobileUnk00607da0 *)&m_bounds)->FUN_00607da0((const RHMobileUnk00607da0 &)bounds);
}

void EmitSBFrameWnd(SBFrameWnd *window)
{
    ((RHMenuCampaignMap *)window)->FUN_0061a1e0(*(RHMapTitleText *)0, *(RHMapBox *)0, 0);
    window->FUN_0061a350(0);
    window->FUN_0061a3a0();
    window->FUN_0061a430(window->m_bounds);
    window->FUN_0061a570();
    window->FUN_0061a610(0);
    ((RHPortraitRootLifetime *)window)->FUN_0061a800(0);
    ((RHPortraitRootLifetime *)window)->FUN_0061a070(0);
    ((RHPortraitRootLifetime *)window)->FUN_0061a920(0);
    ((RHPortraitRootLifetime *)window)->FUN_0061aa30(0);
    ((RHPortraitRootLifetime *)window)->FUN_0061a6e0(0);
    window->FUN_0061ab10(0);
    window->FUN_0061ac80(window->m_bounds.m_0);
    window->FUN_0061ad20(window->m_bounds);
}
