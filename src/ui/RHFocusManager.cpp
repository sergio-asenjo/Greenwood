#include "RHFocusManager.h"
#include <utility>

#include "RHUnk00641782.h"

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@?$list@UGroupable@RHFocusManager@@V?$allocator@UGroupable@RHFocusManager@@@std@@@std@@QAE?AViterator@12@V312@@Z

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@?$list@PAVRHFocusFocusableView@@V?$allocator@PAVRHFocusFocusableView@@@std@@@std@@QAE?AViterator@12@V312@@Z

// TEMPLATE: GAME 0x0057c9c0 FOLDED
// ??Eiterator@?$list@UGroupable@RHFocusManager@@V?$allocator@UGroupable@RHFocusManager@@@std@@@std@@QAE?AV012@H@Z

inline void RHFocusShortcutTree::RotateLeft(RHFocusShortcutNode *node)
{
    RHUnk00641782 lock;
    RHFocusShortcutNode *right = node->right;
    node->right = right->left;
    if (right->left != g_unk0x006c0ac0)
        right->left->parent = node;
    right->parent = node->parent;
    if (node == head->parent)
        head->parent = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

inline void RHFocusShortcutTree::RotateRight(RHFocusShortcutNode *node)
{
    RHUnk00641782 lock;
    RHFocusShortcutNode *left = node->left;
    node->left = left->right;
    if (left->right != g_unk0x006c0ac0)
        left->right->parent = node;
    left->parent = node->parent;
    if (node == head->parent)
        head->parent = left;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right = node;
    node->parent = left;
}

// GLOBAL: GAME 0x006c0abc
unsigned g_unk0x006c0abc = 0;

// GLOBAL: GAME 0x006c0ac0
RHFocusShortcutNode *g_unk0x006c0ac0 = 0;

inline RHFocusShortcutTree::RHFocusShortcutTree(const std::less<unsigned short> &compare, const std::allocator<RHFocusShortcutValue> &allocator)
    : m_compare(compare), m_allocator(allocator)
{
    multi = false;
    std::_Lockit lock;
    if (g_unk0x006c0ac0 == 0) {
        RHFocusShortcutNode *nil = (RHFocusShortcutNode *)operator new(sizeof(RHFocusShortcutNode));
        nil->parent = 0;
        nil->color = 1;
        g_unk0x006c0ac0 = nil;
        nil->left = 0;
        g_unk0x006c0ac0->right = 0;
    }
    ++g_unk0x006c0abc;
    head = BuyNode(g_unk0x006c0ac0, 0);
    count = 0;
    head->left = head;
    head->right = head;
}

// FUNCTION: GAME 0x004ffa20
RHFocusManager::RHFocusManager(int orientation)
    : m_cursors(m_groups, m_focus),
      m_point(-1.0f, -1.0f), m_ui(0)
{
    if (orientation == 0) {
        m_navigation[0] = 2;
        m_navigation[1] = 4;
        m_navigation[2] = 1;
        m_navigation[3] = 3;
    }
    else {
        m_navigation[0] = 1;
        m_navigation[1] = 3;
        m_navigation[2] = 2;
        m_navigation[3] = 4;
    }
}

// TEMPLATE: GAME 0x004ffbb0
// ??1RHFocusShortcutTree@@QAE@XZ

#define m_groupAllocator (*(unsigned *)((char *)this + 0x10))
#define m_groupHead (*(RHFocusNode<RHFocusGroupableView> **)((char *)this + 0x14))
#define m_groupCount (*(unsigned *)((char *)this + 0x18))
#define m_focusHead (*(RHFocusNode<RHFocusFocusableView> **)((char *)this + 0x20))
#define m_focusCount (*(unsigned *)((char *)this + 0x24))
#define m_ignoreFirst (*(const void ***)((char *)this + 0x2c))
#define m_ignoreLast (*(const void ***)((char *)this + 0x30))
#define m_ignoreEnd (*(const void ***)((char *)this + 0x34))
#define m_groupCursor (*(RHFocusNode<RHFocusGroupableView> **)((char *)this + 0x38))
#define m_focusCursor (*(RHFocusNode<RHFocusFocusableView> **)((char *)this + 0x3c))
#define m_40 ((unsigned char *)this + 0x40)
#define m_shortcutFirst (*(unsigned short **)((char *)this + 0x58))
#define m_shortcutLast (*(unsigned short **)((char *)this + 0x5c))
#define m_shortcutEnd (*(unsigned short **)((char *)this + 0x60))
#define m_position ((float *)((char *)this + 0x64))

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

// FUNCTION: GAME 0x004ffce0
void RHFocusManager::FUN_004ffce0(RHFocusGroupableView *widget, unsigned short key)
{
    RHFocusShortcutValue value;
    value.key = key;
    value.widget = 0;
    typedef RHFocusShortcutInsertResult (RHFocusShortcutTree::*Insert)(const RHFocusShortcutValue &);
    Insert insert = &RHFocusShortcutTree::FUN_00500a70;
    RHFocusShortcutTree *tree = (RHFocusShortcutTree *)((char *)this + 0x44);
    RHFocusShortcutInsertResult result = (tree->*insert)(value);
    result.first.node->widget = widget;
}

#undef m_40
#include "RHCampaign.h"
#define m_40 ((unsigned char *)this + 0x40)

DECOMP_SIZE_ASSERT(RHFocusManager, 0x70)
DECOMP_STATIC_ASSERT(offsetof(RHFocusManager, m_groups) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHFocusManager, m_focus) == 0x1c)
DECOMP_STATIC_ASSERT(offsetof(RHFocusManager, m_ignored) == 0x28)
DECOMP_STATIC_ASSERT(offsetof(RHFocusManager, m_cursors) == 0x38)
DECOMP_STATIC_ASSERT(offsetof(RHFocusManager, m_shortcuts) == 0x44)
DECOMP_STATIC_ASSERT(offsetof(RHFocusManager, m_pressed) == 0x54)
DECOMP_STATIC_ASSERT(offsetof(RHFocusManager, m_point) == 0x64)
DECOMP_STATIC_ASSERT(offsetof(RHFocusManager, m_ui) == 0x6c)
DECOMP_SIZE_ASSERT(RHFocusShortcutNode, 0x18)
DECOMP_SIZE_ASSERT(RHFocusShortcutTree, 0x10)
DECOMP_SIZE_ASSERT(RHFocusShortcutIterator, 0x04)
DECOMP_SIZE_ASSERT(RHFocusShortcutInsertResult, 0x08)

