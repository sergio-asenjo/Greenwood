// Anonymous cluster at 0x004fe2xx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets are exact from Game.exe; the element strides are 192 and 160.

struct RHUnk004fe210
{
    char m_0[192];
};

class RHUnk004fe200
{
public:
    int FUN_004fe220();
    int m_0;
    RHUnk004fe210 *m_4;
    RHUnk004fe210 *m_8;
};

class RHUnk004fe260
{
public:
    int FUN_004fe280();
    int m_0;
    int m_4;
    int m_8;
};

// Parked: the target keeps the quotient in edx and copies to eax last
// (sar edx,5; mov eax,edx; shr eax,0x1f; add edx,eax; mov eax,edx); VC6 emits
// the re-scheduled copy-first form (mov eax,edx; sar eax,5; mov ecx,eax; ...)
// for every probed source shape (int, pointer difference, named local).
// STUB: GAME 0x004fe220
int RHUnk004fe200::FUN_004fe220()
{
    if (m_4 == 0)
        return 0;
    return m_8 - m_4;
}

// Parked: the target keeps the quotient in edx and copies to eax last
// (sar edx,6; mov eax,edx; shr eax,0x1f; add edx,eax; mov eax,edx); VC6 emits
// the re-scheduled copy-first form for every probed source shape (int, named
// local dividend, pointer difference).
// STUB: GAME 0x004fe280
int RHUnk004fe260::FUN_004fe280()
{
    if (m_4 == 0)
        return 0;
    int size = m_8 - m_4;
    return size / 160;
}

void EmitRHUnk004fe200(RHUnk004fe200 *object)
{
    object->FUN_004fe220();
}

void EmitRHUnk004fe260(RHUnk004fe260 *object)
{
    object->FUN_004fe280();
}
