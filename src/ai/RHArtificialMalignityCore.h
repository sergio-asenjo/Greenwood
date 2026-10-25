#ifndef RHARTIFICIALMALIGNITYCORE_H
#define RHARTIFICIALMALIGNITYCORE_H

#include "RHArtificialIntelligenceCore.h"
#include "RHMalignityTargetList.h"

class SBFile;
class RHUnk005fc3b0;
struct RHMalignityPosition;
struct RHMalignityStimulus;
struct RHMalignityList;
struct RHUnk00441dd0Record;

class RHArtificialMalignity : public virtual RHArtificialIntelligence
{
public:
    RHArtificialMalignity();
    ~RHArtificialMalignity();
    virtual void V0c();
    void InitOneAI();
    bool SerializeExactlyThisAI(SBFile &file);
    void InitializeFriendCheck(unsigned short actor, unsigned short delay, unsigned short waypoint);
    void FUN_00439cb0(const RHMalignityPosition &position, unsigned short radius);
    void FUN_00439e70(void *actor, const RHMalignityPosition &position);
    void FUN_00439f60(const RHMalignityStimulus &stimulus);
    void FUN_0043a080(const RHMalignityPosition &position);
    void FUN_0043a170(const RHMalignityPosition &position);
    void FUN_00438620(unsigned short value);
    unsigned short FUN_00433010();
    void FUN_00433790(const RHMalignityPosition &position);
    bool FUN_00435bd0();
    int FUN_00436400(SBFile &file);
    void FUN_0043b1b0(RHMalignityPosition position, int mode);
    void FUN_0043c960(RHMalignityPosition position, int mode);
    short FUN_00440cf0(RHUnk00441dd0Record *record);
    int FUN_00441020(RHUnk00441dd0Record *record, RHMalignityList *list);
    void FUN_00441f20();
    bool FUN_004436e0(const struct RHUnk00443850Record *source, bool mode);
    bool FUN_00443850(const struct RHUnk00443850Record *source);
    void FUN_004439a0(struct RHUnk004439a0Record *record, unsigned char flags);
    void FUN_00443af0(unsigned value);
    void *FUN_00443c40(void *value);
    void *FUN_00443d10(const RHMalignityPosition *position);
    void *FUN_00443e20(int team, unsigned short radius, unsigned char flags, int type);
    unsigned FUN_00443fa0(unsigned first, unsigned second, unsigned third, unsigned fourth);
    void FUN_004444a0();
    void FUN_00444bb0(void *record);
    void FUN_004450a0(void *target);
    void FUN_00445180(void *value);
    bool FUN_00445510(RHMalignityPosition position, void *actor);
    void FUN_004457c0(const RHMalignityPosition &position);
    bool FUN_00438cb0(int command, bool mode);
    void FUN_004459b0();
    void FUN_00445b40();
    void *FUN_00445d40();
    bool FUN_004460f0();
    void FUN_004461a0(void *target, void *actor);
    void FUN_00446700();
    bool FUN_004468a0();
    void FUN_004469e0();
    void FUN_00446d20();
    void FUN_00446eb0(void *actor);
    void FUN_00447030(void *guard);
    void FUN_00447420(void *target);
    void FUN_00447490(void *target);
    void *FUN_004474e0();
    bool FUN_00447640(RHMalignityPosition &target);
    void FUN_00447da0(RHMalignityPosition &position, unsigned short &heading);
    unsigned short FUN_00449170();
    bool FUN_00449810(const RHMalignityPosition &position, unsigned short heading);
    bool FUN_00449ac0();
    unsigned short FUN_00449d40(void *group);
    bool FUN_0044a090();
    void FUN_0044a760(void *actor);
    void FUN_0044a830(void *actor);
    void FUN_0044b000();
    bool FUN_0044b120(const RHMalignityPosition &position);
    void *FUN_0044b7b0();
    void FUN_0044b800();
    void FUN_0044b810(void *point);
    void FUN_0044b840(void *point);
    bool FUN_0044b870(void *area, unsigned short id);
    void FUN_0044ca90();
    bool FUN_0044cf00();
    void FUN_00430020();
    void FUN_004303e0();
    void FUN_0044d0b0();
    void FUN_00430300(int mode);
    void *FUN_0043d780(unsigned short flags);
    bool FUN_0043f340(void *actor);
    bool FUN_0043f540(void *actor);
    void FUN_0043fa80(void *target, void *actor);
    void FUN_0043fc60(void *target, void *actor);
    void FUN_00440040(void *target, RHMalignityPosition position, RHUnk005fc3b0 *direction, int mode, void *actor);
    RHUnk00441dd0Record *FUN_00441dd0();
    bool FUN_0044afa0(void *actor);
    void Emit(SBFile &file);
    char m_04[0x2e0];
    RHMalignityTargetList m_targets;
    char m_308[0x4c];
    RHArtificialIntelligence &VirtualBase()
    {
        return *(RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]);
    }
    RHArtificialIntelligence &Base()
    {
        return *(RHArtificialIntelligence *)((char *)this + (*(int **)((char *)this - 0x358))[1] - 0x358);
    }
};

#endif
