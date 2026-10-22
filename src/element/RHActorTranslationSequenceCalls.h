#ifndef RH_ACTOR_TRANSLATION_SEQUENCE_CALLS_H
#define RH_ACTOR_TRANSLATION_SEQUENCE_CALLS_H

class RHOrder;

class RHActorTranslationSequenceCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c(int value, bool mode) = 0;
    void FUN_00585970(RHOrder *order);
};

#endif
