#ifndef RHELEMENTACTOR_CALLS_H
#define RHELEMENTACTOR_CALLS_H

#include "SB.h"
#include <string>
#include <memory.h>
#include <iterator>
#include <new>
#include "RHActorTranslation.h"

// SIZE 0x08
class SBGeoVector2D;
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    void FUN_005fc390(const SBGeoPoint2D &other) throw();
    float FUN_005fc700(float scale) const;
    bool Serialize(SBFile &file);
    bool operator==(const SBGeoPoint2D &other) const;
    bool FUN_005fc0e0(const SBGeoPoint2D &other) const;
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    float m_0; // 0x00
    float m_4; // 0x04
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float x, float y);
    SBGeoVector2D(const SBGeoPoint2D &other);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D(const SBGeoPoint2D &first, const SBGeoPoint2D &last);
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &other);
    SBGeoPoint2D FUN_00608f40() const;
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &other);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &other) const;
    SBGeoPoint2D m_0; // 0x00
    SBGeoPoint2D m_8; // 0x08
    char m_10; // 0x10
};

#include "RHTripleVectorCalls.h"

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *previous;
    void *data;
};
struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
    RHScriptIter operator++(int);
};
class RHUnk0046eb30
{
public:
    RHScriptIter FUN_0046eb80();
    RHScriptIter erase(RHScriptIter position);
};

class RHUnk0040f060
{
public:
    RHUnk0040f060();
    ~RHUnk0040f060()
    {
        RHScriptNode *sentinel = head;
        RHScriptNode *current = sentinel->next;
        while (current != sentinel)
        {
            RHScriptNode *previous = current;
            current = current->next;
            ((RHUnk0046eb30 *)this)->erase(RHScriptIter(previous));
        }
        RHScriptIter iterator(head->next);
        while (iterator.node != head)
            ((RHUnk0046eb30 *)this)->erase(iterator++);
        ::operator delete(head);
        head = 0;
        count = 0;
    }
    int m_0;
    RHScriptNode *head;
    int count;
    char m_c[0x18];
};

class RHElement
{
public:
    virtual bool Serialize(SBFile &file);
    int FUN_004671b0() const;
    void CrossElevationLine(class RHElevationLine *line);
    char m_04[0xa4];
};

class RHEngine
{
public:
    bool SerializeElementPointer(SBFile &file, RHElement *&element);
};
class RHReconnaissanceEngine
{
public:
    bool Unk004c3cb0(SBFile &file, void *&value);
};
class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &file, void *&value);
};
class RHOrder;
class RHSequenceElement
{
public:
    virtual void Unk0();
    virtual void Unk1();
    virtual void Unk2();
    virtual void FUN_00585970(void *value, bool flag);
    int Unk00587160(int argument);
    char m_4[0xc];
    int m_10;
    char m_14[0x58];
    SBGeoPoint2D m_6c;
};
class RHSequenceManager
{
public:
    bool PreSerializePointer(SBFile &file, RHOrder **order);
    bool PreSerializePointer(SBFile &file, RHSequenceElement **element, bool launch);
    bool FUN_0058bd70(void *actor, int command);
};
class RHSequence
{
public:
    bool Serialize(SBFile &file, bool loading);
};
class RHUnk00582220
{
public:
    RHUnk00582220();
    ~RHUnk00582220();
    char m_0[0x3c];
};
class RHScrollScript
{
public:
    bool FUN_006348f0(SBFile &file);
};

struct RHUnkSectorGlobal;
extern RHEngine *g_pEngine;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
void RHSerializeName(SBFile &file, const char *name);
bool FUN_005e0c90(SBFile &file, std::string &value);

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

struct RHActorPointNode
{
    RHActorPointNode *next;
    RHActorPointNode *previous;
    SBGeoPoint2D point;
};
struct RHActorPointIterator
{
    RHActorPointNode *node;
    RHActorPointIterator(RHActorPointNode *value) : node(value) {}
};
class RHActorPointList
{
public:
    int m_0;
    RHActorPointNode *head;
    int count;
    RHActorPointNode *cursor;
    char dirty;
    char m_11[3];
    int index;
    RHActorPointIterator begin() { return RHActorPointIterator(head->next); }
    RHActorPointIterator end() { return RHActorPointIterator(head); }
    SBGeoPoint2D &Get(int wanted)
    {
        int size = count;
        if (dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(cursor = begin().node), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(cursor = end().node), wanted - size, category);
            }
            dirty = 0;
            index = wanted;
        }
        else
        {
            int previous = index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)(cursor = begin().node), wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + size) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)(cursor = end().node), wanted - size, category);
                }
                index = wanted;
            }
        }
        return cursor->point;
    }
    RHActorPointNode *BuyNode(RHActorPointNode *next, RHActorPointNode *previous)
    {
        RHActorPointNode *node = (RHActorPointNode *)::operator new(sizeof(RHActorPointNode));
        node->next = next ? next : node;
        node->previous = previous ? previous : node;
        return node;
    }
    void Construct(SBGeoPoint2D *point, const SBGeoPoint2D &source)
    {
        new (point) SBGeoPoint2D(source);
    }
    RHActorPointIterator insert(RHActorPointIterator position, const SBGeoPoint2D &source)
    {
        RHActorPointNode *node = position.node;
        node->previous = BuyNode(node, node->previous);
        node = node->previous;
        node->previous->next = node;
        Construct(&node->point, source);
        ++count;
        dirty = 1;
        return RHActorPointIterator(node);
    }
};

