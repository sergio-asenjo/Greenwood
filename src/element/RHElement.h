#include "SB.h"
#include "Decomp.h"

// SIZE 0x0c
class RHUnk005df510
{
public:
    int m_0; // 0x00
    int m_4; // 0x04
    int m_8; // 0x08
    bool Serialize(SBFile &file);
};

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    short CellX() const { return (short)((short)m_0 >> 6); }
    short CellY() const { return (short)((short)m_4 >> 6); }
    float m_0; // 0x00
    float m_4; // 0x04
    bool Serialize(SBFile &file);
};

class RHUnk005b5ed0
{
public:
    bool FUN_005b5ed0(SBFile &file);
};

class RHElevationLine;

// SIZE 0xa8
class RHElement
{
public:
    virtual bool Serialize(SBFile &file); // vtable+0x00
    int FUN_00462190() const;
    void FUN_004621d0(RHUnk005df510 &point) const;
    void FUN_004621f0();
    char FUN_00462200() const;
    char FUN_00462210(void *value);
    void *FUN_004622d0() const;
    void CrossElevationLine(RHElevationLine *line);
    void Emit(SBFile &file);

    undefined m_04[4]; // 0x04
    char m_08; // 0x08
    undefined m_09[3]; // 0x09
    int m_0c; // 0x0c
    short m_10; // 0x10
    char m_12; // 0x12
    undefined m_13[0x3d]; // 0x13
    RHUnk005b5ed0 *m_50; // 0x50
    undefined m_54[0x1c]; // 0x54
    char m_70; // 0x70
    char m_71; // 0x71
    undefined m_72[2]; // 0x72
    RHUnk005df510 m_74; // 0x74
    SBGeoPoint2D m_80; // 0x80
    char m_88; // 0x88
    undefined m_89; // 0x89
    short m_8a; // 0x8a
    short m_8c; // 0x8c
    undefined m_8e[6]; // 0x8e
    undefined m_94[10]; // 0x94
    undefined m_9e[2]; // 0x9e
    int m_a0; // 0xa0
    short m_a4; // 0xa4
    char m_a6; // 0xa6
    undefined m_a7; // 0xa7
};

void RHSerializeName(SBFile &file, const char *name);

// SIZE 0xfc
class RHBonusInfoBase
{
public:
    void FUN_0055f290();
    void FUN_0055fa70(void *area);
    undefined m_00[4]; // 0x00
    undefined4 m_04; // 0x04
    undefined4 m_08; // 0x08
    undefined m_0c[0x14]; // 0x0c
    SBGeoPoint2D m_20; // 0x20
    undefined m_28[0xb2]; // 0x28
    undefined2 m_da; // 0xda
    undefined m_dc[0x0c]; // 0xdc
    void *m_e8; // 0xe8
    void *m_ec; // 0xec
    undefined m_f0[8]; // 0xf0
    void *m_f8; // 0xf8
};

class SBGeoBoundingBox2D
{
public:
    bool FUN_00608400(const SBGeoPoint2D &point) const;
};

class RHUnkSectorPoints
{
public:
    SBGeoPoint2D &Unk0060cef0(unsigned index);
};

class RHElementAreaShape
{
public:
    bool FUN_0060c660(const SBGeoPoint2D &point) const;
    unsigned FUN_0060ce80() const;
    const SBGeoPoint2D &FUN_0060cef0(unsigned index) const
    {
        return ((RHUnkSectorPoints *)this)->Unk0060cef0(index);
    }
    undefined m_00[0x24]; // 0x00
    undefined2 m_24; // 0x24
};

class RHElementArea
{
public:
    undefined m_00[4]; // 0x00
    RHElementAreaShape m_04; // 0x04
    undefined m_2a[0x12]; // 0x2a
    SBGeoBoundingBox2D m_3c; // 0x3c
    undefined m_3d[0x1b]; // 0x3d
    char *m_58; // 0x58
    undefined m_5c[4]; // 0x5c
    void *m_60; // 0x60
};

// SIZE 0x2c
class RHElevationLine
{
public:
    undefined m_00[4]; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    float m_0c; // 0x0c
    float m_10; // 0x10
    undefined m_14[0xc]; // 0x14
    short m_20; // 0x20
    unsigned short m_22; // 0x22
    void *m_24; // 0x24
    void *m_28; // 0x28
};

// SIZE 0x0c
struct RHElementAreaNode
{
    RHElementAreaNode(RHElementAreaNode *nextNode, RHElementAreaNode *previousNode)
        : next(nextNode ? nextNode : this), prev(previousNode ? previousNode : this) {}
    RHElementAreaNode *next; // 0x00
    RHElementAreaNode *prev; // 0x04
    RHElementArea *data; // 0x08
};

// SIZE 0x04
struct RHElementAreaIter
{
    RHElementAreaNode *node; // 0x00
    RHElementAreaIter(RHElementAreaNode *value) : node(value) {}
};

// SIZE 0x0c
class RHElementAreaListBase
{
public:
    RHElementAreaListBase(const char &allocator);
    ~RHElementAreaListBase();
    void Clear();
    RHElementAreaIter begin();
    RHElementAreaIter erase(RHElementAreaIter first, RHElementAreaIter last);
    undefined m_00[4]; // 0x00
    RHElementAreaNode *m_04; // 0x04
    unsigned m_08; // 0x08
};

// SIZE 0x18
class RHElementAreaList : public RHElementAreaListBase
{
public:
    RHElementAreaList(const char &allocator) : RHElementAreaListBase(allocator) { m_10 = true; }
    ~RHElementAreaList()
    {
        erase(begin(), RHElementAreaIter(m_04));
    }
    void GoTo(int index);
    RHElementAreaNode *m_0c; // 0x0c
    bool m_10; // 0x10
    undefined m_11[3]; // 0x11
    int m_14; // 0x14
};

// SIZE 0x24
class RHUnk0040f060 : public RHElementAreaListBase
{
public:
    RHUnk0040f060();
    ~RHUnk0040f060() { Clear(); }
    void GoTo(int index);
    RHElementAreaNode *m_0c; // 0x0c
    bool m_10; // 0x10
    undefined m_11[3]; // 0x11
    int m_14; // 0x14
    undefined m_18[0xc]; // 0x18
};

class RHElementGrid
{
public:
    void FUN_004e89d0(void *list, int cell, unsigned mask);
    undefined m_00[0x3e98]; // 0x00
    unsigned short m_3e98; // 0x3e98
    unsigned short m_3e9a; // 0x3e9a
    undefined m_3e9c[0x1a0]; // 0x3e9c
    undefined *m_403c; // 0x403c
    undefined m_4040[0x148]; // 0x4040
    void *m_4188; // 0x4188
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    ~SBGeoVector2D() {}
};

SBGeoVector2D operator*(float factor, const SBGeoVector2D &point);
