#ifndef RHMESSAGE_H
#define RHMESSAGE_H

class RHMessage
{
public:
    RHMessage(int type, int value);
    RHMessage(int type);
    ~RHMessage();
    void *FUN_00549050(unsigned flags);
    unsigned m_vptr;
    int m_type;
    int m_value;
};

#endif
