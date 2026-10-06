#include "RHElementScroll.h"

// GLOBAL: GAME 0x006c09ec
RHElementScroll *g_scrollExecutingScript;

// Parked: local coloring and projection-branch scheduling.
// STUB: GAME 0x004ba030
void RHElementScroll::InitializeFromMissionStream(SBFile &file)
{
    std::string unused;
    unsigned short x;
    unsigned short y;
    unsigned flags;
    unsigned value;
    unsigned short projectionIndex;
    unsigned short index;
    unsigned short layer;
    char taken;
    char scripted;
    file.Access(&x, 2);
    file.Access(&y, 2);
    file.Access(&flags, 4);
    file.Access(&value, 4);
    file.Access(&projectionIndex, 2);
    file.Access(&index, 2);
    file.Access(&layer, 2);
    file.Access(m_16c, 3);
    file.Access(&m_16f, 1);
    file.Access(&taken, 1);
    if (taken)
        ((RHUnk004ba7a0 *)this)->Set(1);
    file.Access(&scripted, 1);
    if (scripted)
    {
        std::string name;
        FUN_005e0c90(file, name);
        if (name.empty())
            SBAssert(1,
                     // STRING: GAME 0x006aedd0
                     "P:\\Robin Hood\\RHElementScroll.Cpp", 101,
                     // STRING: GAME 0x006ae798
                     "Script error: a scripted object had no valid script class name.");
        if (g_unk0x6c0691 == 1)
        {
            RHUnkSectorScript *script = (RHUnkSectorScript *)&m_100;
            script->Unk00639a30(name);
            m_160 = this ? script : 0;
        }
    }
    Info()->m_4.SetPoint(SBGeoPoint2D((float)x, (float)y));
    Info()->m_4.m_da = layer;
    Info()->m_e0 = index == 0xffff ? Global()->m_4184 : Global()->m_4064[index];
    RHBonusProjection *projection;
    if (projectionIndex != 0xffff)
        projection = Global()->m_4144[projectionIndex];
    else
        projection = 0;
    if (projection != 0)
    {
        if (!(projection->Flags() & 1))
            SBAssert(1, "P:\\Robin Hood\\RHElementScroll.Cpp", 245,
                     // STRING: GAME 0x006ae404
                     "DA F\xc4LLT MIR NICHTS MEHR EIN ! Civilian (%d,%d) not lying on projection area !",
                     Info()->X(), Info()->Y());
        if (!projection->Inside(Info()->m_4.m_20))
            SBAssert(1, "P:\\Robin Hood\\RHElementScroll.Cpp", 249,
                     // STRING: GAME 0x006ae39c
                     "DA F\xc4LLT MIR NICHTS MEHR EIN ! Civilian (%d,%d) map position not lying in projection area screen box !",
                     Info()->X(), Info()->Y());
    }
    Info()->m_4.FUN_0055fa20(projection);
    Info()->m_4.FUN_0055f290();
    Info()->FUN_005bd560(0, true);
    Info()->m_4.m_28 = Info()->m_4.m_c;
    Info()->RestorePoint();
    Info()->m_4.SetFlags(flags & 0xf);
    FUN_004ba400();
}

// deferred: 0x004ba690, 98.48% annotated; sole diff is the matched base call, pending reccmp #534.
bool RHElementScroll::Serialize(SBFile &file)
{
    RHSerializeName(file,
                    // STRING: GAME 0x006aedf4
                    "RHElementScroll");
    if (file.Access(&m_164, 4) < 0)
    {
        SBString *err = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementScroll.Cpp", 497,
                 "Serialize failed reason is %s", err->m_chars ? err->m_chars : "");
        return false;
    }
    if (file.Access(&m_168, 4) < 0)
    {
        SBString *err = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementScroll.Cpp", 498,
                 "Serialize failed reason is %s", err->m_chars ? err->m_chars : "");
        return false;
    }
    if (file.m_version > 7 && g_unk0x6c0691 && m_100.m_58)
        m_100.FUN_006348f0(file);
    return RHElementObject::Serialize(file);
}

// FUNCTION: GAME 0x004ba760
void RHElementScroll::SetScrollExecutingScript(RHElementScroll *scroll)
{
    if (g_scrollExecutingScript)
        SBAssert(1, "P:\\Robin Hood\\RHElementScroll.Cpp", 525,
                 // STRING: GAME 0x006aee04
                 "Fatal: two scrolls cannot execute script at the same time.");
    g_scrollExecutingScript = scroll;
}

void RHElementScroll::Emit(SBFile &file)
{
    InitializeFromMissionStream(file);
    Serialize(file);
    SetScrollExecutingScript(this);
}
