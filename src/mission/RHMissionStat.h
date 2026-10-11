// RHMissionStat — declarations shared by RHMissionStat.cpp (decompiled TU)
// and RHMissionStat_stubs.cpp (external-symbol stubs).
//
// BINDING (0x0054e250): RHMissionStat::Serialize(SBFile&). See
// src/RHMissionStat.cpp for the evidence chain.
//
// Member layout is derived from the target instructions of
// RHMissionStat::Serialize (0x0054e250): nine 32-bit fields at +0x04..+0x24,
// then an opaque list object at +0x28 whose element serializer is the free
// helper at 0x004593f0.

#include "SB.h"
#include <string>

// The list object at RHMissionStat+0x28. It is a std::vector<std::wstring>:
// the ctor at 0x0054cf60 zeroes +0x28..+0x37 and the element serializer
// (0x004593f0) walks [this+0x04, this+0x08) with a 16-byte stride. Modelled
// with named fields so the wstring getters can re-derive the target offsets.
class RHUnk0054e250List
{
public:
    char m_pad0[4];
    std::wstring *m_first; // [this+0x04]
    std::wstring *m_last;  // [this+0x08]
    std::wstring *m_end;   // [this+0x0c]

    unsigned size() const { return m_first == 0 ? 0 : (unsigned)(m_last - m_first); }
};

class RHMissionStat
{
public:
    // Virtual so the object layout carries the vptr at +0x00 the target
    // instructions imply (the first serialised int is at +0x04).
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);

    void FUN_0054cfa0(const void *source);
    void FUN_0054d150(const void *value);
    void FUN_0054d310(std::wstring &text) const;
    void FUN_0054d550(std::wstring &text) const;
    void FUN_0054d760(std::wstring &text) const;
    void FUN_0054d9c0(std::wstring &text) const;
    void FUN_0054db50(std::wstring &text) const;
    void FUN_0054dd10(std::wstring &text) const;
    void FUN_0054dee0(std::wstring &text) const;
    std::wstring FUN_0054e090() const;

    int m_f04; // [0x04]
    int m_f08; // [0x08]
    int m_f0c; // [0x0c]
    int m_f10; // [0x10]
    int m_f14; // [0x14]
    int m_f18; // [0x18]
    int m_f1c; // [0x1c]
    int m_f20; // [0x20]
    int m_f24; // [0x24]

    RHUnk0054e250List m_list; // [0x28]
};

// Target 0x005e1b70 (RHSerializeName): serialises a type-name tag into the
// stream. Declared identically in include/RHElementObject.h; no TU includes
// both headers, so the declaration does not collide.
void RHSerializeName(SBFile &file, const char *name);

// Target 0x005e23d0: looks up a localized wide string by id.
std::wstring FUN_005e23d0(unsigned long id);

// Target 0x00452030 (defined in RHScript.cpp): campaign-value accessor.
class RHUnk00452030
{
public:
    int Get(int index);
};

// Defined and annotated (GLOBAL 0x006c07fc) in RHScript.cpp.
extern RHUnk00452030 *g_unk0x6c07fc;
// Target 0x005e2bf0: localized wide-string lookup by numeric key.
std::wstring FUN_005e2bf0(int value);

// Target 0x00642bc9: statically-linked wsprintfW (wide-char formatted output).
// Declared identically in RHMissionStat_stubs.cpp, where its LIBRARY seed lives.
// `extern "C"` is required: VC6 /GX omits the EH frame for a wide-string
// temporary that is only live across C-linkage (non-throwing) calls.
extern "C" int __cdecl wsprintfW(unsigned short *buffer, const unsigned short *format, ...);

// Target 0x004593f0: serialises a container of elements, invoking the
// per-element serializer passed as the third argument.
bool RHUnk004593f0SerializeList(SBFile &file, RHUnk0054e250List &list, void *elementFn);
