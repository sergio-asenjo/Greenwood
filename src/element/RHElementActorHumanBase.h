#ifndef RHELEMENTACTORHUMANBASE_H
#define RHELEMENTACTORHUMANBASE_H

#include "RHActorCommand.h"

class SBFile;
class RHSequenceElement;
class RHActorTranslationSequenceCalls;
class RHUnk00613e90;

class RHElementActor
{
public:
    virtual bool Serialize(SBFile &file);
    void Translate(RHSequenceElement *element, RHcommand command);
    void ExecuteImmediately(RHSequenceElement *element);
    void GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third);
    void FUN_0046bcb0(int value);
    void FUN_00462940(int value);
    void FUN_00468f40(void *value);
    int FUN_0046e960();
    int FUN_00463d90(unsigned value) const;
    bool FUN_00464230();
    void FUN_0046bd40(RHSequenceElement *element);
    bool FUN_0046b760(unsigned flags, void *value);
    bool FUN_0046b2b0(unsigned flags, RHActorTranslationSequenceCalls *sequence);
    bool FUN_0046b4b0(unsigned flags, RHActorTranslationSequenceCalls *sequence);
    void FUN_00478c20(RHUnk00613e90 &point, int posture);
    void FUN_00478960(RHUnk00613e90 &point);
    void FUN_00478ae0(RHUnk00613e90 &point);
};

#endif
