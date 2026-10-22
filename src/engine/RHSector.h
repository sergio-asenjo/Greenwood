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

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    float m_x;
    float m_y;
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    bool Serialize(SBFile &file);
};
#endif

#include "RHUnk0060c2c0.h"
#include "SBGeoBoundingBox2DCore.h"

// VTABLE: GAME 0x00679bf4
// SIZE 0x58
class RHSector : public RHUnk0060c2c0
{
public:
    RHSector();
    RHSector(int type);
    ~RHSector();
    void *FUN_0057caf0(unsigned flags);
    virtual void UnkV0(); // vtable+0x00
    int Unk0057cd60(SBFile &file, bool mode);
    void FUN_0057d390(void *draw, unsigned long surface, const SBGeoBoundingBox2D &box, float scale, unsigned short layer);
    void DisplayAlpha(unsigned long color, unsigned long alpha, bool mode);
    int m_30; // 0x30
    bool m_34;
    unsigned short m_36;
    unsigned short m_38;
    SBGeoBoundingBox2D m_3c;
    undefined m_50[8];
};

template <class T>
class RHSectorArrayStorage : public std::vector<T>
{
public:
    ~RHSectorArrayStorage() { clear(); }
};

template <class T>
class RHSectorArray : public RHSectorArrayStorage<T>
{
public:
    RHSectorArray() { m_dirty = 1; }
    ~RHSectorArray()
    {
        int count = size();
        for (int i = 0; i < count; ++i)
        {
            if ((*this)[i] != 0)
                delete (*this)[i];
        }
        erase(begin(), end());
    }
    char m_pad10[4];
    char m_dirty; // [0x14]
    char m_pad15[3];
    void Resize(unsigned int count, const T &value = T())
    {
        if (size() < count)
            insert(end(), count - size(), value);
        else if (count < size())
            ((RHMissionArrayStorage *)this)->FUN_004609a0(begin() + count, end());
        m_dirty = 1;
    }
};

class RHUnk00522540;

// VTABLE: GAME 0x00679c9c
// SIZE 0x84
class RHSectorArchery : public RHSector
{
public:
    RHSectorArchery();
    virtual ~RHSectorArchery();
    void InitializeFromMissionStream(SBFile &file);
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    RHSectorArray<RHUnk00522540 *> m_58; // [0x58]
    char m_pad70[8];
    void *m_78; // [0x78]
    unsigned short m_7c; // [0x7c]
    unsigned short m_7e; // [0x7e]
    unsigned short m_80; // [0x80]
    unsigned short m_82; // 0x82
};

struct RHUnkSectorGlobal
{
    char m_pad0[0x4064];
    void **m_4064; // [0x4064]
    char m_pad4068[0x11c];
    void *m_4184; // [0x4184]
};

extern RHUnkSectorGlobal *g_unk0x6c0a9c;

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

extern float g_unk0x679cc4;
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

// SIZE 0x108
class RHSectorLift
{
public:
    int FUN_0057dcf0(int animation);
    int FUN_0057dd90(int animation);
    bool FUN_0057de30(RHElementActor *actor);
    bool FUN_0057dec0();
    bool FUN_0057def0();
    int Unk0057e060(SBFile &file, class RHUnkSectorLiftGrid *grid);
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    void Emit(SBFile &file, class RHUnkSectorLiftGrid *grid);

    char m_pad0[0xf0];
    int m_f0; // [0xf0]
    short m_f4; // [0xf4]
    short m_f6; // [0xf6]
    char m_f8; // [0xf8]
    char m_f9; // [0xf9]
    short m_fa; // [0xfa]
    int m_fc; // [0xfc]
    class RHUnk0051aa00 *m_100; // [0x100]
    class RHUnk0051aa00 *m_104; // [0x104]
};

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
    virtual void UnkV0(); // vtable+0x00
    virtual void UnkV4(SBFile &file, bool mode); // vtable+0x04
    virtual void UnkV8(); // vtable+0x08
    virtual void UnkVc(); // vtable+0x0c
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

class RHUnk0057dc80
{
public:
    void *FUN_0057dcc0(unsigned flags);
    RHUnk0057dc80();
    ~RHUnk0057dc80();
    void FUN_0057d490();
    char m_00[0x30];
    int m_30;
    char m_34[0xc0];
    unsigned short m_f4;
    unsigned short m_f6;
    char m_f8;
    char m_f9;
    char m_fa[2];
    int m_fc;
};

class RHUnk0051aa00
{
public:
    RHUnk0051aa00();
    ~RHUnk0051aa00();
    void Unk0051b2a0(SBFile &file, RHSectorBuilding *building);
    char m_pad0[0x1c];
    float m_1c; // [0x1c]
    char m_pad20[0x9c];
};

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
