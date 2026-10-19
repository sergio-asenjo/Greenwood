#ifndef RHSEQUENCEGENERICCALLS_H
#define RHSEQUENCEGENERICCALLS_H

// VTABLE: GAME 0x00679cd8
// SIZE 0x64
class RHUnk00584d60
{
public:
    RHUnk00584d60();
    RHUnk00584d60(unsigned short level, int command, void *actor);
    ~RHUnk00584d60();
    virtual void FUN_00584d30();
    void SetFlag(bool value) { m_60 = value; }
    unsigned char m_04;  // 0x04
    char m_05[0x0b];     // 0x05
    int m_10;            // 0x10
    unsigned short m_14; // 0x14
    char m_16[0x32];     // 0x16
    void *m_48;          // 0x48
    char m_4c[0x14];     // 0x4c
    bool m_60;           // 0x60
    char m_61[3];        // 0x61
};

#endif
