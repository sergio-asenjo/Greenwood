#ifndef RHPORTRAITROOTLIFETIME_H
#define RHPORTRAITROOTLIFETIME_H

#include "Decomp.h"
#include <memory>
#include <string>

class SBFrameWidgetView;
class RHUnk005ef320;
class RHMapTitleText;
#include "RHMapBox.h"
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

struct SBFrameWidgetArray
{
    SBFrameWidgetArray(const std::allocator<SBFrameWidgetView *> &value = std::allocator<SBFrameWidgetView *>())
        : allocator(value), first(0), last(0), end(0), dirty(true) {}
    ~SBFrameWidgetArray();
    unsigned Size() const { return first == 0 ? 0 : last - first; }
    unsigned CountOf() const;
    void Grow(unsigned size);
    std::allocator<SBFrameWidgetView *> allocator;
    SBFrameWidgetView **first;
    SBFrameWidgetView **last;
    SBFrameWidgetView **end;
    undefined m_10[4];
    bool dirty;
    undefined m_15[0x0b];
};

struct SBFrameInputEvent
{
    int type;
    void *widget;
    void *data;
    SBFrameInputEvent *next;
};

struct SBFrameWidgetNode
{
    SBFrameWidgetNode *next;
    SBFrameWidgetNode *previous;
    SBFrameWidgetView *widget;
};

struct SBFrameWidgetIterator
{
    SBFrameWidgetNode *node;
    SBFrameWidgetIterator() {}
    SBFrameWidgetIterator(SBFrameWidgetNode *value) : node(value) {}
    SBFrameWidgetIterator &operator++() { node = node->next; return *this; }
    SBFrameWidgetView *&operator*() { return node->widget; }
};

struct SBFrameWidgetFindList
{
    SBFrameWidgetFindList(const std::allocator<SBFrameWidgetView *> &value = std::allocator<SBFrameWidgetView *>());
    ~SBFrameWidgetFindList();
    std::allocator<SBFrameWidgetView *> allocator;
    SBFrameWidgetNode *head;
    int count;
    SBFrameWidgetIterator cursor;
    bool dirty;
    undefined m_11[3];
    int index;
    bool cursorValid;
    undefined m_19[3];
    int result;
    SBFrameWidgetView *current;

    inline void Seek(int position);

    int Find(SBFrameWidgetView *widget)
    {
        current = widget;
        cursorValid = true;
        cursor = SBFrameWidgetIterator(head->next);
        return Search(count);
    }

    int Find(SBFrameWidgetView *widget, int size)
    {
        current = widget;
        cursorValid = true;
        cursor = SBFrameWidgetIterator(head->next);
        return Search(size);
    }

    int Search(int size)
    {
        int position;
        for (position = 0; position < size; ++position) {
            if (*cursor == current)
                break;
            ++cursor;
        }
        if (position < size) {
            result = position;
            dirty = false;
            index = position;
        } else {
            dirty = true;
            result = -1;
        }
        return result;
    }
};

// VTABLE: GAME 0x0067ad9c
class RHPortraitRootLifetime
{
public:
    RHPortraitRootLifetime();
    ~RHPortraitRootLifetime();
    void *FUN_0061a070(unsigned flags);
    virtual bool FUN_0061a1e0(const RHMapTitleText &title, const RHMapBox &box, unsigned flags);
    bool FUN_0061a800(void *widget);
    bool FUN_0061a920(void *widget);
    bool FUN_0061aa30(void *widget);
    void *FUN_0061a6e0(const void *input);

    SBFrameWidgetArray m_widgets;
    std::wstring m_title;
    unsigned long m_flags;
    SBFrameWidgetFindList m_excluded;
    bool m_enabled;
    bool m_visible;
    bool m_tooltipEnabled;
    undefined m_5f;
    std::wstring m_tooltip;
    RHMapBox m_bounds;
    RHUnk005ef320 *m_draw;
    unsigned long m_display;
    void *m_resource;
    SBFrameInputEvent m_input;

    int Size() const { return m_widgets.Size(); }
};

#endif
