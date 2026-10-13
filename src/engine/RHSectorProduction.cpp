#include "SBNullstr.h"
#include "RHSectorProduction.h"
#include <string.h>

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHSectorProduction::Occupant, 0x10)
DECOMP_SIZE_ASSERT(RHSectorProduction::Occupants, 0x10)
DECOMP_SIZE_ASSERT(RHSectorProduction, 0x34)

class RHPCDescription;

class RHEngine
{
public:
    RHElementActorPC *GetPC(RHPCDescription *description) const;
};

extern RHEngine *g_pEngine;

struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

class RHFastFindGrid
{
public:
    void FUN_004fc590();
    void FUN_004fc660();
};

struct RHBonusProjection;

class RHBonusInfoBase
{
public:
    void FUN_0055f290();
    void FUN_0055fa20(RHBonusProjection *projection);
    void FUN_0055fa70(void *area);
};

class RHBonusInfo
{
public:
    void FUN_005bd560(void *value, bool flag);
};

class RHActorPositionCalls
{
public:
    void FUN_00464530(const SBGeoPoint2D &point);
};

class RHElementActor
{
public:
    void FUN_00462700(unsigned short value);
};

class RHUnk0049d4f0
{
public:
    bool Unk(int value);
};

class RHUnk00452030;
extern RHUnk00452030 *g_unk0x6c07fc;

class RHUnk004d8460
{
public:
    void FUN_004d8460(void *actor, int first, int second);
};

struct RHSectorProductionInfoHead
{
    int m_0;
};

struct RHSectorProductionPosition
{
    char m_00[0xda];
    unsigned short m_da;
    void SetLayer(unsigned short layer) { m_da = layer; }
};

struct RHSectorProductionInfo : RHSectorProductionInfoHead, RHSectorProductionPosition
{
};

// SIZE 0x100
class RHSectorProductionBonus
{
public:
    RHSectorProductionBonus(int action, int flags, unsigned short count);
    RHSectorProductionBonus(unsigned long relic, int flags, int count);
    char m_00[0x50];
    char *m_50;
    char m_54[0xac];
};

class RHSectorProductionRelics : public std::vector<unsigned long>
{
public:
    unsigned long &At(unsigned int index)
    {
        if (size() <= index)
        {
            typedef void (std::vector<unsigned long>::*Xran)() const;
            Xran xran = &RHSectorProductionRelics::_Xran;
            (this->*xran)();
        }
        return *(begin() + index);
    }
};

class RHSectorProductionCampaign
{
public:
    RHSectorProductionRelics *FUN_005cb6f0();
};

struct RHSectorProductionActorNode
{
    void *m_0;
    void *m_4;
    char *m_8;
};

class RHSectorProductionActorList
{
public:
    void GoTo(int index);
    char m_00[8];
    int m_count;
    RHSectorProductionActorNode *m_c;
    char *Current() const { return m_c->m_8; }
};

class RHFastFindGateArray
{
public:
    unsigned int FUN_0059fbc0()
    {
        typedef unsigned (std::vector<unsigned long>::*Size)() const;
        Size size = &std::vector<unsigned long>::size;
        return (((const std::vector<unsigned long> *)this)->*size)();
    }
    int m_0;
    void **m_first;
    void **m_last;
    void **m_end;
    void **m_cursor;
    bool m_dirty;
    bool m_15;
    int m_18;
    void *m_1c;
    int Find(void *value)
    {
        m_dirty = false;
        m_1c = value;
        int count = FUN_0059fbc0();
        m_15 = true;
        m_cursor = m_first;
        int index;
        for (index = 0; index < count; ++index, ++m_cursor)
        {
            if (*m_cursor == m_1c)
                break;
        }
        if (index >= count)
            index = -1;
        m_18 = index;
        return index;
    }
};

struct RHSectorProductionGlobal
{
    char m_pad0[0x4140];
    RHFastFindGateArray m_4140;
};

struct RHSectorProductionPositionView
{
    char m_00[0x20];
    SBGeoPoint2D m_20;
    char m_28[0xc0];
    void *m_e8;
};

struct RHSectorProductionActorView
{
    char m_00[0x50];
    char *m_50;
    char m_54[0x5a4];
    void *m_5f8;
    void *Description() const { return m_5f8; }
    const SBGeoPoint2D &Point() const { return *(SBGeoPoint2D *)(m_50 + 0x24); }
    void *Projection() const { return ((RHSectorProductionPositionView *)(m_50 + 4))->m_e8; }
};

struct RHSectorProductionRuntime
{
    char m_00[0x48dc];
    char **m_first;
    char **m_last;
};

struct RHSectorProductionMission
{
    char *m_0;
    int m_4;
    int m_8;
};

