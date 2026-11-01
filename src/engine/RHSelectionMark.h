#ifndef RHSELECTIONMARK_H
#define RHSELECTIONMARK_H

class RHSprite;
class RHUnk005ef320;
class RHUnkSpriteBank;

class RHUnk00581c40
{
public:
    RHUnk00581c40();
    ~RHUnk00581c40();
    void *FUN_00581c20(unsigned flags);
    unsigned long LoadFromResource();
    unsigned m_vptr;
    RHSprite *m_4;
    RHUnk005ef320 *m_8;
    RHUnkSpriteBank *m_c;
    unsigned m_10;
    int m_14;
    char m_18;
    char m_19;
    short m_1a;
};

#endif
