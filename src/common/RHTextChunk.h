#ifndef RH_TEXT_CHUNK_H
#define RH_TEXT_CHUNK_H

#include <list>
#include <iterator>

// SIZE 0xb4
struct RHTextChunk
{
    char m_text[0x84]; // 0x00
    char m_font[0x20]; // 0x84
    unsigned short m_flags; // 0xa4
    unsigned long m_color; // 0xa8
    unsigned long m_ac; // 0xac
    unsigned long m_size; // 0xb0
};

struct RHScriptNode;
struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};
class RHUnk0046eb30
{
public:
    RHScriptIter FUN_0046eb80();
};
void FUN_00625270(RHTextChunk *pointer, const RHTextChunk &value);
struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

// SIZE 0xd4
class RHTextChunkList : public std::list<RHTextChunk>
{
public:
    typedef _Node Node;
    struct Iterator
    {
        _Nodeptr node;
        Iterator(_Nodeptr value) : node(value) {}
    };
    _Nodeptr &Head() { return _Head; }
    Iterator Begin() { return Iterator(Head()->_Next); }
    Iterator End() { return Iterator(Head()); }
    _Nodeptr &SetCurrent(Iterator iterator)
    {
        m_current = iterator.node;
        return m_current;
    }
    void GoTo(int wanted)
    {
        int count = _Size;
        if (m_dirty)
        {
            if (wanted <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(Begin()), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(End()), wanted - count, category);
            }
            m_dirty = false;
            m_index = wanted;
        }
        else
        {
            int previous = m_index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(Iterator((_Nodeptr)((RHUnk0046eb30 *)this)->FUN_0046eb80().node)), wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(End()), wanted - count, category);
                }
                m_index = wanted;
            }
        }
    }
    void InsertLast(const RHTextChunk &value)
    {
        _Nodeptr head = _Head;
        _Nodeptr previous = head->_Prev;
        _Nodeptr node = (_Nodeptr)operator new(sizeof(_Node));
        node->_Next = head != 0 ? head : node;
        node->_Prev = previous != 0 ? previous : node;
        head->_Prev = node;
        node->_Prev->_Next = node;
        FUN_00625270(&node->_Value, value);
        ++_Size;
        m_dirty = true;
    }
    void Append(const RHTextChunk &value)
    {
        push_back(value);
        m_dirty = true;
    }
    RHTextChunk &At(int wanted)
    {
        GoTo(wanted);
        return m_current->_Value;
    }
    const char *TextAt(int wanted);

    _Nodeptr m_current; // 0x0c
    bool m_dirty; // 0x10
    int m_index; // 0x14
    bool m_searchValid; // 0x18
    int m_searchIndex; // 0x1c
    RHTextChunk m_searchValue; // 0x20
};

// SIZE 0xd8
class RHUnk00624a60
{
public:
    RHUnk00624a60();
    void *FUN_00624aa0(unsigned flags);
    ~RHUnk00624a60();
    void FUN_00624c40(const char *text, unsigned int &position, RHTextChunk *chunk);
    const char *FUN_00624ed0(unsigned short index);
    unsigned short FUN_006250d0(const char *text);

    unsigned char m_00[4]; // 0x00
    RHTextChunkList m_list; // 0x04
};

#endif
