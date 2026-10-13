#ifndef RHFOCUSMANAGER_H
#define RHFOCUSMANAGER_H

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
    virtual void V00() = 0;
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

class RHFocusManager
{
public:
    void FUN_004ffc20(RHFocusFocusableView *widget);
    void FUN_004ffc70(RHFocusGroupableView *widget, bool sleeping);
    void FUN_004fffe0(bool hidden);
    bool FUN_00500010(const void *widget) const;
    RHFocusEvent *FUN_00500040(RHFocusEvent *first, RHFocusEvent *second) const;
    RHFocusEvent *FUN_00500070();
    RHFocusEvent *FUN_005000d0();
    RHFocusEvent *FUN_005006a0();
    RHFocusEvent *FUN_00500720();
    RHFocusEvent *FUN_00500750();
    RHFocusEvent *FUN_005007a0(RHFocusGroupableView *widget);
    void FUN_00500830(const void *position);
    static RHFocusEvent *FUN_005008a0(RHFocusEvent *first, const void *widget);

    unsigned m_navigation[4];
    unsigned m_groupAllocator;
    RHFocusNode<RHFocusGroupableView> *m_groupHead;
    unsigned m_groupCount;
    unsigned m_focusAllocator;
    RHFocusNode<RHFocusFocusableView> *m_focusHead;
    unsigned m_focusCount;
    unsigned m_ignoreAllocator;
    const void **m_ignoreFirst;
    const void **m_ignoreLast;
    const void **m_ignoreEnd;
    RHFocusNode<RHFocusGroupableView> *m_groupCursor;
    RHFocusNode<RHFocusFocusableView> *m_focusCursor;
    unsigned char m_40[0x18];
    unsigned short *m_shortcutFirst;
    unsigned short *m_shortcutLast;
    unsigned short *m_shortcutEnd;
};

#endif