class RHActorString
{
public:
    char m_0;
    char *m_4;
    unsigned m_8;
    unsigned m_c;

    const char *c_str() const { return m_4 ? m_4 : ""; }
    void FUN_00402780();
    bool FUN_00402280(unsigned length, bool trim = false);
    void FUN_00402260(unsigned length);
    void FUN_00401ee0(bool release);
    void Assign(const RHActorString &source)
    {
        unsigned count = std::string::npos;
        unsigned length = source.m_8;
        if (count < length)
            length = count;
        if (this == &source)
        {
            if (m_8 < length)
                std::_Xran();
            FUN_00402780();
            if (m_8 - length < count)
                count = m_8 - length;
            if (count > 0)
            {
                memmove(m_4 + length, m_4 + length + count, m_8 - length - count);
                unsigned remaining = m_8 - count;
                if (FUN_00402280(remaining))
                    FUN_00402260(remaining);
            }
            typedef std::string &(std::string::*Erase)(unsigned, unsigned);
            Erase erase = &std::string::erase;
            (((std::string *)this)->*erase)(0, 0);
        }
        else if (length > 0 && length == source.m_8 && (unsigned char)source.c_str()[-1] < 254)
        {
            FUN_00401ee0(true);
            m_4 = (char *)source.c_str();
            m_8 = source.m_8;
            m_c = source.m_c;
            ++m_4[-1];
        }
        else if (FUN_00402280(length, true))
        {
            memcpy(m_4, source.c_str(), length);
            FUN_00402260(length);
        }
    }
};

#include "RHUnkSectorScript.h"

#include "RHActorScriptContext.h"

struct RHBonusProjection;

class RHBonusInfoBase
{
public:
    char FUN_004671d0() const;
    void FUN_004671e0(char value);
    SBGeoVector2D FUN_00468f10(int value) const;
    void FUN_0055f290();
    void FUN_0055fa20(RHBonusProjection *projection);
    void FUN_0055fa70(void *area);
    void FUN_00462970(int action);
    void SetFlagFd() { *((char *)this + 0xfd) = 1; }
    void ResetTarget(const SBGeoPoint2D &point)
    {
        *(SBGeoPoint2D *)((char *)this + 0x44) = point;
        *(int *)((char *)this + 8) = 0;
    }
};
class RHUnkPathActorInfoBase
{
public:
    void *Unk0055fa10(int value);
};
class RHBonusInfo
{
public:
    void FUN_005bd560(void *value, bool flag);
    void FUN_005bd650(int value1, int value2);
    void FUN_005bd7b0(int value);
};
class RHElementActor;

#include "RHActorGridCalls.h"
class RHElementActor;

#include "RHActorAreaCalls.h"
class RHElementActor;
class RHTitbits;
class RHScriptBatchCalls
{
public:
    void Unk0040d980(int stimulus);
    void Unk0046bcf0(int posture, int value);
    void Unk0046bd10(int state);
    void Unk00464630();
    void Unk0046b9e0();
    void *Unk0058a940(void *context, int value, void *element);
    int Unk005c2ec0(void *position, int layer, int kind, void *actor, int value1, int value2, int value3, int value4);
};
extern RHTitbits *g_unk0x6c10e8;
extern RHElementActor *g_unk0x6c100c;
extern float g_actorStepScale;

class RHActorScriptBase : public RHUnkSectorScript
{
public:
    char m_0[0x60];
};

class RHActorPositionCalls
{
public:
    void FUN_00464530(const SBGeoPoint2D &point);
};

class RHMobileSegment
{
public:
    RHMobileSegment(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~RHMobileSegment();
    SBGeoPoint2D first;
    SBGeoPoint2D second;
};

class RHMobileGrid
{
public:
    void FUN_004ed370(void *lines, unsigned short layer, const RHMobileSegment &segment, unsigned mask);
};

class RHMobilePosition
{
public:
    void FUN_0055fc20(bool value);
};

class RHElevationLine
{
public:
    char m_00[4];
    SBGeoPoint2D m_04;
    SBGeoPoint2D m_0c;
    unsigned m_14;
    char m_18[0xc];
    void *m_24;
    void *m_28;
};

#include "RHActorCrossingHumanCalls.h"

#include "RHElementAreaShape.h"

class RHPatch
{
public:
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
    void FUN_00550150();
};

#include "RHSectorScript.h"

void __stdcall FUN_0048a970(RHElementActor *actor);

struct RHActorEngineFlags
{
    char m_0[0x4d98];
    unsigned m_4d98;
};

enum RHActorUnkType { RHActorUnkType12 = 12 };

class RHUnk0046bcb0
{
public:
    void Unk(int value);
};

class RHUnk0058a3d0
{
public:
    void *Unk(void *context, int value, void *sequence);
};


extern char g_unk0x6c0691;

class RHActorSequenceCursor
{
public:
    RHOrder *FUN_005855a0();
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c(int first, int second);
};

#endif
