#include "SBNullstr.h"
#include "RHShortBriefings.h"

// FUNCTION: GAME 0x005a3030
bool RHShortBriefings::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b7834
    RHSerializeName(file, "RHShortBriefings");
    SerializeContainer(file, m_0, SerializeShortBriefing);
    SerializeContainer(file, m_10, SerializeShortBriefing);
    return true;
}

// deferred: unannotated pending reccmp #534 (callback address)
// FUNCTION: GAME 0x005a32a0
bool RHShortBriefings::SerializeShortBriefing(SBFile &file, ShortBriefing &value)
{
    if (file.Access(&value.m_0, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        // STRING: GAME 0x006b77a8
        SBAssert(0, "P:\\Robin Hood\\RHShortBriefings.cpp", 399, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&value.m_4, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHShortBriefings.cpp", 400, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

void RHShortBriefings::Emit(SBFile &file)
{
    Serialize(file);
    ShortBriefing value;
    SerializeShortBriefing(file, value);
}
