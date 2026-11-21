#ifndef RHSEQUENCECONSTRUCTIONCALLS_H
#define RHSEQUENCECONSTRUCTIONCALLS_H

#include <list>

class RHSequenceElement;
class SBGeoPoint2D;
class SBFile;
struct RHMovementBox;

class RHSequenceElementListStorage : public std::list<RHSequenceElement *>
{
public:
    class Cursor : public std::list<RHSequenceElement *>::iterator
    {
    public:
        _Nodeptr &Node() { return _Ptr; }
    };

    RHSequenceElementListStorage() : m_dirty(true) {}
    ~RHSequenceElementListStorage();
    void GoTo(int wanted);
    void GoToInline(int wanted);
    void Append(RHSequenceElement *const &element, volatile bool &dirty)
    {
        _Nodeptr node = _Head;
        _Acc::_Prev(node) = _Buynode(node, _Acc::_Prev(node));
        node = _Acc::_Prev(node);
        _Acc::_Next(_Acc::_Prev(node)) = node;
        allocator.construct(&_Acc::_Value(node), element);
        unsigned count = *(volatile unsigned *)&_Size;
        dirty = true;
        _Size = count + 1;
    }
    _Nodeptr &SetCurrent(iterator position)
    {
        m_cursor.Node() = position._Mynode();
        return m_cursor.Node();
    }
    __forceinline void AdvanceCurrent(int distance)
    {
        for (; distance > 0; --distance)
            ++m_cursor;
        for (; distance < 0; ++distance)
            --m_cursor;
    }
    Cursor m_cursor;
    bool m_dirty;
    int m_index;
};

class RHSequenceElementList : public RHSequenceElementListStorage
{
public:
    ~RHSequenceElementList();
    void DeleteAll();
    void clear();
};

// VTABLE: GAME 0x00679cd4
class RHSequence
{
public:
    RHSequence();
    virtual ~RHSequence();
    bool Serialize(SBFile &file, bool pointers);
    static bool SerializeStaticStuff(SBFile &file);
    void Unk005849e0(RHSequenceElement *first, RHSequenceElement *second);
    void Emit(SBFile &file);
    bool FUN_00582640(unsigned short &level, void *actor, int style, const SBGeoPoint2D &start, void *startArea, unsigned short startLayer, const SBGeoPoint2D &end, void *endArea, unsigned short endLayer, void *element, float distance, unsigned long flags, float scale);
    bool FUN_00583630(unsigned short &level, void *actor, int style, const SBGeoPoint2D &start, void *startArea, unsigned short startLayer, void *&endArea, unsigned short &endLayer, void *element, RHMovementBox *line, float distance, unsigned long flags);
    int m_04;
    RHSequenceElementList m_elements;
    char m_20[0x0c];
    short m_2c;
    short m_2e;
    short m_30;
    short m_32;
    char m_34;
    char m_35[7];
};

#endif
