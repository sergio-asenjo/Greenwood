#include "RHSector.h"
#include "RHEngine.h"
#include "VMCore.h"
#include "SBFilePosition.h"

extern RHEngine *g_pEngine;

DECOMP_SIZE_ASSERT(RHSector, 0x58)
DECOMP_SIZE_ASSERT(RHUnk00522540, 0x1c)
DECOMP_SIZE_ASSERT(RHUnkSectorPoints, 0x2c)
DECOMP_SIZE_ASSERT(RHSectorArchery, 0x84)
DECOMP_SIZE_ASSERT(RHSectorScript, 0xf8)
DECOMP_SIZE_ASSERT(RHSectorLift, 0x108)
DECOMP_SIZE_ASSERT(RHUnk0057d440, 0x5c)
DECOMP_SIZE_ASSERT(RHSectorDoor, 0x35)
DECOMP_SIZE_ASSERT(RHSectorBuilding, 0x11c)

class SBGeoBoundingBox2D
{
public:
    void Unk00607dc0(const SBGeoPoint2D &point);
};

class RHScrollScript
{
public:
    bool FUN_006348f0(SBFile &file);
};

struct RHScriptNode
{
    RHScriptNode *next; // 0x00
    RHScriptNode *prev; // 0x04
    void *data; // 0x08
};

