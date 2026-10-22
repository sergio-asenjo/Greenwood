#ifndef RHELEMENTACTORANIMAL_H
#define RHELEMENTACTORANIMAL_H

#include "SB.h"
#include "Decomp.h"

// SIZE 0x08
class SBGeoVector2D;
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &point) const;
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &point) const;
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &point) const;
    float m_x; // 0x00
    float m_y; // 0x04
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float x, float y);
    ~SBGeoVector2D() {}
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
    SBGeoVector2D(const SBGeoVector2D &other);
};

class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    RHUnk005fc3b0() {}
    ~RHUnk005fc3b0() {}
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other)
    {
        return (RHUnk005fc3b0 &)SBGeoVector2D::operator=((const SBGeoVector2D &)other);
    }
    RHUnk005fc3b0 &FUN_005fc4d0(float factor);
    float Unk005fc6a0(float value);
    void FUN_005fc7c0(float length);
    RHUnk005fc3b0 &Unk005fcd40(unsigned char direction, float length);
};

// SIZE 0x08


// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    SBGeoBoundingBox2D &FUN_00607da0(const SBGeoBoundingBox2D &other);
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    SBGeoPoint2D FUN_00608f40() const;
    SBGeoPoint2D m_p0; // 0x00
    SBGeoPoint2D m_p1; // 0x08
    bool m_flag; // 0x10
    undefined m_11[3]; // 0x11
};

// SIZE 0x8c
class RHUnkPathActorInfoBase
{
public:
    void *Unk0055fa10(int index);
    undefined m_00[0x88]; // 0x00
    int m_88; // 0x88
};

class RHUnk005b5e00
{
public:
    void *Unk();
};

// SIZE 0x16
class RHAnimalConversionEntry
{
public:
    undefined m_00[0x14]; // 0x00
    unsigned short m_14; // 0x14
};

// SIZE 0x08
class RHAnimalConversion
{
public:
    undefined m_00[0x4]; // 0x00
    RHAnimalConversionEntry *m_4; // 0x04
};

// SIZE 0xe4
class RHAnimalSprite
{
public:
    RHUnkPathActorInfoBase *Position() { return (RHUnkPathActorInfoBase *)((char *)this + 4); }
    undefined m_00[0x18]; // 0x00
    float m_18; // 0x18
    undefined m_1c[0x8]; // 0x1c
    SBGeoPoint2D m_24; // 0x24
    undefined m_2c[0xac]; // 0x2c
    unsigned short m_d8; // 0xd8
    undefined m_da[0x4]; // 0xda
    unsigned short m_de; // 0xde
    int m_e0; // 0xe0
};

// SIZE 0x10
struct RHAnimalNoisePosition
{
    float m_x; // 0x00
    float m_y; // 0x04
    int m_8; // 0x08
    unsigned short m_c; // 0x0c
};

class RHElementActorNPC
{
public:
    static void Noise(int type, RHAnimalNoisePosition &position, float radius, void *source);
};

class RHScriptBatchCalls
{
public:
    void *Unk0058a940(void *context, int value, void *element);
};

// SIZE 0x9c
class RHUnk00588530
{
public:
    RHUnk00588530(unsigned short priority, int command, void *element, int animation,
                  const SBGeoPoint2D &destination, void *target, float speed, unsigned long flags);
    undefined m_00[0x9c]; // 0x00
};

class RHUnkPathGeometry
{
public:
    bool Unk004f9170(const SBGeoPoint2D &a, const SBGeoPoint2D &b, unsigned short layer, void *radius);
};

struct RHUnkSectorGlobal;

// SIZE 0x4738
class RHEngine
{
public:
    undefined m_00[0x4730]; // 0x00
    float m_4730; // 0x4730
    float m_4734; // 0x4734
};

enum RHanimalStimulusType
{
};

// SIZE 0x220
class RHElementActorAnimal
{
public:
    void Think(RHanimalStimulusType stimulus);
    bool GoTo(const SBGeoPoint2D &destination, unsigned short flags);
    void WalkSomewhere();
    void Startle();
    void GetRestless();
    void Flee(bool run);
    void *GetNearestSeekPoint(unsigned short layer);
    void ThisIsYourNewHome();

    static unsigned short marrWalkDistance[9];
    static unsigned short marrWaitTime[9];
    static unsigned short marrMaxTurnAngle[9];
    static unsigned short marrRunProbability[9];
    static unsigned short marrTerritoryEdgeLength[9];
    static unsigned short marrStartleBoxEdgeLength[9];
    static unsigned short marrRestlessBoxEdgeLength[9];

    undefined m_00[0x50]; // 0x00
    RHAnimalSprite *m_50; // 0x50
    undefined m_54[0x8]; // 0x54
    RHScriptBatchCalls *m_5c; // 0x5c
    undefined m_60[0x158]; // 0x60
    unsigned short m_1b8; // 0x1b8
    undefined m_1ba[0x2]; // 0x1ba
    int m_1bc; // 0x1bc
    undefined m_1c0[0x5]; // 0x1c0
    char m_1c5; // 0x1c5
    undefined m_1c6[0x2]; // 0x1c6
    SBGeoPoint2D m_1c8; // 0x1c8
    int m_1d0; // 0x1d0
    int m_1d4; // 0x1d4
    undefined m_1d8[0x2]; // 0x1d8
    unsigned short m_1da; // 0x1da
    unsigned short m_1dc; // 0x1dc
    undefined m_1de[0x2]; // 0x1de
    SBGeoBoundingBox2D m_1e0; // 0x1e0
    undefined m_1f4[0x28]; // 0x1f4
    char m_21c; // 0x21c
    undefined m_21d[0x3]; // 0x21d
};

extern float g_unk0x00677488;
extern RHEngine *g_pEngine;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
extern char g_unk0x6c0560[4];

#endif
