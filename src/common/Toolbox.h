#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "SB.h"
#include <string>
#include <deque>

struct ToolboxChunk
{
    unsigned long m_start; // +0x00
    unsigned long m_size; // +0x04
};

struct ToolboxChunkIterator
{
    ToolboxChunkIterator(ToolboxChunk *, ToolboxChunk **);
    ToolboxChunk *m_first; // +0x00
    ToolboxChunk *m_last; // +0x04
    ToolboxChunk *m_next; // +0x08
    ToolboxChunk **m_map; // +0x0c
};

class ToolboxChunks : public std::deque<ToolboxChunk>
{
public:
    void FUN_005e3070();
    ToolboxChunk **FUN_005e31d0(unsigned int);
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
        else if (_Last._Map < _Map + (_Mapsize - 1))
        {
            *++_Last._Map = block;
            ToolboxChunkIterator cursor(block, _Last._Map);
            *(ToolboxChunkIterator *)&_Last = cursor;
        }
        else
        {
            int count = _Last._Map - _First._Map + 1;
            ToolboxChunk **map = FUN_005e31d0(2 * count);
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

class SBGeoPoint2D
{
public:
    SBGeoPoint2D(float, float);
    ~SBGeoPoint2D();
    float m_x;
    float m_y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
};

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int, int, int, int);
    void Unk005e5160(unsigned long);
    void FUN_005e5260();
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
    void FUN_005e61e0(unsigned long, unsigned long, unsigned long, unsigned long);
    void FUN_005e6440(unsigned long, int, int, unsigned long, unsigned long);
    unsigned short UnkField10c() const { return m_depth; }
    char m_00[0x10c];
    unsigned short m_depth; // +0x10c
};

class RHUnk006114c0
{
public:
    RHUnk006114c0();
    virtual ~RHUnk006114c0();
    virtual void Unk04();
    virtual void Unk08();
    virtual void Unk0c();
    virtual void Unk10();
    virtual void Unk14();
    virtual void Unk18();
    virtual void Unk1c();
    virtual bool Unk20(RHUnkFXDraw *, unsigned long);
    bool Unk00611710(SBFile &);
    bool Unk00611e10(unsigned long, unsigned long);
    RHUnk006114c0 *Unk00612ad0(const SBGeoPoint2D &, const SBGeoVector2D &);
    bool Unk00613530(RHUnkFXDraw *, unsigned long);
    unsigned short UnkField20() const { return m_width; }
    unsigned short UnkField22() const { return m_height; }
    char m_04[0x1c];
    unsigned short m_width; // +0x20
    unsigned short m_height; // +0x22
    char m_24[0x14]; // sizeof 0x38
};

class RHUnk005f4fc0 : public SBFile
{
public:
    RHUnk005f4fc0();
    ~RHUnk005f4fc0();
    int FUN_005f5090(const std::string &, int);
    int FUN_005f5090(const RHProfileText &, int);
    void FUN_005f5290();
    unsigned int Position() const { return *(const unsigned int *)((const char *)this + 0xc); }
    unsigned int Size() const { return *(const unsigned int *)((const char *)this + 8); }
    char m_14[0x44]; // sizeof 0x58
};

class RHUnk0060e4c0
{
public:
    void FUN_0060e4c0();
    bool FUN_0060f1c0(const RHUnk0060e4c0 &);
    void FUN_0060f1e0(SBFile &);
    char m_00[0x6c]; // sizeof 0x6c
};

RHUnk0060e4c0 *FUN_005e1b20(RHUnk0060e4c0 *, const char *);
class ToolboxPositionFile : public SBFile
{
public:
    unsigned long FUN_005f5440();
};
class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

struct ToolboxMouseState
{
    short m_x; // +0x00
    short m_y; // +0x02
    unsigned short m_flags; // +0x04
    unsigned short m_buttons; // +0x06
    unsigned short m_extra; // +0x08
};

unsigned long FUN_005f0ce0();
bool FUN_005f1150(ToolboxMouseState &, unsigned char *);
bool FUN_005e17a0(unsigned char *);
void FUN_005e1380();
void FUN_005e1400();

namespace Toolbox
{
    void DisplayPicture(const char *, bool);
    void PlaySlide(const std::string &, unsigned short);
    void Emit();
}

void RHSerializeName(SBFile &, const char *);
void FUN_005e1d50(SBFile &, unsigned long, int);
void FUN_005e20c0(SBFile &);

#endif
