#ifndef RHARTIFICIALMALIGNITY_H
#define RHARTIFICIALMALIGNITY_H

#include "SB.h"
#include "Decomp.h"
#include "RHScript.h"
#include <iterator>

class RHEngine;
extern RHEngine *g_pEngine;

struct RHMalignityAlertPayload;

struct RHMalignityStimulus
{
    RHMalignityStimulus() : m_type(0), m_24(0), m_28(0) {}
    RHMalignityStimulus(unsigned value, const RHMalignityAlertPayload &payload);
    ~RHMalignityStimulus() {}
    undefined m_00[0x1c];
    unsigned m_type;
    unsigned m_20;
    void *m_24;
    char m_28;
};

struct RHMalignityWaypoint
{
    undefined m_00[0x64]; // 0x00
    short x; // +0x64
    short y; // +0x66
    void *area; // +0x68
    unsigned short layer; // +0x6c
    RHMalignityPosition Position()
    {
        RHMalignityPosition position;
        position.x = x;
        position.y = y;
        position.area = area;
        position.layer = layer;
        return position;
    }
};

#include "RHMalignityArray.h"

// SIZE 0x0c
struct RHMalignityNode
{
    RHMalignityNode *next; // 0x00
    RHMalignityNode *previous; // 0x04
    void *value; // 0x08
};

class RHSequenceElement;
class RHElementActor;
#include "RHSectorActorList.h"

// SIZE 0x18
struct RHMalignityList
{
    int m_allocator; // +0x00
    RHMalignityNode *m_head; // +0x04
    int m_count; // +0x08
    RHMalignityNode *m_current; // +0x0c
    bool m_dirty; // +0x10
    undefined m_11[3]; // 0x11
    int m_index; // +0x14

    void Clear();
    __forceinline void FUN_005c8e40(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    void Seek(int wanted);
    void RemoveFirst();
    int size() { return m_count; }

    void InsertLast(void *const &value)
    {
        RHMalignityNode *node = m_head;
        node->previous = (RHMalignityNode *)((RHUnk0046eb30 *)this)->Unk0059f720((RHScriptNode *)node, (RHScriptNode *)node->previous);
        node = node->previous;
        node->previous->next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&value);
        ++m_count;
        m_dirty = true;
    }
};

#include "RHMalignityActorCalls.h"

// SIZE 0x40
struct RHUnk00441dd0Record
{
    void *m_0; // 0x00
    RHMalignityPosition m_4; // 0x04
    void *m_14; // 0x14
    RHMalignityPosition m_18; // 0x18
    unsigned short m_28; // 0x28
    unsigned char m_2a; // 0x2a
    unsigned char m_2b; // 0x2b
    unsigned short m_2c; // 0x2c
    unsigned short m_2e; // 0x2e
    unsigned char m_30; // 0x30
    undefined m_31[3]; // 0x31
    int m_34; // 0x34
    int m_38; // 0x38
    int m_3c; // 0x3c

    RHUnk00441dd0Record() : m_2a(0), m_2b(0), m_2c(0), m_2e(0x1a0a), m_30(0), m_34(0), m_38(0), m_3c(0) {}
};

#include "RHArtificialMalignityCore.h"

unsigned FUN_00445210(float first, unsigned second, unsigned third, unsigned fourth, float fifth, unsigned sixth, void *seventh, unsigned eighth);

RHUnk00613e90 FUN_00414360(const RHMalignityPosition &position, bool mode);
SBGeoVector2D FUN_0040ec20(const RHMalignityPosition &first, RHMalignityPosition second);
#include "RHActorAreaCalls.h"
template <bool InlineHead>
class RHCampaignIndexList
{
public:
    undefined4 m_allocator; // 0x00
    RHScriptNode *m_head; // 0x04
    int m_count; // 0x08
    RHScriptIter FUN_004fe2e0(RHScriptIter position, const unsigned short &value);
};

struct RHMalignityIterator
{
    RHMalignityNode *node; // 0x00
    RHMalignityIterator(RHMalignityNode *value = 0) : node(value) {}
};

class RHAIUnk0044e8b0
{
public:
    RHMalignityIterator FUN_0044e8b0(RHMalignityIterator first, RHMalignityIterator last);
    RHScriptIter FUN_0044e8b0(RHScriptIter first, RHScriptIter last);
    RHMalignityIterator FUN_0046eb80();
    RHMalignityIterator FUN_00424410(RHMalignityIterator position, void *const &value);
    void FUN_0045a440(void *const &value);
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

void *FUN_0048f170(void *value);
class RHMalignityNodeValue
{
public:
    void *FUN_0040eab0(int mode);
};

class RHPath
{
public:
    bool TestIfPathIsFine(RHElementActor *actor);
};

class RHMalignityAlertCalls
{
public:
    void FUN_0042c890(int type, void *actor);
};

#include "RHMalignityOwnerCalls.h"

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    undefined m_00[0x14]; // 0x00
    SBGeoPoint2D FUN_00608f40() const;
};
class RHPathActorInfo
{
public:
    const SBGeoBoundingBox2D &FUN_00560450();
};

class RHUnk00608f10
{
public:
    int FUN_00608f10(void *value);
    bool FUN_006082a0(void *value);
};

class RHUnk0055dbb0
{
public:
    char *FUN_0055dbb0();
};

#include "RHMalignityGeometryCalls.h"

