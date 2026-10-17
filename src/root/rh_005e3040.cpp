// Anonymous cluster at 0x005e304x.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets are exact from Game.exe.

class RHUnk005e3010
{
public:
    char m_0;
};

class RHUnk005e3000
{
public:
    RHUnk005e3000(const RHUnk005e3010 *src);
    char m_0;
    int m_4;
    int m_8;
    int m_c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    int m_20;
    int m_24;
    int m_28;
    int m_2c;
};

// FUNCTION: GAME 0x005e3040
RHUnk005e3000::RHUnk005e3000(const RHUnk005e3010 *src)
{
    m_0 = src->m_0;
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
    m_10 = 0;
    m_14 = 0;
    m_18 = 0;
    m_1c = 0;
    m_20 = 0;
    m_24 = 0;
    m_28 = 0;
    m_2c = 0;
}

void EmitRHUnk005e3000(const RHUnk005e3010 *src)
{
    RHUnk005e3000 object(src);
}
