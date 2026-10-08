#include "RHSectorProduction.h"

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHSectorProduction::Occupant, 0x10)
DECOMP_SIZE_ASSERT(RHSectorProduction::Occupants, 0x10)
DECOMP_SIZE_ASSERT(RHSectorProduction, 0x34)

// SIZE 0x24
struct RHSoundPendingData
{
    undefined m_00[0x24]; // 0x00
    void FUN_0052c5a0();
};

DECOMP_SIZE_ASSERT(RHSoundPendingData, 0x24)

// FUNCTION: GAME 0x0045a910
inline RHSectorProduction::Occupant &RHSectorProduction::Occupant::operator=(const Occupant &other)
{
    m_0 = other.m_0;
    m_point = other.m_point;
    m_c = other.m_c;
    return *this;
}

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

inline void RHSectorProduction::Occupants::DestroyElements(Occupant *first, Occupant *last)
{
    for (; first != last; ++first)
        ((RHSoundPendingData *)first)->FUN_0052c5a0();
}

inline RHSectorProduction::Occupant *RHSectorProduction::Occupants::UninitializedCopy(
    const Occupant *first, const Occupant *last, Occupant *out)
{
    for (; first != last; ++out, ++first)
        FUN_0045a850(out, *first);
    return out;
}

inline void RHSectorProduction::Occupants::UninitializedFill(Occupant *first, unsigned count,
                                                            const Occupant &value)
{
    for (; count > 0; --count, ++first)
        FUN_0045a850(first, value);
}

inline void RHSectorProduction::Occupants::Fill(Occupant *first, Occupant *last, const Occupant &value)
{
    for (; first != last; ++first)
        *first = value;
}

inline RHSectorProduction::Occupant *RHSectorProduction::Occupants::Allocate(int count)
{
    if (count < 0)
        count = 0;
    return (Occupant *)operator new((unsigned)count * sizeof(Occupant));
}

// FUNCTION: GAME 0x005815f0
void RHSectorProduction::Occupants::Insert(Occupant *where, unsigned count, const Occupant &value)
{
    if ((unsigned)(m_end - m_last) < count)
    {
        unsigned capacity = size() + (count < size() ? size() : count);
        Occupant *storage = Allocate(capacity);
        Occupant *next = UninitializedCopy(m_first, where, storage);
        UninitializedFill(next, count, value);
        UninitializedCopy(where, m_last, next + count);
        DestroyElements(m_first, m_last);
        operator delete(m_first);
        m_end = storage + capacity;
        m_last = storage + size() + count;
        m_first = storage;
    }
    else if ((unsigned)(m_last - where) < count)
    {
        UninitializedCopy(where, m_last, where + count);
        UninitializedFill(m_last, count - (m_last - where), value);
        Fill(where, m_last, value);
        m_last += count;
    }
    else if (count > 0)
    {
        UninitializedCopy(m_last - count, m_last, m_last);
        Occupant *first = m_last - count;
        Occupant *out = m_last;
        while (where != first)
            *--out = *--first;
        Fill(where, where + count, value);
        m_last += count;
    }
}

// deferred: unannotated pending reccmp #534
// 0x005818c0: historically exact; callback and Insert annotations are coupled.
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
    m_occupants.Insert(m_occupants.end(), 1, occupant);
}
