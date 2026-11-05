#ifndef RHSEQUENCECONSTRUCTIONCALLS_H
#define RHSEQUENCECONSTRUCTIONCALLS_H

#include <list>

class RHSequenceElement;
class SBGeoPoint2D;

class RHSequenceElementListStorage : public std::list<RHSequenceElement *>
{
public:
    RHSequenceElementListStorage() : m_dirty(true) {}
    ~RHSequenceElementListStorage();
    iterator m_cursor;
    bool m_dirty;
};

class RHSequenceElementList : public RHSequenceElementListStorage
{
public:
    ~RHSequenceElementList();
    void DeleteAll();
    void clear();
};

// VTABLE: GAME 0x00679cd4
class RHUnk00582220
{
public:
    RHUnk00582220();
    ~RHUnk00582220();
    virtual void *FUN_00582280(unsigned int flags);
    void Slot00();
    bool FUN_00582640(unsigned short &level, void *actor, int style, const SBGeoPoint2D &start, void *startArea, unsigned short startLayer, const SBGeoPoint2D &end, void *endArea, unsigned short endLayer, void *element, float distance, unsigned long flags, float scale);
    int m_04;
    RHSequenceElementList m_elements;
    char m_1c[0x10];
    short m_2c;
    short m_2e;
    short m_30;
    short m_32;
    char m_34;
    char m_35[7];
};

#endif
