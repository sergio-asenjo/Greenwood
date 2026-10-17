#ifndef SCSERIALIZE_H
#define SCSERIALIZE_H

#include <stdio.h>
#include "SB.h"
#include "RHCivilianProfile.h"
#include "RHArtificialIntelligence.h"

int SCSerializeUnk00643c56(FILE *);
extern "C" FILE *SCSerializeUnk00643c43(const char *, const char *);
int SCSerializeUnk00642a2f(const char *, ...);

// SIZE 0x0c
class SCSerializeUnkList
{
public:
    explicit SCSerializeUnkList(const std::allocator<char> &allocator = std::allocator<char>())
    {
        m_allocator = *(const char *)&allocator;
        m_head = ((RHUnk0046eb30 *)this)->Unk0059f720(0, 0);
        m_count = 0;
    }
    ~SCSerializeUnkList();
    char m_allocator; // 0x00
    RHScriptNode *m_head; // 0x04
    int m_count; // 0x08
};

// SIZE 0x0c
class SCSerializeUnkList00424340
{
public:
    explicit SCSerializeUnkList00424340(const std::allocator<char> &allocator = std::allocator<char>())
    {
        m_allocator = *(const char *)&allocator;
        m_head = ((RHArtificialIntelligenceStimulusList *)this)->Unk00424340(0, 0);
        m_count = 0;
    }
    ~SCSerializeUnkList00424340();
    char m_allocator; // 0x00
    RHArtificialIntelligenceStimulusNode *m_head; // 0x04
    int m_count; // 0x08
};

// SIZE 0x10
class SCSerializeUnkArray
{
public:
    explicit SCSerializeUnkArray(const std::allocator<char> &allocator = std::allocator<char>())
    {
        m_allocator = *(const char *)&allocator;
        m_first = 0;
        m_last = 0;
        m_end = 0;
    }
    ~SCSerializeUnkArray();
    char m_allocator; // 0x00
    void *m_first; // 0x04
    void *m_last; // 0x08
    void *m_end; // 0x0c
};

// SIZE 0x10
class RHUnk0059fba0
{
public:
    RHUnk0059fba0(const char &allocator);
    char m_00; // 0x00
    void *m_04; // 0x04
    void *m_08; // 0x08
    void *m_0c; // 0x0c
};

// SIZE 0x6c
// VTABLE: GAME 0x0067bbcc
class SCSerializeUnkObject
{
public:
    SCSerializeUnkObject() : m_5c((const char &)std::allocator<char>()) {}
    virtual ~SCSerializeUnkObject(); // vtable+0x00
    int FUN_0063a940(FILE *, bool);
    RHProfileText m_04; // 0x04
    RHProfileText m_14; // 0x14
    int m_24; // 0x24
    SCSerializeUnkList m_28; // 0x28
    SCSerializeUnkList m_34; // 0x34
    SCSerializeUnkList00424340 m_40; // 0x40
    SCSerializeUnkArray m_4c; // 0x4c
    RHUnk0059fba0 m_5c; // 0x5c
};

// SIZE 0x0c
struct SCSerializeUnkNode
{
    SCSerializeUnkNode *m_next; // 0x00
    SCSerializeUnkNode *m_previous; // 0x04
    SCSerializeUnkObject *m_object; // 0x08
};

// SIZE 0x10
class SCSerialize
{
public:
    FILE *m_00; // 0x00
    char m_pad04[4]; // 0x04
    SCSerializeUnkNode *m_08; // 0x08
    int m_0c; // 0x0c

    bool Destroy();
    bool OpenSCB(const char *, bool);
    bool CloseSCB();
    int ReadSCB();
    int Serialize(bool);
};

#endif
