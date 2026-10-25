#ifndef RHRECONNAISSANCEREPORT_H
#define RHRECONNAISSANCEREPORT_H
#include "RHSectorActorList.h"

#include "RHOrder.h"

struct RHTitbitNode;
class RHTitbitList
{
public:
    void Clear(void *out, RHTitbitNode *first, RHTitbitNode *last);
    __forceinline void At(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
};

struct RHReconnaissanceNode
{
    RHReconnaissanceNode *m_next;
    RHReconnaissanceNode *m_prev;
    RHElement *m_data;
};

class RHReconnaissanceList
{
public:
    char m_pad0[4];
    RHReconnaissanceNode *m_head; // +0x04
    unsigned m_count; // +0x08
    RHReconnaissanceNode *m_cur; // +0x0c
    char m_valid; // +0x10
    char m_pad11[3];
    int m_index; // +0x14

    RHUnkIter end() { return RHUnkIter(m_head); }
    RHUnkIter begin() { return RHUnkIter(m_head->m_next); }
    RHUnkIter erase(RHUnkIter first, RHUnkIter last)
    {
        typedef RHUnkIter (RHTitbitList::*Erase)(RHUnkIter, RHUnkIter);
        return (((RHTitbitList *)this)->*(Erase)&RHTitbitList::Clear)(first, last);
    }
    void clear()
    {
        erase(begin(), end());
        m_valid = 1;
    }
    void push_back(RHElement *value)
    {
        RHUnkIter result = ((RHUnkList *)this)->insert(end(), (RHOrder *const &)value);
        m_valid = 1;
    }
    RHElement *operator[](unsigned index)
    {
        ((RHTitbitList *)this)->At(index);
        return m_cur->m_data;
    }
};

class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &file, void *&value);
};
struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

class RHReconnaissanceEngine
{
public:
    bool Unk004c3cb0(SBFile &file, void *&value);
};

class RHReconnaissanceReport
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    char m_0[8]; // +0x00
    void *m_8; // +0x08
    int m_c; // +0x0c
    int m_10; // +0x10
    RHReconnaissanceList m_14; // +0x14
    char m_pad2c[0xc];
    void *m_38; // +0x38
    char m_3c; // +0x3c
};

#endif
