#include "RHEngine.h"
#include "RHScript.h"

struct RHbeamMe;

class RHEngineSerializationCalls
{
public:
    void FUN_0058a430();
    void FUN_005a5c50();
    void FUN_0048fa30();
    void FUN_004d88e0(void *element, int first, int second);
    void FUN_0050f000();
    void FUN_0050f010();
};

void RHEngineSerializationCalls::FUN_0058a430() {}
void RHEngineSerializationCalls::FUN_005a5c50() {}
void RHEngineSerializationCalls::FUN_0048fa30() {}
void RHEngineSerializationCalls::FUN_004d88e0(void *, int, int) {}
void RHEngineSerializationCalls::FUN_0050f000() {}
void RHEngineSerializationCalls::FUN_0050f010() {}
void FUN_005a5cd0() {}

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

void RHEngineMissionCalls::FUN_004c1ab0(SBFile &, RHMission *, std::string &, unsigned *) {}
void RHEngineMissionCalls::FUN_004c3680(SBFile &) {}
void RHEngineMissionCalls::FUN_004c3630(SBFile &) {}
void RHEngineMissionCalls::FUN_004c3930(SBFile &, int) {}
void RHEngineMissionCalls::FUN_004c1ee0(SBFile &) {}
void RHEngineMissionCalls::FUN_004c20a0(SBFile &) {}
void RHEngineMissionCalls::FUN_004c2830(SBFile &) {}

class RHEngineReinforcementCalls
{
public:
    void *FUN_00452130(void *profile);
    void FUN_004936a0(int value);
    void FUN_00491fd0(const RHbeamMe &beamMe);
    void FUN_004d8460(void *actor, int first, int second);
    unsigned FUN_004e4460(void **value, int insert);
    SBGeoPoint2D FUN_004a49e0();
    bool FUN_004f6c20(const SBGeoPoint2D &origin, SBGeoPoint2D &destination,
        unsigned short layer, const SBGeoPoint2D &extent);
};

void *RHEngineReinforcementCalls::FUN_00452130(void *) { return 0; }
void RHEngineReinforcementCalls::FUN_004936a0(int) {}
void RHEngineReinforcementCalls::FUN_00491fd0(const RHbeamMe &) {}
void RHEngineReinforcementCalls::FUN_004d8460(void *, int, int) {}
unsigned RHEngineReinforcementCalls::FUN_004e4460(void **, int) { return 0; }
SBGeoPoint2D RHEngineReinforcementCalls::FUN_004a49e0() { return SBGeoPoint2D(); }
bool RHEngineReinforcementCalls::FUN_004f6c20(const SBGeoPoint2D &, SBGeoPoint2D &, unsigned short, const SBGeoPoint2D &) { return false; }

class RHUnk0048f280
{
public:
    RHUnk0048f280(void *description);
    char m_data[0x60c];
};

RHUnk0048f280::RHUnk0048f280(void *) {}

class RHUnk00588830
{
public:
    RHUnk00588830(unsigned short level, int command, void *actor, int style, int value);
    char m_data[0x9c];
};

RHUnk00588830::RHUnk00588830(unsigned short, int, void *, int, int) {}
void FUN_0048c5b0(void *, int) {}

class RHEngineBackgroundCalls
{
public:
    void FUN_00611660(const std::string &path);
    void FUN_004e7fa0(int width, int height);
};

void RHEngineBackgroundCalls::FUN_00611660(const std::string &) {}
void RHEngineBackgroundCalls::FUN_004e7fa0(int, int) {}
std::string FUN_004e4b40(const std::string &, const std::string &) { return std::string(); }
std::string FUN_004e4c70(const std::string &, const char *) { return std::string(); }

class RHEngineBeamCalls
{
public:
    void FUN_004e4120(RHbeamMe *position, unsigned count, const RHbeamMe &value);
};

void RHEngineBeamCalls::FUN_004e4120(RHbeamMe *, unsigned, const RHbeamMe &)
{
}

void *FUN_004622e0(int, void *)
{
    return 0;
}

void RHEngineBuildingCalls::FUN_0057e680(void *)
{
}

void RHEngine::FUN_004c1d20(SBFile &) {}
void RHEngine::FUN_004c1df0(SBFile &) {}
void RHEngine::FUN_004c2150(SBFile &) {}
void RHEngine::FUN_004e35f0(SBFile &) {}
