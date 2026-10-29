#ifndef RHGATE_H
#define RHGATE_H

#include "SB.h"
#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include <list>
#include "RHMotionAreaList.h"

class RHElementActor;
class RHFastFindSector;
class RHSectorBuilding;
class RHUnk0051e1e0;
class RHMission;
class RHUnk0051a5e0;

struct RHGateLink
{
    RHUnk0051a5e0 *first;
    RHUnk0051a5e0 *second;
    RHFastFindSector *sector;
    float distance;
};

class RHFastFindCursorList : public RHMotionAreaListStorage<RHGateLink *>
{
public:
    RHFastFindCursorList() : m_dirty(true) {}
    void InsertLast(RHGateLink *const &value)
    {
        iterator (std::list<RHGateLink *>::*insertValue)(iterator, RHGateLink *const &) = &std::list<RHGateLink *>::insert;
        (this->*insertValue)(end(), value);
        m_dirty = true;
    }
    void Append(RHGateLink *value)
    {
        void (std::list<RHMission *>::*appendValue)(RHMission *const &) = &std::list<RHMission *>::push_back;
        (((std::list<RHMission *> *)this)->*appendValue)((RHMission *const &)value);
        m_dirty = true;
    }
    void InsertValue(RHGateLink *value) { InsertLast(value); }
    iterator m_cursor;
    bool m_dirty;
    int m_index;
};

// VTABLE: GAME 0x0067909c
// SIZE 0x88
class RHUnk0051a5e0
{
public:
    RHUnk0051a5e0();
    virtual bool FUN_0051abe0(bool, RHElementActor *, bool, bool, bool);
    virtual bool Serialize(SBFile &file);
    void Link(RHUnk0051a5e0 *other);
    RHFastFindSector *FirstSector() const { return m_10; }
    RHFastFindSector *SecondSector() const { return m_0c; }
    unsigned char m_04[8];
    RHFastFindSector *m_0c;
    RHFastFindSector *m_10;
    unsigned short m_14;
    short m_16;
    SBGeoPoint2D m_18;
    SBGeoPoint2D m_20;
    unsigned char m_28[4];
    RHFastFindCursorList m_2c;
    unsigned char m_44[0xc];
    RHFastFindCursorList m_50;
    unsigned char m_68[0x20];
};

// VTABLE: GAME 0x006790a4
// SIZE 0xbc
class RHUnk0051aa00 : public RHUnk0051a5e0
{
public:
    RHUnk0051aa00();
    ~RHUnk0051aa00();
    virtual bool FUN_0051abe0(bool, RHElementActor *, bool, bool, bool);
    virtual bool Serialize(SBFile &file);
    void Unk0051b2a0(SBFile &file, RHSectorBuilding *building);
    void AdaptPoints();
    int m_88;
    unsigned char m_8c[8];
    SBGeoPoint2D m_94;
    int m_9c;
    int m_a0;
    int m_a4;
    int m_a8;
    unsigned char m_ac[4];
    int m_b0;
    unsigned char m_b4[8];
};

// VTABLE: GAME 0x006790ac
// SIZE 0x90
class RHUnk0051b6e0 : public RHUnk0051a5e0
{
public:
    RHUnk0051b6e0(RHUnk0051e1e0 *first, RHUnk0051e1e0 *second);
    ~RHUnk0051b6e0();
    virtual bool FUN_0051abe0(bool, RHElementActor *, bool, bool, bool);
    RHUnk0051e1e0 *m_88;
    RHUnk0051e1e0 *m_8c;
};

void RHSerializeName(SBFile &file, const char *name);

#endif
