// Anonymous cluster at 0x0051c8f0.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

struct RHUnkPathRegistry;
extern RHUnkPathRegistry *g_unk0x6c0b9c;

class RHUnk0051c8f0
{
public:
    RHUnk0051c8f0();
    unsigned m_vptr;
    char m_4;
    char m_5[3];
    int m_8;
    int m_c;
    int m_10;
    char m_14[4];
    bool m_18;
};

// FUNCTION: GAME 0x0051c8f0
RHUnk0051c8f0::RHUnk0051c8f0()
{
    char value;
    m_4 = value;
    m_8 = 0;
    m_c = 0;
    m_10 = 0;
    m_18 = 1;
    m_vptr = 0x6790b8;
    g_unk0x6c0b9c = (RHUnkPathRegistry *)this;
}
