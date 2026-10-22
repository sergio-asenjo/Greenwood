// Anonymous cluster at 0x0049b36x.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets are exact from Game.exe.

struct RHUnk0049b310
{
    int m_0;
    int m_4;
    int m_8;
};

class RHUnk0049b300
{
public:
    void FUN_0049b360(const RHUnk0049b310 *value);
    char m_0[0x50];
    char *m_50;
};

// FUNCTION: GAME 0x0049b360
void RHUnk0049b300::FUN_0049b360(const RHUnk0049b310 *value)
{
    char *base = m_50 + 4;
    *(RHUnk0049b310 *)(base + 0xc) = *value;
    *(int *)(base + 4) = 1;
}

void EmitRHUnk0049b300(RHUnk0049b300 *object, const RHUnk0049b310 *value)
{
    object->FUN_0049b360(value);
}
