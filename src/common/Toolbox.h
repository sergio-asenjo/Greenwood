#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "SB.h"
#include "MD5.h"
#include "Decomp.h"
#include <string>
#include <deque>
#include <list>
#include <iterator>
#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"

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
    explicit ToolboxChunks(const std::allocator<ToolboxChunk> &allocation = std::allocator<ToolboxChunk>());
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

#include "SBDrawManagerCore.h"
#include "SBDrawViewport.h"

// SIZE 0x10e
class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(unsigned short, unsigned short, unsigned long, bool);
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
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

#include "RHTextChunk.h"


#endif
