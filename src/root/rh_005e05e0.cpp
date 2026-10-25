// AVI recording stream owner reached through the global at 0x006c06a4.
// No __FILE__ or oracle binding: class and method identity are unproven.
// Offsets are exact from Game.exe.

struct IAVIStream;
struct IAVIFile;

// LIBRARY: GAME 0x005e3ae4
extern "C" unsigned long __stdcall AVIStreamRelease(IAVIStream *) { return 0; }
// LIBRARY: GAME 0x005e3ade
extern "C" unsigned long __stdcall AVIFileRelease(IAVIFile *) { return 0; }

class RHUnk005e05e0
{
public:
    bool FUN_005e05e0();
    char m_0[0x114];
    IAVIStream *m_114;
    IAVIStream *m_118;
    IAVIFile *m_11c;
    char m_120[0x38];
    void *m_158;
};

// FUNCTION: GAME 0x005e05e0
bool RHUnk005e05e0::FUN_005e05e0()
{
    if (m_158)
    {
        operator delete(m_158);
        m_158 = 0;
        AVIStreamRelease(m_118);
        AVIStreamRelease(m_114);
        AVIFileRelease(m_11c);
    }
    return true;
}
