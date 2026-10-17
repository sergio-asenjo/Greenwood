// Anonymous cluster at 0x00451ffx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets and the 12-byte element stride are exact from Game.exe.

struct RHUnk00451f10
{
    int *m_0;
    int m_4;
    int m_8;
};

class RHUnk00451f00
{
public:
    RHUnk00451f10 *FUN_00451ff0(int key);
    char m_0[0x148];
    RHUnk00451f10 *m_148;
    RHUnk00451f10 *m_14c;
};

// Parked: the target keeps the cursor in edx and hoists the zero result into
// eax; VC6 allocates the cursor to eax and the key to edx from every probed
// loop shape, so the result cannot be reserved.
// STUB: GAME 0x00451ff0
RHUnk00451f10 *RHUnk00451f00::FUN_00451ff0(int key)
{
    RHUnk00451f10 *element = m_148;
    while (element != m_14c)
    {
        if (*element->m_0 == key)
            return element;
        element++;
    }
    return 0;
}

void EmitRHUnk00451f00(RHUnk00451f00 *object)
{
    object->FUN_00451ff0(0);
}
