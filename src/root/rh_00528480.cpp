// Anonymous cluster at 0x0052848x.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets and the 0x27c element stride are exact from Game.exe.

struct RHUnk00528410
{
    char m_0[0x27c];
};

class RHUnk00528400
{
public:
    RHUnk00528410 *FUN_00528480(RHUnk00528410 *target);
    char m_0[0x19c];
    RHUnk00528410 m_19c[10];
};

// Parked: the target keeps the cursor in edx and hoists the zero result into
// eax; VC6 allocates the cursor to eax from every probed loop shape, so the
// result register cannot be reserved.
// STUB: GAME 0x00528480
RHUnk00528410 *RHUnk00528400::FUN_00528480(RHUnk00528410 *target)
{
    RHUnk00528410 *element = m_19c;
    RHUnk00528410 *last = m_19c + 10;
    while (element != last)
    {
        if (element == target)
            return element;
        element++;
    }
    return 0;
}

void EmitRHUnk00528400(RHUnk00528400 *object)
{
    object->FUN_00528480(0);
}
