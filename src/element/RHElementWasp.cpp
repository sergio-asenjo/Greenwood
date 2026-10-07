#include "RHElementWasp.h"

// Parked: counted engine/base callees resolve asymmetrically through the ILT.
// STUB: GAME 0x004bd120
bool RHElementWasp::Serialize(SBFile &file)
{
    RHEngine *engine = g_pEngine;
    RHSerializeName(file,
                    // STRING: GAME 0x006aef4c
                    "RHElementWasp");
    engine->FUN_004c42d0(file, m_15c);
    engine->FUN_004c3d90(file, m_160);
    if (file.Access(&m_168, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0,
                 // STRING: GAME 0x006aef2c
                 "P:\\Robin Hood\\RHElementWasp.cpp",
                 554, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_164, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementWasp.cpp", 555,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    m_16c.Serialize(file);
    return RHElementObject::Serialize(file);
}

void RHElementWasp::Emit(SBFile &file)
{
    Serialize(file);
}
