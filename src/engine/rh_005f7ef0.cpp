// Anonymous cluster at 0x005f7efx (bzip2 stream holder).
// No __FILE__ or oracle evidence: class and method identity are unproven.

typedef void BZFILE;

extern "C" void __stdcall BZ2_bzclose(BZFILE *b);

class RHUnk005f7ef0
{
public:
    void FUN_005f7ef0();
    BZFILE *m_0;
};

// FUNCTION: GAME 0x005f7ef0
void RHUnk005f7ef0::FUN_005f7ef0()
{
    if (m_0)
        BZ2_bzclose(m_0);
    m_0 = 0;
}
