#ifndef RHELEMENTACTORSOLDIERCORE_H
#define RHELEMENTACTORSOLDIERCORE_H

#include "RHElementActorNPC.h"

struct RHSoldierTransition;
class RHSoldierActorCalls;
struct RHSoldierSequenceElement;

class RHElementActorSoldier : public RHElementActorNPC
{
public:
    virtual bool Serialize(SBFile &file);
    unsigned short FUN_004a1cc0();
    unsigned short FUN_004a1cf0();
    unsigned short FUN_004a1d00();
    bool FUN_004a1d30();
    void *FUN_004a1d50();
    void *FUN_004a1d60();
    void FUN_004a1d70(void *neighbour);
    void FUN_004a1d80(void *neighbour);
    int FUN_004a1d90();
    int FUN_004a1da0();
    int FUN_004a1db0();
    void InitializeFromMissionStream(SBFile &file);
    void FUN_004a2550(void *element);
    void *FUN_004a5190(RHSoldierActorCalls *target);
    void FUN_004a4a40();
    bool FUN_004a4aa0(const SBGeoPoint2D &point, RHElementActorHuman *pc, int focus);
    void GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third);
    void SetAttentiveMode(bool value, bool flag);
    bool FUN_004a5670();
    bool FUN_004a5680();
    bool FUN_004a5690();
    bool FUN_004a56a0();
    bool FUN_004a5340(unsigned flags, RHSoldierTransition *element);
    bool FUN_004a53d0(unsigned flags, RHSoldierTransition *element);
    bool FUN_004a5460();
    bool FUN_004a54f0();
    void FUN_004a55b0(RHSoldierActorCalls *neighbour);
    void FUN_004a5610(RHSoldierActorCalls *neighbour);
    int FUN_004a56d0(RHSoldierSequenceElement *element);
    void FUN_004a5770(RHSoldierSequenceElement *element);
    void SetAppleSmell(bool enabled);
    void FUN_004a5a00(void *first, void *second);
    void FUN_004a5a50();
    void FUN_004a5b70(void *actor);
    unsigned short FUN_004a5b90();
    unsigned short FUN_004a5ba0();
    void SetOutlineColors();
    int FUN_004a5d30();
    void FUN_004a5d50(RHMalignityPosition position, unsigned short first, unsigned short second, void *actor);
    void Emit(SBFile &file);

private:
    char m_704[0x338];
    int m_unkA3c;
};

#endif
