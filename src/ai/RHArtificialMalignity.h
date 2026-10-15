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

class RHSequenceElement;
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
    void FUN_005c8e40(int index);
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
    float FUN_0048db80(void *position, void *actor);
    void FUN_0048e420(void *actor);
    void FUN_0048e580();
    void FUN_0048e5b0(unsigned operation, unsigned short value, unsigned unused);
    unsigned short FUN_0048e5f0(unsigned operation);
    unsigned short FUN_0048e610();
    void FUN_0048e620(unsigned short value);
    void FUN_0048e630(unsigned operation, unsigned short value);
    void FUN_0048e650(unsigned operation, unsigned short value);
    bool FUN_0048e670(void *actor);
    void FUN_0048e870(void *actor);
    void FUN_0048ebe0();
    void FUN_00487aa0(int value);
    void FUN_00487ad0(const RHMalignityPosition &position);
    void FUN_0048c700(void *actor, unsigned mode);
    unsigned char FUN_0048ca20(void *actor, unsigned mode);
    void FUN_0048cb90(void *actor);
    void FUN_0048d050();
    void FUN_00478c20(RHUnk00613e90 &point, bool mode);
    unsigned char FUN_0048c8e0(void *actor, unsigned mode);
    bool FUN_0048a130(void *actor);
    bool FUN_0048a350(void *actor);
};

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
    void FUN_00439cb0(const RHMalignityPosition &position, unsigned short radius);
    void FUN_00439e70(void *actor, const RHMalignityPosition &position);
    void FUN_00439f60(const RHMalignityStimulus &stimulus);
    void FUN_0043a080(const RHMalignityPosition &position);
    void FUN_0043a170(const RHMalignityPosition &position);
    void FUN_00438620(unsigned short value);
    void FUN_0043b1b0(RHMalignityPosition position, int mode);
    void FUN_0043c960(RHMalignityPosition position, int mode);
    short FUN_00440cf0(RHUnk00441dd0Record *record);
    int FUN_00441020(RHUnk00441dd0Record *record, RHMalignityList *list);
    void FUN_00441f20();
    unsigned FUN_004436e0(void *record, char mode);
    unsigned FUN_00443850(void *record);
    void FUN_004439a0(void *record, unsigned char flags);
    void FUN_00443af0(unsigned value);
    void *FUN_00443c40(void *value);
    void *FUN_00443d10(void *position);
    void *FUN_00443e20(unsigned index, unsigned radius, unsigned flags, int type);
    unsigned FUN_00443fa0(unsigned first, unsigned second, unsigned third, unsigned fourth);
    void FUN_004444a0();
    void FUN_00444bb0(void *record);
    void FUN_004450a0();
    void FUN_00445180();
    bool FUN_00445510(RHMalignityPosition position, void *actor);
    void FUN_004457c0(const RHMalignityPosition &position);
    bool FUN_00438cb0(int command, bool mode);
    void FUN_004459b0();
    void FUN_00445b40();
    void *FUN_00445d40();
    bool FUN_004460f0();
    void FUN_004461a0(void *target, void *actor);
    void FUN_00446700();
    bool FUN_004468a0();
    void FUN_004469e0();
    void FUN_00446d20();
    void FUN_00446eb0(void *actor);
    void FUN_00447030(void *guard);
    void FUN_00447420(void *target);
    void FUN_00447490(void *target);
    void *FUN_004474e0();
    bool FUN_00447640(RHMalignityPosition &target);
    void FUN_00447da0(RHMalignityPosition &position, unsigned short &heading);
    unsigned short FUN_00449170();
    bool FUN_00449810(const RHMalignityPosition &position, unsigned short heading);
    bool FUN_00449ac0();
    unsigned short FUN_00449d40(void *group);
    bool FUN_0044a090();
    void FUN_0044a760(void *actor);
    void FUN_0044a830(void *actor);
    void FUN_0044b000();
    bool FUN_0044b120(const RHMalignityPosition &position);
    void *FUN_0044b7b0();
    void FUN_0044b800();
    void FUN_0044b810(void *point);
    void FUN_0044b840(void *point);
    bool FUN_0044b870(void *area, unsigned short id);
    void FUN_0044ca90();
    bool FUN_0044cf00();
    void FUN_00430020();
    void FUN_004303e0();
    void FUN_0044d0b0();
    void FUN_00430300(int mode);
    void *FUN_0043d780(unsigned short flags);
    bool FUN_0043f340(void *actor);
    bool FUN_0043f540(void *actor);
    void FUN_0043fa80(void *target, void *actor);
    void FUN_0043fc60(void *target, void *actor);
    void FUN_00440040(void *target, RHMalignityPosition position, RHUnk005fc3b0 *direction, int mode, void *actor);
    RHUnk00441dd0Record *FUN_00441dd0();
    bool FUN_0044afa0(void *actor);
    void Emit(SBFile &file);

    RHMalignityBaseView &VirtualBase()
    {
        return *(RHMalignityBaseView *)((char *)this + (*(int **)this)[1]);
    }

    RHMalignityBaseView &Base()
    {
        return *(RHMalignityBaseView *)((char *)this + (*(int **)((char *)this - 0x358))[1] - 0x358);
    }
};

unsigned FUN_00445210(float first, unsigned second, unsigned third, unsigned fourth, float fifth, unsigned sixth, void *seventh, unsigned eighth);

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
    void FUN_0040eab0(int mode);
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
struct RHMalignityOwnedList;

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
extern float g_unk0x00677504;
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
SBGeoPoint2D FUN_005fc580(const SBGeoPoint2D &point, float factor);
RHMalignityPosition FUN_0040ed40(const RHMalignityPosition &position, SBGeoVector2D vector);
RHMalignityPosition FUN_0040ece0(const RHMalignityPosition &position, SBGeoPoint2D point);
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

inline unsigned short RHMalignityHeading(void *actor)
{
    return RHMalignityField<unsigned short>(RHMalignityField<void *>(actor, 0x50), 0xd8);
}

#endif
