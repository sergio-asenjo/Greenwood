#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "SB.h"
#include "MD5.h"
#include "Decomp.h"
#include <string>
#include <deque>
#include <list>
#include <iterator>

// SIZE 0x08
struct ToolboxChunk
{
    unsigned long m_start; // +0x00
    unsigned long m_size; // +0x04
};

template <class T>
struct ToolboxDequeIterator
{
    ToolboxDequeIterator(T *, T **);
    T *m_first;
    T *m_last;
    T *m_next;
    T **m_map;
};

typedef ToolboxDequeIterator<ToolboxChunk> ToolboxChunkIterator;

class ToolboxChunks : public std::deque<ToolboxChunk>
{
public:
    void FUN_005e3070();
    void Buyback()
    {
        ToolboxChunk *block = (ToolboxChunk *)operator new(4096);
        if (empty())
        {
            _Mapsize = 2;
            _Map = (ToolboxChunk **)operator new(8);
            _Map[1] = block;
            ToolboxChunkIterator cursor(block + 256, _Map + 1);
            *(ToolboxChunkIterator *)&_First = cursor;
            _Last = _First;
        }
        else if (_Last._Map < *(_Tptr *volatile *)&_Map + (_Mapsize - 1))
        {
            *++_Last._Map = block;
            ToolboxChunkIterator cursor(block, _Last._Map);
            *(ToolboxChunkIterator *)&_Last = cursor;
        }
        else
        {
            int count = _Last._Map - _First._Map + 1;
            typedef std::deque<ToolboxChunk> Chunks;
            ToolboxChunk **(Chunks::*grow)(unsigned int) = &ToolboxChunks::_Growmap;
            ToolboxChunk **map = (this->*grow)(2 * count);
            map[count] = block;
            ToolboxChunkIterator cursor(_First._Next, map);
            *(ToolboxChunkIterator *)&_First = cursor;
            _Last = iterator(block, map + count);
        }
    }
    void Append(const ToolboxChunk &value)
    {
        if (empty() || _Last._Next == _Last._Last)
        {
            Buyback();
            Construct(_Last._Next++, value);
        }
        else if (_Last._Next + 1 == _Last._Last)
        {
            Construct(_Last._Next++, value);
            FUN_005e3070();
        }
        else
            Construct(_Last._Next++, value);
        ++_Size;
    }
    static void Construct(ToolboxChunk *destination, const ToolboxChunk &value)
    {
        if (destination)
            *destination = value;
    }
};

// SIZE 0x10
class RHProfileText
{
public:
    explicit RHProfileText(const char *value, const std::allocator<char> &allocator = std::allocator<char>())
    {
        m_allocator = *(const char *)&allocator;
        FUN_00401ee0(false);
        unsigned int size = strlen(value);
        if (FUN_00402280(size, true))
        {
            memcpy(m_chars, value, size);
            m_size = size;
            m_chars[size] = 0;
        }
    }
    ~RHProfileText() { FUN_00401ee0(true); }
    bool FUN_00402280(unsigned int, bool);
    void FUN_00401ee0(bool);
    char m_allocator; // +0x00
    char *m_chars; // +0x04
    unsigned int m_size; // +0x08
    unsigned int m_capacity; // +0x0c
};

// SIZE 0x10
class RHUnk00423b10
{
public:
    void FUN_00423b10(unsigned int);
    undefined m_allocator; // 0x00
    unsigned short *m_chars; // 0x04
    unsigned int m_size; // 0x08
    unsigned int m_capacity; // 0x0c
};

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D(float, float);
    ~SBGeoPoint2D();
    float m_x; // 0x00
    float m_y; // 0x04
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

#include "SBDrawManagerCore.h"
#include "SBDrawViewport.h"

// SIZE 0x10e
class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int, int, int, bool);
    void Unk005e5160(unsigned long);
    void FUN_005e5260();
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
    void FUN_005e6440(unsigned long, int, int, unsigned long, unsigned long);
    unsigned short UnkField10c() const { return m_depth; }
    undefined m_00[0x10c]; // 0x00
    unsigned short m_depth; // +0x10c
};

#include "RHUnk006114c0.h"

#include "RHUnk005f4fc0.h"

#include "SBFilePosition.h"
class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

#include "ToolboxMouseState.h"

unsigned long FUN_005f0ce0();
bool FUN_005f1150(ToolboxMouseState &, unsigned char *);
bool FUN_005e17a0(unsigned char *);
void FUN_005e1380();
void FUN_005e1400();

#include "ToolboxWideString.h"

namespace Toolbox
{
    MD5 *MD5_string(MD5 *, unsigned char *);
    unsigned long HexaAsciiToInteger(const char *);
    void DisplayPicture(const char *, bool);
    void PlaySlide(const std::string &, unsigned short);
    void HSV_To_RGB(float h, float s, float v, float &r, float &g, float &b);
    void Emit();
}

void RHSerializeName(SBFile &, const char *);
void FUN_005e1d50(SBFile &, unsigned long, int);
void FUN_005e20c0(SBFile &);
void FUN_005e3730(const unsigned short *, unsigned short *, long, unsigned long, unsigned long, unsigned long);
void FUN_005e37c0(const unsigned short *, unsigned short *, long, unsigned long, unsigned long, unsigned long, unsigned long);
void FUN_005e3869(const unsigned short *, unsigned short *, long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
void FUN_005e3919(const unsigned short *, unsigned short *, long, unsigned long, unsigned long, unsigned long, unsigned long);

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

// SIZE 0x18
class RHTextChunkList : public std::list<RHTextChunk>
{
public:
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
    RHTextChunk &At(int wanted)
    {
        GoTo(wanted);
        return m_current->_Value;
    }

    _Nodeptr m_current; // 0x0c
    bool m_dirty; // 0x10
    int m_index; // 0x14
};

class RHUnk00624a60
{
public:
    RHUnk00624a60();
    void *FUN_00624aa0(unsigned flags);
    ~RHUnk00624a60();
    void FUN_00624c40(const char *text, unsigned int &position, RHTextChunk *chunk);
    const char *FUN_00624ed0(unsigned short index);
    unsigned short FUN_006250d0(const char *text);

    undefined m_00[4]; // 0x00
    RHTextChunkList m_list; // 0x04
};


#endif
