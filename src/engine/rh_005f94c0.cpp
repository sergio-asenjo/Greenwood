// Anonymous cluster at 0x005f94cx (Hercules/MDA debug console).
// No __FILE__ or oracle evidence: class and method identity are unproven.

int FUN_00579a20();

class RHUnk005f94c0
{
public:
    RHUnk005f94c0();
    void FUN_005f94f0();
    unsigned char m_0;
    unsigned char m_1[3];
    int m_4;
};

// FUNCTION: GAME 0x005f94c0
RHUnk005f94c0::RHUnk005f94c0()
{
    m_0 = ((int (*)(const char *))FUN_00579a20)(
              // STRING: GAME 0x006bb18c
              "enable_hercules") != 0;
    FUN_005f94f0();
}

// FUNCTION: GAME 0x005f94f0
void RHUnk005f94c0::FUN_005f94f0()
{
    if (m_0)
    {
        m_4 = 0;
        unsigned int *screen = (unsigned int *)0xb0000;
        for (int i = 0; i < 1000; ++i)
            screen[i] = 0x07000700;
    }
}
