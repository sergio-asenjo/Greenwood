#include "RHFocusManager.h"

// FUNCTION: GAME 0x004ffc20
void RHFocusManager::FUN_004ffc20(RHFocusFocusableView *widget)
{
    RHFocusNode<RHFocusFocusableView> *head = m_focusHead;
    RHFocusNode<RHFocusFocusableView> *previous = head->previous;
    RHFocusNode<RHFocusFocusableView> *node = new RHFocusNode<RHFocusFocusableView>;
    node->next = head ? head : node;
    node->previous = previous ? previous : node;
    head->previous = node;
    node->previous->next = node;
    RHFocusFocusableView **value = &node->value;
    if (value)
        *value = widget;
    ++m_focusCount;
    *(RHFocusManager **)((char *)widget + 4) = this;
}

struct RHFocusGroupableEntry
{
    RHFocusGroupableView *widget;
    bool sleeping;
};

struct RHFocusGroupableNode
{
    RHFocusGroupableNode *next;
    RHFocusGroupableNode *previous;
    RHFocusGroupableEntry value;
};

// FUNCTION: GAME 0x004ffc70
void RHFocusManager::FUN_004ffc70(RHFocusGroupableView *widget, bool sleeping)
{
    RHFocusGroupableEntry entry;
    entry.widget = widget;
    entry.sleeping = sleeping;
    RHFocusGroupableNode *head = (RHFocusGroupableNode *)m_groupHead;
    RHFocusGroupableNode *previous = head->previous;
    RHFocusGroupableNode *node = new RHFocusGroupableNode;
    node->next = head ? head : node;
    node->previous = previous ? previous : node;
    head->previous = node;
    node->previous->next = node;
    RHFocusGroupableEntry *value = &node->value;
    if (value)
        *value = entry;
    ++m_groupCount;
}

// FUNCTION: GAME 0x004fffe0
void RHFocusManager::FUN_004fffe0(bool hidden)
{
    for (RHFocusNode<RHFocusGroupableView> *node = m_groupHead->next;
         node != m_groupHead; node = node->next)
        node->value->V08(hidden);
}

// FUNCTION: GAME 0x00500010
bool RHFocusManager::FUN_00500010(const void *widget) const
{
    const void **last = m_ignoreLast;
    const void **first = m_ignoreFirst;
    for (; first != last; ++first)
        if (*first == widget)
            break;
    return first != last;
}

// Parked: the loop test is duplicated and the return blocks are not tail-merged.
// STUB: GAME 0x00500040
RHFocusEvent *RHFocusManager::FUN_00500040(RHFocusEvent *first, RHFocusEvent *second) const
{
    if (first) {
        RHFocusEvent *event = first;
        while (event != second) {
            RHFocusEvent *previous = event;
            event = event->next;
            if (event == 0) {
                previous->next = second;
                break;
            }
        }
        return first;
    }
    return second;
}

// Parked: the count and cursor registers differ and the false return is duplicated.
// STUB: GAME 0x00500070
RHFocusEvent *RHFocusManager::FUN_00500070()
{
    if (m_focusCount != 0) {
        RHFocusNode<RHFocusFocusableView> *head = m_focusHead;
        RHFocusNode<RHFocusFocusableView> *cursor = m_focusCursor;
        if (cursor == head)
            return 0;
        typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
        Link link = &RHFocusManager::FUN_00500040;
        RHFocusEvent *result = (this->*link)(0, m_focusCursor->value->V04(false));
        m_focusCursor = m_focusCursor->next;
        if (m_focusCursor != m_focusHead)
            return (this->*link)(result, m_focusCursor->value->V04(true));
        return result;
    }
    return 0;
}

// Parked: virtual-call target and previous-cursor update registers differ.
// STUB: GAME 0x005000d0
RHFocusEvent *RHFocusManager::FUN_005000d0()
{
    RHFocusEvent *result = 0;
    if (m_focusCount != 0) {
        RHFocusNode<RHFocusFocusableView> *head = *(RHFocusNode<RHFocusFocusableView> *volatile *)&m_focusHead;
        RHFocusNode<RHFocusFocusableView> *cursor = m_focusCursor;
        typedef RHFocusEvent *(RHFocusManager::*Reset)();
        typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
        Reset reset = &RHFocusManager::FUN_005006a0;
        Link link = &RHFocusManager::FUN_00500040;
        if (cursor == head)
            result = (this->*reset)();
        else {
            if (cursor == head->next)
                goto done;
            result = cursor->value->V04(false);
        }
        result = (this->*link)(0, result);
        m_focusCursor = m_focusCursor->previous;
        result = (this->*link)(result, m_focusCursor->value->V04(true));
    }
done:
    return result;
}

