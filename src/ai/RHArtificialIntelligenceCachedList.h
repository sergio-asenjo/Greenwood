#ifndef RHARTIFICIALINTELLIGENCECACHEDLIST_H
#define RHARTIFICIALINTELLIGENCECACHEDLIST_H

#include <list>
#include "RHStimulus.h"
#include "SBListCursor.h"

template<class T>
class RHArtificialIntelligenceCachedList : public std::list<T>
{
public:
    typedef std::allocator<T> Allocator;
    RHArtificialIntelligenceCachedList(const Allocator &allocation = Allocator())
        : std::list<T>(allocation), dirty(true) {}
    ~RHArtificialIntelligenceCachedList()
    {
        typedef std::list<T> Storage;
        void (Storage::*clear)() = &Storage::clear;
        (this->*clear)();
    }
    __forceinline void GoTo(int wanted)
    {
        reinterpret_cast<RHProfileListCursor *>(this)->GoTo(wanted);
    }
    __forceinline iterator &Current()
    {
        return *reinterpret_cast<iterator *>(&cursor);
    }
    iterator Seek(int wanted)
    {
        typedef typename std::list<T>::_Nodeptr Node;
        iterator position = dirty || wanted < index ? begin() : iterator(static_cast<Node>(cursor));
        int start = dirty || wanted < index ? 0 : index;
        if ((_Size + start) / 2 < wanted)
        {
            position = end();
            start = _Size;
        }
        std::advance(position, wanted - start);
        cursor = *reinterpret_cast<Node *>(&position);
        index = wanted;
        dirty = false;
        return position;
    }
    void *cursor;
    bool dirty;
    char m_11[3];
    int index;
    bool searching;
    char m_19[3];
    int found;
    T value;
};

template<>
class RHArtificialIntelligenceCachedList<RHStimulus> : public std::list<RHStimulus>
{
public:
    typedef _Node Node;
    typedef std::allocator<RHStimulus> Allocator;
    RHArtificialIntelligenceCachedList(const Allocator &allocation = Allocator())
        : std::list<RHStimulus>(allocation), dirty(true) {}
    // FUNCTION: GAME 0x00423fa0
    ~RHArtificialIntelligenceCachedList()
    {
        ClearNodes();
    }
    void ClearNodes()
    {
        this->clear();
    }
    void *cursor;
    bool dirty;
    char m_11[3];
    int index;
    bool searching;
    char m_19[3];
    int found;
    RHStimulus value;
};

#endif
