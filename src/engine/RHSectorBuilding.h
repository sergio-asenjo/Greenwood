#ifndef RHSECTORBUILDING_H
#define RHSECTORBUILDING_H

#include <list>
#include "RHSectorActorIterator.h"
#include "RHSectorCore.h"
#include "RHMotionAreaList.h"

class RHElementActor;
class SBFile;
class SBGeoBoundingBox2D;
class RHUnkSectorLiftGrid;

// VTABLE: GAME 0x00679c34
class RHUnk0057d490 : public RHSector
{
public:
    RHUnk0057d490();
    virtual ~RHUnk0057d490();
    void FUN_0057d760(void *gate, bool side);
    virtual void FUN_0057d390(void *draw, unsigned long surface, const SBGeoBoundingBox2D &box, float scale, unsigned short layer);
    void Emit(void *gate, bool side);
    char m_58[4];
    RHMotionAreaList<void *> m_gates;
    RHMotionAreaList<bool> m_sides;
    RHMotionAreaList<void *> m_areas;
    RHMotionAreaList<void *> m_c8;
    bool m_ec;
    char m_ed[3];
};

class RHBuildingActorList : public std::list<RHElementActor *>
{
public:
    RHBuildingActorList() : m_dirty(true) {}
    ~RHBuildingActorList() { erase(begin(), end()); }
    iterator m_cursor;
    bool m_dirty;
    char m_11[3];
    int m_index;
    char m_18[0xc];
};

// VTABLE: GAME 0x00679c58
class RHSectorBuilding : public RHUnk0057d490
{
public:
    RHSectorBuilding();
    virtual ~RHSectorBuilding();
    virtual void FUN_0057d390(void *draw, unsigned long surface, const SBGeoBoundingBox2D &box, float scale, unsigned short layer);
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
    bool Serialize(SBFile &file);
    virtual int FUN_0057e710(SBFile &file, RHUnkSectorLiftGrid *grid);
    void Emit(SBFile &file);
    unsigned short m_f0;
    char m_f2[2];
    RHBuildingActorList m_occupants;
    unsigned char m_118;
    unsigned char m_pad119[3];
};

#endif
