#ifndef RHELEMENTNET_H
#define RHELEMENTNET_H

#include "SB.h"
#include "RHEngine.h"
#include <iterator>

class RHElementProjectile
{
public:
    virtual bool Serialize(SBFile &file);
    char m_04[0x158];
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
    RHScriptIter() {}
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

class RHUnk0046eb30
{
public:
    RHScriptIter begin();
};

struct RHUnk004b1520List
{
    char m_00[4];
    RHScriptNode *m_04;
    int m_08;
    RHScriptIter m_0c;
    bool m_10;
    int m_14;

    RHScriptIter end() { return RHScriptIter(m_04); }
    RHScriptIter FUN_0044e8b0(RHScriptIter first, RHScriptIter last);
    RHScriptIter FUN_00424410(RHScriptIter position, void *const &value);
};

class RHTitbitList
{
public:
    void At(int index);
};

class RHElementNet : public RHElementProjectile
{
public:
    virtual bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    char m_15c[0x40];
    RHUnk004b1520List m_19c;
    char m_1b4[0x0c];
    int m_1c0;
    char m_1c4;
    char m_1c5;
};

#endif
