#ifndef RHARTIFICIALMALIGNITY_H
#define RHARTIFICIALMALIGNITY_H

#include "SB.h"
#include "Decomp.h"
#include <iterator>

class RHEngine;
extern RHEngine *g_pEngine;

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &point);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &point);
    float FUN_005fc700(float scale) const;
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &point) const;
    ~SBGeoPoint2D();
    float m_x; // 0x00
    float m_y; // 0x04
};

// SIZE 0x08
class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    ~RHUnk005fc3b0() {}
    RHUnk005fc3b0 &Unk005fcd40(unsigned short direction, float length);
    float FUN_005fc680(const RHUnk005fc3b0 &vector, float scale) const;
};

// SIZE 0x0c
class RHUnk00613e90
{
public:
    RHUnk00613e90();
    float x; // 0x00
    float y; // 0x04
    float z; // 0x08
};

// SIZE 0x10
struct RHMalignityPosition
{
    float x; // +0x00
    float y; // +0x04
    void *area; // +0x08
    unsigned short layer; // +0x0c
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

// SIZE 0x0c
struct RHMalignityArray
{
    int m_grow; // +0x00
    void **m_first; // +0x04
    void **m_last; // +0x08
    unsigned short size() { return m_first ? m_last - m_first : 0; }
};

// SIZE 0x0c
struct RHMalignityNode
{
    RHMalignityNode *next; // 0x00
    RHMalignityNode *previous; // 0x04
    void *value; // 0x08
};

struct RHScriptNode;
class RHUnk0046eb30
{
public:
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
};

class RHSequenceElement;
class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
};

class RHElementActor;
// SIZE 0x24
class RHSectorActorList
{
public:
    void Unk005c8e40(int index);
    int Unk004b8f80(RHElementActor *const &value, bool mode);
    undefined4 m_allocator; // 0x00
    RHMalignityNode *m_head; // 0x04
    int m_count; // 0x08
    RHMalignityNode *volatile m_current; // 0x0c
    bool m_dirty; // 0x10
    undefined m_11[3]; // 0x11
    int m_index; // 0x14
    bool m_forward; // 0x18
    undefined m_19[3]; // 0x19
    volatile int m_result; // 0x1c
    RHElementActor *volatile m_value; // 0x20
};

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

class RHMalignityActorCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c() = 0;
    virtual void V40() = 0;
    virtual void V44() = 0;
    virtual bool V48() = 0; // vtable+0x48
    virtual void V4c() = 0;
    virtual void V50() = 0;
    virtual void V54() = 0;
    virtual void V58() = 0;
    virtual void V5c() = 0;
    virtual void V60() = 0;
    virtual void V64() = 0;
    virtual void V68() = 0;
    virtual void V6c() = 0;
    virtual void V70() = 0;
    virtual void V74() = 0;
    virtual void V78() = 0;
    virtual void V7c() = 0;
    virtual void V80() = 0;
    virtual void V84() = 0;
    virtual void V88() = 0;
    virtual void V8c() = 0;
    virtual void V90() = 0;
    virtual void V94() = 0;
    virtual void V98() = 0;
    virtual void V9c() = 0;
    virtual void Va0() = 0;
    virtual void Va4() = 0;
    virtual void Va8() = 0;
    virtual void Vac() = 0;
    virtual void Vb0() = 0;
    virtual void Vb4() = 0;
    virtual void Vb8() = 0;
    virtual void Vbc() = 0;
    virtual void Vc0() = 0;
    virtual void Vc4() = 0;
    virtual void Vc8() = 0;
    virtual unsigned Vcc() = 0; // vtable+0xcc
    virtual void Vd0() = 0;
    virtual void Vd4(unsigned short value, int duration, bool first, bool second) = 0; // vtable+0xd4
    virtual void Vd8() = 0;
    virtual void Vdc() = 0;
    virtual void Ve0() = 0;
    virtual void Ve4() = 0;
    virtual void Ve8() = 0;
    virtual void Vec(int value, int mode) = 0; // vtable+0xec
    virtual bool Vf0() = 0; // vtable+0xf0
    virtual bool Vf4() = 0; // vtable+0xf4
    virtual bool Vf8() = 0; // vtable+0xf8
    virtual void Vfc() = 0;
    virtual void V100() = 0;
    virtual void V104() = 0;
    virtual void V108() = 0;
    virtual void V10c() = 0;
    virtual void V110() = 0;
    virtual void V114() = 0;
    virtual void V118() = 0;
    virtual bool V11c() = 0; // vtable+0x11c
    virtual void V120() = 0;
    virtual void V124() = 0;
    virtual void V128() = 0;
    virtual void V12c() = 0;
    virtual int V130() = 0; // vtable+0x130
    bool FUN_0048a260(const RHUnk00613e90 &point);
    void FUN_0048ebe0();
    void FUN_0048c700(void *actor, unsigned mode);
    void FUN_0048d050();
    void FUN_00478c20(RHUnk00613e90 &point, bool mode);
    unsigned char FUN_0048c8e0(void *actor, bool mode);
    bool FUN_0048a130(void *actor);
};

