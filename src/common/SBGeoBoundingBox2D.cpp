#include "SBGeoBoundingBox2D.h"

bool SBGeoBoundingBox2D::FUN_00607c70(SBFile &file)
{
    if (file.Access(m_00, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0,
            // STRING: GAME 0x006bb528
            "P:\\Robin Hood\\SBLibNG\\SBGeoBoundingBox2D.cpp", 0x115,
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(m_00 + 4, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBGeoBoundingBox2D.cpp", 0x116,
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(m_00 + 8, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBGeoBoundingBox2D.cpp", 0x117,
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(m_00 + 12, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBGeoBoundingBox2D.cpp", 0x118,
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(m_00 + 16, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBGeoBoundingBox2D.cpp", 0x11a,
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    return true;
}

void EmitSBGeoBoundingBox2D(SBGeoBoundingBox2D *box, SBFile &file)
{
    box->FUN_00607c70(file);
}
