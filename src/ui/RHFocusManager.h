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

class RHFocusManager
{
public:
    RHFocusManager(int orientation);
    void FUN_004ffc20(RHFocusFocusableView *widget);
    void FUN_004ffc70(RHFocusGroupableView *widget, bool sleeping);
    void FUN_004ffce0(RHFocusGroupableView *widget, unsigned short key);
    void FUN_004ffd20(const void *widget);
    int FUN_004ffed0(const void *input) const;
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
    float m_position[2];
    void *m_ui;
};

#endif
