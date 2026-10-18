#ifndef RHHUMANLISTCORE_H
#define RHHUMANLISTCORE_H

#include "Decomp.h"

struct RHScriptNode;
struct RHScriptIter;
class RHUnkIter;

struct RHHumanList
{
    undefined4 m_0;
    RHScriptNode *head;
    unsigned count;
    RHScriptNode *cursor;
    undefined valid;
    undefined m_11[3];
    int index;

    RHScriptIter begin();
    RHScriptIter end();
    void Clear();
    void Insert(void *const &value);
    void InsertRepeated(RHUnkIter position, unsigned amount, void *const &value);
    void Resize(unsigned wanted, void *value);
};

#endif
