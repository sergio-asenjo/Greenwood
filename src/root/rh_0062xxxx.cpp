// Anonymous cluster at 0x0061ddxx / 0x00651xxx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets are exact from Game.exe.

struct RHUnk0061dd10
{
    RHUnk0061dd10 *m_0;
};

class RHUnk0061dd00
{
public:
    int FUN_0061dd30();
    int m_0;
    int m_4;
    RHUnk0061dd10 *m_8;
    RHUnk0061dd10 *m_c;
    RHUnk0061dd10 *m_10;
};

// FUNCTION: GAME 0x0061dd30
int RHUnk0061dd00::FUN_0061dd30()
{
    int count = -1;
    RHUnk0061dd10 *node = m_8->m_0;
    while (node != m_10)
    {
        node = node->m_0;
        count++;
    }
    return count;
}

// FUNCTION: GAME 0x00651133
int FUN_00651133(const void *value)
{
    return *(int *)((const char *)value + 0x10);
}

void EmitRHUnk0061dd00(RHUnk0061dd00 *object)
{
    object->FUN_0061dd30();
}

void EmitFUN_00651133(const void *value)
{
    FUN_00651133(value);
}
