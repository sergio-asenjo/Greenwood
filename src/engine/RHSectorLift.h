#ifndef RHSECTORLIFT_H
#define RHSECTORLIFT_H

#include "RHSectorBuilding.h"

class RHUnk0051aa00;

// VTABLE: GAME 0x00679c44
// SIZE 0x108
class RHSectorLift : public RHUnk0057d490
{
public:
    RHSectorLift();
    virtual ~RHSectorLift();
    int FUN_0057dcf0(int animation);
    int FUN_0057dd90(int animation);
    bool FUN_0057de30(RHElementActor *actor);
    bool FUN_0057dec0();
    bool FUN_0057def0();
    virtual int Unk0057e060(SBFile &file, RHUnkSectorLiftGrid *grid);
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    void Emit(SBFile &file, RHUnkSectorLiftGrid *grid);
    int m_f0;
    short m_f4;
    short m_f6;
    char m_f8;
    char m_f9;
    short m_fa;
    int m_fc;
    RHUnk0051aa00 *m_100;
    RHUnk0051aa00 *m_104;
};

#endif
