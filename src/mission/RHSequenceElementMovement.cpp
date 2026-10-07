#include "RHSequenceElementMovement.h"

// STRING: GAME 0x006b757c
#define RH_MOVEMENT_FILE "P:\\Robin Hood\\RHSequenceElementMovement.cpp"

#define RH_MOVEMENT_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, RH_MOVEMENT_FILE, line, "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

void RHSequenceElementMovement::Emit(SBFile &file, bool pointers)
{
    Serialize(file, pointers);
}

// Parked: counted geometry/sequence callees resolve asymmetrically through the ILT.
// STUB: GAME 0x00589910
bool RHSequenceElementMovement::Serialize(SBFile &file, bool pointers)
{
    FUN_00584ef0(file, pointers);
    RH_MOVEMENT_ACCESS(m_94, 4, 1308);
    RH_MOVEMENT_ACCESS(m_8c, 4, 1310);
    RH_MOVEMENT_ACCESS(m_90, 2, 1311);
    RH_MOVEMENT_ACCESS(m_88, 4, 1312);
    RH_MOVEMENT_ACCESS(m_74, 2, 1313);
    RH_MOVEMENT_ACCESS(m_98, 4, 1314);
    m_6c.Serialize(file);
    g_pEngine->SerializeNestedA(file, &m_84);
    RHUnkPathGeometry *grid = (RHUnkPathGeometry *)g_unk0x6c0a9c;
    grid->Unk004fc030(file, m_7c);
    ((RHFastFindGrid *)grid)->SerializeLinePointer(file, m_80);
    grid->Unk004fbec0(file, m_78);
    bool exists;
    if (!file.m_bLoading)
    {
        exists = m_68 != 0;
        RH_MOVEMENT_ACCESS(exists, 1, 1334);
        if (exists)
            m_68->Serialize(file, false);
    }
    else
    {
        RH_MOVEMENT_ACCESS(exists, 1, 1342);
        if (exists)
        {
            m_68 = (RHSequence *)new RHUnk00582220;
            m_68->Serialize(file, false);
        }
        else
            m_68 = 0;
    }
    if (pointers)
        ((RHSequenceManager *)g_unk0x6c1040)->PreSerializePointer(file, &m_64, false);
    else if (file.m_bLoading)
        m_64 = 0;
    return true;
}
