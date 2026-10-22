#ifndef RHSEQUENCEELEMENTCALLS_H
#define RHSEQUENCEELEMENTCALLS_H

class RHSequenceElementCalls
{
public:
    virtual void Slot00() = 0;
    virtual void Slot04() = 0;
    virtual void Slot08() = 0;
    virtual void Slot0c(int state, int value) = 0;
    virtual void Slot10(int priority) = 0;
    virtual void FUN_00585d00();
    virtual void FUN_00585c80();
    virtual void FUN_00585d40();
    virtual void FUN_00585e30();
    virtual void FUN_00585cc0(int value);
    void FUN_00585320(int state, int value);
    void FUN_00585450(int priority);
    void FUN_00585570();
    void FUN_00585940(RHSequenceElementCalls *other);
    bool FUN_00585b70();
    RHSequenceElementCalls *FUN_00585d80();
    void FUN_00585df0(RHSequenceElementCalls *other);
    void Emit(int value, RHSequenceElementCalls *other);

    char m_04[0x0c];
    int m_10;
    char m_14[0x28];
    int m_3c;
    int m_40;
    int m_44;
    void *m_48;
    RHSequenceElementCalls *m_4c;
    RHSequenceElementCalls *m_50;
    void *m_54;
    int m_58;
    int m_5c;
    int m_60;
};

#endif
