#ifndef SCSERIALIZE_H
#define SCSERIALIZE_H

#include <stdio.h>

int SCSerializeUnk00643c56(FILE *);
FILE *SCSerializeUnk00643c43(const char *, const char *);
int SCSerializeUnk00642a2f(const char *, ...);

class SCSerializeUnkObject
{
public:
    virtual void FUN_00(unsigned int);
};

struct SCSerializeUnkNode
{
    SCSerializeUnkNode *m_next;
    SCSerializeUnkNode *m_previous;
    SCSerializeUnkObject *m_object;
};

class SCSerialize
{
public:
    FILE *m_00;
    char m_pad04[4];
    SCSerializeUnkNode *m_08;
    int m_0c;

    bool Destroy();
    bool OpenSCB(const char *, bool);
    bool CloseSCB();
    int ReadSCB();
    int Serialize(bool);
};

#endif
