// Shared SB* engine declarations used by more than one decompiled TU.
//
// Extracted verbatim from RHSword.h so RHSword.cpp keeps its exact layout and
// RHElementObject.cpp can reuse the same class/signature declarations:
//   SBFile::Access(void*, int)  -> ?Access@SBFile@@QAEHPAXH@Z
//   SBFile::GetError()          -> ?GetError@SBFile@@QAEPAVSBString@@XZ
//   SBAssert(...)               -> ?SBAssert@@YAXHPBDH0ZZ
//
// The definitions live in RHSword_stubs.cpp (single definition; both TUs just
// declare, so the linker sees one entity per call target).

struct SBString
{
    char *m_pad0;
    char *m_chars;
};

class SBFile
{
public:
    char m_pad0[4];
    char m_bLoading;    // [this+4]: 0 = writing, non-zero = reading
    char m_pad1[0xb];   // [this+5, this+0x10)
    unsigned m_version; // [this+0x10]: stream version

    int Access(void *buf, int size);
    SBString *GetError();
};

inline void SBAssert(int, const char *, int, const char *, ...) {}
