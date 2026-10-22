#ifndef RHELEMENTACTORCIVILIANCORE_H
#define RHELEMENTACTORCIVILIANCORE_H

#include "SB.h"
#include "Decomp.h"

class RHSequenceElement;
struct RHSoldierSequenceElement;
struct RHCivilianProfileView;

#include "RHElementActorNPC.h"

// SIZE 0x70c
class RHElementActorCivilian : public RHElementActorNPC
{
public:
    virtual bool Serialize(SBFile &file);
    void GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third);
    int FUN_00470390(class RHOrder *order);
    bool FUN_00470ca0();
    bool FUN_00470cc0();
    bool FUN_00470ce0();
    unsigned short FUN_00470180();
    void FUN_00470190(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
    char FUN_004701a0();
    void FUN_004701c0(int remark, unsigned flags);
    int FUN_004701f0();
    int FUN_00470460();
    bool FUN_00470310();
    void FUN_00470a10(SBFile &file);
    void FUN_00470480(SBFile &file);
    bool FUN_00470d00(void *first, void *second, int kind);
    bool FUN_00470e50(void *first, void *second, int kind);
    void *FUN_00470f70(void *element);
    void FUN_00471090();
    void FUN_00471400(int first, int second);
    void FUN_00471420(int first, int second);
    bool FUN_00471240(RHElementActorCivilian *arg);
    int FUN_004712b0(RHSoldierSequenceElement *element);
    bool FUN_00475810(RHElementActorCivilian *arg);
    bool FUN_004646e0(RHElementActorCivilian *arg);
    bool FUN_00485990();
    void Emit(SBFile &file);

private:
    undefined4 m_unk704;
    RHCivilianProfileView *m_708;
};

#endif
