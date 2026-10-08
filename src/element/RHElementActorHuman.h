#ifndef RHELEMENTACTORHUMAN_H
#define RHELEMENTACTORHUMAN_H

#include "SB.h"
#include "Decomp.h"
#include <new>
#include <list>
#include <iterator>
#include "RHActorTranslation.h"

class RHSequenceElement
{
public:
    int Unk00587160(int argument);
    char m_00[0x10];
    int m_10;
};
enum RHcommand { RHcommandUnk0 = 0 };
class RHOrder;
class RHUnk00613e90;
class RHElementActor
{
public:
    virtual bool Serialize(SBFile &file); // vtable+0x00
    void Translate(RHSequenceElement *element, RHcommand command);
    void FUN_0046bcb0(int value);
    void FUN_00478c20(RHUnk00613e90 &point, bool value);
};
class RHEngine
{
public:
    bool FUN_004c3bd0(SBFile &file, void *&value);
    bool SerializeNestedB(SBFile &file, void *value);
};
extern RHEngine *g_pEngine;
struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &file, void *&value);
};
class RHFastFindGrid
{
public:
    bool SerializeLinePointer(SBFile &file, void *&value);
};
class RHUnk004b2190Member
{
public:
    bool Serialize(SBFile &file);
};
class RHSightObstacle
{
public:
    bool Serialize(SBFile &file);
};
class RHSequenceManager
{
public:
    bool PreSerializePointer(SBFile &file, RHSequenceElement **value, bool mode);
};
void RHSerializeName(SBFile &file, const char *name);

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &other) const;
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &other) const;
    float FUN_005fc6a0(float value) const;
    float Unk005fc6d0(float value) const;
    float m_0;
    float m_4;
};

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    ~RHUnk005fc3b0() {}
    float Unk005fc6a0(float value);
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
};
class RHUnk0046eb30
{
public:
    RHScriptIter erase(RHScriptIter position);
    RHScriptIter FUN_0046eb80();
};
class RHUnkIter
{
public:
    void *m_p;
    RHUnkIter(void *value) : m_p(value) {}
};
class RHUnkList
{
public:
    RHUnkIter insert(RHUnkIter position, RHOrder *const &value);
};
struct RHTitbitNode;
class RHTitbitList
{
public:
    void Clear(void *result, RHTitbitNode *first, RHTitbitNode *last);
    void At(int index);
};
// SIZE 0x08
struct RHHumanOpponent
{
    void *m_actor; // 0x00
    void *m_line; // 0x04
};
// SIZE 0x10
struct RHHumanOpponentNode
{
    RHHumanOpponentNode *next; // 0x00
    RHHumanOpponentNode *previous; // 0x04
    RHHumanOpponent value; // 0x08
};
// SIZE 0x04
struct RHHumanOpponentIterator
{
    RHHumanOpponentNode *node; // 0x00
    RHHumanOpponentIterator(RHHumanOpponentNode *value) : node(value) {}
};
class RHHumanOpponentListCalls
{
public:
    RHHumanOpponentIterator FUN_00486110(RHHumanOpponentIterator position, const RHHumanOpponent &value);
};
// SIZE 0x18
struct RHHumanList
{
    undefined4 m_0; // 0x00
    RHScriptNode *head; // 0x04
    unsigned count; // 0x08
    RHScriptNode *cursor; // 0x0c
    undefined valid; // 0x10
    undefined m_11[3]; // 0x11
    int index; // 0x14

    RHScriptIter begin() { return RHScriptIter(head->next); }
    RHScriptIter end() { return RHScriptIter(head); }
    void Clear()
    {
        typedef RHScriptIter (RHTitbitList::*Erase)(RHScriptIter, RHScriptIter);
        (((RHTitbitList *)this)->*(Erase)&RHTitbitList::Clear)(begin(), end());
        valid = 1;
    }
    void Insert(void *const &value)
    {
        ((RHUnkList *)this)->insert(RHUnkIter(head), (RHOrder *const &)value);
    }
    void InsertRepeated(RHUnkIter position, unsigned amount, void *const &value)
    {
        while (amount != 0)
        {
            ((RHUnkList *)this)->insert(position, (RHOrder *const &)value);
            --amount;
        }
    }
    void Resize(unsigned wanted, void *value)
    {
        if (count < wanted)
            InsertRepeated(RHUnkIter(head), wanted - count, value);
        else if (wanted < count)
        {
            while (wanted < count)
            {
                RHScriptNode *last = head->previous;
                last->previous->next = last->next;
                last->next->previous = last->previous;
                ::operator delete(last);
                --count;
            }
        }
    }
};

