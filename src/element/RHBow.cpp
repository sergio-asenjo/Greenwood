#include "SBNullstr.h"
#include "RHBow.h"
#include "SB.h"
#include "RHProfileManager.h"

RHProfileManager *RHUnk00436500GetProfileManager();

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

// FUNCTION: GAME 0x004502e0
short RHBow::FUN_004502e0(unsigned type) const
{
    return *(short *)((char *)m_04 + type * 40 + 2);
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
