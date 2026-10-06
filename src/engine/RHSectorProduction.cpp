#include "RHSectorProduction.h"

// FUNCTION: GAME 0x00580970
bool RHSectorProduction::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b744c
    RHSerializeName(file, "RHSectorProduction");
    if (file.Access(&m_0, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        // STRING: GAME 0x006b7424
        SBAssert(0, "P:\\Robin Hood\\RHSectorProduction.cpp", 490, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_4, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHSectorProduction.cpp", 491, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2c, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHSectorProduction.cpp", 492, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2e, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHSectorProduction.cpp", 493, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_30, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHSectorProduction.cpp", 494, "Serialize failed reason is %s", reason);
        return false;
    }
    FUN_005818c0(file, m_occupants, (bool (*)(SBFile &, Occupant &))0x00580ab0);
    return true;
}

// deferred: unannotated pending reccmp #534
// 0x00580ab0: exact when annotated; annotation resolves the caller's literal callback asymmetrically.
bool RHSectorProduction::SerializeOccupant(SBFile &file, Occupant &occupant)
{
    FUN_00453da0(file, occupant.m_0);
    occupant.m_point.Serialize(file);
    if (file.m_version >= 47)
    {
        if (file.Access(&occupant.m_c, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHSectorProduction.cpp", 523, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.m_version >= 46)
        {
            short scratch;
            if (file.Access(&scratch, 2) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHSectorProduction.cpp", 530, "Serialize failed reason is %s", reason);
                return false;
            }
        }
        if (file.m_bLoading)
            occupant.m_c = 0xffff;
    }
    return true;
}

// deferred: unannotated pending reccmp #534
// 0x005818c0: exact when annotated; occupant-container instantiation, not SerializePoint.
bool RHSectorProduction::FUN_005818c0(SBFile &file, Occupants &occupants,
                                    bool (*serialize)(SBFile &, Occupant &))
{
    if (!file.m_bLoading)
    {
        unsigned count = occupants.size();
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHSectorProduction.cpp", 39, "Serialize failed reason is %s", reason);
            return false;
        }
        for (Occupant *it = occupants.begin(); it != occupants.end(); ++it)
            if (!serialize(file, *it))
                return false;
    }
    else
    {
        Occupants &list = occupants;
        list.clear();
        unsigned count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHSectorProduction.cpp", 60, "Serialize failed reason is %s", reason);
            return false;
        }
        while (count > 0)
        {
            {
                Occupant value;
                if (!serialize(file, value))
                    return false;
                list.Insert(list.end(), 1, value);
            }
            --count;
        }
    }
    return true;
}

void RHSectorProduction::Emit(SBFile &file)
{
    Serialize(file);
    Occupant occupant;
    SerializeOccupant(file, occupant);
}
