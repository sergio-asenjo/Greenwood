#include "SBNullstr.h"
#include "RHSequenceElementDamage.h"

class RHUnk00584d60
{
public:
    RHUnk00584d60(unsigned short level, int command, void *actor);
    ~RHUnk00584d60();
    char m_00[4];
    unsigned char m_04;
    char m_05[0x0b];
    int m_10;
    unsigned short m_14;
    char m_16[0x32];
    void *m_48;
    char m_4c[0x18];
};

class RHSequenceElementCalls
{
public:
    void FUN_00585df0(RHSequenceElementCalls *other);
};

class RHUnk586050
{
public:
    RHUnk586050();
    char m_00[4];
    unsigned char m_04;
    char m_05[0x5f];
    void *m_64;
    unsigned short m_68;
    unsigned short m_6a;
    char m_6c;
    char m_6d[3];
    RHSword *m_70;
    int m_74;
    void *m_78;
};

class RHUnk005861c0 : public RHUnk00584d60
{
public:
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target);
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target, unsigned short value68, unsigned short value6a);
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target, void *value78, unsigned short value68);
    RHUnk005861c0(unsigned short level, int command, void *actor, unsigned short value68, unsigned short value6a);
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target, unsigned short value6a, int style);
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target, RHSword *sword, int value74);
    ~RHUnk005861c0();
    void *FUN_00586090(unsigned int flags);
    RHUnk005861c0 *FUN_005862c0();
    void *m_64;
    unsigned short m_68;
    unsigned short m_6a;
    char m_6c;
    char m_6d[3];
    RHSword *m_70;
    int m_74;
    void *m_78;
};

// FUNCTION: GAME 0x00586050
RHUnk586050::RHUnk586050()
{
    ((RHSequenceElement *)this)->RHSequenceElement::RHSequenceElement();
    m_74 = 11;
    m_64 = 0;
    m_68 = 0;
    m_6a = 0;
    m_6c = 0;
    m_70 = 0;
    m_78 = 0;
    *(unsigned *)this = 0x679d30;
    m_04 = 1;
}

// FUNCTION: GAME 0x00586090
void *RHUnk005861c0::FUN_00586090(unsigned int flags)
{
    this->~RHUnk005861c0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005860b0
RHUnk005861c0::RHUnk005861c0(unsigned short level, int command, void *actor, void *target)
    : RHUnk00584d60(level, command, actor)
{
    m_74 = 11;
    m_64 = target;
    m_68 = 0;
    m_6a = 0;
    m_6c = 0;
    m_70 = 0;
    m_78 = 0;
    *(unsigned *)this = 0x679d30;
    m_04 = 1;
}

// FUNCTION: GAME 0x00586100
RHUnk005861c0::RHUnk005861c0(unsigned short level, int command, void *actor, void *target, unsigned short value68, unsigned short value6a)
    : RHUnk00584d60(level, command, actor)
{
    m_64 = target;
    m_68 = value68;
    m_6a = value6a;
    m_6c = 0;
    m_70 = 0;
    m_74 = 11;
    m_78 = 0;
    *(unsigned *)this = 0x679d30;
    m_04 = 1;
}

// FUNCTION: GAME 0x00586160
RHUnk005861c0::RHUnk005861c0(unsigned short level, int command, void *actor, void *target, void *value78, unsigned short value68)
    : RHUnk00584d60(level, command, actor)
{
    m_64 = target;
    m_68 = value68;
    m_6a = 0;
    m_6c = 0;
    m_70 = 0;
    m_74 = 11;
    m_78 = value78;
    *(unsigned *)this = 0x679d30;
    m_04 = 1;
}

// FUNCTION: GAME 0x005861c0
RHUnk005861c0::RHUnk005861c0(unsigned short level, int command, void *actor, unsigned short value68, unsigned short value6a)
    : RHUnk00584d60(level, command, actor)
{
    m_64 = 0;
    m_68 = value68;
    m_6a = value6a;
    m_6c = 0;
    m_70 = 0;
    m_74 = 11;
    m_78 = 0;
    *(unsigned *)this = 0x679d30;
    m_04 = 1;
}

// FUNCTION: GAME 0x00586210
RHUnk005861c0::RHUnk005861c0(unsigned short level, int command, void *actor, void *target, unsigned short value6a, int style)
    : RHUnk00584d60(level, command, actor)
{
    m_64 = target;
    m_68 = 0;
    m_6a = value6a;
    m_6c = style == 3;
    m_70 = 0;
    m_74 = 11;
    m_78 = 0;
    *(unsigned *)this = 0x679d30;
    m_04 = 1;
}

// FUNCTION: GAME 0x00586270
RHUnk005861c0::RHUnk005861c0(unsigned short level, int command, void *actor, void *target, RHSword *sword, int value74)
    : RHUnk00584d60(level, command, actor)
{
    m_64 = target;
    m_68 = 0;
    m_6a = 0;
    m_6c = 0;
    m_70 = sword;
    m_74 = value74;
    m_78 = 0;
    *(unsigned *)this = 0x679d30;
    m_04 = 1;
}

// FUNCTION: GAME 0x005862c0
RHUnk005861c0 *RHUnk005861c0::FUN_005862c0()
{
    RHUnk005861c0 *copy = new RHUnk005861c0(m_14, m_10, m_48, m_64, m_70, m_74);
    ((RHSequenceElementCalls *)copy)->FUN_00585df0((RHSequenceElementCalls *)this);
    copy->m_6c = m_6c;
    copy->m_74 = m_74;
    copy->m_6a = m_6a;
    copy->m_68 = m_68;
    copy->m_64 = m_64;
    copy->m_70 = m_70;
    copy->m_78 = m_78;
    return copy;
}

// FUNCTION: GAME 0x00586370
bool RHSequenceElementDamage::Serialize(SBFile &file, bool pointers)
{
    FUN_00584ef0(file, pointers);
    if (file.Access(&m_6c, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0,
                 // STRING: GAME 0x006b7524
                 "P:\\Robin Hood\\RHSequenceElementDamage.cpp",
                 304, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_74, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHSequenceElementDamage.cpp", 305,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_6a, 2) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHSequenceElementDamage.cpp", 306,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_68, 2) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHSequenceElementDamage.cpp", 307,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    g_pEngine->SerializeElementPointer(file, *(RHElement **)(&m_64));
    RHSword::SerializePointer(file, m_70);
    g_pEngine->FUN_004c41f0(file, m_78);
    return true;
}

void RHSequenceElementDamage::Emit(SBFile &file, bool pointers)
{
    Serialize(file, pointers);
}
