#ifndef RHSECTOR_H
#define RHSECTOR_H

#include "SB.h"
#include "Decomp.h"
#include <string.h>
#include <vector>
#include <string>

void RHSerializeName(SBFile &file, const char *name);
class RHMissionArrayStorage;
class SBGeoBoundingBox2D;
class SBGeoVector2D;

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    float m_x;
    float m_y;
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    bool Serialize(SBFile &file);
};
#endif

#include "RHSectorCore.h"

#include "RHSectorArchery.h"

#include "RHUnkSectorGlobal.h"

// VTABLE: GAME 0x00679140
// SIZE 0x1c
class RHUnk00522540 : public SBGeoPoint2D
{
public:
    RHUnk00522540();
    virtual ~RHUnk00522540(); // vtable+0x00
    void Unk005225a0(SBFile &file);
    bool FUN_00522680(SBFile &file);
    undefined2 m_c; // 0x0c
    undefined2 m_e; // 0x0e
    void *m_10; // 0x10
    undefined m_14; // 0x14
    undefined m_15; // 0x15
    undefined2 m_16; // 0x16
    void *m_18; // 0x18
};

// SIZE 0x2c
#include "RHUnkSectorPoints.h"
#include "RHUnk00613e90.h"

#include "RHUnkSectorScript.h"

extern char g_unk0x6c0691;

struct RHUnkSectorPosition
{
    char m_pad0[0x24];
    float m_24; // [0x24]
    float m_28; // [0x28]
};

enum RHUnkSectorActorType
{
    RHUnkSectorType0,
    RHUnkSectorType12 = 12
};

class RHElementActor
{
public:
    unsigned short FUN_004626e0() const;
    char m_pad0[4];
    unsigned int m_4; // [0x04]
    char m_pad8[0x48];
    RHUnkSectorPosition *m_50; // [0x50]
    char m_pad54[0x578];
    RHElementActor *m_5cc; // [0x5cc]
    char m_pad5d0[0x20];
    int m_5f0; // [0x5f0]

    RHUnkSectorActorType UnkType() const { return (RHUnkSectorActorType)(m_4 & 0xf); }
};

#include "RHSectorBuilding.h"
#include "RHSectorActorList.h"

#include "RHSectorScript.h"

extern RHElementActor *g_unk0x6c100c;

class RHSectorGateCalls
{
public:
    void FUN_0057dea0(RHElementActor *actor, bool mode);
    bool FUN_0057deb0(RHElementActor *actor, bool mode);
    undefined m_00[0xb4];
    bool m_b4;
};

#include "RHSectorLift.h"

class RHUnk005f5440
{
public:
    int Unk();
};

// VTABLE: GAME 0x00679c24
// SIZE 0x5c
class RHUnk0057d440 : public RHSector
{
public:
    RHUnk0057d440();
    virtual ~RHUnk0057d440();
    RHSectorLift *m_58; // [0x58]
};

// VTABLE: GAME 0x00679c04
// SIZE 0x5c
class RHUnk0057d3a0 : public RHSector
{
public:
    RHUnk0057d3a0();
    virtual ~RHUnk0057d3a0();
};

// VTABLE: GAME 0x00679c14
// SIZE 0x5c
class RHUnk0057d3f0 : public RHSector
{
public:
    RHUnk0057d3f0();
    virtual ~RHUnk0057d3f0();
};

// VTABLE: GAME 0x00679c6c
// SIZE 0x5c
class RHUnk0057ed80 : public RHSector
{
public:
    RHUnk0057ed80();
    virtual ~RHUnk0057ed80();
};

// VTABLE: GAME 0x00679c8c
// SIZE 0x70
class RHUnk0057ee90 : public RHSector
{
public:
    RHUnk0057ee90();
    virtual ~RHUnk0057ee90();
    int m_58;           // 0x58
    SBGeoPoint2D m_5c;  // 0x5c
    RHUnk00613e90 m_64; // 0x64
};

#include "RHGate.h"

class RHSectorLiftArray : public std::vector<RHUnk0051aa00 *>
{
public:
    // [0x00] allocator; [0x04] _First; [0x08] _Last; [0x0c] _End.
    char m_pad10[4];
    char m_dirty; // [0x14]
    char m_pad15[3];
    void InsertLast(RHUnk0051aa00 *value)
    {
        insert(end(), 1, value);
        m_dirty = 1;
    }
};

class RHUnkSectorLiftGrid
{
public:
    char m_pad0[0x4080];
    RHSectorLiftArray m_4080; // [0x4080]
};

// SIZE 0x35
class RHSectorDoor
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    char m_pad0[0x34];
    char m_34; // [0x34]
};

#endif
