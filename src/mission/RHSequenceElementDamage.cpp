#include "RHSequenceElementDamage.h"

// Parked: counted sword/engine callees resolve asymmetrically through the ILT.
// STUB: GAME 0x00586370
bool RHSequenceElementDamage::Serialize(SBFile &file, bool pointers)
{
    FUN_00584ef0(file, pointers);
    if (file.Access(&m_6c, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0,
                 // STRING: GAME 0x006b7524
                 "P:\\Robin Hood\\RHSequenceElementDamage.cpp",
                 304, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_74, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHSequenceElementDamage.cpp", 305,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_6a, 2) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHSequenceElementDamage.cpp", 306,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_68, 2) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHSequenceElementDamage.cpp", 307,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    g_pEngine->SerializeNestedA(file, &m_64);
    RHSword::SerializePointer(file, m_70);
    g_pEngine->FUN_004c41f0(file, m_78);
    return true;
}

void RHSequenceElementDamage::Emit(SBFile &file, bool pointers)
{
    Serialize(file, pointers);
}
