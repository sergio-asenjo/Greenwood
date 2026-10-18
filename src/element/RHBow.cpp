#include "SBNullstr.h"
#include "RHBow.h"
#include "SB.h"
#include "RHProfileManager.h"
#include <stdlib.h>

RHProfileManager *RHUnk00436500GetProfileManager();
extern float g_rhuirendererportrait_percent;

// FUNCTION: GAME 0x00450070
unsigned RHBow::FUN_00450070(int type) const
{
    unsigned result;
    switch (type)
    {
    case 0: result = (unsigned short)((const Profile *)m_04)->m_00; break;
    case 1: result = (unsigned short)((const Profile *)m_04)->m_28; break;
    }
    return result;
}

// FUNCTION: GAME 0x004500a0
unsigned RHBow::FUN_004500a0() const
{
    const Profile *profile = (const Profile *)m_04;
    if (profile->m_78)
        return (unsigned short)profile->m_28;
    return (unsigned short)profile->m_00;
}

// FUNCTION: GAME 0x004500c0
unsigned RHBow::FUN_004500c0(unsigned skill, unsigned range) const
{
    float distance = (float)range;
    int type = FUN_004504b0(distance);
    unsigned maximum = FUN_00450070(type);
    if (range <= maximum) {
        unsigned percent = (unsigned)(distance / maximum * g_rhuirendererportrait_percent);
        int first;
        int second;
        float secondX;
        if (percent < 20) {
            first = 0;
            second = 1;
            distance = 0.0f;
            secondX = 20.0f;
        } else if (percent < 40) {
            first = 1;
            second = 2;
            distance = 20.0f;
            secondX = 40.0f;
        } else if (percent < 60) {
            first = 2;
            second = 3;
            distance = 40.0f;
            secondX = 60.0f;
        } else if (percent < 80) {
            first = 3;
            second = 4;
            distance = 60.0f;
            secondX = 80.0f;
        } else {
            first = 4;
            second = 5;
            distance = 80.0f;
            secondX = 100.0f;
        }
        int firstSkill;
        int secondSkill;
        if (skill < 50) {
            firstSkill = 0;
            secondSkill = 1;
        } else {
            firstSkill = 1;
            secondSkill = 2;
        }
        float firstChance = Interpolat(distance, secondX,
            (float)((const unsigned short *)m_04)[type * 20 + firstSkill * 6 + first + 2],
            (float)((const unsigned short *)m_04)[type * 20 + firstSkill * 6 + second + 2], (float)percent);
        float secondChance = Interpolat(distance, secondX,
            (float)((const unsigned short *)m_04)[type * 20 + secondSkill * 6 + first + 2],
            (float)((const unsigned short *)m_04)[type * 20 + secondSkill * 6 + second + 2], (float)percent);
        return (unsigned)Interpolat(0.0f, 100.0f, firstChance, secondChance, (float)skill);
    }
    return 0;
}

// FUNCTION: GAME 0x004502e0
short RHBow::FUN_004502e0(unsigned type) const
{
    return *(short *)((char *)m_04 + type * 40 + 2);
}

// FUNCTION: GAME 0x00450300
float RHBow::Interpolat(float firstX, float secondX, float firstY, float secondY, float value)
{
    return (secondY - firstY) / abs((int)(secondX - firstX)) * abs((int)(value - firstX)) + firstY;
}

// FUNCTION: GAME 0x00450350
bool RHBow::Serialize(SBFile &file)
{
    return RHUnk00436500GetProfileManager()->SerializeProfilePointer(file, *(const Profile **)&m_04);
}

void EmitBowAccessors(const RHBow *bow, unsigned type)
{
    bow->FUN_00450070(type);
    bow->FUN_004500a0();
    bow->FUN_004502e0(type);
    bow->FUN_004500c0(type, type);
    RHBow::Interpolat(0, 100, 0, 100, 50);
}

// FUNCTION: GAME 0x00450370
bool RHBow::SerializePointer(SBFile &file, RHBow *&ptr)
{
    bool exists;

    if (!file.m_bLoading)
    {
        exists = (ptr != 0);
        if (file.Access(&exists, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // STRING: GAME 0x006ab8c0
                     "P:\\Robin Hood\\RHBow.cpp",
                     305, "Serialize failed reason is %s", reason);
            return false;
        }
        if (exists)
            return ptr->Serialize(file);
        return true;
    }

    if (file.Access(&exists, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHBow.cpp", 316, "Serialize failed reason is %s", reason);
        return false;
    }
    if (exists)
    {
        ptr = new RHBow;
        return ptr->Serialize(file);
    }
    return true;
}
