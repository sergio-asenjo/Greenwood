#ifndef RHELEMENTACTOR_CALLS_H
#define RHELEMENTACTOR_CALLS_H

#include "SB.h"
#include <string>
#include <memory.h>
#include <iterator>
#include <new>
#include "RHActorTranslation.h"

// SIZE 0x08
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
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &other) const;
    float m_0; // 0x00
    float m_4; // 0x04
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(const SBGeoPoint2D &other);
    ~SBGeoVector2D() {}
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &other);
    SBGeoPoint2D FUN_00608f40() const;
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &other);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &other) const;
    SBGeoPoint2D m_0; // 0x00
    SBGeoPoint2D m_8; // 0x08
    char m_10; // 0x10
};

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    RHUnk00613e90(float x, float y, float z);
    void FUN_00467990(float x, float y, float z);
    RHUnk00613e90 FUN_005df550(const RHUnk00613e90 &other) const;
    float m_0;
    float m_4;
    float m_8;
};

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
void FUN_005e0c90(SBFile &file, std::string &value);

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
    RHActorString &FUN_00402a70(unsigned start, unsigned length);
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
            FUN_00402a70(0, 0);
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

class RHUnkSectorScript
{
public:
    bool Unk00639a30(const std::string &name);
};

class RHActorScriptContext
{
public:
    void FUN_004030a0();
    void FUN_004033b0(int message, int argument1, int argument2);
    RHUnkSectorScript *m_0;
};

struct RHBonusProjection;

class RHBonusInfoBase
{
public:
    SBGeoVector2D FUN_00468f10(int value) const;
    void FUN_0055f290();
    void FUN_0055fa20(RHBonusProjection *projection);
    void FUN_0055fa70(void *area);
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
class RHActorGridCalls
{
public:
    short FUN_004e8fc0(const SBGeoPoint2D &point, const SBGeoPoint2D &origin, short layer, void *&area);
    unsigned short FUN_004e9800(const SBGeoPoint2D &point, void *&area, int &layer);
    bool FUN_004f5e50(SBGeoPoint2D &point, const SBGeoPoint2D &other, int layer);
};
class RHActorAreaCalls
{
public:
    void *FUN_0057d800(const SBGeoPoint2D &point);
};
class RHElementActor;
class RHUnk005c38b0;
class RHScriptBatchCalls
{
public:
    void Unk0046bcf0(int posture, int value);
    void Unk005c2ec0(void *position, int layer, int kind, void *actor, int value1, int value2, int value3, int value4);
};
extern RHUnk005c38b0 *g_unk0x6c10e8;
extern RHElementActor *g_unk0x6c100c;
extern float g_actorStepScale;
extern float g_actorEffectOffset;

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

class RHActorCrossingHumanCalls
{
public:
    void FUN_004846d0();
    bool FUN_004843a0(void *area);
    bool FUN_004843d0(SBGeoPoint2D &point, void *area, bool value);
};

class RHElementAreaShape
{
public:
    bool FUN_0060c660(const SBGeoPoint2D &point) const;
};

class RHPatch
{
public:
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
    void FUN_00550150();
};

class RHSectorScript
{
public:
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
};

void __stdcall FUN_0048a970(RHElementActor *actor);

struct RHActorEngineFlags
{
    char m_0[0x4d98];
    unsigned m_4d98;
};

enum RHActorUnkType { RHActorUnkType12 = 12 };

extern char g_unk0x6c0691;

#endif
