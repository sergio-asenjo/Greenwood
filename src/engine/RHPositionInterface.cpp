#include "SBNullstr.h"
#include "RHPositionInterface.h"
#include "RHOrder.h"

class RHBonusInfoBase : public RHPositionInterface
{
public:
    void FUN_0055f290();
};

// FUNCTION: GAME 0x0055eee0
RHPositionInterface::RHPositionInterface(unsigned long owner)
{
    m_4 = 0;
    m_8 = 0;
    m_d8 = 2;
    m_d6 = 0;
    m_ec = 0;
    m_f0 = 0;
    m_dc = 0;
    m_e8 = 0;
    m_f8 = *(int *)((char *)g_unk0x6c0a9c + 0x4188);
    m_88 = 1;
    m_8c = 1;
    m_e4 = 0;
    m_e0 = 0;
    m_90 = 0xffff;
    m_92 = 0xffff;
    m_bc = 0;
    SetVector(m_134, 0.0f, 0.0f, 0.0f);
    m_124 = 0;
    SetPoint(m_128, 0.0f, 0.0f);
    m_d4 = 0;
    m_d6 = 0;
    m_74 = 0;
    m_7c = 0;
    m_78 = 0;
    m_fc = 0;
    m_fd = 1;
    m_fe = 0;
    m_100 = 0;
    m_104.FUN_00607d90();
    m_11c = 4.0f;
    m_120 = 0;
    m_d9 = 0;
    m_130 = 0;
    m_0 = owner;
}

// FUNCTION: GAME 0x0055f0f0
bool RHPositionInterface::Turn()
{
    if (m_fe)
        return TurnAntiVibration();
    unsigned short difference = (unsigned short)(m_d6 - m_d4);
    difference &= 15;
    if (difference == 0)
        return false;
    if (difference < 8)
        m_d4 = (unsigned short)(m_d4 + 1) & 15;
    else
        m_d4 = (unsigned short)(m_d4 - 1) & 15;
    return true;
}

// FUNCTION: GAME 0x0055f140
bool RHPositionInterface::TurnFast()
{
    unsigned short difference = (unsigned short)(m_d6 - m_d4);
    difference &= 15;
    if (difference == 0)
        return false;
    if (difference < 8)
    {
        if (difference >= 2)
        {
            m_d4 = (unsigned short)(m_d4 + 2) & 15;
            return true;
        }
    }
    else if (difference <= 14)
    {
        m_d4 = (unsigned short)(m_d4 - 2) & 15;
        return true;
    }
    m_d4 = (unsigned short)(m_d4 + difference) & 15;
    return true;
}

// FUNCTION: GAME 0x0055f1a0
bool RHPositionInterface::TurnSlow(unsigned char delay)
{
    if (m_d8 == 0)
    {
        unsigned short difference = (unsigned short)(m_d6 - m_d4);
        difference &= 15;
        if (difference == 0)
            return false;
        m_d8 = delay;
        if (difference < 8)
            m_d4 = (unsigned short)(m_d4 + 1) & 15;
        else
            m_d4 = (unsigned short)(m_d4 - 1) & 15;
    }
    else
        --m_d8;
    return true;
}

// FUNCTION: GAME 0x0055f210
bool RHPositionInterface::TurnAntiVibration()
{
    unsigned short difference = (unsigned short)(m_d6 - m_d4);
    difference &= 15;
    if (difference == 0)
        return false;
    if (difference < 8)
    {
        if (m_d9 >= 2)
            m_d4 = (unsigned short)(m_d4 + 1) & 15;
        else if (m_d9 < 0)
            m_d9 = 0;
        else
            ++m_d9;
    }
    else
    {
        if (m_d9 <= -2)
            m_d4 = (unsigned short)(m_d4 - 1) & 15;
        else if (m_d9 > 0)
            m_d9 = 0;
        else
            --m_d9;
    }
    return true;
}

// Parked: VC6 sinks the ebp/edi saves past the state check and swaps one slope product.
// STUB: GAME 0x0055f290
void RHBonusInfoBase::FUN_0055f290()
{
    if (m_4 == 7)
        return;
    if ((char)m_4 & 1)
    {
        MapFrom3D();
        SpriteFromMap();
    }
    else if ((char)(m_4 >> 1) & 1)
    {
        SpriteFromMap();
        Position3DFromMap();
    }
    else if ((char)(m_4 >> 2) & 1)
    {
        m_20 = m_18.Unk005fc190(m_80);
        UpdateBox();
        Position3DFromMap();
    }
    m_4 = 7;
}

// FUNCTION: GAME 0x0055f550
void RHSpritePositionCalls::FUN_0055f550()
{
    if (IsMapValid())
        return;
    if (IsSpriteValid())
    {
        m_20 = m_18.Unk005fc190(m_80);
        UpdateBox();
    }
    else
    {
        MapFrom3D();
    }
    m_4 |= 2;
}

// FUNCTION: GAME 0x0055f6d0
void RHPositionInterface::ComputePositionSprite()
{
    if ((char)(m_4 >> 2) & 1)
        return;
    if ((char)(m_4 >> 1) & 1)
    {
        m_18 = m_20.FUN_005fc200(m_80);
        Floor(m_18.m_x);
        Floor(m_18.m_y);
        m_4 |= 4;
    }
    else
    {
        MapFrom3D();
        m_18 = m_20.FUN_005fc200(m_80);
        Floor(m_18.m_x);
        Floor(m_18.m_y);
        m_4 = 7;
    }
}

// FUNCTION: GAME 0x0055f870
void RHPositionInterface::ComputePosition3D()
{
    if (Is3DValid())
        return;
    if (IsMapValid())
    {
        Position3DFromMap();
        m_4 |= 1;
    }
    else
    {
        m_20 = m_18.Unk005fc190(m_80);
        UpdateBox();
        Position3DFromMap();
        m_4 = 7;
    }
}