// SIZE 0x49c
class RHUnk005864a0;
class RHElementActorHuman
{
public:
    void Translate(RHSequenceElement *element, RHcommand command);
    bool Serialize(SBFile &file);
    int FUN_004838f0(bool alternate);
    int FUN_0047b760(void *actor, int *value);
    void FUN_0047c420(void *value);
    int FUN_0047c4c0(RHElementActorHuman *actor);
    void FUN_0047d920(RHElementActorHuman *actor);
    int FUN_0047e7d0(RHUnk005864a0 *element);
    void FUN_0047e9d0(RHUnk005864a0 *element);
    int FUN_00484a70(void *value);
    bool FUN_00484bb0(RHElementActorHuman *actor, SBGeoPoint2D &result, void *line);
    void Emit(SBFile &file, RHSequenceElement *element, RHcommand command);

    char m_000[0x1b8]; // +0x50: position owner; +0x5c: sequence manager; +0x64: grid; +0x144: action state.
    RHHumanList m_1b8; // +0x1b8: sequence pointer list; head +0x1bc, count +0x1c0.
    char m_1d0[0x1c]; // +0x1d0: serialized 28-byte block.
    undefined m_1ec[0x20]; // 0x1ec
    RHHumanList m_20c; // +0x20c: actor pointer list; cursor +0x218, dirty +0x21c.
    undefined m_224[0xc]; // 0x224
    int m_230; // 0x230
    int m_234; // 0x234
    int m_238; // 0x238
    short m_23c; // 0x23c
    undefined m_23e; // 0x23e
    undefined m_23f; // 0x23f
    short m_240[9]; // +0x240: nine serialized words.
    undefined m_252[2]; // 0x252
    void *m_254; // 0x254
    undefined m_258[8]; // 0x258
    RHHumanList m_260; // +0x260: 8-byte opponent records; count +0x268, cursor +0x26c.
    undefined m_278[0x10]; // 0x278
    undefined m_288; // 0x288
    undefined m_289; // 0x289
    short m_28a; // 0x28a
    int m_28c; // 0x28c
    void *m_290; // 0x290
    char m_294[0x1a8]; // +0x294: sight-obstacle serializer receiver.
    char m_43c[0x40]; // +0x43c: nested serializer receiver.
    undefined m_47c; // 0x47c
    undefined m_47d[3]; // 0x47d
    int m_480; // 0x480
    int m_484; // 0x484
    short m_488; // 0x488
    undefined m_48a; // 0x48a
    undefined m_48b; // 0x48b
    int m_48c; // 0x48c
    undefined m_490; // 0x490
    undefined m_491; // 0x491
    short m_492; // 0x492
    short m_494; // 0x494
    undefined m_496; // 0x496
    undefined m_497; // 0x497
    void *m_498; // 0x498
};

// SIZE 0x134
class RHUnk0046bd20
{
public:
    int FUN_0046bd20();
    undefined m_000[0x130]; // 0x000
    RHSequenceElement *m_130; // 0x130
};

// SIZE 0x7c
class RHUnk005864a0
{
public:
    undefined4 FUN_005864a0();
    undefined4 FUN_005864b0();
    undefined4 FUN_005864c0();
    undefined4 FUN_005864d0();
    undefined m_00[0x64]; // 0x00
    undefined4 m_64; // 0x64
    undefined m_68[8]; // 0x68
    undefined4 m_70; // 0x70
    undefined4 m_74; // 0x74
    undefined4 m_78; // 0x78
};

// SIZE 0x08
class RHUnk005c1d50
{
public:
    undefined4 FUN_005c1d50(int index);
    unsigned short FUN_005c1dd0(int index, void *actor);
    undefined4 m_00; // 0x00
    undefined *m_04; // 0x04
};

// SIZE 0x14
struct RHHumanMapNode
{
    RHHumanMapNode *m_left; // 0x00
    RHHumanMapNode *m_parent; // 0x04
    RHHumanMapNode *m_right; // 0x08
    int m_key; // 0x0c
    undefined4 m_value; // 0x10
};

// SIZE 0x04
struct RHHumanMapIterator
{
    RHHumanMapNode *m_node; // 0x00
    RHHumanMapIterator(RHHumanMapNode *node) : m_node(node) {}
    RHHumanMapNode &operator*() const { return *m_node; }
    RHHumanMapNode *operator->() const { return &**this; }
    bool operator==(const RHHumanMapIterator &other) const { return m_node == other.m_node; }
    bool operator!=(const RHHumanMapIterator &other) const { return !(*this == other); }
};

