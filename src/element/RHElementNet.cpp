#include "SBNullstr.h"
#include "RHElementNet.h"
#include "RHPCActionQueryCalls.h"

class RHSprite
{
public:
    bool FUN_005b9e30(void *first, void *second, bool third);
};

// FUNCTION: GAME 0x004b14a0
bool RHElementNet::FUN_004b14a0(void *point, void *pc, int focus) const
{
    if (*((char *)this + 0x12) && pc &&
        *(unsigned short *)(*(char **)((char *)this + 0x50) + 0xde) != 0xffff &&
        *(unsigned int *)((char *)g_pEngine + 0x4a00) <= 1 && focus == 3)
        return !*((char *)this + 0x132) && ((RHUnk0049d4f0 *)pc)->Unk(0x11) &&
               (*(RHSprite **)((char *)this + 0x50))->FUN_005b9e30(point, *(void **)((char *)this + 0x54), false);
    return false;
}

// FUNCTION: GAME 0x004b1520
bool RHElementNet::Serialize(SBFile &file)
{
    RHElementProjectile::Serialize(file);
    unsigned int count;
    void *value;
    if (file.m_bLoading)
    {
        RHUnk004b1520List &list = m_19c;
        list.FUN_0044e8b0(((RHUnk0046eb30 *)&list)->FUN_0046eb80(), list.end());
        list.m_10 = true;
        if (file.Access(&count, 2) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0,
                     // STRING: GAME 0x006aece4
                     "P:\\Robin Hood\\RHElementNet.cpp",
                     523, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned short index = 0; index < (unsigned short)count; ++index)
        {
            g_pEngine->FUN_004c3bd0(file, value);
            list.FUN_00424410(list.end(), value);
            list.m_10 = true;
        }
    }
    else
    {
        count = m_19c.m_08;
        if (file.Access(&count, 2) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHElementNet.cpp", 535,
                     "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned short index = 0; index < (unsigned short)count; ++index)
        {
            RHUnk004b1520List &list = m_19c;
            ((RHTitbitList *)&list)->At(index);
            value = list.m_0c.node->data;
            g_pEngine->FUN_004c3bd0(file, value);
        }
    }
    if (file.Access(&m_1c0, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementNet.cpp", 544,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_1c4, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementNet.cpp", 545,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_1c5, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementNet.cpp", 546,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    return true;
}

void RHElementNet::Emit(SBFile &file)
{
    FUN_004b14a0(0, 0, 0);
    Serialize(file);
}
