#ifndef RHPATCH_H
#define RHPATCH_H

#include "RHSector.h"
#include "RHEngine.h"
#include <list>

class RHPatchActorList
{
public:
    std::list<RHElementActor *> list;
    std::list<RHElementActor *>::iterator current;
    char valid;
    char padding11[3];
    int index;
    char searchValid;
    char padding19[3];
    int searchIndex;
    RHElementActor *searchValue;

    int Find(RHElementActor *actor)
    {
        int count = list.size();
        searchValue = actor;
        searchValid = 1;
        void *head = *(void **)((char *)&list + 4);
        void *first = *(void *volatile *)head;
        *(void **)&current = first;
        int wanted = 0;
        for (; wanted < count; ++wanted, current++)
            if (*current == searchValue)
                break;
        if (wanted < count)
        {
            searchIndex = wanted;
            valid = 0;
            index = wanted;
        }
        else
        {
            valid = 1;
            searchIndex = -1;
        }
        return searchIndex;
    }
};

class RHProfileFile
{
public:
    int FUN_005f5370(int offset, int origin);
};

class RHSequenceElement;
class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
};

struct RHScriptNode;
struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

class RHUnk0046eb30
{
public:
    RHScriptIter erase(RHScriptIter position);
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
};

struct RHTitbitNode;
class RHTitbitList
{
public:
    void Clear(void *result, RHTitbitNode *first, RHTitbitNode *last);
};

class RHPatchVirtualCalls
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16(SBFile &file);
};

class RHPatchDoorCalls
{
public:
    void FUN_0051b660();
};

class RHUnk0054f870
{
public:
    bool Unk0054f870(SBFile &file);
};

class RHPatch
{
public:
    bool Serialize(SBFile &file) { return ((RHUnk0054f870 *)this)->Unk0054f870(file); }
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
    void FUN_0054fe10();
    void FUN_00550070(bool mode);
    void FUN_00550150();
    void Emit(SBFile &file, RHElementActor *actor);

    char m_0; // +0x00
    char m_1;
    char m_2; // +0x02
    char padding3[8];
    char m_b; // +0x0b
    char m_c; // +0x0c
    char paddingd[11];
    RHPatchVirtualCalls *m_18; // +0x18, Serialize slot +0x40
    char padding1c[0x15c];
    RHPatchActorList m_178; // +0x178, head +0x17c, count +0x180
    char m_19c; // +0x19c
};

extern RHEngine *g_pEngine;

#endif