// SIZE 0x10
class RHHumanMap
{
public:
    RHHumanMapNode *FUN_00588060(const int &key);
    RHHumanMapIterator end() const { return RHHumanMapIterator(m_head); }
    RHHumanMapIterator find(const int &key)
    {
        RHHumanMapIterator position = FUN_00588060(key);
        return position == end() || key < position->m_key ? end() : position;
    }
    undefined m_00[4]; // 0x00
    RHHumanMapNode *m_head; // 0x04
    undefined4 m_08; // 0x08
    undefined4 m_0c; // 0x0c
};

// SIZE 0x74
class RHUnk00586f70
{
public:
    void FUN_00586f70(int key, undefined value);
    undefined FUN_005870c0(int key);
    undefined4 FUN_00587340(int key);
    undefined m_00[0x64]; // 0x00
    RHHumanMap m_64; // 0x64
};

class RHManagerListCalls
{
public:
    void FUN_0058bed0();
};

// SIZE 0x04
class RHUnk0058bed0Object
{
public:
    virtual ~RHUnk0058bed0Object() = 0; // vtable+0x00
};

class RHUnk0048c700
{
public:
    void FUN_0048c700(void *actor, int value);
};

// SIZE 0x4964
struct RHHumanEngineActorArray
{
    unsigned short Size() const
    {
        if (!m_first)
            return 0;
        return m_last - m_first;
    }
    undefined m_0000[0x495c]; // 0x0000
    RHUnk0048c700 **m_first; // 0x495c
    RHUnk0048c700 **m_last; // 0x4960
};

// SIZE 0x04
class RHHumanVirtualCalls
{
public:
    virtual void V000() = 0; // vtable+0x000
    virtual void V004() = 0; // vtable+0x004
    virtual void V008() = 0; // vtable+0x008
    virtual void V00c() = 0; // vtable+0x00c
    virtual void V010() = 0; // vtable+0x010
    virtual void V014() = 0; // vtable+0x014
    virtual void V018() = 0; // vtable+0x018
    virtual void V01c() = 0; // vtable+0x01c
    virtual void V020() = 0; // vtable+0x020
    virtual void V024(void *value) = 0; // vtable+0x024
    virtual void V028() = 0; // vtable+0x028
    virtual void V02c() = 0; // vtable+0x02c
    virtual void V030() = 0; // vtable+0x030
    virtual void V034() = 0; // vtable+0x034
    virtual void V038() = 0; // vtable+0x038
    virtual void V03c() = 0; // vtable+0x03c
    virtual void V040() = 0; // vtable+0x040
    virtual void V044() = 0; // vtable+0x044
    virtual bool V048() = 0; // vtable+0x048
    virtual void V04c() = 0; // vtable+0x04c
    virtual void V050() = 0; // vtable+0x050
    virtual void V054() = 0; // vtable+0x054
    virtual void V058() = 0; // vtable+0x058
    virtual void V05c() = 0; // vtable+0x05c
    virtual void V060() = 0; // vtable+0x060
    virtual void V064() = 0; // vtable+0x064
    virtual void V068() = 0; // vtable+0x068
    virtual void V06c() = 0; // vtable+0x06c
    virtual void V070() = 0; // vtable+0x070
    virtual void V074() = 0; // vtable+0x074
    virtual void V078() = 0; // vtable+0x078
    virtual void V07c() = 0; // vtable+0x07c
    virtual void V080() = 0; // vtable+0x080
    virtual void V084() = 0; // vtable+0x084
    virtual void V088() = 0; // vtable+0x088
    virtual void V08c() = 0; // vtable+0x08c
    virtual void V090() = 0; // vtable+0x090
    virtual void V094() = 0; // vtable+0x094
    virtual void V098() = 0; // vtable+0x098
    virtual void V09c() = 0; // vtable+0x09c
    virtual void V0a0() = 0; // vtable+0x0a0
    virtual void V0a4() = 0; // vtable+0x0a4
    virtual void V0a8() = 0; // vtable+0x0a8
    virtual void V0ac() = 0; // vtable+0x0ac
    virtual void V0b0() = 0; // vtable+0x0b0
    virtual void V0b4() = 0; // vtable+0x0b4
    virtual void V0b8() = 0; // vtable+0x0b8
    virtual void V0bc(unsigned value, void *actor) = 0; // vtable+0x0bc
    virtual void V0c0() = 0; // vtable+0x0c0
    virtual void V0c4() = 0; // vtable+0x0c4
    virtual void V0c8(int value, int amount) = 0; // vtable+0x0c8
    virtual void V0cc() = 0; // vtable+0x0cc
    virtual void V0d0() = 0; // vtable+0x0d0
    virtual void V0d4() = 0; // vtable+0x0d4
    virtual void V0d8(unsigned short value, void *actor) = 0; // vtable+0x0d8
    virtual void V0dc() = 0; // vtable+0x0dc
    virtual void V0e0() = 0; // vtable+0x0e0
    virtual void V0e4() = 0; // vtable+0x0e4
    virtual void V0e8() = 0; // vtable+0x0e8
    virtual void V0ec() = 0; // vtable+0x0ec
    virtual void V0f0() = 0; // vtable+0x0f0
    virtual void V0f4() = 0; // vtable+0x0f4
    virtual bool V0f8() = 0; // vtable+0x0f8
    virtual void V0fc() = 0; // vtable+0x0fc
    virtual void V100() = 0; // vtable+0x100
    virtual void V104() = 0; // vtable+0x104
    virtual void V108() = 0; // vtable+0x108
    virtual void V10c() = 0; // vtable+0x10c
    virtual void V110() = 0; // vtable+0x110
    virtual void V114() = 0; // vtable+0x114
    virtual void V118() = 0; // vtable+0x118
    virtual void V11c() = 0; // vtable+0x11c
    virtual void V120() = 0; // vtable+0x120
    virtual unsigned short V124() = 0; // vtable+0x124
    virtual void V128() = 0; // vtable+0x128
    virtual void V12c() = 0; // vtable+0x12c
    virtual int V130() = 0; // vtable+0x130
    virtual void V134() = 0; // vtable+0x134
    virtual void V138() = 0; // vtable+0x138
    virtual void V13c() = 0; // vtable+0x13c
    virtual void V140() = 0; // vtable+0x140
    virtual void V144() = 0; // vtable+0x144
    virtual void V148() = 0; // vtable+0x148
    virtual void V14c() = 0; // vtable+0x14c
    virtual void V150() = 0; // vtable+0x150
    virtual void V154() = 0; // vtable+0x154
    virtual void V158() = 0; // vtable+0x158
    virtual void V15c() = 0; // vtable+0x15c
    virtual void V160() = 0; // vtable+0x160
    virtual void V164() = 0; // vtable+0x164
    virtual bool V168() = 0; // vtable+0x168
};

