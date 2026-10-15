#include "SBNullstr.h"
#include "RHPositionInterface.h"

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
            m_ec = (char *)m_e8 + 0xa8;
    }
    g_pEngine->SerializeElementPointer(file, m_120);
    m_c.Serialize(file);
    m_20.Serialize(file);
    m_18.Serialize(file);
    m_28.Serialize(file);
    m_3c.Serialize(file);
    m_34.Serialize(file);
    m_44.Serialize(file);
    m_4c.Serialize(file);
    m_54.Serialize(file);
    m_60.Serialize(file);
    m_6c.Serialize(file);
    m_128.Serialize(file);
    m_134.Serialize(file);
    m_c0.Serialize(file);
    m_104.Serialize(file);
    return true;
}

void RHPositionInterface::Emit(SBFile &file)
{
    Turn();
    TurnFast();
    TurnSlow(1);
    TurnAntiVibration();
    Serialize(file);
}
