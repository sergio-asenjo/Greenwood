#ifndef RHELEMENTACTORNPC_CALLS_H
#define RHELEMENTACTORNPC_CALLS_H

#include "SB.h"
#include "RHElementActorNPC.h"

void RHSerializeName(SBFile &file, const char *name);
bool FUN_00416b30(void *&value, SBFile &file);

class RHEngine
{
public:
    bool SerializeNestedA(SBFile &file, void *storage);
    bool FUN_004c4490(SBFile &file, void *&value);
};
extern RHEngine *g_pEngine;

struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &file, void *&value);
};

class SBGeoPoint2D
{
public:
    bool Serialize(SBFile &file);
    float m_x;
    float m_y;
};

class RHArtificialIntelligence
{
public:
    bool Unk00414be0(SBFile &file);
};

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

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *prev;
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
};
struct RHSectorActorNode;
class RHSectorActorIter
{
public:
    RHSectorActorNode *m_p;
    RHSectorActorIter(RHSectorActorNode *node) : m_p(node) {}
    RHSectorActorIter operator++(int);
};

struct RHNPCDetectableList : public RHPathHistoryList
{
    char m_18[0x1c];
};

#endif
