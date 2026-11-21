#ifndef RHPORTRAITROOTLIFETIME_H
#define RHPORTRAITROOTLIFETIME_H

#include "Decomp.h"
#include <memory>
#include <string>
#include <vector>

class SBFrameWidgetView;
class SBDrawManager;
class SBGeoPoint2D;
class SBGeoBoundingBox2D;
struct SBFrameEvent;
#include "RHMapBox.h"
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

struct SBFrameWidgetArray : public std::vector<SBFrameWidgetView *>
{
    SBFrameWidgetArray(const std::allocator<SBFrameWidgetView *> &value = std::allocator<SBFrameWidgetView *>())
        : std::vector<SBFrameWidgetView *>(value), dirty(true) {}
    ~SBFrameWidgetArray();
    unsigned Size() const { return size(); }
    SBFrameWidgetView **&First() { return _First; }
    unsigned CountOf() const;
    void Grow(unsigned size);
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
    SBFrameWidgetIterator operator++(int)
    {
        SBFrameWidgetIterator previous = *this;
        ++*this;
        return previous;
    }
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
    virtual ~RHPortraitRootLifetime();
    virtual bool FUN_0061a1e0(const std::wstring &title, const RHMapBox &box, unsigned flags);
    virtual void FUN_0061a350(unsigned long display);
    virtual void *FUN_0061a6e0(const void *input);
    virtual SBFrameEvent *FUN_0061a610(const void *input);
    virtual void FUN_0061a570();
    virtual void FUN_0061a430(SBGeoBoundingBox2D &bounds);
    virtual void FUN_0061a3a0();
    virtual void *FUN_0050e530();
    virtual void *FUN_0050e530B();
    virtual void FUN_0061ac80(const SBGeoPoint2D &position);
    virtual void FUN_0061ad20(const SBGeoBoundingBox2D &bounds);
    virtual bool FUN_0061a800(void *widget);
    virtual bool FUN_0061a920(void *widget);
    virtual bool FUN_0061aa30(void *widget);
    virtual bool FUN_0061ab10(void *widget);
    virtual int FUN_0050e540(void *value);
    virtual char FUN_0050e5c0();
    virtual void FUN_0050e5d0(char value);
    virtual char FUN_0050e5e0();

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
    SBDrawManager *m_draw;
    unsigned long m_display;
    void *m_resource;
    SBFrameInputEvent m_input;

    int Size() const { return m_widgets.Size(); }
};

#endif
