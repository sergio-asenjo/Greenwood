#ifndef RHARTIFICIALBONHOMIE_H
#define RHARTIFICIALBONHOMIE_H

#include "SB.h"

void RHSerializeName(SBFile &file, const char *name);
bool FUN_00416b30(void *&value, SBFile &file);

inline char *RHBonhomieBase(void *self)
{
    return (char *)self + (*(int **)((char *)self - 0x1c))[1] - 0x1c;
}

class RHArtificialBonhomie
{
public:
    bool SerializeExactlyThisAI(SBFile &file);
    void FUN_0040d910(unsigned flags);
    void FUN_0040d9e0(unsigned char frame);
    void FUN_0040dcb0(int state, int substate);
    void FUN_0040de30();
    int FUN_0040e0a0(SBFile &file);
    void Emit(SBFile &file);

    // Offsets relative to the incoming serializer this, not a complete-object layout.
    // -0x18: byte; -0x14: pointer; -0x10: byte; -0x08: word; -0x06: word.
};

struct RHMalignityPosition;
struct RHMalignityStimulus;
class RHElementActorHuman;
struct RHBonhomieActorBase;

class RHBonhomieSpeechReceiver
{
public:
    bool FUN_0040d150(const RHMalignityStimulus &stimulus);
    RHBonhomieActorBase ActorBase();
    void FUN_0040d440(RHElementActorHuman *target);
    void FUN_0040d690(const RHMalignityStimulus &stimulus);
    void FUN_0040d800(void *actor);
    bool FUN_0040e290(RHMalignityPosition position, int mode);
    void FUN_0040dbe0(bool phase);
};

#endif
