#ifndef RHPORTRAITROOTLIFETIME_H
#define RHPORTRAITROOTLIFETIME_H

#include "Decomp.h"

class SBFrameWidgetView;
class RHUnk005ef320;
class RHMapTitleText;
class RHMapBox;

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
    SBFrameWidgetIterator(SBFrameWidgetNode *value = 0) : node(value) {}
    SBFrameWidgetIterator &operator++() { node = node->next; return *this; }
    SBFrameWidgetView *&operator*() { return node->widget; }
};

struct SBFrameWidgetFindList
{
    unsigned allocator;
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

class RHPortraitRootLifetime
{
public:
    RHPortraitRootLifetime();
    ~RHPortraitRootLifetime();
    void *FUN_0061a070(unsigned flags);
    bool FUN_0061a1e0(const RHMapTitleText &title, const RHMapBox &box, unsigned flags);
    bool FUN_0061a800(void *widget);
    bool FUN_0061a920(void *widget);
    bool FUN_0061aa30(void *widget);
    void *FUN_0061a6e0(const void *input);

    unsigned m_vptr;
    undefined m_04[4];
    SBFrameWidgetView **m_first;
    SBFrameWidgetView **m_last;
    undefined m_10[0x24];
    unsigned long m_flags;
    SBFrameWidgetFindList m_excluded;
    bool m_enabled;
    bool m_visible;
    undefined m_5e[0x12];
    undefined m_bounds[0x14];
    RHUnk005ef320 *m_draw;
    unsigned long m_display;
    void *m_resource;
    SBFrameInputEvent m_input;

    int Size() const { return m_first == 0 ? 0 : m_last - m_first; }
};

#endif