class RHMalignityVectorCalls
{
public:
    RHUnk00613e90 FUN_005df550(const RHUnk00613e90 &point);
};

// SIZE 0x10
struct RHMalignityOwnedList;

// SIZE 0x0c
struct RHMalignityOwnedPoint
{
    undefined4 m_00; // 0x00
    SBGeoPoint2D m_04; // 0x04
    ~RHMalignityOwnedPoint();
};

struct RHMalignityOwnedRecord
{
    ~RHMalignityOwnedRecord();
};

// SIZE 0x3c
class RHUnk00521770
{
public:
    RHUnk00521770 *FUN_00521770();
    void *FUN_005217a0(unsigned flags);
    void FUN_005217c0();
    undefined4 m_vtable; // 0x00
    undefined m_04[8]; // 0x04
    undefined4 m_0c; // 0x0c
    undefined m_10[4]; // 0x10
    undefined4 m_14; // 0x14
    undefined m_18; // 0x18
    undefined m_19[3]; // 0x19
    undefined4 m_1c; // 0x1c
    undefined4 m_20; // 0x20
    undefined4 m_24; // 0x24
    undefined m_28[4]; // 0x28
    bool m_2c; // 0x2c
    undefined m_2d[12]; // 0x2d
    bool m_39; // 0x39
};

extern undefined g_unk0x006c0e48[];

// SIZE 0x14
struct RHMalignityMessage
{
    void *actor; // 0x00
    unsigned type; // 0x04
    bool m_08; // 0x08
    bool m_09; // 0x09
    bool m_0a; // 0x0a
    undefined m_0b; // 0x0b
    bool m_0c; // 0x0c
    undefined m_0d[3]; // 0x0d
    unsigned m_10; // 0x10
    RHMalignityMessage() : type(7)
    {
        m_0a = false;
        m_08 = false;
        m_09 = false;
        m_0c = false;
        m_10 = 0;
    }
    ~RHMalignityMessage() {}
};

// SIZE 0x1c
struct RHMalignityMessageNode
{
    RHMalignityMessageNode *next; // 0x00
    RHMalignityMessageNode *previous; // 0x04
    RHMalignityMessage value; // 0x08
};

#include "RHMobileUnk006100e0.h"

#include "SBGeoSegment2D.h"

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &value);
};

class RHMalignitySegment
{
public:
    RHMalignitySegment(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~RHMalignitySegment();
    undefined m_00[0x10]; // 0x00
};

class RHMalignityArrayCalls
{
public:
    void FUN_0059fba0(const unsigned &value);
    void FUN_004e60a0(void *position, unsigned count, const unsigned &value);
    void FUN_004e62b0(void *position, unsigned count, const RHMalignitySegment &value);
};

// SIZE 0x50
class RHMalignityRectangle
{
public:
    RHMalignityRectangle();
    ~RHMalignityRectangle();
    undefined m_00[0x50]; // 0x00
};

class RHMalignityEngineCalls
{
public:
    void FUN_004da8d0(const SBGeoBoundingBox2D &box);
};

class RHUnk004dab90Rectangle : public RHMalignityRectangle
{
public:
    RHUnk004dab90Rectangle()
    {
        unsigned value = 0;
        RHMalignityArrayCalls &indices = *(RHMalignityArrayCalls *)(m_00 + 0x2c);
        indices.FUN_0059fba0(value);
        m_00[0x40] = 1;
    }
    ~RHUnk004dab90Rectangle();
};

// SIZE 0x24
class RHMalignityQueryList : public RHMalignityList
{
public:
    RHMalignityQueryList();
    ~RHMalignityQueryList() { FUN_004e6c10(); FUN_004e52a0(); }
    void FUN_004e6c10();
    void FUN_004e52a0();
    undefined m_18[0x0c]; // 0x18
};

class RHMalignityGridCalls
{
public:
    bool FUN_004f5e50(SBGeoBoundingBox2D &box, const SBGeoPoint2D &point, unsigned short layer);
    void FUN_004ed370(RHMalignityQueryList &list, unsigned short layer, const RHMalignitySegment &segment, unsigned mask);
    void FUN_004ed070(RHMalignityQueryList &list, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned mask);
};

SBGeoVector2D operator*(float factor, const SBGeoVector2D &point);
SBGeoVector2D FUN_005fc580(const SBGeoVector2D &point, float factor);
RHMalignityPosition FUN_0040ed40(const RHMalignityPosition &position, SBGeoVector2D vector);
RHMalignityPosition FUN_0040ece0(const RHMalignityPosition &position, SBGeoPoint2D point);

class RHFastFindTacticalArray
{
public:
    int allocator;
    void **first;
    void **last;
};

extern RHFastFindTacticalArray g_unk0x006c0718;

class RHSaveGame;
template <class T>
class SBArray
{
public:
    int m_grow;
    T *m_first;
    T *m_last;
    T *m_end;
    void Insert(T *position, unsigned count, const T &value);
};
typedef SBArray<RHSaveGame *> RHMalignityResetArray;
extern unsigned *g_unk0x006c08a4;

template <class T>
inline T &RHMalignityField(void *object, int offset)
{
    return *(T *)((char *)object + offset);
}

inline unsigned short RHMalignityHeading(void *actor)
{
    return RHMalignityField<unsigned short>(RHMalignityField<void *>(actor, 0x50), 0xd8);
}

#endif
