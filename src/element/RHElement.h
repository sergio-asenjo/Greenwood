#include "SB.h"

class RHUnk005df510
{
public:
    int m_0;
    int m_4;
    int m_8;
    void Serialize(SBFile &file);
};

class SBGeoPoint2D
{
public:
    ~SBGeoPoint2D();
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    short CellX() const { return (short)((short)m_0 >> 6); }
    short CellY() const { return (short)((short)m_4 >> 6); }
    float m_0;
    float m_4;
    bool Serialize(SBFile &file);
};

class RHUnk005b5ed0
{
public:
    bool FUN_005b5ed0(SBFile &file);
};

class RHElevationLine;

class RHElement
{
public:
    virtual bool Serialize(SBFile &file);
    void CrossElevationLine(RHElevationLine *line);
    void Emit(SBFile &file);

    char m_04[4];
    char m_08;
    char m_09[3];
    int m_0c;
    short m_10;
    char m_12;
    char m_13[0x3d];
    RHUnk005b5ed0 *m_50;
    char m_54[0x1c];
    char m_70;
    char m_71;
    char m_72[2];
    RHUnk005df510 m_74;
    SBGeoPoint2D m_80;
    char m_88;
    char m_89;
    short m_8a;
    short m_8c;
    char m_8e[6];
    char m_94[10];
    char m_9e[2];
    int m_a0;
    short m_a4;
    char m_a6;
    char m_a7;
};

void RHSerializeName(SBFile &file, const char *name);

class RHBonusInfoBase
{
public:
    void FUN_0055f290();
    void FUN_0055fa70(void *area);
};

class SBGeoBoundingBox2D
{
public:
    bool FUN_00608400(const SBGeoPoint2D &point) const;
};

class RHElementAreaShape
{
public:
    bool FUN_0060c660(const SBGeoPoint2D &point) const;
};

class RHElementArea
{
public:
    char m_00[4];
    RHElementAreaShape m_04;
    char m_05[0x37];
    SBGeoBoundingBox2D m_3c;
    char m_3d[0x1b];
    char *m_58;
};

class RHElevationLine
{
public:
    char m_00[4];
    float m_04;
    float m_08;
    float m_0c;
    float m_10;
    char m_14[0xc];
    short m_20;
    unsigned short m_22;
    void *m_24;
    void *m_28;
};

struct RHElementAreaNode
{
    RHElementAreaNode *next;
    RHElementAreaNode *prev;
    RHElementArea *data;
};

struct RHElementAreaIter
{
    RHElementAreaNode *node;
    RHElementAreaIter(RHElementAreaNode *value) : node(value) {}
};

class RHElementAreaListBase
{
public:
    RHElementAreaListBase(const char &allocator);
    ~RHElementAreaListBase();
    void Clear();
    RHElementAreaIter begin();
    RHElementAreaIter erase(RHElementAreaIter first, RHElementAreaIter last);
    char m_00[4];
    RHElementAreaNode *m_04;
    unsigned m_08;
};

class RHElementAreaList : public RHElementAreaListBase
{
public:
    RHElementAreaList(const char &allocator) : RHElementAreaListBase(allocator) { m_10 = true; }
    ~RHElementAreaList()
    {
        erase(begin(), RHElementAreaIter(m_04));
    }
    void GoTo(int index);
    RHElementAreaNode *m_0c;
    bool m_10;
    char m_11[3];
    int m_14;
};

class RHUnk0040f060 : public RHElementAreaListBase
{
public:
    RHUnk0040f060();
    ~RHUnk0040f060() { Clear(); }
    void GoTo(int index);
    RHElementAreaNode *m_0c;
    bool m_10;
    char m_11[3];
    int m_14;
    char m_18[0xc];
};

class RHElementGrid
{
public:
    void FUN_004e89d0(void *list, int cell, unsigned mask);
    char m_00[0x3e98];
    unsigned short m_3e98;
};

SBGeoPoint2D FUN_005fc4f0(float factor, const SBGeoPoint2D &point);
