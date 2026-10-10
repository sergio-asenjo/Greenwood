#include "SBNullstr.h"
#include "RHReconnaissanceReport.h"

// FUNCTION: GAME 0x0056df30
bool RHReconnaissanceReport::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b2274
    RHSerializeName(file, "RHReconnaissanceReport");

    if (file.Access(&m_10, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        // STRING: GAME 0x6b2248
        SBAssert(0, "P:\\Robin Hood\\RHReconnaissanceReport.cpp", 79, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(m_0, 16) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHReconnaissanceReport.cpp", 80, "Serialize failed reason is %s", reason);
        return false;
    }
    if (!((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_8))
        return false;

    unsigned count;
    RHElement *element;
    if (file.m_bLoading)
    {
        RHReconnaissanceList &list = m_14;
        list.clear();
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHReconnaissanceReport.cpp", 90, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            if (!g_pEngine->SerializeElementPointer(file, element))
                return false;
            list.push_back(element);
        }
    }
    else
    {
        count = m_14.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHReconnaissanceReport.cpp", 105, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            element = m_14[i];
            if (!g_pEngine->SerializeElementPointer(file, element))
                return false;
        }
    }
    if (!((RHReconnaissanceEngine *)g_pEngine)->Unk004c3cb0(file, m_38))
        return false;
    if (file.Access(&m_3c, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHReconnaissanceReport.cpp", 117, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

void RHReconnaissanceReport::Emit(SBFile &file)
{
    Serialize(file);
}
