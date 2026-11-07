#ifndef RHARTIFICIALINTELLIGENCECACHEDLIST_H
#define RHARTIFICIALINTELLIGENCECACHEDLIST_H

#include <list>
#include "RHStimulus.h"

template<class T>
class RHArtificialIntelligenceCachedList : public std::list<T>
{
public:
    RHArtificialIntelligenceCachedList() : dirty(true) {}
    ~RHArtificialIntelligenceCachedList()
    {
        typedef std::list<T> Storage;
        void (Storage::*clear)() = &Storage::clear;
        (this->*clear)();
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
    RHArtificialIntelligenceCachedList() : dirty(true) {}
    // FUNCTION: GAME 0x00423fa0
    ~RHArtificialIntelligenceCachedList()
    {
        ClearNodes();
    }
    void ClearNodes()
    {
        typedef std::list<unsigned long> Native;
        ((Native *)this)->clear();
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