class RHSequenceElement;
class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
};

// FUNCTION: GAME 0x004ffd20
void RHFocusManager::FUN_004ffd20(const void *widget)
{
    RHScriptFXArray *array = (RHScriptFXArray *)((char *)this + 0x28);
    void *const &value = *(void *const *)&widget;
    void **position = array->last;
    if ((unsigned)(array->end - array->last) < 1) {
        unsigned size = array->first == 0 ? 0 : array->last - array->first;
        unsigned grow = size > 1 ? size : 1;
        int capacity = (array->first == 0 ? 0 : array->last - array->first) + grow;
        int allocation = capacity;
        if (allocation < 0)
            allocation = 0;
        void **storage = (void **)operator new(allocation * 4);
        void **destination = storage;
        for (void **source = array->first; source != position; ++source, ++destination)
            RHSeqList::CopyData((RHSequenceElement **)destination, (RHSequenceElement *const *)source);
        array->Unk004fe450(destination, 1, value);
        ++destination;
        array->Unk004fe420(position, array->last, destination);
        array->Unk005008e0(array->first, array->last);
        operator delete(array->first);
        array->end = storage + capacity;
        unsigned previousSize = array->first == 0 ? 0 : array->last - array->first;
        array->last = storage + previousSize + 1;
        array->first = storage;
    }
    else if ((unsigned)(array->last - position) < 1) {
        array->Unk004fe420(position, array->last, position + 1);
        array->Unk004fe450(array->last, 1 - (array->last - position), value);
        void **last = array->last;
        for (void **destination = position; destination != last; ++destination)
            *destination = value;
        ++array->last;
    }
    else {
        array->Unk004fe420(array->last - 1, array->last, array->last);
        void **source = array->last - 1;
        void **destination = array->last;
        while (position != source)
            *--destination = *--source;
        void **last = position + 1;
        for (destination = position; destination != last; ++destination)
            *destination = value;
        ++array->last;
    }
}

#include "SBUIKeyboardCalls.h"

unsigned FUN_005fb1d0(unsigned key);

// FUNCTION: GAME 0x004ffed0
int RHFocusManager::FUN_004ffed0(const void *input) const
{
    unsigned short key = 0;
    int action = 0;
    for (; key <= 255; ++key) {
        if (action != 0)
            break;
        int pressed = (*(RHGameWidgetInputCalls **)((char *)input + 0x0c))->FUN_0060e240(key);
        unsigned index = key;
        int state = *(int *)((char *)*(RHGameWidgetInputCalls **)((char *)input + 0x0c) + 0xa0c + index * 4);
        RHGameWidgetInputCalls *shortcuts = *(RHGameWidgetInputCalls **)((char *)input + 0x0c);
        if (pressed == 1) {
            if (state == 2 || state == 0) {
                unsigned translated = FUN_005fb1d0(key & 0x7f);
                if (translated > 0) {
                    switch (translated) {
                    case 37: action = 1; break;
                    case 38: action = 2; break;
                    case 39: action = 3; break;
                    case 40: action = 4; break;
                    case 13:
                        if (state == 0)
                            action = 5;
                        break;
                    }
                }
            }
        }
        else if (pressed == 0 && ((RHPortraitKeyboardCalls *)shortcuts)->FUN_0060e270(key)) {
            unsigned translated = FUN_005fb1d0(key & 0x7f);
            if (translated > 0 && translated == 13)
                action = 6;
        }
    }
    return action;
}

