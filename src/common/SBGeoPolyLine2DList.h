#ifndef SBGEOPOLYLINE2DLIST_H
#define SBGEOPOLYLINE2DLIST_H

#include "Decomp.h"
#include <list>

#include "RHPathQueryCalls.h"

class RHMobileUnk00611360;

// SIZE 0x10
struct RHUnkPolyLineTail
{
    undefined m_00[8]; // 0x00
    SBGeoPoint2D m_08; // 0x08
};

// SIZE 0x28
class RHUnkPolyLineBase : public std::list<SBGeoPoint2D>
{
public:
    RHUnkPolyLineBase() : m_dirty(true) {}
    iterator Begin()
    {
        _Nodeptr sentinel = _Head;
        _Nodeptr first = *(_Nodeptr volatile *)&sentinel->_Next;
        return iterator(first);
    }
    iterator End()
    {
        _Nodeptr sentinel = *(_Nodeptr volatile *)&_Head;
        return iterator(sentinel);
    }
    struct Cursor : std::list<SBGeoPoint2D>::iterator
    {
        Cursor &Assign(_Nodeptr value)
        {
            *(_Nodeptr volatile *)this = value;
            return *this;
        }
    };
    iterator m_cursor; // 0x0c
    bool m_dirty; // 0x10
    int m_index; // 0x14
    RHUnkPolyLineTail m_18; // 0x18
};

class SBGeoPolyLine2DList : public RHUnkPolyLineBase
{
public:
    void Seek(int wanted);
    SBGeoPolyLine2DList();
    SBGeoPolyLine2DList(const SBGeoPolyLine2DList &other);
    SBGeoPolyLine2DList(const RHMobileUnk00611360 &other);
    void FUN_00610600(const SBGeoPolyLine2DList &other);
    void FUN_00610640(const RHMobileUnk00611360 &other);
    bool FUN_006107e0();
    void GoTo(int index) { ((RHPathQueryCalls *)this)->FUN_005c8e40(index); }
    void Load(SBGeoPoint2D &target)
    {
        const SBGeoPoint2D &value = *m_cursor;
        target = value;
    }
    void FUN_00610a00(const SBGeoPoint2D &point);
    void FUN_00610a60(const SBGeoPoint2D &point);
    void FUN_00610ac0();
    void FUN_00610b10();
    void FUN_00610b50(unsigned long index);
    const SBGeoPoint2D &FUN_00610cb0(unsigned long index) const;
};

#endif
