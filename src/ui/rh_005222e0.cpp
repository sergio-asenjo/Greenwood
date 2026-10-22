// Anonymous cluster at 0x005222exx / 0x0052233xx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

class RHEngine;
extern RHEngine *g_pEngine;

class RHUnk005222e0
{
public:
    char FUN_005222e0();
    void FUN_00522330(unsigned char amount);
    char m_00[0x14];
    unsigned m_14;
    char m_18[0x20];
    char m_38;
};

// FUNCTION: GAME 0x005222e0
char RHUnk005222e0::FUN_005222e0()
{
    int delta = (int)(*(unsigned *)((char *)g_pEngine + 0x4a94) - m_14);
    if (delta >= 0)
        m_38 = 100;
    else if (delta <= -10000)
        m_38 = 0;
    else
        m_38 = (char)(delta * 100 / 10000 + 100);
    return m_38;
}

// FUNCTION: GAME 0x00522330
void RHUnk005222e0::FUN_00522330(unsigned char amount)
{
    unsigned now = *(unsigned *)((char *)g_pEngine + 0x4a94);
    if (m_14 < now)
        m_14 = now;
    m_14 += amount * 100;
    unsigned maximum = now + 10000;
    if (m_14 > maximum)
        m_14 = maximum;
}