struct RHScriptIter
{
    RHScriptNode *node; // 0x00
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

class RHUnk0046eb30
{
public:
    undefined4 allocator; // 0x00
    RHScriptNode *head; // 0x04
    int count; // 0x08
    RHScriptIter erase(RHScriptIter position);
};

// GLOBAL: GAME 0x6c100c
RHElementActor *g_unk0x6c100c;

// GLOBAL: GAME 0x6c0a9c
RHUnkSectorGlobal *g_unk0x6c0a9c;

// GLOBAL: GAME 0x679cc4
float g_unk0x679cc4 = 0.00034836700069718063f;

// GLOBAL: GAME 0x6c0691
char g_unk0x6c0691;

inline void *RHUnkSectorLookup(unsigned short sector)
{
    if (sector == 0xffff)
        return g_unk0x6c0a9c->m_4184;
    return g_unk0x6c0a9c->m_4064[sector];
}

// FUNCTION: GAME 0x00408900
int RHUnkSectorScriptRef::Unk00408900()
{
    ((VMCore *)m_0)->FUN_00639300(&std::string("Initialize"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x004089f0
int RHUnkSectorScriptRef::Unk004089f0(RHElementActor *actor)
{
    ((VMCore *)m_0)->FUN_006392e0(&actor, 4);
    // STRING: GAME 0x006a6cf4
    ((VMCore *)m_0)->FUN_00639300(&std::string("EnterZone"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x00408af0
int RHUnkSectorScriptRef::Unk00408af0(RHElementActor *actor)
{
    ((VMCore *)m_0)->FUN_006392e0(&actor, 4);
    // STRING: GAME 0x006a6d00
    ((VMCore *)m_0)->FUN_00639300(&std::string("ExitZone"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// deferred: 0x0046eb30, parked body; shared by counted callers.
RHScriptIter RHUnk0046eb30::erase(RHScriptIter position)
{
    RHScriptNode *next = *(RHScriptNode *volatile *)&position.node->next;
    position.node->prev->next = position.node->next;
    position.node->next->prev = position.node->prev;
    operator delete(position.node);
    --count;
    return RHScriptIter(next);
}

// FUNCTION: GAME 0x00522540
RHUnk00522540::RHUnk00522540()
{
    m_18 = 0;
}

// FUNCTION: GAME 0x005225a0
void RHUnk00522540::Unk005225a0(SBFile &file)
{
    unsigned short x, y, sector, scratch, value;
    undefined flag;
    file.Access(&x, 2);
    file.Access(&y, 2);
    file.Access(&sector, 2);
    file.Access(&scratch, 2);
    file.Access(&flag, 1);
    file.Access(&value, 2);
    m_4.m_x = x;
    m_4.m_y = y;
    m_10 = RHUnkSectorLookup(sector);
    m_c = *(unsigned short *)((char *)m_10 + 0x36);
    m_14 = flag;
    m_16 = value;
}

// FUNCTION: GAME 0x00522680
bool RHUnk00522540::FUN_00522680(SBFile &file)
{
    return g_pEngine->FUN_004c3d90(file, m_18);
}

class RHUnk0057c920List
{
public:
    RHUnk0057c920List *m_next;
    RHUnk0057c920List *m_prev;
    char m_08[0x10];
};

class RHUnk0057c920
{
public:
    RHUnk0057c920();
    char m_0;
    char m_1[3];
    RHUnk0057c920List *m_4;
    int m_8;
    char m_c[4];
    bool m_10;
};

// FUNCTION: GAME 0x0057c920
RHUnk0057c920::RHUnk0057c920()
{
    char value;
    m_0 = value;
    RHUnk0057c920List *list = new RHUnk0057c920List;
    list->m_next = list;
    list->m_prev = list;
    m_4 = list;
    m_8 = 0;
    m_10 = 1;
}

// FUNCTION: GAME 0x0057c9c0
RHSectorActorIter RHSectorActorIter::operator++(int)
{
    RHSectorActorIter previous = *this;
    m_p = m_p->m_next;
    return previous;
}

// Parked: coordinate-width, scalar-slot and x87 scheduling differ.
// STUB: GAME 0x0057cd60
int RHSector::Unk0057cd60(SBFile &file, bool mode)
{
    SBGeoPoint2D point;
    int start = ((ToolboxPositionFile *)&file)->FUN_005f5440();
    short width = *(short *)((char *)g_unk0x6c0a9c + 0x3e98) << 6;
    short height = *(short *)((char *)g_unk0x6c0a9c + 0x3e9a) << 6;
    undefined type;
    unsigned short count;
    file.Access(&type, 1);
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        short x, y;
        file.Access(&x, 2);
        file.Access(&y, 2);
        if (mode)
        {
            if (x < 0)
                x = 0;
            else if (x > width)
                x = width;
            if (y < 0)
                y = 0;
            else if (y > height)
                y = height;
        }
        point.m_y = y;
        point.m_x = x;
        ((RHUnkSectorPoints *)((char *)this + 4))->FUN_0060ce90(point, i);
        ((SBGeoBoundingBox2D *)((char *)this + 0x3c))->Unk00607dc0(point);
    }
    undefined flag;
    file.Access(&flag, 1);
    ((RHUnkSectorPoints *)((char *)this + 4))->FUN_0060c2e0();
    return ((ToolboxPositionFile *)&file)->FUN_005f5440() - start;
}

// FUNCTION: GAME 0x0057d390
void RHSector::FUN_0057d390(void *, unsigned long, const SBGeoBoundingBox2D &, float, unsigned short)
{
}

// FUNCTION: GAME 0x0057d3a0
RHUnk0057d3a0::RHUnk0057d3a0()
{
    m_30 = 0x20;
}

// FUNCTION: GAME 0x0057d3f0
RHUnk0057d3f0::RHUnk0057d3f0()
{
    m_30 = 4;
}

// FUNCTION: GAME 0x0057d440
RHUnk0057d440::RHUnk0057d440()
{
    m_30 = 0x400;
}

#include <list>

template <class T>
class RHMotionAreaList : public std::list<T>
{
public:
    void *m_cursor;
    char m_dirty;
    void InsertLast(const T &value)
    {
        insert(end(), value);
        m_dirty = 1;
    }
};

// FUNCTION: GAME 0x0057d760
void RHUnk0057d490::FUN_0057d760(void *gate, bool side)
{
    ((RHMotionAreaList<void *> *)((char *)this + 0x5c))->InsertLast(gate);
    ((RHMotionAreaList<bool> *)((char *)this + 0x80))->InsertLast(side);
}

// FUNCTION: GAME 0x0057ed80
RHUnk0057ed80::RHUnk0057ed80()
{
    m_30 = 0x1040;
}

// FUNCTION: GAME 0x0057dc80
RHUnk0057dc80::RHUnk0057dc80()
{
    FUN_0057d490();
    *(unsigned *)this = 0x679c44;
    m_f4 = 0;
    m_f6 = 0;
    m_f9 = 0;
    m_f8 = 0;
    m_fc = 0;
    m_30 = 0x203;
}

void RHUnk0057dc80::FUN_0057d490() {}

// FUNCTION: GAME 0x0057dcf0
int RHSectorLift::FUN_0057dcf0(int animation)
{
    switch (m_f0)
    {
    case 0:
        return animation == 10 ? 294 : 6;
    case 1:
        return animation == 10 ? 10 : 7;
    case 2:
        if (animation != 10)
            return animation == 143 ? 228 : 35;
        return 296;
    case 3:
        return animation == 10 ? 298 : 20;
    }
    return 7;
}

// FUNCTION: GAME 0x0057dd90
int RHSectorLift::FUN_0057dd90(int animation)
{
    switch (m_f0)
    {
    case 0:
        return animation == 10 ? 294 : 6;
    case 1:
        return animation == 10 ? 10 : 7;
    case 2:
        if (animation != 10)
            return animation == 143 ? 231 : 38;
        return 297;
    case 3:
        return animation == 10 ? 299 : 21;
    }
    return 7;
}

#include "RHScriptEngineCalls.h"

// Parked: full-width boolean tail sharing and actor-state comparison differ.
// STUB: GAME 0x0057de30
bool RHSectorLift::FUN_0057de30(RHElementActor *actor)
{
    switch (m_f0)
    {
    case 1:
        if ((actor->m_4 & 7) == 0 && *(int *)((char *)actor + 0x1d0) != 1)
            return false;
        break;
    case 2:
        return (unsigned int)((actor->m_4 & 7) == 4 && (actor->m_4 & 0x1f) == 4);
    case 3:
        return (unsigned int)(actor->UnkType() == RHUnkSectorType12 &&
            ((RHScriptBatchCalls *)actor)->Unk0049d560(21));
    }
    return true;
}

// FUNCTION: GAME 0x0057dea0
void RHSectorGateCalls::FUN_0057dea0(RHElementActor *, bool)
{
    m_b4 = true;
}

// FUNCTION: GAME 0x0057deb0
bool RHSectorGateCalls::FUN_0057deb0(RHElementActor *, bool)
{
    return false;
}

// FUNCTION: GAME 0x0057dec0
bool RHSectorLift::FUN_0057dec0()
{
    if (m_fc)
    {
        --m_fc;
        return false;
    }
    return m_f4 == 0 || m_f9 == 1;
}

// FUNCTION: GAME 0x0057def0
bool RHSectorLift::FUN_0057def0()
{
    if (m_fc)
    {
        --m_fc;
        return false;
    }
    return m_f4 == 0 || m_f8 == 1;
}

#include "RHActorAreaCalls.h"

// FUNCTION: GAME 0x0057df20
void RHActorAreaCalls::FUN_0057df20(RHElementActor *actor, bool mode)
{
    RHSectorLift &lift = *(RHSectorLift *)this;
    if (mode)
    {
        ++lift.m_f4;
        if (actor->UnkType() == RHUnkSectorType12)
            ++lift.m_f6;
        lift.m_f9 = 1;
        lift.m_fc = 100;
    }
    else
    {
        short count = --lift.m_f4;
        if (actor->UnkType() == RHUnkSectorType12)
        {
            --lift.m_f6;
            if (lift.m_f6 < 0)
                lift.m_f6 = 0;
        }
        if (count <= 0)
        {
            lift.m_f4 = 0;
            lift.m_fc = 0;
            lift.m_f9 = 0;
            lift.m_f8 = 0;
        }
    }
}

// FUNCTION: GAME 0x0057dfc0
void RHActorAreaCalls::FUN_0057dfc0(RHElementActor *actor, bool mode)
{
    RHSectorLift &lift = *(RHSectorLift *)this;
    if (mode)
    {
        ++lift.m_f4;
        if (actor->UnkType() == RHUnkSectorType12)
            ++lift.m_f6;
        lift.m_f8 = 1;
        lift.m_fc = 80;
    }
    else
    {
        short count = --lift.m_f4;
        if (actor->UnkType() == RHUnkSectorType12)
        {
            --lift.m_f6;
            if (lift.m_f6 < 0)
                lift.m_f6 = 0;
        }
        if (count <= 0)
        {
            lift.m_f4 = 0;
            lift.m_fc = 0;
            lift.m_f9 = 0;
            lift.m_f8 = 0;
        }
    }
}

// Unresolved vector inlining/frame layout; target 0x24, current 0x28.
// STUB: GAME 0x0057e060
int RHSectorLift::Unk0057e060(SBFile &file, RHUnkSectorLiftGrid *grid)
{
    int start = ((ToolboxPositionFile *)&file)->FUN_005f5440();
    unsigned char type;
    file.Access(&type, 1);
    m_f0 = type;
    if (m_f0 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x5c5,
                 // STRING: GAME 0x6b7224
                 "DIE EU-GESUNDHEITSMINISTER WARNEN : default lifts are no longer supported, please use a simple motion area with \"square\"-doors !");
        m_f0 = 1;
    }
    RHUnk0057d440 *sector = new RHUnk0057d440;
    sector->UnkV4(file, false);
    sector->m_30 = 0x440;
    sector->m_58 = this;
    float minimum = 3.4028234663852886e38f;
    float maximum = -3.4028234663852886e38f;
    unsigned short count;
    file.Access(&count, 2);
    m_104 = 0;
    m_100 = 0;
    RHSectorLiftArray &gates = grid->m_4080;
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk0051aa00 *gate = new RHUnk0051aa00;
        gate->Unk0051b2a0(file, false);
        if (gate->m_1c > maximum)
        {
            m_100 = gate;
            maximum = gate->m_1c;
        }
        if (gate->m_1c < minimum)
        {
            m_104 = gate;
            minimum = gate->m_1c;
        }
        gates.InsertLast(gate);
    }
    file.Access(&m_fa, 2);
    return ((ToolboxPositionFile *)&file)->FUN_005f5440() - start;
}

// FUNCTION: GAME 0x0057e390
bool RHSectorLift::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b72a8
    RHSerializeName(file, "RHSectorLift");
    if (file.Access(&m_f6, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b7208
                 "P:\\Robin Hood\\RHsector.cpp",
                 0x61e, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_f4, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x61f, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_f8, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x620, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_f9, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x621, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_fc, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x622, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

// STUB: GAME 0x0057e970
bool RHSectorBuilding::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b72b8
    RHSerializeName(file, "RHSectorBuilding");
    unsigned short count;
    RHElementActor *actor;
    if (!file.m_bLoading)
    {
        count = (unsigned short)m_f4.m_count;
        if (file.Access(&count, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x6bb, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned short i = 0; i < count; ++i)
        {
            m_f4.Unk005c8e40(i);
            actor = m_f4.CurrentValue();
            if (!g_pEngine->FUN_004c3af0(file, (void *&)actor))
                return false;
        }
    }
    else
    {
        RHSectorActorList &list = m_f4;
        RHSectorActorIter it = list.begin();
        while (it.m_p != list.m_head)
            ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)(it++).m_p));
        list.m_valid = 1;
        if (file.Access(&count, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x6ca, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned short i = 0; i < count; ++i)
        {
            if (!g_pEngine->FUN_004c3af0(file, (void *&)actor))
                return false;
            list.insert(RHSectorActorIter(list.m_head), actor);
            list.m_valid = 1;
        }
    }
    if (file.Access(&m_118, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x6d8, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x0057edd0
bool RHSectorDoor::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b72cc
    RHSerializeName(file, "RHSectorDoor");
    if (file.Access(&m_34, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x7e6, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

// Unresolved Access/resize scheduling.
// STUB: GAME 0x0057f360
void RHSectorArchery::InitializeFromMissionStream(SBFile &file)
{
    unsigned short sector;
    file.Access(&sector, 2);
    m_78 = RHUnkSectorLookup(sector);
    unsigned short scratch;
    file.Access(&scratch, 2);
    Unk0057cd60(file, false);
    unsigned short count;
    file.Access(&count, 2);
    m_58.Resize(count);
    m_7c = 0xffff;
    m_80 = 0;
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk00522540 *point = new RHUnk00522540;
        point->Unk005225a0(file);
        m_58[i] = point;
        if (point->m_14)
        {
            if (m_7c == 0xffff)
                m_7c = i;
            ++m_80;
            m_7e = i;
            if (i == 0 || i == count - 1)
                SBAssert(1, "P:\\Robin Hood\\RHsector.cpp", 0x8e4,
                         // STRING: GAME 0x6b72dc
                         "Archery path with shooting point at end detected - this is not allowed!");
        }
    }
}

// FUNCTION: GAME 0x0057f520
bool RHSectorArchery::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b7324
    RHSerializeName(file, "RHSectorArchery");
    if (file.Access(&m_82, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x8fd, "Serialize failed reason is %s", reason);
        return false;
    }
    unsigned short count = (unsigned short)m_58.size();
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk00522540 *entry = m_58[i];
        if (!entry->FUN_00522680(file))
            return false;
    }
    return true;
}

// FUNCTION: GAME 0x0057f8c0
void RHSectorScript::InitializeFromMissionStream(SBFile &file)
{
    ((RHSector *)this)->Unk0057cd60(file, false);
    SBGeoPoint2D point;
    RHUnkSectorPoints &points = *(RHUnkSectorPoints *)((char *)this + 4);
    unsigned int count = (unsigned short)points.Unk0060ce80();
    for (unsigned int i = 0; i < count; ++i)
    {
        point = points.Unk0060cef0(i);
        float y = point.m_y;
        point.m_y = y + g_unk0x679cc4;
        points.Unk0060ced0(point, i);
    }
    file.Access(&m_c8, 2);
    file.Access(&m_36, 2);
    file.Access(&m_b8, 1);
    if (m_b8)
    {
        unsigned short length;
        file.Access(&length, 2);
        m_c0 = new char[length + 1];
        file.Access(m_c0, length);
        m_c0[length] = 0;
        if (g_unk0x6c0691)
        {
            if (!((RHUnkSectorScript *)((char *)this + 0x58))->Unk00639a30(m_c0))
                SBAssert(1, "P:\\Robin Hood\\RHsector.cpp", 0x971,
                         // STRING: GAME 0x6b7334
                         "Structural error in RHD, a Sector has got a script reference that does not exist !");
            *(RHUnkSectorScript **)&m_c4 = this ? (RHUnkSectorScript *)((char *)this + 0x58) : 0;
            m_c4.Unk00408900();
        }
        else
            m_b8 = 0;
    }
}

// STUB: GAME 0x0057fae0
bool RHSectorScript::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b7388
    RHSerializeName(file, "RHSectorScript");
    unsigned short count;
    RHElementActor *actor;
    if (!file.m_bLoading)
    {
        count = (unsigned short)m_cc.m_count;
        if (file.Access(&count, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x990, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned short i = 0; i < count; ++i)
        {
            m_cc.Unk005c8e40(i);
            actor = m_cc.CurrentValue();
            if (!g_pEngine->FUN_004c3af0(file, (void *&)actor))
                return false;
        }
    }
    else
    {
        RHSectorActorList &list = m_cc;
        RHSectorActorNode *it = list.m_head->m_next;
        while (it != list.m_head)
        {
            RHSectorActorNode *previous = it;
            it = it->m_next;
            ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)previous));
        }
        list.m_valid = 1;
        if (file.Access(&count, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x99f, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned short i = 0; i < count; ++i)
        {
            if (!g_pEngine->FUN_004c3af0(file, (void *&)actor))
                return false;
            list.insert(RHSectorActorIter(list.m_head), actor);
            list.m_valid = 1;
        }
    }
    if (g_unk0x6c0691 && m_b8)
        ((RHScrollScript *)((char *)this + 0x58))->FUN_006348f0(file);
    return true;
}

// FUNCTION: GAME 0x0057fcc0
void RHSectorScript::Enter(RHElementActor *actor)
{
    RHSectorActorList &list = m_cc;
    if (list.FindValue(actor) != -1)
    {
        SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x9c5,
                 // STRING: GAME 0x6b7398
                 "VERBOTEN : Actor entering a script sector twice (%3.2f,%3.2f) !",
                 actor->m_50->m_24, actor->m_50->m_28);
    }
    else
    {
        list.insert(RHSectorActorIter(list.m_head->m_next), actor);
        list.m_valid = 1;
    }
    if (m_b8)
    {
        RHElementActor *saved = g_unk0x6c100c;
        g_unk0x6c100c = actor;
        m_c4.Unk004089f0(actor);
        g_unk0x6c100c = saved;
    }
    if (actor->UnkType() == RHUnkSectorType12 && actor->m_5cc)
        Enter(actor->m_5cc);
    if (actor->UnkType() == RHUnkSectorType12 && m_f4 != 0xe)
        actor->m_5f0 = m_f4;
}

// Recursive ILT call plus unresolved inlined-list register allocation.
// STUB: GAME 0x0057fdb0
void RHSectorScript::Leave(RHElementActor *actor)
{
    RHSectorActorList &list = m_cc;
    unsigned short index = (unsigned short)list.Find(actor);
    if (index == 0xffff)
    {
        SBAssert(0, "P:\\Robin Hood\\RHsector.cpp", 0x9fe,
                 // STRING: GAME 0x6b73d8
                 "VERBOTEN : Actor leaving a script sector he hadn't entered (%3.2f,%3.2f) !",
                 actor->m_50->m_24, actor->m_50->m_28);
    }
    else
    {
        list.Unk005c8e40(index);
        list.erase(list.Current());
        list.m_valid = 1;
    }
    if (m_b8)
    {
        RHElementActor *saved = g_unk0x6c100c;
        g_unk0x6c100c = actor;
        m_c4.Unk00408af0(actor);
        g_unk0x6c100c = saved;
    }
    if (actor->UnkType() == RHUnkSectorType12 && actor->m_5cc)
        Leave(actor->m_5cc);
    if (actor->UnkType() == RHUnkSectorType12 && m_f4 != 0xe)
        actor->m_5f0 = 0xc;
}

void RHSectorScript::Emit(RHElementActor *actor)
{
    Enter(actor);
    Leave(actor);
}

void RHSectorScript::Emit(SBFile &file)
{
    InitializeFromMissionStream(file);
    Serialize(file);
}

void RHSectorBuilding::Emit(SBFile &file)
{
    Serialize(file);
}

void RHSectorArchery::Emit(SBFile &file)
{
    InitializeFromMissionStream(file);
    Serialize(file);
}

void RHSectorLift::Emit(SBFile &file)
{
    FUN_0057dcf0(0);
    FUN_0057dd90(0);
    FUN_0057de30(0);
    FUN_0057dec0();
    FUN_0057def0();
    Serialize(file);
}

void RHUnk0057d490::Emit(void *gate, bool side)
{
    FUN_0057d760(gate, side);
}

void RHSectorLift::Emit(SBFile &file, RHUnkSectorLiftGrid *grid)
{
    Unk0057e060(file, grid);
}

void RHSectorDoor::Emit(SBFile &file)
{
    Serialize(file);
}

// FUNCTION: GAME 0x0060ced0
void RHUnkSectorPoints::Unk0060ced0(const SBGeoPoint2D &point, unsigned int index)
{
    m_28 = 0;
    m_29 = 0;
    FUN_006112a0(point, index);
}

// FUNCTION: GAME 0x0060cef0
SBGeoPoint2D &RHUnkSectorPoints::Unk0060cef0(unsigned int index)
{
    return FUN_006112c0(index);
}

void EmitRHSectorVariants(void *storage)
{
    ((RHUnk0057d3a0 *)storage)->RHUnk0057d3a0::RHUnk0057d3a0();
    ((RHUnk0057d3f0 *)storage)->RHUnk0057d3f0::RHUnk0057d3f0();
    ((RHUnk0057ed80 *)storage)->RHUnk0057ed80::RHUnk0057ed80();
    ((RHUnk0057dc80 *)storage)->RHUnk0057dc80::RHUnk0057dc80();
}
