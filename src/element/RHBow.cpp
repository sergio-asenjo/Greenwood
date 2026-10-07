#include "RHBow.h"
#include "SB.h"

// deferred: unannotated pending reccmp #534
bool RHBow::SerializePointer(SBFile &file, RHBow *&ptr)
{
    bool exists;

    if (!file.m_bLoading)
    {
        exists = (ptr != 0);
        if (file.Access(&exists, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // STRING: GAME 0x006ab8c0
                     "P:\\Robin Hood\\RHBow.cpp",
                     305, "Serialize failed reason is %s", reason);
            return false;
        }
        if (exists)
            return ptr->Serialize(file);
        return true;
    }

    if (file.Access(&exists, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHBow.cpp", 316, "Serialize failed reason is %s", reason);
        return false;
    }
    if (exists)
    {
        ptr = new RHBow;
        return ptr->Serialize(file);
    }
    return true;
}