// SIZE 0x0c
class RHUnk00613e90
{
public:
    RHUnk00613e90();
    float m_00; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float x, float y);
    ~SBGeoVector2D() {}
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    SBGeoPoint2D m_00; // 0x00
    SBGeoPoint2D m_08; // 0x08
    undefined m_10; // 0x10
};

// SIZE 0x294
class RHUnk0044d400
{
public:
    void FUN_0044d400(int value, bool propagate);
    void *Actor() { return RHActorField<void *>(this, m_00[1] + 4); }
    int *m_00; // 0x00
    undefined m_04[0x284]; // 0x04
    int m_288; // 0x288
    int m_28c; // 0x28c
    int m_290; // 0x290
};

class RHUnk0042fde0
{
public:
    SBGeoPoint2D FUN_0042fde0() const;
    float FUN_0060ba80(const SBGeoPoint2D &point) const;
};

// SIZE 0x0c
struct RHHumanFloatNode
{
    RHHumanFloatNode *next; // 0x00
    RHHumanFloatNode *previous; // 0x04
    float value; // 0x08
};
// SIZE 0x04
struct RHHumanFloatIterator
{
    RHHumanFloatIterator(RHHumanFloatNode *value) : node(value) {}
    RHHumanFloatNode *node; // 0x00
};
// SIZE 0x0c
class RHSeqList
{
public:
    RHSeqList(const char &allocator);
    undefined m_00[4]; // 0x00
    RHHumanFloatNode *m_head; // 0x04
    unsigned m_count; // 0x08
};
class RHCampaignMissionList
{
public:
    void FUN_004e6c10();
};
class RHUnk004e52a0
{
public:
    void FUN_004e52a0();
};
// SIZE 0x18
class RHHumanFloatList : public RHSeqList
{
public:
    RHHumanFloatList(const char &allocator) : RHSeqList(allocator), valid(1) {}
    ~RHHumanFloatList()
    {
        if (m_head)
        {
            ((RHCampaignMissionList *)this)->FUN_004e6c10();
            ((RHUnk004e52a0 *)this)->FUN_004e52a0();
        }
    }
    RHHumanFloatIterator FUN_00424410(RHHumanFloatIterator position, const float &value);
    RHHumanFloatIterator FUN_0044e8b0(RHHumanFloatIterator first, RHHumanFloatIterator last);
    RHHumanFloatIterator FUN_0046eb80();
    void At(int index);
    void Release()
    {
        FUN_0044e8b0(RHHumanFloatIterator(m_head->next), RHHumanFloatIterator(m_head));
        ::operator delete(m_head);
        m_head = 0;
        m_count = 0;
    }
    RHHumanFloatNode *cursor; // 0x0c
    undefined valid; // 0x10
    undefined m_11[3]; // 0x11
    int index; // 0x14
};