// Parked: effective only; VC6 orders the second slope product operands the other way.
// STUB: GAME 0x0055fc20
void RHMobilePosition::FUN_0055fc20(bool updateDirection)
{
    if (m_8 == 7)
        return;
    bool stationary = false;
    if (Increment3DValid())
    {
        m_6c.m_x = m_60.x;
        m_6c.m_y = m_60.y - m_60.z;
    }
    else if (IncrementMapValid())
        Increment3DFromMap();
    else
    {
        m_6c = m_44.Unk005fc110(m_20);
        stationary = m_6c.FUN_005fc700(1.0f) < 1.0f;
        if (!((RHUnk005fc3b0 &)m_6c).IsZero())
        {
            ((RHUnk005fc3b0 &)m_6c).FUN_005fc7c0(1.0f);
            Increment3DFromMap();
        }
    }
    if (updateDirection && !stationary)
    {
        if (m_74)
            SetHeading(((const RHUnk005fc3b0 &)SBGeoVector2D(m_60.x, m_60.y)).FUN_005fcc50(1.0f) ^ 8);
        else
            SetHeading(((const RHUnk005fc3b0 &)SBGeoVector2D(m_60.x, m_60.y)).FUN_005fcc50(1.0f));
    }
    m_8 = 7;
}

// FUNCTION: GAME 0x0055fe10
bool RHPositionInterface::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b1930
    RHSerializeName(file, "RHPositionInterface");

    if (file.Access(&m_4, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x006b1908
                 "P:\\Robin Hood\\RHpositioninterface.cpp",
                 727, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_8, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 728, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_f8, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 729, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_88, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 730, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_8c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 731, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_d4, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 732, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_d6, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 733, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_d8, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 734, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_da, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 735, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_e0, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 736, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_78, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 737, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_7c, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 738, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_124, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 739, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_fd, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 740, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_fc, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 741, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_fe, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 742, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_d9, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 743, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_f4, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 745, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_74, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 746, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_100, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 748, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_118, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 749, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_bc, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHpositioninterface.cpp", 751, "Serialize failed reason is %s", reason);
        return false;
    }

    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_dc);
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_e4);
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fc030(file, m_f0);
    if (m_da == 0xffff)
        ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fc2d0(file, m_e8);
    else
        ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fc180(file, m_e8);
    if (file.m_bLoading)
    {
        if (m_e8 == 0)
            m_ec = 0;
        else
            m_ec = (RHPositionSlope *)((char *)m_e8 + 0xa8);
    }
    g_pEngine->SerializeElementPointer(file, m_120);
    ((RHUnk005df510 *)&m_c)->Serialize(file);
    m_20.Serialize(file);
    m_18.Serialize(file);
    ((RHUnk005df510 *)&m_28)->Serialize(file);
    m_3c.Serialize(file);
    m_34.Serialize(file);
    m_44.Serialize(file);
    m_4c.Serialize(file);
    ((RHUnk005df510 *)&m_54)->Serialize(file);
    ((RHUnk005df510 *)&m_60)->Serialize(file);
    m_6c.Serialize(file);
    m_128.Serialize(file);
    ((RHUnk005df510 *)&m_134)->Serialize(file);
    m_c0.Serialize(file);
    m_104.Serialize(file);
    return true;
}

// FUNCTION: GAME 0x005b5ab0
RHPositionInterface::~RHPositionInterface()
{
}

void RHPositionInterface::Emit(SBFile &file)
{
    Turn();
    TurnFast();
    TurnSlow(1);
    TurnAntiVibration();
    Serialize(file);
}

class RHEngineReinforcementCalls
{
public:
    bool FUN_004f6c20(const SBGeoPoint2D &, SBGeoPoint2D &, unsigned short, const SBGeoPoint2D &);
};

// FUNCTION: GAME 0x00560460
bool RHSpritePositionCalls::FUN_00560460()
{
    if (m_fe)
    {
        if (m_fc)
            return ((RHEngineReinforcementCalls *)g_unk0x6c0a9c)->FUN_004f6c20(m_20, m_4c, m_da, FUN_004a4a10());
        if (m_100 == 0)
        {
            if (!m_7c)
                return m_6c.FUN_005fc660(m_44.Unk005fc110(m_20)) <= *(float *)&m_78;
            else
            {
                SBGeoVector2D direction(m_6c);
                SBGeoVector2D delta = m_44.Unk005fc110(m_20);
                delta.m_y *= 1.7434468269348145f;
                return direction.FUN_005fc660(delta) <= *(float *)&m_78;
            }
        }
        if (m_120 && *(int *)((char *)m_120 + 4) != 0x103)
        {
            if (WithinTargetRadius(*(float *)((char *)*(void **)((char *)m_120 + 0x50) + 0x11c), m_44.Unk005fc110(m_20)))
                return true;
        }
        return m_44.Unk005fc110(m_20).FUN_005fc700(1.0f) < 10.0f;
    }
    else
    {
        if (!m_7c)
            return m_6c.FUN_005fc660(m_44.Unk005fc110(m_20)) <= *(float *)&m_78;
        else
        {
            SBGeoVector2D direction(m_6c);
            SBGeoVector2D delta = m_44.Unk005fc110(m_20);
            delta.m_y *= 1.7434468269348145f;
            return direction.FUN_005fc660(delta) <= *(float *)&m_78;
        }
    }
}

// Parked: duration widening and one reciprocal product are scheduled differently.
// STUB: GAME 0x00560780
void RHSpritePositionCalls::FUN_00560780(float distance, unsigned short duration)
{
    m_134 = Divided(Scaled(distance, m_60), duration);
}
