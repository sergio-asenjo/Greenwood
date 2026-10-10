#include "SBNullstr.h"
#include "RHSectorProduction.h"

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHSectorProduction::Occupant, 0x10)
DECOMP_SIZE_ASSERT(RHSectorProduction::Occupants, 0x10)
DECOMP_SIZE_ASSERT(RHSectorProduction, 0x34)

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

// FUNCTION: GAME 0x00580ab0
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
        first->~Occupant();
}

// FUNCTION: GAME 0x00459100
void RHSectorProduction::Occupants::Destroy(Occupant *first, Occupant *last)
{
    for (; first != last; ++first)
        first->~Occupant();
}

inline RHSectorProduction::Occupant *RHSectorProduction::Occupants::UninitializedCopy(
    const Occupant *first, const Occupant *last, Occupant *out)
{
    for (; first != last; ++out, ++first)
        std::_Construct(out, *first);
    return out;
}

inline void RHSectorProduction::Occupants::UninitializedFill(Occupant *first, unsigned count,
                                                            const Occupant &value)
{
    for (; count > 0; --count, ++first)
        std::_Construct(first, value);
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
    if ((unsigned)(_End - _Last) < count)
    {
        unsigned capacity = size() + (count < size() ? size() : count);
        Occupant *storage = Allocate(capacity);
        Occupant *next = UninitializedCopy(_First, where, storage);
        UninitializedFill(next, count, value);
        UninitializedCopy(where, _Last, next + count);
        DestroyElements(_First, _Last);
        operator delete(_First);
        _End = storage + capacity;
        _Last = storage + size() + count;
        _First = storage;
    }
    else if ((unsigned)(_Last - where) < count)
    {
        UninitializedCopy(where, _Last, where + count);
        UninitializedFill(_Last, count - (_Last - where), value);
        Fill(where, _Last, value);
        _Last += count;
    }
    else if (count > 0)
    {
        UninitializedCopy(_Last - count, _Last, _Last);
        Occupant *first = _Last - count;
        Occupant *out = _Last;
        while (where != first)
            *--out = *--first;
        Fill(where, where + count, value);
        _Last += count;
    }
}

// FUNCTION: GAME 0x005818c0
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
