// Anonymous cluster at 0x005494fxx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

class RHUnk00549400
{
public:
    int FUN_005494f0();
    char m_0[0x5e];
    unsigned char m_5e;
    char m_5f[0x120 - 0x5f];
    unsigned char m_120;
};

// FUNCTION: GAME 0x005494f0
int RHUnk00549400::FUN_005494f0()
{
    return m_5e != 0 && m_120 == 0;
}

void EmitRHUnk00549400(RHUnk00549400 *object)
{
    object->FUN_005494f0();
}
