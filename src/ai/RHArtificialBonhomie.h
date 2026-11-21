#ifndef RHARTIFICIALBONHOMIE_H
#define RHARTIFICIALBONHOMIE_H

#include "SB.h"
#include "RHArtificialIntelligenceCore.h"

void RHSerializeName(SBFile &file, const char *name);
bool FUN_00416b30(void *&value, SBFile &file);

struct RHMalignityPosition;
class RHElementActorHuman;
struct RHBonhomieActorBase;

// VTABLE: GAME 0x006773e4
class RHArtificialBonhomie : public virtual RHArtificialIntelligence
{
public:
    RHArtificialBonhomie();
    virtual ~RHArtificialBonhomie();
    virtual void V00(int flags);
    virtual bool V08(SBFile &file);
    virtual int V0c(SBFile &file);
    virtual void V10(int state, int substate);
    virtual void V14();
    virtual void V18(unsigned char frame);
    virtual bool V24(RHMalignityStimulus *stimulus);
    virtual void V30(void *target, bool flag);
    virtual void V38(bool enabled);
    bool ProposeGoodAppleChaseFleeDestination(RHMalignityPosition &destination);
    bool HandleStateStimulus(const RHMalignityStimulus &stimulus);
    bool HandleReactionStimulus(RHMalignityStimulus &stimulus);
    bool FUN_0040d150(const RHMalignityStimulus &stimulus);
    RHBonhomieActorBase ActorBase();
    void FUN_0040d440(RHElementActorHuman *target);
    void FUN_0040d690(const RHMalignityStimulus &stimulus);
    void FUN_0040d800(void *actor);
    bool FUN_0040e290(RHMalignityPosition position, int mode);
    void FUN_0040dbe0(bool phase);

    bool m_active;
    void *m_target;
    bool m_acceptsOrders;
    unsigned long m_serialState;
    unsigned short m_14w;
    unsigned short m_16w;
};

inline RHArtificialIntelligence *RHBonhomieInterface(RHArtificialBonhomie *self)
{
    return reinterpret_cast<RHArtificialIntelligence *>(reinterpret_cast<char *>(self) + (*reinterpret_cast<const int *const *>(self))[1]);
}

#endif
