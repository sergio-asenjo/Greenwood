#include "SBNullstr.h"
#include "RHGate.h"
#include "RHFastFindGrid.h"
#include "RHMalignityActorCalls.h"

class RHScriptBatchCalls
{
public:
    bool Unk0049d560(int action);
};

class RHSectorGateCalls
{
public:
    bool FUN_0057deb0(RHElementActor *actor, bool mode);
};

class RHSectorLift
{
public:
    bool FUN_0057de30(RHElementActor *actor);
};

// Parked: permission-call cross-jumping and common return block placement differ.
// STUB: GAME 0x0051abe0
bool RHUnk0051aa00::FUN_0051abe0(bool first, RHElementActor *actor, bool, bool, bool force)
{
    if (!force && m_88 == 8)
        goto fail;
    if (m_8c[0] && m_b4[0] && (*(unsigned *)((char *)actor + 4) & 0xf) == 0xc)
        return ((RHSectorGateCalls *)this)->FUN_0057deb0(actor, first);
    if (!*((char *)this + 8))
        goto fail;
    switch (m_88)
    {
    case 1:
    {
        unsigned flags;
        flags = *(unsigned *)((char *)actor + 4);
        if ((flags & 0xf) == 0xc)
        {
            if (m_8c[0])
            {
                if (!((RHScriptBatchCalls *)actor)->Unk0049d560(0x1c))
                    goto fail;
                return *(bool *)&m_8c[3];
            }
            break;
        }
        if ((flags & 0xf) != 4)
            goto fail;
        if (first && *(int *)((char *)m_10 + 0xfc) >= *(unsigned short *)((char *)m_10 + 0xf0))
            goto fail;
        flags &= 0x1f;
        if (flags == 4)
            return (unsigned int)!m_8c[2];
        if (flags != 0x14 || ((RHMalignityActorCalls *)actor)->Vf4())
            goto fail;
        return (unsigned int)!m_8c[1];
    }
    case 2:
    {
        unsigned flags = *(unsigned *)((char *)actor + 4);
        if ((flags & 0xf) == 0xc)
        {
            if (m_8c[0])
            {
                if (!((RHScriptBatchCalls *)actor)->Unk0049d560(0x1c))
                    goto fail;
                return *(bool *)&m_8c[3];
            }
            break;
        }
        if ((flags & 0xf) != 4)
            goto fail;
        if (first && *(int *)((char *)m_10 + 0xfc) >= *(unsigned short *)((char *)m_10 + 0xf0))
            goto fail;
        flags &= 0x1f;
        if (flags == 4)
            goto fail;
        if (flags != 0x14 || ((RHMalignityActorCalls *)actor)->Vf4())
            goto fail;
        return (unsigned int)!m_8c[1];
    }
    case 0:
    case 3:
    case 7:
    case 8:
    {
        unsigned flags = *(unsigned *)((char *)actor + 4);
        if (flags == 0x103)
            return (unsigned int)!m_8c[2];
        if ((flags & 0xf) == 0xc)
        {
            if (m_8c[0])
            {
                if (!((RHScriptBatchCalls *)actor)->Unk0049d560(0x1c))
                    goto fail;
                return *(bool *)&m_8c[3];
            }
            break;
        }
        if ((flags & 0xf) == 4)
        {
            if ((flags & 0x1f) == 4)
                return (unsigned int)!m_8c[2];
            if ((flags & 0x1f) == 0x14)
                return (unsigned int)!m_8c[1];
        }
        if ((flags & 7) == 0 && *(int *)((char *)actor + 0x1d0) == 7)
            return (unsigned int)!m_8c[2];
        goto fail;
    }
    case 4:
    case 5:
    case 6:
        if ((*(unsigned *)((char *)actor + 4) & 7) == 4 && ((RHMalignityActorCalls *)actor)->Vf4())
            goto fail;
        return ((RHSectorLift *)m_10)->FUN_0057de30(actor);
    default:
        break;
    }
    return true;
fail:
    return false;
}

// FUNCTION: GAME 0x0051ae30
bool RHGate::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b05fc
    RHSerializeName(file, "RHDoor");

    if (file.Access(&m_8c, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x006b05e0
                 "P:\\Robin Hood\\RHGate.cpp",
                 413, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_8d, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 414, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_8e, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 415, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_8f, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 416, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_b4, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 418, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_b6, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 419, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_b8, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 420, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}
