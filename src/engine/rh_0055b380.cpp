// Anonymous cluster at 0x0055b380.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.
//
// Parked: the body, the two uninitialised char locals (both read from [esp+7])
// and every store offset are exact; only the store schedule of m_1c differs.
// The target emits `mov [eax+0x1c],bl` after `mov [eax+0x14],dl`; VC6 hoists it
// to directly after `mov dl,1`. Three shapes tried (two locals, one reused
// local, m_1c assigned after the m_20/m_24/m_28 zero run) -- all 0.96.
class RHUnk0055b380
{
public:
    RHUnk0055b380();
    char m_0;
    char m_1[3];
    int m_4;
    int m_8;
    int m_c;
    char m_10[4];
    bool m_14;
    char m_15[3];
    char m_18[4];
    char m_1c;
    char m_1d[3];
    int m_20;
    int m_24;
    int m_28;
    char m_2c[4];
    bool m_30;
};

// STUB: GAME 0x0055b380
RHUnk0055b380::RHUnk0055b380()
{
    char first;
    char second;
    m_0 = first;
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
    m_14 = 1;
    m_1c = second;
    m_20 = 0;
    m_24 = 0;
    m_28 = 0;
    m_30 = 1;
}
