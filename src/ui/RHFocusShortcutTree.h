#ifndef RHFOCUSSHORTCUTTREE_H
#define RHFOCUSSHORTCUTTREE_H

#include <utility>
#include <memory>
#include <functional>

class RHFocusGroupableView;

struct RHFocusShortcutValue
{
    unsigned short key;
    RHFocusGroupableView *widget;
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

extern unsigned g_unk0x006c0abc;
extern RHFocusShortcutNode *g_unk0x006c0ac0;

class RHFocusShortcutPosition
{
public:
    RHFocusShortcutPosition(RHFocusShortcutNode *value = 0) : node(value) {}
    RHFocusShortcutNode *node;
};

class RHFocusShortcutIterator : public RHFocusShortcutPosition
{
public:
    RHFocusShortcutIterator(RHFocusShortcutNode *value = 0) : RHFocusShortcutPosition(value) {}
    void FUN_005014c0();
    void FUN_00501580();
    bool operator==(const RHFocusShortcutIterator &other) const { return node == other.node; }
    bool operator!=(const RHFocusShortcutIterator &other) const { return !(*this == other); }
    RHFocusShortcutIterator operator++(int)
    {
        RHFocusShortcutIterator previous = *this;
        typedef void (RHFocusShortcutIterator::*Advance)();
        Advance advance = &RHFocusShortcutIterator::FUN_00501580;
        (this->*advance)();
        return previous;
    }
};

typedef std::pair<RHFocusShortcutIterator, bool> RHFocusShortcutInsertResult;

class RHFocusShortcutTree
{
public:
    RHFocusShortcutTree(const std::less<unsigned short> &compare = std::less<unsigned short>(), const std::allocator<RHFocusShortcutValue> &allocator = std::allocator<RHFocusShortcutValue>());
    static RHFocusShortcutNode *&Left(RHFocusShortcutNode *node) { return node->left; }
    static RHFocusShortcutNode *&Parent(RHFocusShortcutNode *node) { return node->parent; }
    static RHFocusShortcutNode *&Right(RHFocusShortcutNode *node) { return node->right; }
    static int &Color(RHFocusShortcutNode *node) { return node->color; }
    RHFocusShortcutNode *&Root() { return head->parent; }
    RHFocusShortcutNode *&Leftmost() { return head->left; }
    RHFocusShortcutNode *&Rightmost() { return head->right; }
    RHFocusShortcutIterator Begin() { return RHFocusShortcutIterator(Leftmost()); }
    RHFocusShortcutIterator End() { return RHFocusShortcutIterator(head); }
    void FreeNode(RHFocusShortcutNode *node) { m_allocator.deallocate(node, 1); }
    void RotateLeft(RHFocusShortcutNode *node);
    void RotateRight(RHFocusShortcutNode *node);
    ~RHFocusShortcutTree()
    {
        FUN_005008f0(Begin(), End());
        FreeNode(head);
        head = 0;
        count = 0;
        {
            std::_Lockit lock;
            if (--g_unk0x006c0abc == 0) {
                FreeNode(g_unk0x006c0ac0);
                g_unk0x006c0ac0 = 0;
            }
        }
    }
    RHFocusShortcutIterator FUN_005008f0(RHFocusShortcutIterator first, RHFocusShortcutIterator last);
    RHFocusShortcutIterator FUN_00500a20(const unsigned short &key);
    RHFocusShortcutInsertResult FUN_00500a70(const RHFocusShortcutValue &value);
    RHFocusShortcutIterator FUN_00500ba0(RHFocusShortcutIterator position);
    void FUN_005010c0(RHFocusShortcutNode *node);
    RHFocusShortcutIterator FUN_00501150(RHFocusShortcutNode *child, RHFocusShortcutNode *parent, const RHFocusShortcutValue &value);
    RHFocusShortcutNode *FUN_00501450(const unsigned short &key);
    RHFocusShortcutNode *BuyNode(RHFocusShortcutNode *parent, int color);
    std::less<unsigned short> m_compare;
    std::allocator<RHFocusShortcutValue> m_allocator;
    RHFocusShortcutNode *head;
    bool multi;
    unsigned count;
};

#endif
