#ifndef RHSPRITE_CALLS_H
#define RHSPRITE_CALLS_H

#include "SB.h"
#include "Decomp.h"
#include <iterator>

template<class T> T &RHSpriteField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
// SIZE 0x08
class SBGeoVector2D;
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    SBGeoPoint2D(const SBGeoPoint2D &);
    ~SBGeoPoint2D();
    bool Serialize(SBFile &file);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    void FUN_005fc390(const SBGeoPoint2D &other) throw();
    SBGeoPoint2D &FUN_005fc1e0(const SBGeoPoint2D &);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &) const;
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &) const;
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &) const;
    float FUN_005fc700(float) const;
    float FUN_005fca90(const SBGeoPoint2D &other, float scale) const;
    bool operator==(const SBGeoPoint2D &) const;
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float m_x; // 0x00
    float m_y; // 0x04
};
#endif

#include "SBGeoVector2D.h"

#define RHUNK005FC3B0_VIEW
class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other)
    {
        return (RHUnk005fc3b0 &)SBGeoVector2D::operator=((const SBGeoVector2D &)other);
    }
    RHUnk005fc3b0 &FUN_005fc5b0(float factor);
    bool IsZero() const { return m_x == 0.0f && m_y == 0.0f; }
    void FUN_005fc7c0(float scale);
    float Unk005fc6a0(float scale);
    unsigned char FUN_005fcc50(float scale) const;
    SBGeoVector2D FUN_005fc8f0(bool direction, float scale) const;
    RHUnk005fc3b0 FUN_005fc9e0(float angle, float scale);
    float FUN_005fc680(const RHUnk005fc3b0 &other, float scale) const;
};

#define SBGEO_BOUNDINGBOX2D_VIEW
// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(const SBGeoPoint2D &, const SBGeoPoint2D &);
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &);
    ~SBGeoBoundingBox2D() {}
    void Unk00607dc0(const SBGeoPoint2D &);
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &);
    bool FUN_00608400(const SBGeoPoint2D &) const;
    int FUN_00609050(const SBGeoPoint2D &, const SBGeoPoint2D &);
    bool Unk00608f30() const;
    bool FUN_006090a0() const;
    SBGeoBoundingBox2D FUN_006092c0(const SBGeoBoundingBox2D &) const;
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &) const;
    bool Serialize(SBFile &);
    void FUN_00607d90();
    SBGeoPoint2D m_00; // 0x00
    SBGeoPoint2D m_08; // 0x08
    bool m_10; // 0x10
};

#include "RHBonusInfo.h"
#include "RHPositionInterface.h"

class RHEngine;
struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
class RHSpriteEngineCalls
{
public:
    unsigned FUN_004d9090();
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


// VTABLE: GAME 0x00679bc8
// SIZE 0x3c
class RHOrder
{
public:
    RHOrder();
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
    bool Unk0049d560(int action);
    int Unk005c2ec0(void *, int, int, void *, int, int, int, int);
    void Unk00419fb0(int value);
    void Unk0040d980(int stimulus);
    void Unk00418bc0();
};

class RHTitbits;
extern RHTitbits *g_unk0x6c10e8;
double FUN_006433ab(double) throw();

#endif
