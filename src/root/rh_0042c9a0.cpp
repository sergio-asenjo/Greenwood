// Anonymous cluster at 0x0042c9axx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

struct RHUnk0042c910
{
    int m_0;
    int m_4;
};

class RHUnk0042c900
{
public:
    bool FUN_0042c9a0();
    RHUnk0042c910 *m_0;
};

// FUNCTION: GAME 0x0042c9a0
bool RHUnk0042c900::FUN_0042c9a0()
{
    char *base = (char *)this + m_0->m_4 + 4;
    int value = *(int *)(*(int *)base + 0x258);
    return value != 0;
}

void EmitRHUnk0042c900(RHUnk0042c900 *object)
{
    object->FUN_0042c9a0();
}
