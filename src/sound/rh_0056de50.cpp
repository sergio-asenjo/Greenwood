// Anonymous cluster at 0x0056de50.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

class RHUnk0056de50List
{
public:
    RHUnk0056de50List *m_next;
    RHUnk0056de50List *m_prev;
    char m_08[0x04];
};

class RHUnk0056de50
{
public:
    RHUnk0056de50();
    int m_0;
    int m_4;
    int m_8;
    short m_c;
    short m_e;
    int m_10;
    char m_14;
    char m_15[3];
    RHUnk0056de50List *m_18;
    int m_1c;
    char m_20[4];
    bool m_24;
    char m_25[3];
    char m_28[0x10];
    int m_38;
    char m_3c;
    char m_3d[3];
};

// FUNCTION: GAME 0x0056de50
RHUnk0056de50::RHUnk0056de50()
{
    char value;
    m_14 = value;
    RHUnk0056de50List *list = new RHUnk0056de50List;
    list->m_next = list;
    list->m_prev = list;
    m_18 = list;
    m_24 = 1;
    m_1c = 0;
    m_10 = 0;
    m_0 = 0;
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
    m_38 = 0;
    m_3c = 0;
}
