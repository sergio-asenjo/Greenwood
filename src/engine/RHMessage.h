#ifndef RHMESSAGE_H
#define RHMESSAGE_H

// VTABLE: GAME 0x00679b60
class RHMessage
{
public:
    RHMessage(int type, int value);
    RHMessage(int type);
    ~RHMessage();
    virtual void *FUN_00549050(unsigned flags);
    int m_type;
    int m_value;
};

#endif