struct RHSectorProductionScript
{
    char m_00[0x36];
    unsigned short m_36;
    char m_38[0x90];
    unsigned short m_c8;
    char m_ca[2];
    RHSectorProductionActorList m_cc;
};

struct RHSectorProductionActor
{
    char m_00[0x50];
    char *m_50;
    char m_54[0x59c];
    int m_5f0;
};

class RHSectorProductionPC
{
public:
    bool FUN_0055bb00(int value);
    void FUN_0051d4e0(int kind, unsigned int amount);
    void FUN_00484360(int amount);
};

extern double g_unk0x00677d90;
extern double g_unk0x00677670;

// FUNCTION: GAME 0x0045a910
inline RHSectorProduction::Occupant &RHSectorProduction::Occupant::operator=(const Occupant &other)
{
    m_0 = other.m_0;
    m_point = other.m_point;
    m_c = other.m_c;
    return *this;
}

// FUNCTION: GAME 0x00580350
int RHSectorProduction::FUN_00580350(int type)
{
    int action = 0;
    switch (type)
    {
    case 0:
        action = 1;
        break;
    case 1:
        action = 4;
        break;
    case 2:
        action = 5;
        break;
    case 3:
        action = 0xb;
        break;
    case 4:
        action = 0xc;
        break;
    case 5:
        action = 0xd;
        break;
    case 6:
        action = 0x10;
        break;
    case 7:
        action = 0x11;
        break;
    case 8:
        action = 0x13;
        break;
    }
    return action;
}

// FUNCTION: GAME 0x005803c0
int RHSectorProduction::FUN_005803c0()
{
    int previous = m_8;
    m_8 = 0;
    m_points.erase(m_points.begin(), m_points.end());
    return previous;
}

// FUNCTION: GAME 0x00580430
void RHSectorProduction::FUN_00580430()
{
    int value = FUN_00580350(m_0);
    if (value == 0)
        return;
    RHSectorProductionRuntime *runtime = (RHSectorProductionRuntime *)g_pEngine;
    unsigned int count = runtime->m_first == 0 ? 0 : runtime->m_last - runtime->m_first;
    m_2c = 0;
    for (unsigned int index = 0; index != count; ++index)
    {
        char *entry = runtime->m_first[index];
        if (entry[0x12] && (*(unsigned int *)(entry + 4) & 0xf) == 3)
        {
            if (*(int *)(entry + 0xa8) == value)
                m_2c += *(unsigned short *)(entry + 0xae);
        }
        else if (value == 1 && entry[0x12] && (*(unsigned int *)(entry + 4) & 0xf) == 7 &&
                 *(int *)(entry + 0xb0) == 5)
            ++m_2c;
    }
}

// FUNCTION: GAME 0x005804e0
void RHSectorProduction::FUN_005804e0()
{
    if (m_0 >= 0 && m_0 <= 8)
        FUN_00580430();
    FUN_00580520();
}

// FUNCTION: GAME 0x00580500
unsigned int RHSectorProduction::FUN_00580500()
{
    return m_occupants.size();
}

// Parked: the occupant-insert argument address takes edx where the target keeps ecx.
// STUB: GAME 0x00580520
void RHSectorProduction::FUN_00580520()
{
    RHSectorProductionScript *script = (RHSectorProductionScript *)m_8;
    if (!script)
        return;
    int count = script->m_cc.m_count;
    Occupants &occupants = m_occupants;
    occupants.ClearAll();
    for (int index = 0; index != count; ++index)
    {
        RHSectorProductionScript *current = (RHSectorProductionScript *)m_8;
        RHSectorProductionActorList &list = current->m_cc;
        list.GoTo(index);
        RHSectorProductionActor *actor = (RHSectorProductionActor *)list.m_c->m_8;
        if ((*(unsigned int *)((char *)actor + 4) & 0xf) == 0xc && FUN_00580940((RHElementActorPC *)actor) == true)
        {
            Occupant occupant;
            occupant.m_0 = ((RHSectorProductionActorView *)actor)->Description();
            occupant.m_point = ((RHSectorProductionActorView *)actor)->Point();
            void *projection = ((RHSectorProductionActorView *)actor)->Projection();
            if (projection == 0)
                occupant.m_c = 0xffff;
            else
                occupant.m_c = ((RHSectorProductionGlobal *)g_unk0x6c0a9c)->m_4140.Find(projection);
            occupants.Insert(occupants.end(), 1, occupant);
        }
    }
}

// FUNCTION: GAME 0x005806b0
unsigned int RHSectorProduction::FUN_005806b0() const
{
    unsigned int result = 0;
    result = m_2e;
    return result;
}

