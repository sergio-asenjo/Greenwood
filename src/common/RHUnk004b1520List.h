#ifndef RHUNK004B1520LIST_H
#define RHUNK004B1520LIST_H

#include "RHScriptListCore.h"

struct RHUnk004b1520List
{
    char m_00[4];
    RHScriptNode *m_04;
    int m_08;
    RHScriptIter m_0c;
    bool m_10;
    int m_14;
    RHScriptIter end() { return RHScriptIter(m_04); }
    RHScriptIter FUN_00424410(RHScriptIter position, void *const &value);
};

#endif
