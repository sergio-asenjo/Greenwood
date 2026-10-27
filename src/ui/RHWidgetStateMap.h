#ifndef RHWIDGETSTATEMAP_H
#define RHWIDGETSTATEMAP_H

#include "Decomp.h"
#include <utility>

class RHUnk00514e10
{
public:
    typedef std::pair<const int, int> Value;
    struct Node
    {
        Node *left;
        Node *parent;
        Node *right;
        Value value;
        int color;
    };
    struct Iterator
    {
        Iterator() {}
        Iterator(Node *node) : node(node) {}
        void FUN_005159d0();
        void FUN_00515a90();
        Iterator operator++(int) { Iterator old = *this; FUN_00515a90(); return old; }
        Node *node;
    };
    struct Pair
    {
        Pair() {}
        Pair(const Iterator &entry, bool inserted) : first(entry), second(inserted) {}
        Iterator first;
        bool second;
    };
    int &FUN_00514e10(const int &key);
    void FUN_00514e50();
    Iterator FUN_00514ec0(Iterator first, Iterator last);
    Pair FUN_00514ff0(const Value &value);
    Iterator FUN_00515120(Iterator entry);
    void FUN_00515640(Node *node);
    Iterator FUN_005156d0(Node *node, Node *parent, const Value &value);
    Node *&Root() { return m_head->parent; }
    Node *&Leftmost() { return m_head->left; }
    Node *&Rightmost() { return m_head->right; }
    Iterator begin() { return Iterator(Leftmost()); }
    static Node *&Left(Node *node) { return node->left; }
    static Node *&Right(Node *node) { return node->right; }
    static Node *&Parent(Node *node) { return node->parent; }
    static int &Color(Node *node) { return node->color; }
    void RotateLeft(Node *node);
    void RotateRight(Node *node);
    undefined m_00[4];
    Node *m_head;
    bool m_multi;
    undefined m_09[3];
    unsigned m_size;
};

#endif
