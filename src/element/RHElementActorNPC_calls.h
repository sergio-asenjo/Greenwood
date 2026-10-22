#ifndef RHELEMENTACTORNPC_CALLS_H
#define RHELEMENTACTORNPC_CALLS_H

#include "RHSprite.h"

#include "RHElementActorNPC.h"

// SIZE 0x90
class RHNPCUnk004867d0
{
public:
    ~RHNPCUnk004867d0();
    char m_00[0x48];
    SBGeoPoint2D m_48; // 0x48
    SBGeoPoint2D m_50; // 0x50
    SBGeoPoint2D m_58; // 0x58
    SBGeoPoint2D m_60; // 0x60
    char m_68[0x28];
};

void RHSerializeName(SBFile &file, const char *name);
bool FUN_00416b30(void *&value, SBFile &file);

extern RHEngine *g_pEngine;

struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

#include "RHArtificialIntelligenceCore.h"

class RHNPCBaseCalls
{
public:
    bool FUN_004799e0(SBFile &file);
};

struct RHPathHistory
{
    int m_0;
    int m_4;
    void *m_8;
    int m_c;
    char m_10;
    char m_pad11;
    unsigned short m_12;
};
struct RHPathHistoryNode
{
    RHPathHistoryNode *m_next;
    RHPathHistoryNode *m_prev;
    RHPathHistory m_data;
};
void RHPathUnk0048f180(RHPathHistory *destination, const RHPathHistory *source);

class RHPathHistoryIter
{
public:
    RHPathHistoryNode *m_p;
    RHPathHistoryIter(RHPathHistoryNode *node) : m_p(node) {}
};

class RHTitbitList
{
public:
    void At(int index);
};

class RHPathHistoryList
{
public:
    int m_0;
    RHPathHistoryNode *m_head;
    int m_count;
    RHPathHistoryNode *m_cur;
    char m_valid;
    char m_pad11[3];
    int m_index;
    RHPathHistoryNode *Unk00551de0(RHPathHistoryNode *next, RHPathHistoryNode *previous);
    RHPathHistoryIter end() { return RHPathHistoryIter(m_head); }
    RHPathHistoryIter insert(RHPathHistoryIter position, const RHDetectable &value)
    {
        RHPathHistoryNode *node = position.m_p;
        node->m_prev = Unk00551de0(node, node->m_prev);
        node = node->m_prev;
        node->m_prev->m_next = node;
        RHPathUnk0048f180(&node->m_data, (const RHPathHistory *)&value);
        ++m_count;
        m_valid = 1;
        return RHPathHistoryIter(node);
    }
};

#include "RHScriptListCore.h"
#include "RHSectorActorIterator.h"

struct RHNPCDetectableList : public RHPathHistoryList
{
    RHNPCDetectableList();
    char m_18[0x1c];
};

class RHNPCActorCalls
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
    virtual void Vcc() = 0;
    virtual void Vd0() = 0;
    virtual void Vd4() = 0;
    virtual void Vd8() = 0;
    virtual void Vdc() = 0;
    virtual void Ve0() = 0;
    virtual void Ve4() = 0;
    virtual void Ve8() = 0;
    virtual void Vec() = 0;
    virtual void Vf0() = 0;
    virtual bool Vf4() = 0;
    virtual bool Vf8() = 0;
    virtual void Vfc() = 0;
    virtual void V100(int first, int second) = 0;
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
    virtual int V130() = 0; // vtable+0x130
};

#endif
