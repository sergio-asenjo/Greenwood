#include "SBNullstr.h"
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

#include "RHSectorLift.h"

// GLOBAL: GAME 0x006c0b68
RHFastFindCursorList g_gateLinks;

// TEMPLATE: GAME 0x00424410 FOLDED
// ?insert@?$list@PAURHGateLink@@V?$allocator@PAURHGateLink@@@std@@@std@@QAE?AViterator@12@V312@ABQAURHGateLink@@@Z

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@?$list@PAURHGateLink@@V?$allocator@PAURHGateLink@@@std@@@std@@QAE?AViterator@12@V312@@Z

// TEMPLATE: GAME 0x0057c9c0 FOLDED
// ??Eiterator@?$list@PAURHGateLink@@V?$allocator@PAURHGateLink@@@std@@@std@@QAE?AV012@H@Z

// FUNCTION: GAME 0x0051a690
void RHUnk0051a5e0::Link(RHUnk0051a5e0 *other)
{
    RHGateLink *link = 0;
    if (m_10 == other->FirstSector())
    {
        link = new RHGateLink;
        g_gateLinks.InsertLast(link);
        m_2c.InsertLast(link);
        other->m_2c.Append(link);
        link->distance = ((RHUnk005fc3b0 &)m_20.Unk005fc110(other->m_20)).Unk005fc6a0(1.0f);
        link->sector = m_10;
        link->second = this;
        link->first = other;
    }
    if (m_10 == other->SecondSector())
    {
        link = new RHGateLink;
        g_gateLinks.InsertLast(link);
        m_2c.InsertLast(link);
        other->m_50.InsertValue(link);
        link->distance = ((RHUnk005fc3b0 &)m_20.Unk005fc110(other->m_18)).Unk005fc6a0(1.0f);
        link->sector = m_10;
        link->second = this;
        link->first = other;
    }
    if (m_0c == other->FirstSector())
    {
        link = new RHGateLink;
        g_gateLinks.InsertLast(link);
        m_50.InsertLast(link);
        other->m_2c.Append(link);
        link->distance = ((RHUnk005fc3b0 &)m_18.Unk005fc110(other->m_20)).Unk005fc6a0(1.0f);
        link->sector = m_0c;
        link->second = this;
        link->first = other;
    }
    if (m_0c == other->SecondSector())
    {
        link = new RHGateLink;
        g_gateLinks.InsertLast(link);
        m_50.InsertLast(link);
        other->m_50.InsertValue(link);
        link->distance = ((RHUnk005fc3b0 &)m_18.Unk005fc110(other->m_18)).Unk005fc6a0(1.0f);
        link->sector = m_0c;
        link->second = this;
        link->first = other;
    }
}

// SYNTHETIC: GAME 0x0051aa90
// RHUnk0051a5e0::~RHUnk0051a5e0

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
bool RHUnk0051aa00::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b05fc
    RHSerializeName(file, "RHDoor");

    if (file.Access(&m_8c[0], 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x006b05e0
                 "P:\\Robin Hood\\RHGate.cpp",
                 413, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_8c[1], 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 414, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_8c[2], 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 415, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_8c[3], 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 416, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_b4[0], 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 418, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_b4[2], 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 419, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_b4[4], 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 420, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}

// STUB: GAME 0x0051b110
void RHUnk0051aa00::AdaptPoints()
{
    switch (m_88)
    {
    case 2:
    {
        SBGeoVector2D direction = m_20.Unk005fc110(m_94);
        ((RHUnk005fc3b0 &)direction).FUN_005fc7c0(1.0f);
        ((RHUnk005fc3b0 &)direction).FUN_005fc4d0(60.0f);
        m_20 = m_94;
        m_20.FUN_005fc1e0(direction);
        break;
    }
    case 4:
        if (*(int *)((char *)m_10 + 0xf0) == 3)
        {
            SBGeoVector2D direction = m_20.Unk005fc110(m_94);
            ((RHUnk005fc3b0 &)direction).FUN_005fc7c0(1.0f);
            ((RHUnk005fc3b0 &)direction).FUN_005fc4d0(60.0f);
            m_20 = m_94;
            m_20.FUN_005fc1e0(direction);
        }
        break;
    case 6:
        if (*(int *)((char *)m_10 + 0xf0) == 3)
        {
            SBGeoVector2D direction = m_20.Unk005fc110(m_94);
            ((RHUnk005fc3b0 &)direction).FUN_005fc7c0(1.0f);
            ((RHUnk005fc3b0 &)direction).FUN_005fc4d0(65.0f);
            m_20 = m_94;
            m_20.FUN_005fc1e0(direction);
        }
        break;
    }
}

#include "RHSectorBuilding.h"

// STUB: GAME 0x0051b6e0
RHUnk0051b6e0::RHUnk0051b6e0(RHUnk0051e1e0 *first, RHUnk0051e1e0 *second)
{
    *(int *)m_04 = 2;
    m_04[4] = 1;
    m_88 = first;
    m_8c = second;
    m_20 = *(SBGeoPoint2D *)((char *)first + 4);
    {
        SBGeoVector2D direction(*(SBGeoVector2D *)((char *)first + 0xc));
        m_20.FUN_005fc1e0(direction);
    }
    m_20.m_x *= 0.5f;
    m_20.m_y *= 0.5f;
    m_18 = *(SBGeoPoint2D *)((char *)second + 4);
    {
        SBGeoVector2D direction(*(SBGeoVector2D *)((char *)second + 0xc));
        m_18.FUN_005fc1e0(direction);
    }
    m_18.m_x *= 0.5f;
    m_18.m_y *= 0.5f;
    m_10 = (RHFastFindSector *)first->m_owner;
    m_0c = (RHFastFindSector *)second->m_owner;
    ((RHUnk0057d490 *)m_10)->FUN_0057d760(this, false);
    ((RHUnk0057d490 *)m_0c)->FUN_0057d760(this, true);
    m_16 = first->GetLayer();
    m_14 = second->GetLayer();
    *(float *)m_28 = ((RHUnk005fc3b0 &)m_20.Unk005fc110(m_18)).Unk005fc6a0(1.0f) + 200.0f;
}