#include <vector>

// FUNCTION: GAME 0x005006a0
RHFocusEvent *RHFocusManager::FUN_005006a0()
{
    RHFocusEvent *result = 0;
    typedef void (RHFocusManager::*Hide)(bool);
    Hide hide = &RHFocusManager::FUN_004fffe0;
    (this->*hide)(false);
    RHFocusNode<RHFocusGroupableView> *head = *(RHFocusNode<RHFocusGroupableView> *volatile *)&m_groupHead;
    RHFocusNode<RHFocusGroupableView> *cursor = m_groupCursor;
    if (cursor != head) {
        typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
        Link link = &RHFocusManager::FUN_00500040;
        result = (this->*link)(0, m_groupCursor->value->V14(false));
        result = (this->*link)(result, m_groupCursor->value->V18(false));
        m_groupCursor = m_groupHead;
    }
    std::vector<unsigned short> &shortcuts = *(std::vector<unsigned short> *)((char *)this + 0x54);
    unsigned short *next = std::copy(shortcuts.end(), shortcuts.end(), shortcuts.begin());
    unsigned short *last = m_shortcutLast;
    m_shortcutLast = next;
    unsigned short *volatile discarded = last;
    return result;
}

// FUNCTION: GAME 0x00500720
RHFocusEvent *RHFocusManager::FUN_00500720()
{
    RHFocusEvent *result = 0;
    RHFocusNode<RHFocusFocusableView> *head = *(RHFocusNode<RHFocusFocusableView> *volatile *)&m_focusHead;
    RHFocusNode<RHFocusFocusableView> *cursor = m_focusCursor;
    if (cursor != head) {
        typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
        Link link = &RHFocusManager::FUN_00500040;
        result = (this->*link)(0, m_focusCursor->value->V04(false));
        m_focusCursor = m_focusHead;
    }
    return result;
}

// FUNCTION: GAME 0x00500750
RHFocusEvent *RHFocusManager::FUN_00500750()
{
    typedef RHFocusEvent *(RHFocusManager::*Reset)();
    typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
    Reset resetFocus = &RHFocusManager::FUN_00500720;
    Reset resetGroup = &RHFocusManager::FUN_005006a0;
    Link link = &RHFocusManager::FUN_00500040;
    RHFocusEvent *result = (this->*link)(0, (this->*resetFocus)());
    return (this->*link)(result, (this->*resetGroup)());
}

// Parked: the initial edi save precedes the zero-result register setup.
// STUB: GAME 0x005007a0
RHFocusEvent *RHFocusManager::FUN_005007a0(RHFocusGroupableView *widget)
{
    RHFocusEvent *result = 0;
    typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
    Link link = &RHFocusManager::FUN_00500040;
    RHFocusNode<RHFocusGroupableView> *head = *(RHFocusNode<RHFocusGroupableView> *volatile *)&m_groupHead;
    if (m_groupCursor != head) {
        m_groupCursor->value->V08(true);
        result = (this->*link)(0, m_groupCursor->value->V14(false));
        result = (this->*link)(result, m_groupCursor->value->V18(false));
    }
    for (RHFocusNode<RHFocusGroupableView> *node = m_groupHead->next;
         node != m_groupHead; node = node->next) {
        if (node->value == widget) {
            m_groupCursor = node;
            node->value->V08(false);
            return (this->*link)(result, node->value->V14(true));
        }
    }
    return result;
}

// FUNCTION: GAME 0x00500830
void RHFocusManager::FUN_00500830(const void *position)
{
    if (m_groupCursor == m_groupHead) {
        for (RHFocusGroupableNode *node = ((RHFocusGroupableNode *)m_groupHead)->next;
             node != (RHFocusGroupableNode *)m_groupHead; node = node->next) {
            RHFocusGroupableEntry entry = node->value;
            if (entry.widget->V0c(position) && m_groupCursor->value != node->value.widget) {
                typedef RHFocusEvent *(RHFocusManager::*Reset)();
                typedef RHFocusEvent *(RHFocusManager::*Focus)(RHFocusGroupableView *);
                Reset reset = &RHFocusManager::FUN_005006a0;
                Focus focus = &RHFocusManager::FUN_005007a0;
                (this->*reset)();
                (this->*focus)(node->value.widget);
                break;
            }
        }
    }
}

