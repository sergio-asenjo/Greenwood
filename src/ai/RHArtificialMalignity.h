#ifndef RHARTIFICIALMALIGNITY_H
#define RHARTIFICIALMALIGNITY_H

#include "SB.h"

class RHEngine;
extern RHEngine *g_pEngine;

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    float m_x;
    float m_y;
};

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    ~RHUnk005fc3b0() {}
};

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    float x;
    float y;
    float z;
};

struct RHMalignityPosition
{
    float x; // +0x00
    float y; // +0x04
    void *area; // +0x08
    unsigned short layer; // +0x0c
};

struct RHMalignityWaypoint
{
    char m_00[0x64];
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

struct RHMalignityArray
{
    int m_grow; // +0x00
    void **m_first; // +0x04
    void **m_last; // +0x08
    unsigned short size() { return m_first ? m_last - m_first : 0; }
};

struct RHMalignityNode
{
    RHMalignityNode *next;
    RHMalignityNode *previous;
    void *value;
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
class RHSectorActorList
{
public:
    void Unk005c8e40(int index);
    int Unk004b8f80(RHElementActor *const &value, bool mode);
};

struct RHMalignityList
{
    int m_allocator; // +0x00
    RHMalignityNode *m_head; // +0x04
    int m_count; // +0x08
    RHMalignityNode *m_current; // +0x0c
    bool m_dirty; // +0x10
    char m_11[3];
    int m_index; // +0x14

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
    virtual bool V48() = 0;
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
    virtual unsigned Vcc() = 0;
    virtual void Vd0() = 0;
    virtual void Vd4(int value, float low, float high, int duration, bool first, bool second) = 0;
    virtual void Vd8() = 0;
    virtual void Vdc() = 0;
    virtual void Ve0() = 0;
    virtual void Ve4() = 0;
    virtual void Ve8() = 0;
    virtual void Vec(int value, int mode) = 0;
    virtual bool Vf0() = 0;
    virtual bool Vf4() = 0;
    virtual bool Vf8() = 0;
    virtual void Vfc() = 0;
    virtual void V100() = 0;
    virtual void V104() = 0;
    virtual void V108() = 0;
    virtual void V10c() = 0;
    virtual void V110() = 0;
    virtual void V114() = 0;
    virtual void V118() = 0;
    virtual void V11c() = 0;
    virtual void V120() = 0;
    virtual void V124() = 0;
    virtual void V128() = 0;
    virtual void V12c() = 0;
    virtual int V130() = 0;
    bool FUN_0048a260(const RHUnk00613e90 &point);
    void FUN_0048ebe0();
    void FUN_0048c700(void *actor, bool mode);
    void FUN_0048d050();
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
    virtual void V00(int mode) = 0;
    virtual void V04(int mode) = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10(int state, int substate) = 0;

    SBGeoPoint2D FUN_0040cc20(void *actor);
    void FUN_0041a300(void *actor);
    void FUN_0041ab30();
    bool FUN_00419e10(void *actor);
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
class RHScriptBatchCalls
{
public:
    void Unk0041ac50();
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
    int FUN_00438710(unsigned value);
};

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
