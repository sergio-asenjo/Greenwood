#ifndef RHGENERICMAP_H
#define RHGENERICMAP_H

#include <new>

struct RHGenericValue
{
    unsigned int m_0;
    unsigned int m_4;
    unsigned int m_8;
};

struct RHGenericNode
{
    RHGenericNode *left;
    RHGenericNode *parent;
    RHGenericNode *right;
    int key;
    RHGenericValue value;
    int color;
};

struct RHGenericIterator;

struct RHGenericConstIterator
{
    RHGenericNode *node;
    RHGenericConstIterator() {}
    RHGenericConstIterator(RHGenericNode *value) : node(value) {}
    RHGenericConstIterator(const RHGenericIterator &value);
};

struct RHGenericIterator : RHGenericConstIterator
{
    RHGenericIterator() {}
    RHGenericIterator(RHGenericNode *value) : RHGenericConstIterator(value) {}
    void FUN_00587ed0();
    void FUN_005880d0();
    RHGenericIterator operator++(int)
    {
        RHGenericIterator previous(*this);
        FUN_00587ed0();
        return previous;
    }
    bool operator==(const RHGenericIterator &other) const { return node == other.node; }
    bool operator!=(const RHGenericIterator &other) const { return !(*this == other); }
    RHGenericNode *Node() const { return node; }
    void EmitTree();
};

inline RHGenericConstIterator::RHGenericConstIterator(const RHGenericIterator &value) : node(value.node) {}

struct RHGenericPair
{
    int key;
    RHGenericValue value;
};

struct RHGenericInsertResult
{
    RHGenericIterator iterator;
    bool inserted;
    RHGenericInsertResult(const RHGenericIterator &value, const bool &success) : iterator(value), inserted(success) {}
};

class RHGenericMap
{
public:
    RHGenericMap();
    ~RHGenericMap();
    RHGenericInsertResult FUN_005873a0(const RHGenericPair &value);
    RHGenericIterator FUN_005874d0(RHGenericIterator first, RHGenericIterator last);
    RHGenericIterator FUN_00587600(RHGenericIterator position);
    RHGenericIterator FUN_00587b20(const int &key);
    RHGenericIterator FUN_00587bd0(RHGenericNode *position, RHGenericNode *parent, const RHGenericPair &value);
    void FUN_00587b40(RHGenericNode *node);
    RHGenericNode *FUN_00587f80(RHGenericNode *node, RHGenericNode *parent);
    RHGenericNode *FUN_005880b0(RHGenericNode *parent, int color);
    void EmitTree(RHGenericNode *node);
    void RotateLeft(RHGenericNode *node);
    void RotateRight(RHGenericNode *node);
    static RHGenericNode *&Left(RHGenericNode *node) { return node->left; }
    static RHGenericNode *&Parent(RHGenericNode *node) { return node->parent; }
    static RHGenericNode *&Right(RHGenericNode *node) { return node->right; }
    static int &Color(RHGenericNode *node) { return node->color; }
    static RHGenericNode *Minimum(RHGenericNode *node);
    static RHGenericNode *Maximum(RHGenericNode *node);
    RHGenericNode *&Root() { return head->parent; }
    RHGenericNode *&Leftmost() { return head->left; }
    RHGenericNode *&Rightmost() { return head->right; }
    RHGenericIterator begin() { return RHGenericIterator(Leftmost()); }
    RHGenericIterator end() { return RHGenericIterator(head); }
    void Clear() { FUN_005874d0(begin(), end()); }
    RHGenericMap &Assign(const RHGenericMap &other);
    void Initialize();
    void Freenode(RHGenericNode *node) { operator delete(node); }
    RHGenericNode *Buynode(RHGenericNode *parent, int color)
    {
        RHGenericNode *node = (RHGenericNode *)operator new(sizeof(RHGenericNode));
        Parent(node) = parent;
        Color(node) = color;
        return node;
    }
    RHGenericConstIterator Find(const int &key)
    {
        const RHGenericIterator &lower = FUN_00587b20(key);
        RHGenericConstIterator position(lower);
        return position.node == head || key < position.node->key ? RHGenericConstIterator(head) : position;
    }

    char m_00[4];
    RHGenericNode *head;
    bool multi;
    unsigned int count;
};

#endif
