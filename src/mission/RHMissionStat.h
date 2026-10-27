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
#include "RHMissionStatCore.h"

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
