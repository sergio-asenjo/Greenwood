// Anonymous cluster at 0x004fe2xx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets are exact from Game.exe; the element strides are 192 and 160.

struct RHUnk004fe210
{
    char m_0[192];
};

class RHUnk004fd7f0
{
public:
    ~RHUnk004fd7f0();
    char m_data[0xc0];
};

class RHUnk004fda20
{
public:
    ~RHUnk004fda20();
    char m_data[0xa0];
};

class RHUnk004fe200
{
public:
    int FUN_004fe220();
    void FUN_004fe250(RHUnk004fd7f0 *first, RHUnk004fd7f0 *last);
    int m_0;
    RHUnk004fe210 *m_4;
    RHUnk004fe210 *m_8;
};

class RHUnk004fe260
{
public:
    int FUN_004fe280();
    void FUN_004fe2b0(RHUnk004fda20 *first, RHUnk004fda20 *last);
    int m_0;
    int m_4;
    int m_8;
};

class RHUnk004fe1f0List
{
public:
    RHUnk004fe1f0List *m_next;
    RHUnk004fe1f0List *m_prev;
    char m_08[0x0c];
};

class RHUnk004fe1f0
{
public:
    RHUnk004fe1f0(const char *value);
    char m_0;
    char m_1[3];
    RHUnk004fe1f0List *m_4;
    int m_8;
};

// FUNCTION: GAME 0x004fe1f0
RHUnk004fe1f0::RHUnk004fe1f0(const char *value)
{
    m_0 = *value;
    RHUnk004fe1f0List *list = new RHUnk004fe1f0List;
    list->m_next = list;
    list->m_prev = list;
    m_4 = list;
    m_8 = 0;
}

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

// FUNCTION: GAME 0x004fe250
void RHUnk004fe200::FUN_004fe250(RHUnk004fd7f0 *first, RHUnk004fd7f0 *last)
{
    for (; first != last; ++first)
        first->~RHUnk004fd7f0();
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

// FUNCTION: GAME 0x004fe2b0
void RHUnk004fe260::FUN_004fe2b0(RHUnk004fda20 *first, RHUnk004fda20 *last)
{
    for (; first != last; ++first)
        first->~RHUnk004fda20();
}

void EmitRHUnk004fe200(RHUnk004fe200 *object)
{
    object->FUN_004fe220();
}

void EmitRHUnk004fe260(RHUnk004fe260 *object)
{
    object->FUN_004fe280();
}
