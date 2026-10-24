#ifndef RHELEMENTPURSE_H
#define RHELEMENTPURSE_H

#include "SB.h"
#include "RHProjectileLifetime.h"
#include <list>

class RHElementCoin;

class __declspec(novtable) RHElementPurse : public RHProjectileLifetime
{
public:
    RHElementPurse(void *victim);
    ~RHElementPurse();
    void *FUN_004b9180(unsigned flags);
    int FUN_004b9200();
    int FUN_004b9210();
    bool FUN_004b97c0();
    unsigned short FUN_004b98a0();
    void AddChild(RHElementCoin *coin);
    void FUN_004b9990();
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);

private:
    std::list<RHElementCoin *> m_coins; // [0x15c]
    short m_unk168; // [0x168]
};

#endif
