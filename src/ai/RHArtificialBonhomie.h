#ifndef RHARTIFICIALBONHOMIE_H
#define RHARTIFICIALBONHOMIE_H

#include "SB.h"

void RHSerializeName(SBFile &file, const char *name);
bool FUN_00416b30(void *&value, SBFile &file);

class RHArtificialBonhomie
{
public:
    bool SerializeExactlyThisAI(SBFile &file);
    void FUN_0040d910(unsigned flags);
    void Emit(SBFile &file);

    // Offsets relative to the incoming serializer this, not a complete-object layout.
    // -0x18: byte; -0x14: pointer; -0x10: byte; -0x08: word; -0x06: word.
};

class RHBonhomieSpeechReceiver
{
public:
    void FUN_0040dbe0(bool phase);
};

#endif