SBGeoPoint2D FUN_005fc4f0(float factor, const SBGeoPoint2D &point);

class RHHumanActorCalls
{
public:
    void FUN_00479320(RHUnk00613e90 &point);
    int FUN_0047b8a0(const RHUnk00613e90 &point, int *value, bool mode);
    void FUN_0047d270(void *actor);
    void FUN_0049d780();
    void FUN_0047d4c0();
    SBGeoPoint2D FUN_004237d0();
};

class RHScriptBatchCalls
{
public:
    void Unk0040d980(int state);
    void Unk0058a940(void *context, int value, void *element);
};

class RHUnk0047ca50
{
public:
    void Unk();
};

// SIZE 0x74
class RHUnk005866a0
{
public:
    RHUnk005866a0(unsigned short level, int command, void *actor);
    ~RHUnk005866a0();
    void Unk00586ed0(int property, int value);
    void Unk00586e00(int property, bool value);
    undefined m_00[0x74]; // 0x00
};

class RHHumanWeaponCalls
{
public:
    unsigned short FUN_005c1d70(int index);
    unsigned short FUN_005c1b70(void *actor, void *target, unsigned short value);
    unsigned short FUN_005c1db0(int index);
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

inline RHHumanOpponent &RHHumanOpponentAt(RHHumanList &list, int wanted)
{
    int size = list.count;
    if (list.valid)
    {
        std::bidirectional_iterator_tag category;
        if (wanted <= (size + 1) / 2)
            FUN_005c9010((RHUnk005c9010Iterator &)(list.cursor = list.head->next), wanted, category);
        else
            FUN_005c9010((RHUnk005c9010Iterator &)(list.cursor = list.head), wanted - size, category);
        list.valid = 0;
        list.index = wanted;
    }
    else
    {
        int previous = list.index;
        if (wanted != previous)
        {
            std::bidirectional_iterator_tag category;
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                    FUN_005c9010((RHUnk005c9010Iterator &)(list.cursor = ((RHUnk0046eb30 *)&list)->FUN_0046eb80().node), wanted, category);
                else
                    FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted - previous, category);
            }
            else if (wanted < (previous + size) / 2)
                FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted - previous, category);
            else
                FUN_005c9010((RHUnk005c9010Iterator &)(list.cursor = list.head), wanted - size, category);
            list.index = wanted;
        }
    }
    return ((RHHumanOpponentNode *)list.cursor)->value;
}

// SIZE 0x18
struct RHSoundSettings
{
    RHSoundSettings();
    ~RHSoundSettings() { ((SBGeoPoint2D *)m_04)->~SBGeoPoint2D(); }
    int m_00; // 0x00
    undefined m_04[8]; // 0x04
    void *m_0c; // 0x0c
    undefined m_10[4]; // 0x10
    void *m_14; // 0x14
};
// SIZE 0x20
struct RHSoundChannelSettings
{
    float m_00; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    unsigned short m_0c; // 0x0c
    unsigned short m_0e; // 0x0e
    unsigned short m_10; // 0x10
    unsigned short m_12; // 0x12
    float m_14[3]; // 0x14
};
class RHSoundGeometryView
{
public:
    bool FUN_005b2ff0(const RHSoundSettings &sound, bool mode, RHSoundChannelSettings &settings);
};
class RHSound
{
public:
    int FUN_005a72c0(const RHSoundSettings &sound, RHSoundChannelSettings &settings, unsigned position);
    bool FUN_005a8220(int first, int second, int third, const SBGeoPoint2D &point);
    bool FUN_005a8330(int first, int second, int third, const SBGeoPoint2D &point);
};

#endif
