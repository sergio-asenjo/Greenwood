#ifndef RHELEMENTPROJECTILE_H
#define RHELEMENTPROJECTILE_H
#include "RHSectorActorList.h"

#include "SB.h"
#include "RHEngine.h"
#include <iterator>

class RHElementObject
{
public:
    virtual bool Serialize(SBFile &file);
    char m_04[0xfc];
};

class RHUnk005df510
{
public:
    int m_0;
    int m_4;
    int m_8;
    bool Serialize(SBFile &file);
};

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    RHUnk005df510 m_00;
    short m_0c;
    char m_0e;
    char m_0f;
    int m_10;
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
    RHScriptIter begin();
    RHScriptIter FUN_0046eb80();
    RHScriptIter erase(RHScriptIter position);
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);
class RHSequenceElement;
class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
};

class RHTitbitList
{
public:
    __forceinline void At(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
};

struct RHProjectileList
{
    int m_00;
    RHScriptNode *m_head;
    int m_count;
    RHScriptIter m_cursor;
    char m_valid;
    char m_11[3];
    int m_index;

    RHScriptIter begin() { return ((RHUnk0046eb30 *)this)->begin(); }
    void Advance(int distance)
    {
        std::bidirectional_iterator_tag category;
        FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, distance, category);
    }
    void *&Get(int wanted)
    {
        int size = m_count;
        if (m_valid)
        {
            if (wanted <= (size + 1) / 2)
            {
                m_cursor = begin();
                Advance(wanted);
            }
            else
            {
                m_cursor = RHScriptIter(m_head);
                Advance(wanted - size);
            }
            m_valid = 0;
            m_index = wanted;
        }
        else
        {
            int previous = m_index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        m_cursor = begin();
                        Advance(wanted);
                    }
                    else
                        Advance(wanted - previous);
                }
                else if (wanted < (size + previous) / 2)
                    Advance(wanted - previous);
                else
                {
                    m_cursor = RHScriptIter(m_head);
                    Advance(wanted - size);
                }
                m_index = wanted;
            }
        }
        return m_cursor.node->data;
    }
    void Resize(int wanted)
    {
        void **value = new void *;
        if (wanted <= m_count)
        {
            int amount = m_count - wanted;
            while (amount > 0)
            {
                ((RHUnk0046eb30 *)this)->erase(RHScriptIter(m_head->previous));
                --amount;
            }
        }
        else
        {
            int amount = wanted - m_count;
            while (amount > 0)
            {
                RHScriptNode *position = m_head;
                RHScriptNode *node = ((RHUnk0046eb30 *)this)->Unk0059f720(position, position->previous);
                position->previous = node;
                node->previous->next = node;
                RHSeqList::CopyData((RHSequenceElement **)&node->data, (RHSequenceElement *const *)value);
                ++m_count;
                --amount;
            }
        }
        delete value;
        m_valid = 1;
    }
};

class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &file, void *&value);
};

extern RHEngine *g_pEngine;
void RHSerializeName(SBFile &file, const char *name);

class RHElementProjectile : public RHElementObject
{
public:
    virtual bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    void FUN_004b8230();
    void CopyTrajectory(RHElementProjectile *other);
    unsigned ComputeNumberOfFramesLeft() const;
    int FUN_004b8d70(void *first, void *second, void *third);
    int FUN_004b8da0() const;
    void PlayImpactSound(const void *position, bool special) const;

    RHUnk005df510 m_100; // [0x100]
    RHUnk005df510 m_10c; // [0x10c]
    char m_118[8]; // [0x118,0x120)
    void *m_120; // [0x120]
    char m_124[4];
    short m_128; // [0x128]
    char m_12a[2];
    void *m_12c; // [0x12c]
    short m_130; // [0x130]
    char m_132; // [0x132]
    char m_133; // [0x133]
    char m_134;
    char m_135; // [0x135]
    char m_136[2];
    RHProjectileList m_138; // [0x138,0x150)
    char m_150[12];
};

#endif
