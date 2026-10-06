#include "RHSector.h"

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

// Unresolved vector inlining/frame layout; target 0x24, current 0x28.
// STUB: GAME 0x0057e060
int RHSectorLift::Unk0057e060(SBFile &file, RHUnkSectorLiftGrid *grid)
{
    int start = ((RHUnk005f5440 *)&file)->Unk();
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
    return ((RHUnk005f5440 *)&file)->Unk() - start;
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

// deferred: unannotated pending reccmp #534 (0x0057fcc0, recursive ILT call).
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
}

void RHSectorArchery::Emit(SBFile &file)
{
    InitializeFromMissionStream(file);
}

void RHSectorLift::Emit(SBFile &file)
{
    Serialize(file);
}

void RHSectorLift::Emit(SBFile &file, RHUnkSectorLiftGrid *grid)
{
    Unk0057e060(file, grid);
}

void RHSectorDoor::Emit(SBFile &file)
{
    Serialize(file);
}
