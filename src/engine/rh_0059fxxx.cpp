// Anonymous cluster at 0x0059fxxx (list-node ctors).
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

class RHUnk0059f6f0List
{
public:
    RHUnk0059f6f0List *m_next;
    RHUnk0059f6f0List *m_prev;
    char m_08[0x08];
};

class RHUnk0059f6f0
{
public:
    RHUnk0059f6f0();
    char m_0[4];
    char m_4;
    char m_5[3];
    RHUnk0059f6f0List *m_8;
    int m_c;
    char m_10[4];
    bool m_14;
};

// FUNCTION: GAME 0x0059f6f0
RHUnk0059f6f0::RHUnk0059f6f0()
{
    char value;
    m_4 = value;
    RHUnk0059f6f0List *list = new RHUnk0059f6f0List;
    list->m_next = list;
    list->m_prev = list;
    m_8 = list;
    m_c = 0;
    m_14 = 1;
}

class RHUnk0059f900List
{
public:
    RHUnk0059f900List *m_next;
    RHUnk0059f900List *m_prev;
    char m_08[0x08];
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

// FUNCTION: GAME 0x0059f900
RHUnk0059f900::RHUnk0059f900()
{
    char value;
    m_0 = value;
    RHUnk0059f900List *list = new RHUnk0059f900List;
    list->m_next = list;
    list->m_prev = list;
    m_4 = list;
    m_8 = 0;
    m_10 = 1;
}

class RHUnk0059fae0
{
public:
    RHUnk0059fae0();
    char m_0;
    char m_1[3];
    int m_4;
    int m_8;
    int m_c;
    char m_10[4];
    bool m_14;
};

// FUNCTION: GAME 0x0059fae0
RHUnk0059fae0::RHUnk0059fae0()
{
    char value;
    m_0 = value;
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
    m_14 = 1;
}
