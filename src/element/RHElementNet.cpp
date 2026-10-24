#include "SBNullstr.h"
#include "RHElementNet.h"
#include "RHPCActionQueryCalls.h"
#include <new>

class RHSprite
{
public:
    bool FUN_005b9e30(void *first, void *second, bool third);
};

class RHNetVictimCalls
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30();
    virtual void V34();
    virtual void V38();
    virtual void V3c();
    virtual void V40();
    virtual void V44(int state);
    virtual bool V48();
};

class RHUnk0046bcb0
{
public:
    void Unk(int value);
};

class RHScriptBatchCalls
{
public:
    void Unk00464630();
    void Unk0040d980(int state);
};

class RHBonusInfo
{
public:
    void FUN_005bd560(void *value, bool flag);
};

class RHElementActorNPC
{
public:
    static void FUN_0048c6a0(void *actor, unsigned mode);
};

class RHMobileUnk00520c50
{
public:
    void FUN_00520c50(float first, float second);
};

inline void RHNetCopyPosition(float *destination, const char *sprite)
{
    float y = *(const float *)(sprite + 0x28);
    float x = *(const float *)(sprite + 0x24);
    destination[0] = x;
    destination[1] = y;
}

inline void RHNetPushRepulsivePoint(RHNetListStorage &list, void *point)
{
    RHScriptNode *next = list.m_04;
    RHScriptNode *previous = next->previous;
    RHScriptNode *node = (RHScriptNode *)operator new(sizeof(RHScriptNode));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    new (&node->data) void *(point);
    ++list.m_08;
    list.m_10 = true;
}

inline RHScriptNode *&RHNetSetCursor(RHNetListStorage &list, RHScriptIter iterator)
{
    list.m_0c = iterator.node;
    return list.m_0c;
}

inline void RHNetGoTo(RHNetListStorage &list, int wanted)
{
    int size = list.m_08;
    if (list.m_10)
    {
        if (wanted <= (size + 1) / 2)
        {
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)RHNetSetCursor(list, RHScriptIter(list.m_04->next)), wanted, category);
        }
        else
        {
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)RHNetSetCursor(list, RHScriptIter(list.m_04)), wanted - size, category);
        }
        list.m_10 = false;
        list.m_14 = wanted;
    }
    else
    {
        int previous = list.m_14;
        if (wanted != previous)
        {
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    RHScriptIter &cursor = (RHScriptIter &)list.m_0c;
                    cursor = ((RHUnk0046eb30 *)&list)->FUN_0046eb80();
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)list.m_0c, wanted - previous, category);
                }
            }
            else if (wanted < (previous + size) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)list.m_0c, wanted - previous, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)RHNetSetCursor(list, RHScriptIter(list.m_04)), wanted - size, category);
            }
            list.m_14 = wanted;
        }
    }
}

DECOMP_SIZE_ASSERT(RHElementNet, 0x1c8)
DECOMP_SIZE_ASSERT(RHNetListStorage, 0x18)
DECOMP_SIZE_ASSERT(RHUnk005209d0, 0x14)
DECOMP_SIZE_ASSERT(RHUnk00520ae0, 0x40)

// FUNCTION: GAME 0x004b07c0
RHElementNet::RHElementNet(void *victim) : RHProjectileLifetime(0x11, victim)
{
    *(unsigned long *)this = 0x006785dc;
    *(unsigned long *)((char *)this + 0xb0) = 9;
}

// FUNCTION: GAME 0x004b0860
void *RHElementNet::FUN_004b0860(unsigned flags)
{
    this->~RHElementNet();
    if (flags & 1)
        operator delete(this);
    return this;
}

// STUB: GAME 0x004b0880
RHElementNet::~RHElementNet()
{
    RHScriptNode *head = m_19c.m_04;
    RHScriptNode *node = head->next;
    while (node != head)
    {
        RHScriptNode *erased = node;
        node = node->next;
        erased->previous->next = erased->next;
        erased->next->previous = erased->previous;
        operator delete(erased);
        --m_19c.m_08;
    }
}

