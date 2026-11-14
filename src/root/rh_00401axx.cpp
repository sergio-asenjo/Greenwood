#include "SBNullstr.h"
#include <vector>
#include <string.h>
#include "RHUnk00401490.h"


// FUNCTION: GAME 0x00401a30
int RHUnk00401490::FUN_00401a30()
{
    return m_4.size();
}

// FUNCTION: GAME 0x00401a50
int RHUnk00401490::FUN_00401a50(int index)
{
    return m_4[index].size();
}

// FUNCTION: GAME 0x00401a80
std::string *RHUnk00401490::FUN_00401a80(int i, int j)
{
    return &m_4[i][j];
}

// FUNCTION: GAME 0x00401aa0
int FUN_00401aa0(const std::vector<std::string> &values)
{
    if (!values.empty() && strcmp(values[0].c_str(), "") != 0)
        return 0;
    return 1;
}

void EmitRHUnk00401a00(RHUnk00401490 *object)
{
    object->FUN_00401a30();
    object->FUN_00401a50(0);
    object->FUN_00401a80(0, 0);
}

// FUNCTION: GAME 0x00402d60
void *RHUnk00402d60::FUN_00402d60(unsigned flags)
{
    char *last = m_8;
    char *first = m_4;
    while (first != last)
    {
        ((std::string *)first)->~basic_string();
        first += 0x10;
    }
    operator delete(m_4);
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
    if (flags & 1)
        operator delete(this);
    return this;
}
