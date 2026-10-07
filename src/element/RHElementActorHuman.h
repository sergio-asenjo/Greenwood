#ifndef RHELEMENTACTORHUMAN_H
#define RHELEMENTACTORHUMAN_H

#include "SB.h"
#include <new>
#include <list>
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
class RHElementActor
{
public:
    virtual bool Serialize(SBFile &file);
    void Translate(RHSequenceElement *element, RHcommand command);
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
    ~SBGeoPoint2D();
    float m_0;
    float m_4;
};

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    ~RHUnk005fc3b0() {}
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
struct RHHumanOpponent
{
    void *m_actor;
    void *m_line;
};
struct RHHumanOpponentNode
{
    RHHumanOpponentNode *next;
    RHHumanOpponentNode *previous;
    RHHumanOpponent value;
};
struct RHHumanOpponentIterator
{
    RHHumanOpponentNode *node;
    RHHumanOpponentIterator(RHHumanOpponentNode *value) : node(value) {}
};
class RHHumanOpponentListCalls
{
public:
    RHHumanOpponentIterator FUN_00486110(RHHumanOpponentIterator position, const RHHumanOpponent &value);
};
struct RHHumanList
{
    int m_0;
    RHScriptNode *head;
    unsigned count;
    RHScriptNode *cursor;
    char valid;
    char m_11[3];
    int index;

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

class RHElementActorHuman
{
public:
    void Translate(RHSequenceElement *element, RHcommand command);
    bool Serialize(SBFile &file);
    void Emit(SBFile &file, RHSequenceElement *element, RHcommand command);

    char m_000[0x1b8]; // +0x50: position owner; +0x5c: sequence manager; +0x64: grid; +0x144: action state.
    RHHumanList m_1b8; // +0x1b8: sequence pointer list; head +0x1bc, count +0x1c0.
    char m_1d0[0x1c]; // +0x1d0: serialized 28-byte block.
    char m_1ec[0x20];
    RHHumanList m_20c; // +0x20c: actor pointer list; cursor +0x218, dirty +0x21c.
    char m_224[0xc];
    int m_230;
    int m_234;
    int m_238;
    short m_23c;
    char m_23e;
    char m_23f;
    short m_240[9]; // +0x240: nine serialized words.
    char m_252[2];
    void *m_254;
    char m_258[8];
    RHHumanList m_260; // +0x260: 8-byte opponent records; count +0x268, cursor +0x26c.
    char m_278[0x10];
    char m_288;
    char m_289;
    short m_28a;
    int m_28c;
    void *m_290;
    char m_294[0x1a8]; // +0x294: sight-obstacle serializer receiver.
    char m_43c[0x40]; // +0x43c: nested serializer receiver.
    char m_47c;
    char m_47d[3];
    int m_480;
    int m_484;
    short m_488;
    char m_48a;
    char m_48b;
    int m_48c;
    char m_490;
    char m_491;
    short m_492;
    short m_494;
    char m_496;
    char m_497;
    void *m_498;
};

#endif
