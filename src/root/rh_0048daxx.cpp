// Anonymous cluster at 0x0048daxx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets are exact from Game.exe.

struct RHUnk0048da10
{
    char m_0[0x10];
    int m_10;
    char m_14[0x4c - 0x14];
    RHUnk0048da10 *m_4c;
    RHUnk0048da10 *m_50;
};

// Parked: the target lowers the two-value membership test to the switch
// sub-chain (sub ecx,2; je; sub ecx,0x9f; jne) and shares one false/true
// epilogue; the && / == || != loop shapes all give the cmp-chain plus a
// duplicated tail.
// STUB: GAME 0x0048da40
bool __stdcall FUN_0048da40(RHUnk0048da10 *value)
{
    if (value->m_50 != 0)
        return false;
    for (;;)
    {
        RHUnk0048da10 *node = value->m_4c;
        if (node == 0)
            return true;
        switch (node->m_10)
        {
        case 2:
        case 0xa1:
            if (node->m_50 != 0)
                return false;
            value = node;
            break;
        default:
            return false;
        }
    }
}

void EmitFUN_0048da40(RHUnk0048da10 *value)
{
    FUN_0048da40(value);
}
