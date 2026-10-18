// Anonymous cluster at 0x004e3fd0.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

class RHUnk004e3fd0List
{
public:
    RHUnk004e3fd0List *m_next;
    RHUnk004e3fd0List *m_prev;
    char m_08[8];
};

class RHUnk004e3fd0
{
public:
    RHUnk004e3fd0(const char *value);
    char m_0;
    char m_1[3];
    RHUnk004e3fd0List *m_4;
    int m_8;
};

// FUNCTION: GAME 0x004e3fd0
RHUnk004e3fd0::RHUnk004e3fd0(const char *value)
{
    m_0 = *value;
    RHUnk004e3fd0List *list = new RHUnk004e3fd0List;
    list->m_next = list;
    list->m_prev = list;
    m_4 = list;
    m_8 = 0;
}
