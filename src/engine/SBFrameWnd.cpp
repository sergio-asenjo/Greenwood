#include "SBFrameWnd.h"

DECOMP_SIZE_ASSERT(SBFrameWnd, 0x90)

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

// Parked: loop bound occupies ebp while the event tail spills to the stack.
// STUB: GAME 0x0061a610
SBFrameEvent *SBFrameWnd::FUN_0061a610(const void *input)
{
    unsigned count;
    SBFrameEvent *first = 0;
    SBFrameEvent *last = 0;
    if (!m_enabled)
        return 0;
    count = Size();
    for (unsigned index = 0; index < count; ++index) {
        SBFrameWidgetView *widget = m_first[index];
        if (m_excluded.Find(widget, m_excluded.count) == -1) {
            SBFrameEvent *event = widget->V14(input);
            if (event != 0) {
                if (last == 0)
                    first = event;
                else
                    last->next = event;
                last = event;
            }
        }
    }
    return first;
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
    window->FUN_0061a350(0);
    window->FUN_0061a3a0();
    window->FUN_0061a430(window->m_bounds);
    window->FUN_0061a570();
    window->FUN_0061a610(0);
    window->FUN_0061ac80(window->m_bounds.m_0);
    window->FUN_0061ad20(window->m_bounds);
}