// FUNCTION: GAME 0x004b1270
void RHElementNet::FUN_004b1270()
{
    unsigned count = m_19c.m_08;
    for (unsigned index = 0; index < count; ++index)
    {
        RHNetListStorage &list = m_19c;
        ((RHTitbitList *)&list)->At(index);
        char *victim = (char *)list.m_0c->data;
        if (--*(short *)(victim + 0x23c) == 0)
        {
            if (*(int *)(*(char **)(victim + 0x50) + 0x8c) == 0x11)
                ((RHNetVictimCalls *)victim)->V44(3);
            ((RHUnk0046bcb0 *)victim)->Unk(5);
            ((RHScriptBatchCalls *)victim)->Unk00464630();
            (*(RHBonusInfo **)(victim + 0x50))->FUN_005bd560(0, true);
            if ((*(unsigned *)(victim + 4) & 0xf) == 4)
            {
                ((RHScriptBatchCalls *)(victim + 0x49c + (*(int **)(victim + 0x49c))[1]))->Unk0040d980(0x1e);
                if (!((RHNetVictimCalls *)victim)->V48() && !*(victim + 0x1ce))
                    RHElementActorNPC::FUN_0048c6a0(victim, 1);
            }
        }
    }
    RHScriptNode *head = m_19c.m_04;
    RHScriptNode *node = head->next;
    while (node != head)
    {
        RHScriptNode *erased = node;
        node = node->next;
        erased->previous->next = erased->next;
        erased->next->previous = erased->previous;
        operator delete(erased);
        --m_19c.m_08;
    }
    m_19c.m_10 = true;
}

// FUNCTION: GAME 0x004b1380
void RHElementNet::FUN_004b1380(RHNetListStorage &points, RHNetListStorage &, void *)
{
    if (!*((char *)this + 0x132) && !m_1c4 && m_19c.m_08)
    {
        RHNetCopyPosition((float *)((char *)this + 0xc0), *(const char **)((char *)this + 0x50));
        RHNetCopyPosition((float *)((char *)&m_15c + 4), *(const char **)((char *)this + 0x50));
        RHMobileUnk00520c50 *outer = (RHMobileUnk00520c50 *)((char *)this + 0xbc);
        outer->FUN_00520c50(40.0f, 15.0f);
        RHMobileUnk00520c50 *inner = (RHMobileUnk00520c50 *)&m_15c;
        inner->FUN_00520c50(15.0f, 30.0f);
        RHNetPushRepulsivePoint(points, outer);
        RHNetPushRepulsivePoint(points, inner);
    }
}

// FUNCTION: GAME 0x004b14a0
bool RHElementNet::FUN_004b14a0(void *point, void *pc, int focus) const
{
    if (*((char *)this + 0x12) && pc &&
        *(unsigned short *)(*(char **)((char *)this + 0x50) + 0xde) != 0xffff &&
        *(unsigned int *)((char *)g_pEngine + 0x4a00) <= 1 && focus == 3)
        return !*((char *)this + 0x132) && ((RHUnk0049d4f0 *)pc)->Unk(0x11) &&
               (*(RHSprite **)((char *)this + 0x50))->FUN_005b9e30(point, *(void **)((char *)this + 0x54), false);
    return false;
}

// FUNCTION: GAME 0x004b1520
bool RHElementNet::Serialize(SBFile &file)
{
    ((RHElementProjectile *)this)->RHElementProjectile::Serialize(file);
    unsigned int count;
    void *value;
    if (file.m_bLoading)
    {
        RHNetListStorage &list = m_19c;
        list.FUN_0044e8b0(((RHUnk0046eb30 *)&list)->FUN_0046eb80(), list.end());
        list.m_10 = true;
        if (file.Access(&count, 2) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0,
                     // STRING: GAME 0x006aece4
                     "P:\\Robin Hood\\RHElementNet.cpp",
                     523, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned short index = 0; index < (unsigned short)count; ++index)
        {
            g_pEngine->FUN_004c3bd0(file, value);
            list.FUN_00424410(list.end(), value);
            list.m_10 = true;
        }
    }
    else
    {
        count = m_19c.m_08;
        if (file.Access(&count, 2) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHElementNet.cpp", 535,
                     "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned short index = 0; index < (unsigned short)count; ++index)
        {
            RHNetListStorage &list = m_19c;
            ((RHTitbitList *)&list)->At(index);
            value = list.m_0c->data;
            g_pEngine->FUN_004c3bd0(file, value);
        }
    }
    if (file.Access(&m_1c0, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementNet.cpp", 544,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_1c4, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementNet.cpp", 545,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_1c5, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementNet.cpp", 546,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x004b19d0
bool RHElementNet::FUN_004b19d0()
{
    unsigned count = m_19c.m_08;
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
    {
        RHNetListStorage &list = m_19c;
        RHNetGoTo(list, index);
        char *element = *(char **)((char *)list.m_0c->data + 0x134);
        if (element && *(int *)(element + 0x24) == 0x85)
            return true;
    }
    return false;
}

void RHElementNet::Emit(SBFile &file)
{
    FUN_004b0860(0);
    FUN_004b1270();
    FUN_004b19d0();
    FUN_004b1380(m_19c, m_19c, 0);
    FUN_004b14a0(0, 0, 0);
    RHElementNet::Serialize(file);
}
