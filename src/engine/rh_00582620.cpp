// Anonymous cluster at 0x0058253x / 0x0058262x.
// No __FILE__ or oracle evidence: class and method identity are unproven.

void FUN_00582560() {}

class RHUnk00582620
{
public:
    bool FUN_00582530();
    void FUN_00582620(int arg);
    char m_00[0x10];
    int m_10;
    char m_14[0x18];
    unsigned short m_2c;
    char m_2e[2];
    short m_30;
    char m_32[2];
    char m_34;
};

// FUNCTION: GAME 0x00582530
bool RHUnk00582620::FUN_00582530()
{
    if (!m_34)
        m_34 = 1;
    if ((unsigned short)m_2c == m_10)
        return false;
    FUN_00582560();
    return true;
}

// FUNCTION: GAME 0x00582620
void RHUnk00582620::FUN_00582620(int arg)
{
    m_30--;
    if (m_30 == 0)
        FUN_00582560();
}
