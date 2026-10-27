#include "SBNullstr.h"
#include "RHSprite.h"
#include "RHElementBonus.h"
#include "RHElementObject.h"
#include "RHEngineWidenedCalls.h"
#include <stdlib.h>

int FUN_004a7240(volatile int value);
int FUN_004a72e0(volatile int value);
int FUN_004a7380(volatile int value);
int FUN_004a7460(volatile int value);
void *FUN_004b3120(int type);

DECOMP_SIZE_ASSERT(RHElementBonus, 0x100)
DECOMP_SIZE_ASSERT(RHObjectConstructorCalls, 0x100)
DECOMP_SIZE_ASSERT(RHBonusInfoBase, 0xdc)
DECOMP_SIZE_ASSERT(RHBonusInfo, 0xe4)

// FUNCTION: GAME 0x004a70c0
RHElementBonus::RHElementBonus(int action, bool flag, unsigned short quantity)
    : RHObjectConstructorCalls(3, flag, action)
{
    *(unsigned *)this = 0x00678328;
    Initialize(FUN_004a7460(action), quantity);
}

// FUNCTION: GAME 0x004a7130
void *RHElementBonus::FUN_004a7130(unsigned flags)
{
    this->~RHElementBonus();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x004a7150
RHElementBonus::RHElementBonus(BonusType type, bool flag, unsigned short quantity)
    : RHObjectConstructorCalls(3, flag, FUN_004a7240(type))
{
    *(unsigned *)this = 0x00678328;
    Initialize(FUN_004a7380(type), quantity);
}

// FUNCTION: GAME 0x004a71d0
RHElementBonus::RHElementBonus(unsigned long type, bool flag, unsigned short quantity)
    : RHObjectConstructorCalls(3, flag, FUN_004a72e0(type))
{
    *(unsigned *)this = 0x00678328;
    Initialize(type, quantity);
}

// FUNCTION: GAME 0x004a7240
int FUN_004a7240(volatile int value)
{
    switch (value)
    {
    case 0: return 1;
    case 1: return 5;
    case 2: return 0xb;
    case 3: return 0xc;
    case 4: return 0xd;
    case 5: return 0x10;
    case 6: return 0x11;
    case 7: return 0x13;
    case 8: return 4;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        return 0;
    }
    return value;
}

void EmitFUN_004a7240()
{
    FUN_004a7240(0);
}

// FUNCTION: GAME 0x004a72e0
int FUN_004a72e0(volatile int value)
{
    switch (value)
    {
    case 0x11: return 1;
    case 0x18: return 5;
    case 0x10: return 0xb;
    case 0xf: return 0xc;
    case 0x13: return 0xd;
    case 0x15: return 0x10;
    case 0x14: return 0x11;
    case 0x19: return 0x13;
    case 0x16: return 4;
    case 0xe:
    case 0x12:
    case 0x17:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
        return 0;
    }
    return value;
}

void EmitFUN_004a72e0()
{
    FUN_004a72e0(0);
}

// FUNCTION: GAME 0x004a7380
int FUN_004a7380(volatile int value)
{
    switch (value)
    {
    case 3: return 0xf;
    case 10: return 0xe;
    case 2: return 0x10;
    case 0: return 0x11;
    case 11: return 0x12;
    case 4: return 0x13;
    case 5: return 0x15;
    case 6: return 0x14;
    case 8: return 0x16;
    case 9: return 0x17;
    case 1: return 0x18;
    case 7: return 0x19;
    case 12: return 0x1a;
    case 13: return 0x1b;
    case 14: return 0x1c;
    case 15: return 0x1d;
    case 16: return 0x1e;
    case 17: return 0x1f;
    case 18: return 0x20;
    }
    return value;
}

void EmitFUN_004a7380()
{
    FUN_004a7380(0);
}

// FUNCTION: GAME 0x004a7460
int FUN_004a7460(volatile int value)
{
    switch (value)
    {
    case 12: return 0xf;
    case 11: return 0x10;
    case 1: return 0x11;
    case 13:
    case 14: return 0x13;
    case 16: return 0x15;
    case 17: return 0x14;
    case 4: return 0x16;
    case 5: return 0x18;
    case 19: return 0x19;
    }
    return value;
}

void EmitFUN_004a7460()
{
    FUN_004a7460(0);
}

inline void RHElementBonus::ApplyProjection(RHBonusProjection *projection)
{
    if (projection != 0)
    {
        if (!(projection->Flags() & 1))
        {
            SBAssert(1,
                     // STRING: GAME 0x006ae9ac
                     "P:\\Robin Hood\\RHElementBonus.cpp", 0x1cf,
                     // STRING: GAME 0x006aea34
                     "DA F\xc4LLT MIR NICHTS MEHR EIN ! Bonus (%d,%d) not lying on projection area !",
                     Info()->X(), Info()->Y());
        }
        if (!projection->Inside(Info()->m_4.m_20))
        {
            SBAssert(1, "P:\\Robin Hood\\RHElementBonus.cpp", 0x1da,
                     // STRING: GAME 0x006ae9d0
                     "DA F\xc4LLT MIR NICHTS MEHR EIN ! Bonus (%d,%d) map position not lying in projection area screen box !",
                     Info()->X(), Info()->Y());
        }
    }
    Info()->m_4.FUN_0055fa20(projection);
}

// Parked: the null-projection branch and its edi initialization are scheduled later.
// STUB: GAME 0x004a74f0
RHElementBonus *RHElementBonus::CreateBonusFromMissionStream(SBFile &file)
{
    RHBonusGlobalView *global = (RHBonusGlobalView *)g_unk0x6c0a9c;
    unsigned short type;
    unsigned short quantity;
    file.Access(&type, 2);
    file.Access(&quantity, 2);
    RHElementBonus *bonus = new RHElementBonus((BonusType)type, !((RHBonusEngineView *)g_pEngine)->Flag(), quantity);
    unsigned short x;
    unsigned short y;
    int a;
    unsigned b;
    unsigned short index;
    unsigned short projectionIndex;
    unsigned short layer;
    file.Access(&x, 2);
    file.Access(&y, 2);
    file.Access(&a, 4);
    file.Access(&b, 4);
    file.Access(&projectionIndex, 2);
    file.Access(&index, 2);
    file.Access(&layer, 2);
    bonus->Info()->m_4.SetPoint(SBGeoPoint2D((float)x, (float)y));
    bonus->Info()->m_4.m_da = layer;
    bonus->Info()->m_e0 = index == 0xffff ? global->m_4184 : global->m_4064[index];
    RHBonusProjection *projection = 0;
    if (projectionIndex != 0xffff)
        projection = global->m_4144[projectionIndex];
    bonus->ApplyProjection(projection);
    bonus->Info()->m_4.FUN_0055f290();
    bonus->Info()->FUN_005bd560(0, true);
    bonus->Info()->m_4.m_28 = bonus->Info()->m_4.m_c;
    bonus->Info()->RestorePoint();
    RHBonusInfoBase &base = bonus->Info()->m_4;
    base.SetFlags(a & 0xf);
    return bonus;
}

// FUNCTION: GAME 0x004a7aa0
void RHElementBonus::Initialize(unsigned long type, unsigned short quantity)
{
    *(unsigned long *)((char *)this + 0xb0) = type;
    ((RHElementObject *)this)->Create(true, *(const RHElementObject *)FUN_004b3120(type));
    SetQuantity(quantity);
    RHSprite *sprite = (RHSprite *)Info();
    *(unsigned short *)((char *)sprite + 0x186) =
        rand() % sprite->FUN_005bdcf0(*(unsigned short *)((char *)sprite + 0x184));
}

// FUNCTION: GAME 0x004a7b30
void RHElementBonus::SetQuantity(unsigned short quantity)
{
    unsigned short amount;
    if (*(int *)((char *)this + 0xb0) == 0x17)
    {
        switch (*(volatile unsigned short *)&quantity)
        {
        case 1: amount = 100; break;
        case 2: amount = 500; break;
        case 3: amount = 1000; break;
        case 4: amount = 2500; break;
        case 5: amount = 5000; break;
        }
    }
    else
    {
        if (*(int *)((char *)this + 0xb0) == 0x12)
        {
            amount = quantity;
            int action;
            switch (quantity)
            {
            case 1: action = 0xbe; break;
            case 2: action = 0xbf; break;
            case 3: action = 0xc0; break;
            case 4: action = 0xc1; break;
            case 5: action = 0xc2; break;
            }
            ((RHUnkTargetSprite *)Info())->FUN_005b76e0(action, Info()->m_4.m_d4);
        }
        else
            amount = quantity;
    }
    ((RHElementObject *)this)->FUN_004b2d60(amount);
}

// FUNCTION: GAME 0x004b2f10
RHElementBonus::~RHElementBonus()
{
}

void EmitBonusConstructors(void *storage)
{
    ((RHElementBonus *)storage)->RHElementBonus::RHElementBonus(0, false, 1);
    ((RHElementBonus *)storage)->RHElementBonus::RHElementBonus(0UL, false, 1);
    ((RHElementBonus *)storage)->FUN_004a7130(0);
}
