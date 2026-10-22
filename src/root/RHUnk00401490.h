#ifndef RHUNK00401490_H
#define RHUNK00401490_H

#include <string>
#include <vector>

typedef std::vector<std::vector<std::string> > RHUnk00401490Table;

class RHUnk00401490
{
public:
    RHUnk00401490();
    void *FUN_004014b0(unsigned flags);
    ~RHUnk00401490();
    void FUN_00401550(const char *name);
    void FUN_00401b10();
    unsigned m_vptr;
    RHUnk00401490Table m_4;
};

class RHUnk00401a00
{
public:
    int FUN_00401a30();
    int FUN_00401a50(int index);
    int FUN_00401a80(int i, int j);
    int m_0;
    int m_4;
    unsigned char *m_8;
    unsigned char *m_c;
};

int FUN_00401aa0(const std::vector<std::string> &values);

class RHUnk00402d60
{
public:
    void *FUN_00402d60(unsigned flags);
    char m_0[4];
    char *m_4;
    char *m_8;
    char *m_c;
};

#endif
