#ifndef RHSHADOWPOOLLIFETIME_H
#define RHSHADOWPOOLLIFETIME_H

class RHUnk004e3fd0List
{
public:
    RHUnk004e3fd0List *m_next;
    RHUnk004e3fd0List *m_prev;
    char m_08[8];
};

class RHUnk004e3fd0
{
public:
    RHUnk004e3fd0(const char *value);
    char m_0;
    char m_1[3];
    RHUnk004e3fd0List *m_4;
    int m_8;
};

class RHUnk0059f900List
{
public:
    RHUnk0059f900List *m_next;
    RHUnk0059f900List *m_prev;
    char m_08[8];
};

class RHUnk0059f900
{
public:
    RHUnk0059f900();
    char m_0;
    char m_1[3];
    RHUnk0059f900List *m_4;
    int m_8;
    char m_c[4];
    bool m_10;
};

#endif
