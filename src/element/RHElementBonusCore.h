#ifndef RHELEMENTBONUSCORE_H
#define RHELEMENTBONUSCORE_H

#include "RHElementObject.h"

class SBFile;
class RHBonusInfo;
struct RHBonusProjection;

class __declspec(novtable) RHElementBonus : public RHElementObject
{
public:
    enum BonusType { BONUS_UNKNOWN = 0 };
    RHElementBonus(int action, bool flag, unsigned short quantity);
    RHElementBonus(BonusType type, bool flag, unsigned short quantity);
    RHElementBonus(unsigned long type, bool flag, unsigned short quantity);
    ~RHElementBonus();
    virtual char v10();
    virtual unsigned V68();
    virtual void SetQuantity(unsigned short quantity);
    void *FUN_004a7130(unsigned flags);
    void Initialize(unsigned long type, unsigned short quantity);
    void ApplyProjection(RHBonusProjection *projection);
    RHBonusInfo *&Info() { return *(RHBonusInfo **)((char *)this + 0x50); }
    static RHElementBonus *CreateBonusFromMissionStream(SBFile &file);
};

#endif
