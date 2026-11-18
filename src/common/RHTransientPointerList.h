#ifndef RHTRANSIENTPOINTERLIST_H
#define RHTRANSIENTPOINTERLIST_H

#include <list>
#include "SBListCursor.h"

template<class T>
class RHTransientPointerList : public std::list<T *>
{
public:
    typedef std::list<T *> Base;
    typedef Base::_Node Node;
    RHTransientPointerList();
    RHTransientPointerList(const std::allocator<T *> &allocator) : Base(allocator), dirty(true) {}
    ~RHTransientPointerList() { clear(); }
    unsigned &Count() { return _Size; }
    Node *Head() { return _Head; }
    int GetSize() { return (int &)_Size; }
    __forceinline void GoTo(int index) { ((RHProfileListCursor *)this)->GoTo(index); }
    struct ConstIterator : public std::iterator<std::bidirectional_iterator_tag, void *>
    {
        Node *node;
        ConstIterator() {}
        ConstIterator(Node *value) : node(value) {}
    };
    struct Iterator : public ConstIterator
    {
        Iterator() {}
        Iterator(Node *value) : ConstIterator(value) {}
        void *&operator*() const { return *(void **)&node->_Value; }
        Iterator operator++(int)
        {
            Iterator previous = *this;
            node = node->_Next;
            return previous;
        }
    };
    Iterator Current() const { return Iterator((Node *)cursor); }
    Iterator &SetCurrent(Iterator iterator)
    {
        cursor = iterator.node;
        return *(Iterator *)&cursor;
    }
    int Find(void *const &value);
    void InsertLast(void *value);
    void InsertLastExternal(void *const &value);
    Node *cursor;
    bool dirty;
    char m_11[3];
    int index;
    bool searching;
    char m_19[3];
    int found;
    void *value;
};

template<class T>
int RHTransientPointerList<T>::Find(void *const &value)
{
    void *sought = *(void *const volatile *)&value;
    Node *head = _Head;
    this->value = sought;
    int count = (int &)_Size;
    searching = true;
    SetCurrent(Iterator(head->_Next));
    int position;
    for (position = 0; position < count; ++position, ((Iterator &)cursor)++)
    {
        if (*Current() == this->value)
            break;
    }
    if (position < count)
    {
        found = position;
        dirty = false;
        index = position;
    }
    else
    {
        dirty = true;
        found = -1;
    }
    return found;
}

template<class T>
void RHTransientPointerList<T>::InsertLast(void *value)
{
    Node *head = _Head;
    Node *previous = head->_Prev;
    Node *node = (Node *)operator new(0xc);
    node->_Next = head ? head : node;
    node->_Prev = previous ? previous : node;
    head->_Prev = node;
    node->_Prev->_Next = node;
    if (&node->_Value)
        node->_Value = (T *)value;
    ++_Size;
    dirty = true;
}

template<class T>
void RHTransientPointerList<T>::InsertLastExternal(void *const &value)
{
    Node *head = _Head;
    Node *previous = head->_Prev;
    Node *node = (Node *)operator new(0xc);
    node->_Next = head ? head : node;
    node->_Prev = previous ? previous : node;
    head->_Prev = node;
    node->_Prev->_Next = node;
    node->_Value = (T *)value;
    ++_Size;
    dirty = true;
}

#endif
