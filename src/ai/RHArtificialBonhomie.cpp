#include "SBNullstr.h"
#include "RHArtificialBonhomie.h"

class RHBonhomieAdjustedReceiver
{
public:
    void FUN_0040eb90(bool enabled);
};

// FUNCTION: GAME 0x0040e150
bool RHArtificialBonhomie::SerializeExactlyThisAI(SBFile &file)
{
    // STRING: GAME 0x006a73b0
    RHSerializeName(file, "RHArtificialBonhomie");

    if (file.m_version >= 0x22)
    {
        if (file.Access((char *)this - 6, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // STRING: GAME 0x006a7328
                     "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                     1444, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    if (file.m_version > 0x1d)
    {
        if (file.Access((char *)this - 8, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                     1449, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    if (file.Access((char *)this - 0x18, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                 1452, "Serialize failed reason is %s", reason);
        return false;
    }

    if (!FUN_00416b30(*(void **)((char *)this - 0x14), file))
    {
        SBAssert(1,
                 // STRING: GAME 0x006a7350
                 "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                 1453,
                 // STRING: GAME 0x006a7378
                 "Serialization failed");
        return false;
    }

    if (file.Access((char *)this - 0x10, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                 1454, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}

// FUNCTION: GAME 0x0040eb90
void RHBonhomieAdjustedReceiver::FUN_0040eb90(bool enabled)
{
    *(bool *)((char *)this - 0x10) = !enabled;
}

void EmitRHBonhomieAdjustedReceiver(RHBonhomieAdjustedReceiver *receiver, bool enabled)
{
    receiver->FUN_0040eb90(enabled);
}

void RHArtificialBonhomie::Emit(SBFile &file)
{
    SerializeExactlyThisAI(file);
}
