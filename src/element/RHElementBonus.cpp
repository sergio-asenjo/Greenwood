#include "RHElementBonus.h"

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
                     m_50->X(), m_50->Y());
        }
        if (!projection->Inside(m_50->m_4.m_20))
        {
            SBAssert(1, "P:\\Robin Hood\\RHElementBonus.cpp", 0x1da,
                     // STRING: GAME 0x006ae9d0
                     "DA F\xc4LLT MIR NICHTS MEHR EIN ! Bonus (%d,%d) map position not lying in projection area screen box !",
                     m_50->X(), m_50->Y());
        }
    }
    m_50->m_4.FUN_0055fa20(projection);
}

// Parked: null-branch placement and register allocation.
// Last probe 92.31%; not proven irreducible.
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
    bonus->m_50->m_4.SetPoint(SBGeoPoint2D((float)x, (float)y));
    bonus->m_50->m_4.m_da = layer;
    bonus->m_50->m_e0 = index == 0xffff ? global->m_4184 : global->m_4064[index];
    RHBonusProjection *projection = 0;
    if (projectionIndex != 0xffff)
        projection = global->m_4144[projectionIndex];
    bonus->ApplyProjection(projection);
    bonus->m_50->m_4.FUN_0055f290();
    bonus->m_50->FUN_005bd560(0, true);
    bonus->m_50->m_4.m_28 = bonus->m_50->m_4.m_c;
    bonus->m_50->RestorePoint();
    RHBonusInfoBase &base = bonus->m_50->m_4;
    base.SetFlags(a & 0xf);
    return bonus;
}