// FUNCTION: GAME 0x004fffd0
void *RHFocusManager::FUN_004fffd0()
{
    return m_ui;
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

// FUNCTION: GAME 0x00500040
RHFocusEvent *RHFocusManager::FUN_00500040(RHFocusEvent *first, RHFocusEvent *second) const
{
    if (first) {
        RHFocusEvent *event = first;
        RHFocusEvent *previous;
        while (event) {
            if (event == second)
                goto finished;
            previous = event;
            event = event->next;
        }
        previous->next = second;
    finished:
        return first;
    }
    return second;
}

// FUNCTION: GAME 0x00500070
RHFocusEvent *RHFocusManager::FUN_00500070()
{
    RHFocusEvent *result = 0;
    if (m_focus.size() != 0) {
        RHFocusNode<RHFocusFocusableView> *head = *(RHFocusNode<RHFocusFocusableView> *volatile *)&m_focusHead;
        if (m_focusCursor != head) {
            typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
            Link link = &RHFocusManager::FUN_00500040;
            result = (this->*link)(0, (*m_cursors.focus)->V04(false));
            ++m_cursors.focus;
            if (m_cursors.focus != m_focus.end())
                result = (this->*link)(result, (*m_cursors.focus)->V04(true));
        }
    }
    return result;
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
#include <list>

typedef std::list<RHFocusGroupableEntry> RHFocusGroupList;

DECOMP_SIZE_ASSERT(RHFocusGroupList, 0x0c)
DECOMP_SIZE_ASSERT(RHFocusGroupList::iterator, 0x04)
DECOMP_SIZE_ASSERT(RHFocusGroupableEntry, 0x08)
DECOMP_SIZE_ASSERT(RHFocusGroupableNode, 0x10)

// FUNCTION: GAME 0x00500130
RHFocusEvent *RHFocusManager::FUN_00500130()
{
    RHFocusEvent *result = 0;
    RHFocusGroupList &groups = *(RHFocusGroupList *)&m_groupAllocator;
    RHFocusGroupList::iterator &cursor = *(RHFocusGroupList::iterator *)&m_groupCursor;
    RHFocusGroupList::iterator next;
    typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
    Link link = &RHFocusManager::FUN_00500040;
    if (cursor == groups.end()) {
        next = groups.begin();
    }
    else {
        next = cursor;
        ++next;
        m_groupCursor->value->V08(true);
        result = m_groupCursor->value->V14(false);
        result = (this->*link)(result, m_groupCursor->value->V18(false));
    }
    for (int index = 0; index != groups.size(); ++index, ++next) {
        if (next == groups.end())
            next = groups.begin();
        if (*((bool *)next->widget->V04() + 4) && next->sleeping == true) {
            cursor = next;
            next->widget->V08(false);
            return (this->*link)(result, m_groupCursor->value->V14(true));
        }
    }
    return result;
}

struct RHFocusGroupRange
{
    RHFocusNode<RHFocusGroupableView> *head;
    RHFocusNode<RHFocusGroupableView> *first;
};

inline RHFocusGroupRange RHFocusReadGroupRange(RHFocusManager &manager)
{
    RHFocusGroupRange result;
    result.head = *(RHFocusNode<RHFocusGroupableView> **)((char *)&manager + 0x14);
    result.first = result.head->next;
    return result;
}

// FUNCTION: GAME 0x005001e0
RHFocusEvent *RHFocusManager::FUN_005001e0()
{
    RHFocusEvent *result = 0;
    RHFocusGroupRange group = RHFocusReadGroupRange(*this);
    RHFocusGroupList::iterator &cursor = *(RHFocusGroupList::iterator *)&m_groupCursor;
    RHFocusGroupList::iterator previous;
    if (cursor != *(RHFocusGroupList::iterator *)&group.first && cursor != *(RHFocusGroupList::iterator *)&group.head) {
        previous = cursor;
        --previous;
    }
    else {
        previous = *(RHFocusGroupList::iterator *)&group.head;
        --previous;
    }
    typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
    Link link = &RHFocusManager::FUN_00500040;
    if (m_groupCursor != group.head) {
        m_groupCursor->value->V08(true);
        result = m_groupCursor->value->V14(false);
        result = (this->*link)(result, m_groupCursor->value->V18(false));
    }
    for (unsigned index = 0; index != m_groupCount; ++index, --previous) {
        if (*((bool *)previous->widget->V04() + 4) && previous->sleeping == true) {
            cursor = previous;
            previous->widget->V08(false);
            result = (this->*link)(result, m_groupCursor->value->V14(true));
            break;
        }
        if (previous == *(RHFocusGroupList::iterator *)&m_groupHead->next)
            previous = *(RHFocusGroupList::iterator *)&m_groupHead;
    }
    return result;
}

#include "SBUIBase.h"

// FUNCTION: GAME 0x005002a0
RHFocusEvent *RHFocusManager::FUN_005002a0(RHFocusEvent *events, const void *input, void *ui)
{
    RHFocusEvent *result = events;
    if (!ui || *(void **)((char *)ui + 0x17f0) != 0 || *(void **)((char *)ui + 0x17f4) != 0)
        goto done;
    {
        m_ui = ui;
        const SBGeoPoint2D &position = *(const SBGeoPoint2D *)input;
        for (RHFocusEvent *event = events; event; event = event->next) {
            if (event->type == 11)
                continue;
            if (!m_point.FUN_005fc0e0(position))
                continue;
            {
                typedef bool (RHFocusManager::*Ignore)(const void *) const;
                Ignore ignore = &RHFocusManager::FUN_00500010;
                if (!(this->*ignore)(event->widget)) {
                    typedef RHFocusEvent *(RHFocusManager::*Reset)();
                    Reset reset = &RHFocusManager::FUN_005006a0;
                    (this->*reset)();
                    *(SBGeoPoint2D *)m_position = position;
                    break;
                }
            }
        }
        void *keyboard = *(void **)((char *)input + 0x0c);
        if (((SBUIUnk0060e1b0 *)keyboard)->FUN_0060e260() == true) {
            typedef RHFocusEvent *(RHFocusManager::*Process)(const void *);
            typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
            Process navigation = &RHFocusManager::FUN_005003a0;
            Process shortcuts = &RHFocusManager::FUN_005004d0;
            Link link = &RHFocusManager::FUN_00500040;
            RHFocusEvent *generated = (this->*navigation)(input);
            if (generated) {
                RHFocusEvent *filtered = FUN_005008a0(events, generated->widget);
                result = (this->*link)(filtered, generated);
            }
            else
                result = (this->*link)(events, (this->*shortcuts)(input));
        }
    }
done:
    m_ui = 0;
    return result;
}

// FUNCTION: GAME 0x005003a0
RHFocusEvent *RHFocusManager::FUN_005003a0(const void *input)
{
    RHFocusEvent *result = 0;
    typedef int (RHFocusManager::*GetKey)(const void *) const;
    typedef RHFocusEvent *(RHFocusManager::*Move)();
    typedef void (RHFocusManager::*Synchronize)(const void *);
    typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
    GetKey getKey = &RHFocusManager::FUN_004ffed0;
    Synchronize synchronize = &RHFocusManager::FUN_00500830;
    Link link = &RHFocusManager::FUN_00500040;
    if (m_40[0] && m_groupCount != 0) {
        int action = (this->*getKey)(input);
        if (action != 0) {
            if (action == m_navigation[1]) {
                RHFocusNode<RHFocusFocusableView> *head = *(RHFocusNode<RHFocusFocusableView> *volatile *)&m_focusHead;
                if (m_focusCursor == head) {
                    (this->*synchronize)(input);
                    Move move = &RHFocusManager::FUN_00500130;
                    result = (this->*move)();
                }
            }
            else if (action == m_navigation[0]) {
                RHFocusNode<RHFocusFocusableView> *head = *(RHFocusNode<RHFocusFocusableView> *volatile *)&m_focusHead;
                if (m_focusCursor == head) {
                    (this->*synchronize)(input);
                    Move move = &RHFocusManager::FUN_005001e0;
                    result = (this->*move)();
                }
            }
            else if (action == m_navigation[2]) {
                Move move = &RHFocusManager::FUN_005000d0;
                result = (this->*move)();
            }
            else if (action == m_navigation[3]) {
                Move move = &RHFocusManager::FUN_00500070;
                result = (this->*move)();
            }
            else if (action == 6) {
                RHFocusNode<RHFocusGroupableView> *head = *(RHFocusNode<RHFocusGroupableView> *volatile *)&m_groupHead;
                if (m_groupCursor != head) {
                    result = (this->*link)(0, m_groupCursor->value->V14(false));
                    result = (this->*link)(result, m_groupCursor->value->V18(false));
                    result = (this->*link)(result, m_groupCursor->value->V00());
                    RHFocusNode<RHFocusGroupableView> *end = *(RHFocusNode<RHFocusGroupableView> *volatile *)&m_groupHead;
                    m_groupCursor = end;
                }
            }
            else if (action == 5) {
                RHFocusNode<RHFocusGroupableView> *head = *(RHFocusNode<RHFocusGroupableView> *volatile *)&m_groupHead;
                RHFocusNode<RHFocusGroupableView> *cursor = m_groupCursor;
                if (cursor != head) {
                    RHFocusGroupableView *widget = cursor->value;
                    result = widget->V18(true);
                }
            }
        }
    }
    return result;
}

// STUB: GAME 0x005004d0
RHFocusEvent *RHFocusManager::FUN_005004d0(const void *input)
{
    RHFocusEvent *result = 0;
    if (m_40[1] == true) {
        unsigned key = 0;
        for (; (unsigned short)key <= 255; ++key) {
            RHGameWidgetInputCalls *shortcuts = *(RHGameWidgetInputCalls **)((char *)input + 0x0c);
            int pressed = shortcuts->FUN_0060e240((unsigned short)key);
            typedef RHFocusShortcutIterator (RHFocusShortcutTree::*Find)(const unsigned short &);
            Find find = &RHFocusShortcutTree::FUN_00500a20;
            const unsigned short &shortcut = *(const unsigned short *)&key;
            typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
            Link link = &RHFocusManager::FUN_00500040;
            if (pressed == 1) {
                shortcuts = *(RHGameWidgetInputCalls **)((char *)input + 0x0c);
                int state = *(int *)((char *)shortcuts + 0xa0c + (key & 0xffff) * 4);
                if (state == 0) {
                    RHFocusNode<RHFocusGroupableView> *groupHead = *(RHFocusNode<RHFocusGroupableView> *volatile *)&m_groupHead;
                    if (m_groupCursor == groupHead) {
                        RHFocusNode<RHFocusFocusableView> *focusHead = *(RHFocusNode<RHFocusFocusableView> *volatile *)&m_focusHead;
                        if (m_focusCursor == focusHead) {
                            RHFocusShortcutIterator found = (((RHFocusShortcutTree *)((char *)this + 0x44))->*find)(shortcut);
                            if (found.node != ((RHFocusShortcutTree *)((char *)this + 0x44))->head && found.node->widget != m_groupCursor->value) {
                                typedef void (std::vector<unsigned short>::*Insert)(unsigned short *, unsigned, const unsigned short &);
                                Insert insert = &std::vector<unsigned short>::insert;
                                (m_pressed.*insert)(m_pressed.end(), 1, shortcut);
                                typedef RHFocusEvent *(RHFocusManager::*Focus)(RHFocusGroupableView *);
                                Focus focus = &RHFocusManager::FUN_005007a0;
                                result = (this->*link)(result, (this->*focus)(found.node->widget));
                                return (this->*link)(result, found.node->widget->V18(true));
                            }
                        }
                    }
                }
            }
            else if (pressed == 0) {
                shortcuts = *(RHGameWidgetInputCalls **)((char *)input + 0x0c);
                if (((RHPortraitKeyboardCalls *)shortcuts)->FUN_0060e270((unsigned short)key)) {
                    unsigned short *first = std::find(m_pressed.begin(), m_pressed.end(), shortcut);
                    if (first != m_pressed.end()) {
                        m_pressed.erase(first);
                        RHFocusShortcutIterator found = (((RHFocusShortcutTree *)((char *)this + 0x44))->*find)(shortcut);
                        if (found.node != ((RHFocusShortcutTree *)((char *)this + 0x44))->head && found.node->widget == m_groupCursor->value) {
                            RHFocusEvent *events = (this->*link)(result, m_groupCursor->value->V14(false));
                            events = (this->*link)(events, m_groupCursor->value->V18(false));
                            result = (this->*link)(events, m_groupCursor->value->V00());
                            m_groupCursor = m_groupHead;
                        }
                    }
                }
            }
        }
    }
    return result;
}

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

// FUNCTION: GAME 0x00500780
void RHFocusManager::FUN_00500780(bool value)
{
    m_40[0] = value;
}

// FUNCTION: GAME 0x00500790
void RHFocusManager::FUN_00500790(bool value)
{
    m_40[1] = value;
}

struct RHFocusGroupSnapshot
{
    RHFocusNode<RHFocusGroupableView> *head;
    RHFocusNode<RHFocusGroupableView> *cursor;
};

inline RHFocusGroupSnapshot RHFocusGroupCursor(const RHFocusManager &manager)
{
    RHFocusGroupSnapshot result;
    result.head = *(RHFocusNode<RHFocusGroupableView> **)((char *)&manager + 0x14);
    result.cursor = *(RHFocusNode<RHFocusGroupableView> **)((char *)&manager + 0x38);
    return result;
}

// FUNCTION: GAME 0x005007a0
RHFocusEvent *RHFocusManager::FUN_005007a0(RHFocusGroupableView *widget)
{
    RHFocusEvent *result = 0;
    typedef RHFocusEvent *(RHFocusManager::*Link)(RHFocusEvent *, RHFocusEvent *) const;
    Link link = &RHFocusManager::FUN_00500040;
    RHFocusGroupSnapshot group = RHFocusGroupCursor(*this);
    if (group.cursor != group.head) {
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

// FUNCTION: GAME 0x005008f0
RHFocusShortcutIterator RHFocusShortcutTree::FUN_005008f0(RHFocusShortcutIterator first, RHFocusShortcutIterator last)
{
    if (count != 0 && first.node == head->left && last.node == head) {
        RHUnk00641782 lock;
        RHFocusShortcutNode *node = head->parent;
        {
            RHUnk00641782 inner;
            for (RHFocusShortcutNode *next = node; next != g_unk0x006c0ac0; node = next) {
                FUN_005010c0(next->right);
                next = next->left;
                operator delete(node);
            }
        }
        Root() = g_unk0x006c0ac0;
        count = 0;
        Leftmost() = head;
        Rightmost() = head;
        return Begin();
    }
    while (first.node != last.node)
        FUN_00500ba0(first++);
    return first;
}

// FUNCTION: GAME 0x00500a20
RHFocusShortcutIterator RHFocusShortcutTree::FUN_00500a20(const unsigned short &key)
{
    typedef RHFocusShortcutNode *(RHFocusShortcutTree::*LowerBound)(const unsigned short &);
    LowerBound lowerBound = &RHFocusShortcutTree::FUN_00501450;
    RHFocusShortcutIterator found((this->*lowerBound)(key));
    return found.node == head || key < found.node->key ? RHFocusShortcutIterator(head) : found;
}

// FUNCTION: GAME 0x00500a70
RHFocusShortcutInsertResult RHFocusShortcutTree::FUN_00500a70(const RHFocusShortcutValue &value)
{
    RHFocusShortcutNode *parent = head;
    bool before = true;
    RHFocusShortcutNode *child = parent->parent;
    {
        RHUnk00641782 lock;
        while (child != g_unk0x006c0ac0) {
            parent = child;
            before = value.key < child->key;
            child = before ? child->left : child->right;
        }
    }
    typedef RHFocusShortcutIterator (RHFocusShortcutTree::*Insert)(RHFocusShortcutNode *, RHFocusShortcutNode *, const RHFocusShortcutValue &);
    Insert insert = &RHFocusShortcutTree::FUN_00501150;
    if (multi)
    {
        RHFocusShortcutInsertResult result((this->*insert)(child, parent, value), true);
        return result;
    }
    RHFocusShortcutIterator position(parent);
    if (before) {
        if (position.node == head->left) {
            RHFocusShortcutInsertResult result((this->*insert)(child, parent, value), true);
            return result;
        }
        typedef void (RHFocusShortcutIterator::*Previous)();
        Previous previous = &RHFocusShortcutIterator::FUN_005014c0;
        (position.*previous)();
    }
    if (position.node->key < value.key) {
        RHFocusShortcutInsertResult result((this->*insert)(child, parent, value), true);
        return result;
    }
    RHFocusShortcutInsertResult result(position, false);
    return result;
}

static inline RHFocusShortcutNode *FocusShortcutMin(RHFocusShortcutNode *node)
{
    RHUnk00641782 lock;
    while (node->left != g_unk0x006c0ac0)
        node = node->left;
    return node;
}

static inline RHFocusShortcutNode *FocusShortcutMax(RHFocusShortcutNode *node)
{
    RHUnk00641782 lock;
    while (node->right != g_unk0x006c0ac0)
        node = node->right;
    return node;
}

// FUNCTION: GAME 0x00500ba0
RHFocusShortcutIterator RHFocusShortcutTree::FUN_00500ba0(RHFocusShortcutIterator entry)
{
    RHFocusShortcutNode *removed = (entry++).node;
    RHFocusShortcutNode *original = removed;
    RHFocusShortcutNode *replacement;
    RHUnk00641782 lock;
    if (Left(removed) == g_unk0x006c0ac0)
        replacement = Right(removed);
    else if (Right(removed) == g_unk0x006c0ac0)
        replacement = Left(removed);
    else {
        removed = FocusShortcutMin(Right(removed));
        replacement = Right(removed);
    }
    if (removed != original) {
        Parent(Left(original)) = removed;
        Left(removed) = Left(original);
        if (removed == Right(original))
            Parent(replacement) = removed;
        else {
            Parent(replacement) = Parent(removed);
            Left(Parent(removed)) = replacement;
            Right(removed) = Right(original);
            Parent(Right(original)) = removed;
        }
        if (Root() == original)
            Root() = removed;
        else if (Left(Parent(original)) == original)
            Left(Parent(original)) = removed;
        else
            Right(Parent(original)) = removed;
        Parent(removed) = Parent(original);
        int color = Color(removed);
        Color(removed) = Color(original);
        Color(original) = color;
        removed = original;
    }
    else {
        Parent(replacement) = Parent(removed);
        if (Root() == original)
            Root() = replacement;
        else if (Left(Parent(original)) == original)
            Left(Parent(original)) = replacement;
        else
            Right(Parent(original)) = replacement;
        if (Leftmost() == original) {
            if (Right(original) == g_unk0x006c0ac0)
                Leftmost() = Parent(original);
            else
                Leftmost() = FocusShortcutMin(replacement);
        }
        if (Rightmost() == original) {
            if (Left(original) == g_unk0x006c0ac0)
                Rightmost() = Parent(original);
            else
                Rightmost() = FocusShortcutMax(replacement);
        }
    }
    if (Color(removed) == 1) {
        while (replacement != Root() && Color(replacement) == 1) {
            if (replacement == Left(Parent(replacement))) {
                RHFocusShortcutNode *sibling = Right(Parent(replacement));
                if (Color(sibling) == 0) {
                    Color(sibling) = 1;
                    Color(Parent(replacement)) = 0;
                    RotateLeft(Parent(replacement));
                    sibling = Right(Parent(replacement));
                }
                if (Color(Left(sibling)) == 1 && Color(Right(sibling)) == 1) {
                    Color(sibling) = 0;
                    replacement = Parent(replacement);
                }
                else {
                    if (Color(Right(sibling)) == 1) {
                        Color(Left(sibling)) = 1;
                        Color(sibling) = 0;
                        RotateRight(sibling);
                        sibling = Right(Parent(replacement));
                    }
                    Color(sibling) = Color(Parent(replacement));
                    Color(Parent(replacement)) = 1;
                    Color(Right(sibling)) = 1;
                    RotateLeft(Parent(replacement));
                    break;
                }
            }
            else {
                RHFocusShortcutNode *sibling = Left(Parent(replacement));
                if (Color(sibling) == 0) {
                    Color(sibling) = 1;
                    Color(Parent(replacement)) = 0;
                    RotateRight(Parent(replacement));
                    sibling = Left(Parent(replacement));
                }
                if (Color(Right(sibling)) == 1 && Color(Left(sibling)) == 1) {
                    Color(sibling) = 0;
                    replacement = Parent(replacement);
                }
                else {
                    if (Color(Left(sibling)) == 1) {
                        Color(Right(sibling)) = 1;
                        Color(sibling) = 0;
                        RotateLeft(sibling);
                        sibling = Left(Parent(replacement));
                    }
                    Color(sibling) = Color(Parent(replacement));
                    Color(Parent(replacement)) = 1;
                    Color(Left(sibling)) = 1;
                    RotateRight(Parent(replacement));
                    break;
                }
            }
        }
        Color(replacement) = 1;
    }
    operator delete(removed);
    --count;
    return entry;
}


// FUNCTION: GAME 0x005010c0
void RHFocusShortcutTree::FUN_005010c0(RHFocusShortcutNode *node)
{
    RHUnk00641782 lock;
    RHFocusShortcutNode *next = node;
    while (next != g_unk0x006c0ac0) {
        FUN_005010c0(next->right);
        next = next->left;
        delete node;
        node = next;
    }
}

struct RHsoundGroup;
typedef std::pair<const unsigned long, RHsoundGroup *> RHFocusFoldedPair;
namespace std
{
    template <> void _Construct(RHFocusFoldedPair *destination, const RHFocusFoldedPair &value);
}

// FUNCTION: GAME 0x00501150
RHFocusShortcutIterator RHFocusShortcutTree::FUN_00501150(RHFocusShortcutNode *child, RHFocusShortcutNode *parent, const RHFocusShortcutValue &value)
{
    RHUnk00641782 lock;
    RHFocusShortcutNode *inserted = (RHFocusShortcutNode *)operator new(sizeof(RHFocusShortcutNode));
    inserted->parent = parent;
    inserted->color = 0;
    inserted->left = g_unk0x006c0ac0;
    inserted->right = g_unk0x006c0ac0;
    std::_Construct((RHFocusFoldedPair *)&inserted->key, *(const RHFocusFoldedPair *)&value);
    ++count;
    if (parent == head || child != g_unk0x006c0ac0 || value.key < parent->key) {
        parent->left = inserted;
        if (parent == head) {
            head->parent = inserted;
            head->right = inserted;
        }
        else if (parent == head->left)
            head->left = inserted;
    }
    else {
        parent->right = inserted;
        if (parent == head->right)
            head->right = inserted;
    }
    for (child = inserted; child != head->parent && child->parent->color == 0;) {
        if (Parent(child) == Left(Parent(Parent(child)))) {
            parent = child->parent->parent->right;
            if (parent->color == 0) {
                child->parent->color = 1;
                parent->color = 1;
                child->parent->parent->color = 0;
                child = child->parent->parent;
            }
            else {
                if (child == child->parent->right) {
                    child = child->parent;
                    RotateLeft(child);
                }
                child->parent->color = 1;
                child->parent->parent->color = 0;
                RotateRight(child->parent->parent);
            }
        }
        else {
            parent = Left(Parent(Parent(child)));
            if (parent->color == 0) {
                child->parent->color = 1;
                parent->color = 1;
                child->parent->parent->color = 0;
                child = child->parent->parent;
            }
            else {
                if (child == child->parent->left) {
                    child = child->parent;
                    RotateRight(child);
                }
                child->parent->color = 1;
                child->parent->parent->color = 0;
                RotateLeft(child->parent->parent);
            }
        }
    }
    head->parent->color = 1;
    return RHFocusShortcutIterator(inserted);
}

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

struct RHFocusShortcutAccess
{
    static RHFocusShortcutNode *&Left(RHFocusShortcutNode *node) { return node->left; }
    static RHFocusShortcutNode *&Right(RHFocusShortcutNode *node) { return node->right; }
    static RHFocusShortcutNode *&Parent(RHFocusShortcutNode *node) { return node->parent; }
    static int &Color(RHFocusShortcutNode *node) { return node->color; }
    static RHFocusShortcutNode *Max(RHFocusShortcutNode *node)
    {
        RHUnk00641782 inner;
        while (Right(node) != g_unk0x006c0ac0)
            node = Right(node);
        return node;
    }
};

// FUNCTION: GAME 0x005014c0
void RHFocusShortcutIterator::FUN_005014c0()
{
    RHUnk00641782 lock;
    if (RHFocusShortcutAccess::Color(node) == 0 && RHFocusShortcutAccess::Parent(RHFocusShortcutAccess::Parent(node)) == node)
        node = RHFocusShortcutAccess::Right(node);
    else if (RHFocusShortcutAccess::Left(node) != g_unk0x006c0ac0)
        node = RHFocusShortcutAccess::Max(RHFocusShortcutAccess::Left(node));
    else {
        RHFocusShortcutNode *parent;
        while (node == RHFocusShortcutAccess::Left(parent = RHFocusShortcutAccess::Parent(node)))
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
    new RHFocusManager(0);
    manager->FUN_004ffc20((RHFocusFocusableView *)widget);
    manager->FUN_004ffc70((RHFocusGroupableView *)widget, false);
    manager->FUN_004ffce0((RHFocusGroupableView *)widget, 0);
    manager->FUN_004ffd20(widget);
    manager->FUN_004ffed0(widget);
    manager->FUN_004fffd0();
    manager->FUN_004fffe0(false);
    manager->FUN_00500010(widget);
    manager->FUN_00500040(event, event);
    manager->FUN_00500070();
    manager->FUN_005000d0();
    manager->FUN_00500130();
    manager->FUN_005001e0();
    manager->FUN_005002a0(event, widget, (void *)widget);
    manager->FUN_005003a0(widget);
    manager->FUN_005004d0(widget);
    manager->FUN_005006a0();
    manager->FUN_00500720();
    manager->FUN_00500750();
    manager->FUN_00500780(false);
    manager->FUN_00500790(false);
    manager->FUN_005007a0((RHFocusGroupableView *)widget);
    manager->FUN_00500830(widget);
    RHFocusManager::FUN_005008a0(event, widget);
    ((RHFocusShortcutTree *)((char *)manager + 0x44))->FUN_00500a20(*(const unsigned short *)widget);
    ((RHFocusShortcutTree *)((char *)manager + 0x44))->~RHFocusShortcutTree();
    ((RHFocusShortcutTree *)((char *)manager + 0x44))->FUN_005010c0((RHFocusShortcutNode *)event);
    ((RHFocusShortcutTree *)((char *)manager + 0x44))->FUN_00501450(*(const unsigned short *)widget);
    ((RHFocusShortcutIterator *)event)->FUN_005014c0();
    ((RHFocusShortcutIterator *)event)->FUN_00501580();
}