// FUNCTION: GAME 0x005806c0
RHElementActorPC *RHSectorProduction::FUN_005806c0() const
{
    std::string name;
    RHElementActorPC *result = 0;
    switch (m_0)
    {
    case 0:
    case 1:
    case 9:
        name = "Robin des bois";
        break;
    case 2:
        name = "Will Ecarlate";
        break;
    case 4:
    case 5:
    case 8:
    case 11:
        name = "Frere Tuck";
        break;
    case 6:
        name = "Lady Marianne";
        break;
    case 3:
    case 7:
        name = "Stutely";
        break;
    case 10:
        name = "Petit Jean";
        break;
    }
    if (name.size() != 0)
    {
        Occupants &occupants = (Occupants &)m_occupants;
        for (const Occupant *it = occupants.begin(); it != occupants.end(); ++it)
        {
            const std::string &other = *(std::string *)(*(char **)((char *)it->m_0 + 0x40) + 0x14);
            if (_stricmp(name.c_str(), other.c_str()) == 0)
            {
                result = (RHElementActorPC *)it->m_0;
                break;
            }
        }
    }
    return result;
}

// FUNCTION: GAME 0x00580940
bool RHSectorProduction::FUN_00580940(const RHElementActorPC *pc) const
{
    switch (m_0)
    {
    case 9:
        return ((RHUnk0049d4f0 *)pc)->Unk(1);
    case 12:
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x00580960
char RHSectorProduction::FUN_00580960() const
{
    return m_30;
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

// FUNCTION: GAME 0x00580b70
void RHSectorProduction::FUN_00580b70()
{
    int action = FUN_00580350(m_0);
    if (action == 0)
        return;
    unsigned short amount = m_2c;
    RHEngine *engine = g_pEngine;
    for (Points::iterator it = m_points.begin(); it != m_points.end() && amount != 0; ++it)
    {
        Point point = *it;
        unsigned short count = amount >= 5 ? 5 : amount;
        amount -= count;
        RHSectorProductionBonus *bonus = new RHSectorProductionBonus(action, 0, count);
        ((RHActorPositionCalls *)(bonus->m_50 + 4))->FUN_00464530(point.m_point);
        ((RHSectorProductionInfo *)bonus->m_50)->SetLayer(point.m_8);
        ((RHElementActor *)bonus)->FUN_00462700(point.m_a);
        if (point.m_c == 0xffff)
            ((RHBonusInfoBase *)(bonus->m_50 + 4))->FUN_0055fa20(0);
        else
        {
            RHBonusProjection **table = (RHBonusProjection **)((RHSectorProductionGlobal *)g_unk0x6c0a9c)->m_4140.m_first;
            RHBonusProjection *projection = table[point.m_c];
            ((RHBonusInfoBase *)(bonus->m_50 + 4))->FUN_0055fa20(projection);
        }
        ((RHBonusInfoBase *)(bonus->m_50 + 4))->FUN_0055f290();
        ((RHBonusInfo *)bonus->m_50)->FUN_005bd560(0, true);
        ((RHUnk004d8460 *)engine)->FUN_004d8460(bonus, 0, 1);
    }
    m_30 = m_2c >= m_points.size() * 5 ? 1 : 0;
}

// FUNCTION: GAME 0x00580d20
void RHSectorProduction::FUN_00580d20(const RHMission *mission)
{
    switch (m_0)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        FUN_00581020(mission);
        FUN_00580b70();
        break;
    case 9:
    case 10:
        FUN_005810c0(mission);
        break;
    case 11:
        FUN_00581180(mission);
        break;
    case 12:
        FUN_00580e80();
        break;
    }
    FUN_00580dc0();
    ((RHFastFindGrid *)g_unk0x6c0a9c)->FUN_004fc590();
    ((RHFastFindGrid *)g_unk0x6c0a9c)->FUN_004fc660();
}

// FUNCTION: GAME 0x00580dc0
void RHSectorProduction::FUN_00580dc0()
{
    RHEngine *engine = g_pEngine;
    for (Occupant *it = m_occupants.begin(); it != m_occupants.end(); ++it)
    {
        RHSectorProductionActor *pc = (RHSectorProductionActor *)engine->GetPC((RHPCDescription *)it->m_0);
        if (pc)
        {
            if (it->m_c == 0xffff)
                ((RHBonusInfoBase *)(pc->m_50 + 4))->FUN_0055fa70(0);
            else
                ((RHBonusInfoBase *)(pc->m_50 + 4))->FUN_0055fa70((*(void ***)((char *)g_unk0x6c0a9c + 0x4144))[it->m_c]);
            *(unsigned short *)(pc->m_50 + 0xde) = ((RHSectorProductionScript *)m_8)->m_36;
            ((RHElementActor *)pc)->FUN_00462700(((RHSectorProductionScript *)m_8)->m_c8);
            ((RHActorPositionCalls *)(pc->m_50 + 4))->FUN_00464530(it->m_point);
            ((RHBonusInfoBase *)(pc->m_50 + 4))->FUN_0055f290();
            ((RHBonusInfo *)pc->m_50)->FUN_005bd560(0, true);
            pc->m_5f0 = m_0;
        }
    }
}

// FUNCTION: GAME 0x00580e80
void RHSectorProduction::FUN_00580e80()
{
    RHSectorProductionRelics &relics = *((RHSectorProductionCampaign *)g_unk0x6c07fc)->FUN_005cb6f0();
    RHEngine *engine = g_pEngine;
    unsigned int index = 0;
    for (Points::iterator it = m_points.begin(); it != m_points.end() && index < relics.size(); ++it)
    {
        Point point = *it;
        RHSectorProductionBonus *bonus = new RHSectorProductionBonus(relics.At(index), 0, 1);
        ((RHActorPositionCalls *)(bonus->m_50 + 4))->FUN_00464530(point.m_point);
        ((RHSectorProductionInfo *)bonus->m_50)->SetLayer(point.m_8);
        ((RHElementActor *)bonus)->FUN_00462700(point.m_a);
        if (point.m_c == 0xffff)
            ((RHBonusInfoBase *)(bonus->m_50 + 4))->FUN_0055fa20(0);
        else
        {
            RHBonusProjection **table = (RHBonusProjection **)((RHSectorProductionGlobal *)g_unk0x6c0a9c)->m_4140.m_first;
            RHBonusProjection *projection = table[point.m_c];
            ((RHBonusInfoBase *)(bonus->m_50 + 4))->FUN_0055fa20(projection);
        }
        ((RHBonusInfoBase *)(bonus->m_50 + 4))->FUN_0055f290();
        ((RHBonusInfo *)bonus->m_50)->FUN_005bd560(0, true);
        ((RHUnk004d8460 *)engine)->FUN_004d8460(bonus, 1, 1);
        ++index;
    }
}

// FUNCTION: GAME 0x00581020
void RHSectorProduction::FUN_00581020(const RHMission *mission)
{
    const RHSectorProductionMission *data = (const RHSectorProductionMission *)mission;
    if (data && data->m_8 == 1)
    {
        float base = m_4 * 0.001;
        double factor = FUN_005806c0() ? 1.5 : g_unk0x00677d90;
        unsigned int count = m_occupants.size();
        int amount = (int)(((float)*(unsigned short *)(data->m_0 + 0x52) * count * factor) * base);
        m_2c += amount;
        m_2e = amount;
    }
}

// FUNCTION: GAME 0x005810c0
void RHSectorProduction::FUN_005810c0(const RHMission *mission)
{
    const RHSectorProductionMission *data = (const RHSectorProductionMission *)mission;
    if (data && data->m_8 == 1)
    {
        float base = m_4 * 0.01;
        float factor = FUN_005806c0() ? g_unk0x00677670 : g_unk0x00677d90;
        unsigned short amount = (unsigned short)((*(unsigned short *)(data->m_0 + 0x52) * factor) * base);
        for (Occupant *it = m_occupants.begin(); it != m_occupants.end(); ++it)
        {
            if (m_0 == 10)
                ((RHSectorProductionPC *)it->m_0)->FUN_0051d4e0(0, amount);
            else if (m_0 == 9 && ((RHSectorProductionPC *)it->m_0)->FUN_0055bb00(1))
                ((RHSectorProductionPC *)it->m_0)->FUN_0051d4e0(1, amount);
        }
    }
}

// FUNCTION: GAME 0x00581180
void RHSectorProduction::FUN_00581180(const RHMission *mission)
{
    const RHSectorProductionMission *data = (const RHSectorProductionMission *)mission;
    if (data && data->m_8 == 1)
    {
        RHEngine *engine = g_pEngine;
        float base = m_4 * 0.01;
        float factor = FUN_005806c0() ? 1.5 : g_unk0x00677d90;
        int amount = (int)((*(unsigned short *)(data->m_0 + 0x52) * factor) * base);
        for (Occupant *it = m_occupants.begin(); it != m_occupants.end(); ++it)
        {
            RHSectorProductionPC *pc = (RHSectorProductionPC *)engine->GetPC((RHPCDescription *)it->m_0);
            pc->FUN_00484360(amount);
        }
    }
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

// TEMPLATE: GAME 0x00581a90
// ?copy@std@@YAPAUOccupant@RHSectorProduction@@PAU23@00@Z

// TEMPLATE: GAME 0x00581300
// ?insert@?$vector@UPoint@RHSectorProduction@@V?$allocator@UPoint@RHSectorProduction@@@std@@@std@@QAEXPAUPoint@RHSectorProduction@@IABU34@@Z

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
    void (Points::*insert)(Point *, unsigned, const Point &) = &Points::insert;
    Point point;
    (m_points.*insert)(m_points.end(), 1, point);
}