class RHArtificialIntelligence
{
public:
    void Unk00410010(bool mode);
    bool InitState();
};

class RHMalignityBaseView
{
public:
    virtual void V00(int mode) = 0; // vtable+0x00
    virtual void V04(int mode) = 0; // vtable+0x04
    virtual void V08() = 0; // vtable+0x08
    virtual void V0c() = 0; // vtable+0x0c
    virtual void V10(int state, int substate) = 0; // vtable+0x10

    SBGeoPoint2D FUN_0040cc20(void *actor);
    RHMalignityPosition FUN_004165e0(void *actor, bool mode);
    SBGeoPoint2D FUN_0040cbf0(const RHMalignityPosition &position);
    void FUN_0041a300(void *actor);
    void FUN_0041ab30();
    bool FUN_00419e10(void *actor);
    float FUN_0041a010(void *actor);
    void *m_actor; // +0x04
};

class RHArtificialMalignity
{
public:
    // Entry this: vbptr -0x358; virtual-base displacement from vbtable +0x04.
    // Direct fields: list -0x32c; interval WORD -0x32e; waypoint WORD -0x306.
    // Virtual-base fields: actor +0x04; friend +0x1fc; saved friend +0x200.
    // Virtual-base fields: direction BYTE +0x32; rate BYTE +0x2c; tick +0x1c8.
    // InitOneAI: WORD -0x222; bytes -0x78/-0x77/-0x50; array -0x4c.
    void InitOneAI();
    bool SerializeExactlyThisAI(SBFile &file);
    void InitializeFriendCheck(unsigned short actor, unsigned short delay, unsigned short waypoint);
    void Emit(SBFile &file);

    RHMalignityBaseView &Base()
    {
        return *(RHMalignityBaseView *)((char *)this + (*(int **)((char *)this - 0x358))[1] - 0x358);
    }
};

RHUnk00613e90 FUN_00414360(const RHMalignityPosition &position, bool mode);
SBGeoPoint2D FUN_0040ec20(const RHMalignityPosition &first, RHMalignityPosition second);
class RHActorAreaCalls
{
public:
    void *FUN_0057d800(const SBGeoPoint2D &point);
};
extern float g_unk0x00677488;
extern float g_unk0x0067749c;
extern float g_unk0x006774a0;
class RHScriptBatchCalls
{
public:
    void Unk0041ac50();
};

struct RHScriptNode
{
    RHScriptNode *next; // 0x00
    RHScriptNode *prev; // 0x04
    void *data; // 0x08
};

struct RHScriptIter
{
    RHScriptNode *node; // 0x00
    RHScriptIter(RHScriptNode *value = 0) : node(value) {}
};

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
    void FUN_0040eab0(int mode);
};

class RHArtificialIntelligencePathCursor
{
public:
    void Unk00550f60(unsigned short path);
};

class RHPath
{
public:
    bool TestIfPathIsFine(RHElementActor *actor);
};

class RHMalignityOwnerCalls
{
public:
    unsigned short FUN_00438710(unsigned short value, float low, float high, unsigned short maximum);
};

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

class RHMalignityGeometryCalls
{
public:
    bool FUN_004eff80(const RHUnk00613e90 &first, const RHUnk00613e90 &second, int mode);
};

class RHMalignityVectorCalls
{
public:
    RHUnk00613e90 FUN_005df550(const RHUnk00613e90 &point);
};

// SIZE 0x10
struct RHMalignityOwnedList
{
    undefined4 m_allocator; // 0x00
    RHMalignityNode *m_head; // 0x04
    int m_count; // 0x08
    RHMalignityNode *m_current; // 0x0c
    void FUN_004e65b0();
};

// SIZE 0x3c
class RHUnk00521770
{
public:
    RHUnk00521770 *FUN_00521770();
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

extern float g_unk0x006774ec;
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
    RHMalignityMessage() : type(7), m_0a(false), m_08(false), m_09(false), m_0c(false), m_10(0) {}
    ~RHMalignityMessage() {}
};

// SIZE 0x1c
struct RHMalignityMessageNode
{
    RHMalignityMessageNode *next; // 0x00
    RHMalignityMessageNode *previous; // 0x04
    RHMalignityMessage value; // 0x08
};

// SIZE 0x10
class RHMobileUnk006100e0 : public SBGeoPoint2D
{
public:
    ~RHMobileUnk006100e0();
    undefined m_08[8]; // 0x08
};

class RHMobileUnk0060a820
{
public:
    RHMobileUnk0060a820 &FUN_0060a820(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
};

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

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    ~SBGeoVector2D() {}
    float FUN_005fc660(const SBGeoPoint2D &point) const;
};

SBGeoVector2D operator*(float factor, const SBGeoVector2D &point);
extern float g_unk0x006787f8;

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
extern float g_unk0x006774e4;

template <class T>
inline T &RHMalignityField(void *object, int offset)
{
    return *(T *)((char *)object + offset);
}

#endif