// FUNCTION: GAME 0x005008a0
RHFocusEvent *RHFocusManager::FUN_005008a0(RHFocusEvent *first, const void *widget)
{
    if (first) {
        RHFocusEvent *events = first;
        RHFocusEvent **event = &events;
        do {
            if ((*event)->widget == widget)
                *event = (*event)->next;
            else
                event = &(*event)->next;
        } while (*event != 0);
        return events;
    }
    return 0;
}

class RHUnk00641782
{
public:
    RHUnk00641782();
    ~RHUnk00641782();
    unsigned char m_00;
};

struct RHFocusShortcutNode
{
    RHFocusShortcutNode *left;
    RHFocusShortcutNode *parent;
    RHFocusShortcutNode *right;
    unsigned short key;
    unsigned short m_0e;
    RHFocusGroupableView *widget;
    int color;
};

// GLOBAL: GAME 0x006c0ac0
RHFocusShortcutNode *g_unk0x006c0ac0 = 0;

class RHFocusShortcutTree
{
public:
    RHFocusShortcutNode *FUN_00501450(const unsigned short &key);
    unsigned char m_00[4];
    RHFocusShortcutNode *head;
};

// FUNCTION: GAME 0x00501450
RHFocusShortcutNode *RHFocusShortcutTree::FUN_00501450(const unsigned short &key)
{
    RHUnk00641782 lock;
    RHFocusShortcutNode *node = head->parent;
    RHFocusShortcutNode *result = head;
    while (node != g_unk0x006c0ac0) {
        if (node->key < key)
            node = node->right;
        else {
            result = node;
            node = node->left;
        }
    }
    return result;
}

class RHFocusShortcutIterator
{
public:
    void FUN_005014c0();
    void FUN_00501580();
    RHFocusShortcutNode *node;
};

// Parked: the iterator store precedes nested-lock destruction.
// STUB: GAME 0x005014c0
void RHFocusShortcutIterator::FUN_005014c0()
{
    RHUnk00641782 lock;
    if (node->color == 0 && node->parent->parent == node)
        node = node->right;
    else if (node->left != g_unk0x006c0ac0) {
        RHFocusShortcutNode *maximum = node->left;
        RHUnk00641782 inner;
        while (maximum->right != g_unk0x006c0ac0)
            maximum = maximum->right;
        node = maximum;
    }
    else {
        RHFocusShortcutNode *parent;
        while (node == (parent = node->parent)->left)
            node = parent;
        node = parent;
    }
}

// FUNCTION: GAME 0x00501580
void RHFocusShortcutIterator::FUN_00501580()
{
    RHUnk00641782 lock;
    if (node->right != g_unk0x006c0ac0) {
        RHFocusShortcutNode *minimum = node->right;
        {
            RHUnk00641782 inner;
            while (minimum->left != g_unk0x006c0ac0)
                minimum = minimum->left;
        }
        node = minimum;
    }
    else {
        RHFocusShortcutNode *parent;
        while (node == (parent = node->parent)->right)
            node = parent;
        if (node->right != parent)
            node = parent;
    }
}

void EmitRHFocusManager(RHFocusManager *manager, RHFocusEvent *event, const void *widget)
{
    manager->FUN_004ffc20((RHFocusFocusableView *)widget);
    manager->FUN_004ffc70((RHFocusGroupableView *)widget, false);
    manager->FUN_004fffe0(false);
    manager->FUN_00500010(widget);
    manager->FUN_00500040(event, event);
    manager->FUN_00500070();
    manager->FUN_005000d0();
    manager->FUN_005006a0();
    manager->FUN_00500720();
    manager->FUN_00500750();
    manager->FUN_005007a0((RHFocusGroupableView *)widget);
    manager->FUN_00500830(widget);
    RHFocusManager::FUN_005008a0(event, widget);
    ((RHFocusShortcutTree *)((char *)manager + 0x44))->FUN_00501450(*(const unsigned short *)widget);
    ((RHFocusShortcutIterator *)event)->FUN_005014c0();
    ((RHFocusShortcutIterator *)event)->FUN_00501580();
}
