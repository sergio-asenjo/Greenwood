#ifndef RHUNK0059FAE0_H
#define RHUNK0059FAE0_H

#include <vector>

class RHScriptFXArray;

class RHUnk0059fae0Storage
{
public:
    RHUnk0059fae0Storage(const std::allocator<unsigned long> &allocator = std::allocator<unsigned long>())
        : m_0(allocator), m_4(0), m_8(0), m_c(0) {}
    inline ~RHUnk0059fae0Storage();
    std::allocator<unsigned long> m_0;
    char m_1[3];
    unsigned long *m_4;
    unsigned long *m_8;
    unsigned long *m_c;
};

// SIZE 0x20
class RHUnk0059fae0
{
public:
    RHUnk0059fae0();
    ~RHUnk0059fae0()
    {
        typedef std::vector<int> Values;
        int *(Values::*erase)(int *, int *) = &Values::erase;
        (((Values *)&m_values)->*erase)((int *)m_values.m_4, (int *)m_values.m_8);
    }
    RHUnk0059fae0Storage m_values;
    char m_10[4];
    bool m_14;
    char m_15[0x0b];
};

#endif
