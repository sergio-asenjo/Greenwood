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

// Parked: the target keeps the source pointer in edx and the copy scratch in
// esi; VC6 reuses ecx for the source pointer in every probed order/named-local
// shape.
// STUB: GAME 0x0049b360
void RHUnk0049b300::FUN_0049b360(const RHUnk0049b310 *value)
{
    char *base = m_50 + 4;
    int *target = (int *)(base + 0xc);
    int first = value->m_0;
    int second = value->m_4;
    int third = value->m_8;
    target[0] = first;
    target[1] = second;
    *(int *)(base + 4) = 1;
    target[2] = third;
}

void EmitRHUnk0049b300(RHUnk0049b300 *object, const RHUnk0049b310 *value)
{
    object->FUN_0049b360(value);
}
