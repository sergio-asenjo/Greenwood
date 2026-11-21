#ifndef RHHUMANLISTCORE_H
#define RHHUMANLISTCORE_H

#include "Decomp.h"
#include "RHScriptListCore.h"

class RHUnkIter;

struct RHHumanList : RHUnk0046eb30
{
    RHScriptIter begin();
    RHScriptIter end();
    void Clear();
    void Insert(void *const &value);
    void InsertRepeated(RHUnkIter position, unsigned amount, void *const &value);
    void Resize(unsigned wanted, void *value);
};

#endif
