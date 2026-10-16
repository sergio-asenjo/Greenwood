#include "SBNullstr.h"
#include "RHElementWasp.h"
#include "RHElementWaspNest.h"
#include "RHEngineSerializationCalls.h"
#include "RHProjectileLifetime.h"

DECOMP_SIZE_ASSERT(RHUnk004bc4d0, 0x178)

// FUNCTION: GAME 0x004bc4d0
RHUnk004bc4d0::RHUnk004bc4d0() : RHProjectileLifetime(0, 0), m_15c(0), m_160(0), m_164(0), m_168(0)
{
    *(unsigned long *)this = 0x00678a0c;
}

// FUNCTION: GAME 0x004bc540
RHUnk004bc4d0::RHUnk004bc4d0(const RHElementWaspNest *nest) : RHProjectileLifetime(0, 0), m_15c(nest), m_160(0), m_164(0), m_168(0)
{
    *(unsigned long *)this = 0x00678a0c;
}

// FUNCTION: GAME 0x004bd0f0
void RHElementWasp::FUN_004bd0f0(void *)
{
    ((RHEngineSerializationCalls *)g_pEngine)->FUN_004d88e0(this, 0, 1);
    ((RHElementWaspNest *)m_15c)->WaspKilled();
}

// FUNCTION: GAME 0x004bd120
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

// FUNCTION: GAME 0x004bd200
int RHElementWasp::VictimCandidatureOrdering::operator()(const VictimCandidature &first, const VictimCandidature &second) const
{
    return first.m_00 < second.m_00;
}

void RHElementWasp::Emit(SBFile &file)
{
    RHUnk004bc4d0 *storage = (RHUnk004bc4d0 *)this;
    storage->RHUnk004bc4d0::RHUnk004bc4d0();
    storage->RHUnk004bc4d0::RHUnk004bc4d0((const RHElementWaspNest *)this);
    FUN_004bd0f0(0);
    Serialize(file);
    VictimCandidatureOrdering ordering;
    VictimCandidature first = {0, this};
    ordering(first, first);
}
