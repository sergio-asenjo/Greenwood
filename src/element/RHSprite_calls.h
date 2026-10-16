#ifndef RHSPRITE_CALLS_H
#define RHSPRITE_CALLS_H

#include "SB.h"
#include "Decomp.h"
#include <iterator>

template<class T> T &RHSpriteField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    SBGeoPoint2D(const SBGeoPoint2D &);
    ~SBGeoPoint2D();
    bool Serialize(SBFile &file);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    SBGeoPoint2D &FUN_005fc1e0(const SBGeoPoint2D &);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &) const;
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &) const;
    float FUN_005fc700(float) const;
    bool operator==(const SBGeoPoint2D &) const;
    float m_x; // 0x00
    float m_y; // 0x04
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float, float);
    SBGeoVector2D(const SBGeoPoint2D &);
    ~SBGeoVector2D() {}
    float FUN_005fc660(const SBGeoPoint2D &) const;
};
SBGeoVector2D operator*(float, const SBGeoVector2D &);

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &);
    RHUnk005fc3b0 &FUN_005fc5b0(float factor);
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(const SBGeoPoint2D &, const SBGeoPoint2D &);
    ~SBGeoBoundingBox2D() {}
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &);
    bool FUN_00608400(const SBGeoPoint2D &) const;
    bool FUN_00609050(const SBGeoPoint2D &, const SBGeoPoint2D &);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &) const;
    bool Serialize(SBFile &);
    void FUN_00607d90();
    SBGeoPoint2D m_00; // 0x00
    SBGeoPoint2D m_08; // 0x08
    bool m_10; // 0x10
};

struct RHBonusProjection;
class RHBonusInfoBase
{
public:
    void FUN_0055f290();
    void FUN_0055fa20(RHBonusProjection *);
};
class RHBonusInfo
{
public:
    void FUN_005bd560(void *, bool);
};
class RHUnkPathActorInfoBase
{
public:
    void *Unk0055fa10(int);
};
class RHMobilePosition
{
public:
    void FUN_0055fc20(bool);
};
class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &, void *&);
};

class RHEngine;
struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
class RHSpriteEngineCalls
{
public:
    unsigned FUN_004d9090();
};

class RHSpritePositionCalls
{
public:
    SBGeoVector2D FUN_004a4a10();
    void FUN_0055f550();
    bool FUN_00560460();
    void FUN_00560780(float, unsigned short);
    bool FUN_00561040(void *, float, unsigned short &, bool);
    bool FUN_00563e90();
    void FUN_00563ea0();
};

// SIZE 0x0c
class RHUnk005df4f0
{
public:
    RHUnk005df4f0(float, float, float);
    float m_0; // 0x00
    float m_4; // 0x04
    float m_8; // 0x08
};

#include "RHUnkTargetSpriteCalls.h"

#include "RHFrameHolderCalls.h"

class RHEngineReinforcementCalls
{
public:
    bool FUN_004f6c20(const SBGeoPoint2D &, SBGeoPoint2D &, unsigned short, const SBGeoPoint2D &);
};

// SIZE 0x0c
class RHUnk00613e90
{
public:
    RHUnk00613e90();
    float m_0; // 0x00
    float m_4; // 0x04
    float m_8; // 0x08
};

// VTABLE: GAME 0x00679bc8
// SIZE 0x3c
class RHOrder
{
public:
    RHOrder(RHOrder &);
    virtual ~RHOrder(); // vtable+0x00
    undefined4 m_04; // 0x04
    RHUnk00613e90 m_08; // 0x08
    SBGeoPoint2D m_14; // 0x14
    SBGeoVector2D m_1c; // 0x1c
    int m_24; // 0x24
    undefined m_28; // 0x28
    undefined m_29; // 0x29
    undefined m_2a; // 0x2a
    undefined m_2b; // 0x2b
    undefined m_2c; // 0x2c
    undefined m_2d; // 0x2d
    undefined m_2e[2]; // 0x2e
    void *m_30; // 0x30
    int m_34; // 0x34
    void *m_38; // 0x38
};
struct RHSpriteOrderNode
{
    RHSpriteOrderNode *next;
    RHSpriteOrderNode *previous;
    RHOrder *value;
    static void CopyData(RHOrder **, RHOrder *const *);
};
struct RHSpriteOrderIterator
{
    RHSpriteOrderNode *node;
    RHSpriteOrderIterator(RHSpriteOrderNode *value) : node(value) {}
};
struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);
class RHSpriteOrderList
{
public:
    RHOrder *Value(unsigned short wanted)
    {
        int size = count;
        std::bidirectional_iterator_tag category;
        if (dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                current = FUN_0046eb80();
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
            }
            else
            {
                current = RHSpriteOrderIterator(head);
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - size, category);
            }
            dirty = false;
            index = wanted;
        }
        else if (wanted != index)
        {
            int previous = index;
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    current = FUN_0046eb80();
                    FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
                }
                else
                    FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - previous, category);
            }
            else if (wanted < (previous + size) / 2)
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - previous, category);
            else
            {
                current = RHSpriteOrderIterator(head);
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - size, category);
            }
            index = wanted;
        }
        return current.node->value;
    }
    void RemoveFirst()
    {
        RHOrder *order = Value(1);
        if (order)
            delete order;
        FUN_0046eb30(current);
        dirty = true;
    }
    RHSpriteOrderIterator FUN_0046eb80();
    RHSpriteOrderIterator FUN_0046eb30(RHSpriteOrderIterator);
    char m_00[4];
    RHSpriteOrderNode *head;
    unsigned count;
    RHSpriteOrderIterator current;
    bool dirty;
    int index;
};
class RHSpriteSequenceCalls
{
public:
    void FUN_005859e0(RHOrder *, unsigned short);
};

class RHScriptBatchCalls
{
public:
    void Unk005c2ec0(void *, int, int, void *, int, int, int, int);
};

extern float g_unk0x00677488;
extern float g_unk0x006774f4;
extern float g_unk0x006775d8;
class RHUnk005c38b0;
extern RHUnk005c38b0 *g_unk0x6c10e8;
double FUN_006433ab(double) throw();

#endif
