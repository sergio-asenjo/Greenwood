#include "SBNullstr.h"
#include "RHEngine.h"
#include "RHScript.h"

void RHEngineContinuationCampaignCalls::FUN_00450c10(void *, SBFile &) {}
class RHEngineCameraRotationCalls
{
public:
    void FUN_005fc9a0(float angle, float scale);
};
void RHEngineCameraRotationCalls::FUN_005fc9a0(float, float) {}
class RHUnk00493a80
{
public:
    void FUN_00493a80();
};
void RHUnk00493a80::FUN_00493a80() {}
void FUN_00570850(void *) {}
RHUnk004a1bc0::RHUnk004a1bc0(bool) {}
RHUnk0057ee90::RHUnk0057ee90() {}
RHUnk0057ee40::RHUnk0057ee40() {}
void RHEngineRosterCalls::FUN_0055eda0() {}
unsigned RHEngineRosterCalls::FUN_0055e880() { return 0; }
bool RHEngineMenuStateCalls::FUN_00514970() { return false; }
bool RHEngineSequenceStateCalls::FUN_005823f0() { return false; }
bool RHEngineSequenceStateCalls::FUN_0058a670(void *) { return false; }

RHUnk005069a0::RHUnk005069a0(const RHUnk005069a0 &, int) {}
RHUnk0051d2c0::~RHUnk0051d2c0() {}
int RHHikingGuide::FUN_0051cac0(SBFile &) { return 0; }
bool RHUnk00551da0::FUN_00551da0(SBFile &) { return true; }
void RHUnk004e51e0::FUN_00454bb0() {}

struct RHbeamMe;

#include "RHEngineSerializationCalls.h"

void RHEngineSerializationCalls::FUN_0048fa30() {}
void RHEngineSerializationCalls::FUN_004d88e0(void *, int, int) {}

class RHEngineMissionCalls
{
public:
    void FUN_004c1ab0(SBFile &file, RHMission *mission, std::string &background, unsigned *version);
    void FUN_004c3680(SBFile &file);
    void FUN_004c3630(SBFile &file);
    void FUN_004c3930(SBFile &file, int protoLevel);
    void FUN_004c1ee0(SBFile &file);
    void FUN_004c20a0(SBFile &file);
    void FUN_004c2830(SBFile &file);
};

RHUnk0054eab0::RHUnk0054eab0() {}
void RHUnk0054eab0::FUN_0054eea0(SBFile &, void *) {}
void RHEngineGridCalls::FUN_004efd10(void *, unsigned short, bool) {}
short RHEngineGridCalls::FUN_004e9760(const SBGeoPoint2D &, const SBGeoPoint2D &, void *&, unsigned short &) { return 0; }
short RHEngineGridCalls::FUN_004e9920(const SBGeoPoint2D &, const SBGeoPoint2D &, void *&, unsigned short &) { return 0; }

class RHEngineReinforcementCalls
{
public:
    void *FUN_00452130(void *profile);
    void FUN_004936a0(int value);
    void FUN_00491fd0(const RHbeamMe &beamMe);
    void FUN_004d8460(void *actor, int first, int second);
    unsigned FUN_004e4460(void **value, int insert);
    bool FUN_004f6c20(const SBGeoPoint2D &origin, SBGeoPoint2D &destination,
        unsigned short layer, const SBGeoPoint2D &extent);
};

void RHEngineReinforcementCalls::FUN_004d8460(void *, int, int) {}
bool RHEngineReinforcementCalls::FUN_004f6c20(const SBGeoPoint2D &, SBGeoPoint2D &, unsigned short, const SBGeoPoint2D &) { return false; }

class RHUnk0048f280
{
public:
    RHUnk0048f280(void *description);
    char m_data[0x60c];
};


class RHUnk00588830
{
public:
    RHUnk00588830(unsigned short level, int command, void *actor, int style, int value);
    char m_data[0x9c];
};


class RHEngineBackgroundCalls
{
public:
    bool FUN_00611660(const std::string &path);
    bool FUN_004e7fa0(unsigned short width, unsigned short height);
};

class RHEngineBeamCalls
{
public:
    void FUN_004e4120(RHbeamMe *position, unsigned count, const RHbeamMe &value);
};


RHUnk0046ffe0::RHUnk0046ffe0(bool) {}
RHUnk004ab090::RHUnk004ab090() {}
RHUnk004b9b70::RHUnk004b9b70() {}
RHUnk004bac30::RHUnk004bac30() {}
RHUnk004a8130::RHUnk004a8130(bool) {}

void RHEngineMissionElementCalls::Unk00() {}
void RHEngineMissionElementCalls::Unk04() {}
void RHEngineMissionElementCalls::Unk08() {}
void RHEngineMissionElementCalls::Unk0c() {}
void RHEngineMissionElementCalls::Unk10() {}
void RHEngineMissionElementCalls::Unk14() {}
void RHEngineMissionElementCalls::Unk18() {}
void RHEngineMissionElementCalls::Unk1c() {}
void RHEngineMissionElementCalls::Unk20() {}
void RHEngineMissionElementCalls::Unk24() {}
void RHEngineMissionElementCalls::Unk28() {}
void RHEngineMissionElementCalls::Unk2c() {}
void RHEngineMissionElementCalls::Unk30() {}
void RHEngineMissionElementCalls::Unk34() {}
void RHEngineMissionElementCalls::Unk38(SBFile &) {}
void RHEngineMissionElementCalls::Unk3c(SBFile &) {}

#include "RHEngineWidenedCalls.h"

bool RHEngineWidenedCalls::FUN_004b2010(char, void *) { return false; }
void RHEngineWidenedCalls::FUN_00556260() {}
void RHEngineWidenedCalls::FUN_0055ebf0() {}
void *FUN_004b3120(int) { return 0; }
void RHEngineWidenedCalls::FUN_004eb120(SBFile &, void *) {}
void RHEngineWidenedCalls::FUN_00558670(SBFile &) {}
void RHEngineWidenedCalls::FUN_005bd450() {}
bool RHEngineWidenedCalls::FUN_005b76e0(unsigned, unsigned) { return false; }
void RHEngineWidenedCalls::FUN_0050efd0(void *) {}
void RHEngineWidenedCalls::FUN_004e3660(char) {}
void RHEngineWidenedCalls::FUN_005e5160(unsigned) {}
class RHEngineActorUpdateCalls
{
public:
    void FUN_004af2a0();
};

void RHEngineActorUpdateCalls::FUN_004af2a0() {}

class RHEngineActorActionCalls
{
public:
    void FUN_00490910(unsigned short value);
};

void RHEngineActorActionCalls::FUN_00490910(unsigned short) {}
