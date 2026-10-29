#ifndef RHFOCUSMANAGER_H
#define RHFOCUSMANAGER_H

#include <list>
#include <vector>
#ifndef SBGEO_POINT2D_VIEW
#include "RHRendererPoint.h"
#endif
#include "RHFocusShortcutTree.h"

struct RHFocusEvent
{
    unsigned type;
    const void *widget;
    unsigned data;
    RHFocusEvent *next;
};

class RHFocusGroupableView
{
public:
    virtual RHFocusEvent *V00() = 0;
    virtual void *V04() = 0;
    virtual void V08(bool hidden) = 0;
    virtual bool V0c(const void *position) = 0;
    virtual void V10() = 0;
    virtual RHFocusEvent *V14(bool focused) = 0;
    virtual RHFocusEvent *V18(bool focused) = 0;
};

class RHFocusFocusableView
{
public:
    virtual void V00() = 0;
    virtual RHFocusEvent *V04(bool focused) = 0;
};

template <class T> struct RHFocusNode
{
    RHFocusNode *next;
    RHFocusNode *previous;
    T *value;
};

template<class Group, class Focus>
struct RHFocusCursors
{
    RHFocusCursors(std::list<Group> &groups, std::list<Focus> &focusable)
        : group(groups.end()), focus(focusable.end()), enabled(true), wrap(true) {}
    typename std::list<Group>::iterator group;
    typename std::list<Focus>::iterator focus;
    bool enabled;
    bool wrap;
};

class RHFocusManager
{
public:
    struct Groupable
    {
        RHFocusGroupableView *widget;
        bool sleeping;
    };
    RHFocusManager(int orientation);
    void FUN_004ffc20(RHFocusFocusableView *widget);
    void FUN_004ffc70(RHFocusGroupableView *widget, bool sleeping);
    void FUN_004ffce0(RHFocusGroupableView *widget, unsigned short key);
    void FUN_004ffd20(const void *widget);
    int FUN_004ffed0(const void *input) const;
    void *FUN_004fffd0();
    void FUN_004fffe0(bool hidden);
    bool FUN_00500010(const void *widget) const;
    RHFocusEvent *FUN_00500040(RHFocusEvent *first, RHFocusEvent *second) const;
    RHFocusEvent *FUN_00500070();
    RHFocusEvent *FUN_005000d0();
    RHFocusEvent *FUN_00500130();
    RHFocusEvent *FUN_005001e0();
    RHFocusEvent *FUN_005002a0(RHFocusEvent *events, const void *input, void *ui);
    RHFocusEvent *FUN_005003a0(const void *input);
    RHFocusEvent *FUN_005004d0(const void *input);
    RHFocusEvent *FUN_005006a0();
    RHFocusEvent *FUN_00500720();
    RHFocusEvent *FUN_00500750();
    void FUN_00500780(bool value);
    void FUN_00500790(bool value);
    RHFocusEvent *FUN_005007a0(RHFocusGroupableView *widget);
    void FUN_00500830(const void *position);
    static RHFocusEvent *FUN_005008a0(RHFocusEvent *first, const void *widget);

    unsigned m_navigation[4];
    std::list<Groupable> m_groups;
    std::list<RHFocusFocusableView *> m_focus;
    std::vector<const void *> m_ignored;
    RHFocusCursors<Groupable, RHFocusFocusableView *> m_cursors;
    RHFocusShortcutTree m_shortcuts;
    std::vector<unsigned short> m_pressed;
    SBGeoPoint2D m_point;
    void *m_ui;
};

typedef RHFocusManager::Groupable RHFocusGroupableEntry;

#endif
