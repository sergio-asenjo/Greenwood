#ifndef RHSEQUENCEMANAGER_H
#define RHSEQUENCEMANAGER_H

#include "RHOrder.h"
#include "Decomp.h"
#include <list>
#include <new>

class RHSequence
{
public:
    bool Serialize(SBFile &file, bool loading);
    static bool SerializeStaticStuff(SBFile &file);
};

class RHSequenceElement
{
public:
    static bool SerializeStaticStuff(SBFile &file);
};

class RHManagerListCalls
{
public:
    void FUN_0058bed0();
};

class RHPathSequenceSerializer
{
public:
    bool FUN_0058b7c0(SBFile &file, void *&value);
};

// SIZE 0x3c
class RHUnk00582220
{
public:
    RHUnk00582220();
    ~RHUnk00582220();
    undefined data[0x3c]; // 0x00
};

struct RHScriptNode;
struct RHTitbitNode;
struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
    RHScriptIter(const RHScriptIter &other) : node(other.node) {}
    RHScriptIter &operator=(const RHScriptIter &other) { node = other.node; return *this; }
};

class RHUnk0046eb30
{
public:
    RHScriptIter begin();
    RHScriptIter FUN_0046eb80();
    RHScriptIter erase(RHScriptIter position);
};

class RHTitbitList
{
public:
    void Clear(void *result, RHTitbitNode *first, RHTitbitNode *last);
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
    void GoTo(int index);
};

template<class T> struct RHManagerNode
{
    RHManagerNode *next;
    RHManagerNode *previous;
    T value;
};

// SIZE 0x24
template<class T> class RHManagerList
{
public:
    typedef typename std::list<T>::iterator Iterator;
    undefined4 allocator; // +0x00
    RHManagerNode<T> *head; // +0x04
    int count; // +0x08
    Iterator cursor; // +0x0c
    char valid; // +0x10
    undefined padding[3]; // 0x11
    int index; // +0x14
    undefined padding18[12]; // 0x18

    Iterator begin()
    {
        typedef Iterator (RHUnk0046eb30::*Begin)();
        return (((RHUnk0046eb30 *)this)->*(Begin)&RHUnk0046eb30::begin)();
    }
    Iterator erase(Iterator position)
    {
        typedef Iterator (RHUnk0046eb30::*Erase)(Iterator);
        Iterator result = (((RHUnk0046eb30 *)this)->*(Erase)&RHUnk0046eb30::erase)(position);
        valid = 1;
        return result;
    }
    T &operator[](int wanted)
    {
        ((RHSeqList *)this)->GoTo(wanted);
        return *cursor;
    }
    T &Get(int wanted)
    {
        int size = count;
        if (valid)
        {
            if (wanted <= (size + 1) / 2)
            {
                Iterator &current = cursor;
                typedef Iterator (RHUnk0046eb30::*Begin)();
                current = (((RHUnk0046eb30 *)this)->*(Begin)&RHUnk0046eb30::begin)();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
            }
            else
            {
                cursor = ((std::list<T> *)this)->end();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - size, category);
            }
            valid = 0;
            index = wanted;
        }
        else
        {
            int previous = index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        Iterator &current = cursor;
                        typedef Iterator (RHUnk0046eb30::*Begin)();
                        current = (((RHUnk0046eb30 *)this)->*(Begin)&RHUnk0046eb30::begin)();
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                    }
                }
                else if (wanted < (size + previous) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                }
                else
                {
                    cursor = ((std::list<T> *)this)->end();
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - size, category);
                }
                index = wanted;
            }
        }
        return *cursor;
    }
    void clear()
    {
        Iterator position = ((std::list<T> *)this)->begin();
        Iterator end = ((std::list<T> *)this)->end();
        typedef Iterator (RHUnk0046eb30::*Erase)(Iterator);
        while (position != end)
        {
            (((RHUnk0046eb30 *)this)->*(Erase)&RHUnk0046eb30::erase)(position++);
        }
        valid = 1;
    }

    void push_back(const T &value)
    {
        ((std::list<T> *)this)->push_back(value);
        valid = 1;
    }
};

// SIZE 0x2c
class RHManagerSequenceView
{
public:
    int m_0; // +0x00
    int m_4; // +0x04
    RHManagerList<RHSequenceElement *> m_8; // +0x08
};

// SIZE 0x3c
class RHManagerElementView
{
public:
    undefined padding[0x18]; // 0x00
    RHManagerList<RHOrder *> m_18; // +0x18
};

template<class T> class RHManagerCopyList : public RHManagerList<T>
{
public:
    void push_back(const T &value)
    {
        RHManagerNode<T> *next = head;
        RHManagerNode<T> *previous = next->previous;
        RHManagerNode<T> *node = (RHManagerNode<T> *)::operator new(sizeof(RHManagerNode<T>));
        node->next = next ? next : node;
        node->previous = previous ? previous : node;
        next->previous = node;
        node->previous->next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&value);
        ++count;
        valid = 1;
    }
};

// SIZE 0x1b4
class RHSequenceManager
{
public:
    bool Serialize(SBFile &file);
    bool PreSerializePointer(SBFile &file, RHOrder **order);
    bool PreSerializePointer(SBFile &file, RHSequenceElement **element, bool launch);
    bool PreSerializePointer(SBFile &file, RHSequence **sequence);
    bool SetAllPreSerializedPointers();
    bool SerializeSequenceElementPointer(SBFile &file, RHSequenceElement **element)
    {
        return ((RHPathSequenceSerializer *)this)->FUN_0058b7c0(file, (void *&)*element);
    }
    void Emit(SBFile &file);

    int m_0; // +0x00
    RHManagerList<RHSequence *> m_4; // +0x04
    RHManagerList<RHSequenceElement *> m_28; // +0x28
    RHManagerList<RHOrder **> m_4c; // +0x4c
    RHManagerList<int> m_70; // +0x70
    RHManagerCopyList<RHSequenceElement **> m_94; // +0x94
    RHManagerCopyList<int> m_b8; // +0xb8
    RHManagerCopyList<int> m_dc; // +0xdc
    RHManagerList<RHSequence **> m_100; // +0x100
    RHManagerList<int> m_124; // +0x124
    RHManagerList<RHOrder *> m_148; // +0x148
    RHManagerList<RHSequenceElement *> m_16c; // +0x16c
    RHManagerList<RHSequence *> m_190; // +0x190
};

#endif
